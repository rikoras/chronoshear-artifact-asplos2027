#!/usr/bin/env python3
"""Plot online measurements using the paper's figure functions and theme."""
from pathlib import Path
import argparse,csv,os,sys
ROOT=Path(__file__).resolve().parents[1]
sys.path[:0]=[str(ROOT/'deps/python'),str(Path(__file__).resolve().parent/'plotting')]
sys.dont_write_bytecode=True
os.environ.setdefault('MPLCONFIGDIR',str(Path.home()/'.cache/chronoshear-matplotlib'))
import chronoshear_paper_figures as paper
import chronoshear_paper_threads as threads
import chronoshear_plot_theme as theme
import matplotlib.pyplot as plt
from matplotlib import ticker

NAMES={'aes':'AES','matmul':'MatMul','sodor':'Sodor','rocket':'Rocket Chip',
       'boom-small':'Small BOOM','boom-medium':'Medium BOOM','boom-large':'Large BOOM'}
METHODS={'verilator-1t':'verilator_1t','verilator-4t':'verilator_4t',
         'essent-1t':'essent','repcut-4t':'repcut_4t','chronoshear':'chisa_best'}

def load(path):
    with path.open() as f:return list(csv.DictReader(f))

def save(fig,out,name='throughput'):
    theme.save_figure_multiformat(fig,out/(name+'.pdf'),('pdf','svg','png'),tight=False)
    plt.close(fig);print(out/(name+'.pdf'))

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('directory',type=Path);a=p.parse_args()
    rows=[r for r in load(a.directory/'summary.csv') if r['status']=='pass']
    if not rows:raise SystemExit('No passing samples to plot')
    kinds={r['experiment'] for r in rows};theme.configure_rc_params(plt,font_size=9)
    if 'threads' in kinds:
        data={'rows':[]}
        for r in rows:
            if r['experiment']=='threads':sim='chisa';n=int(r['rtl_cores'])
            elif r['simulator']=='verilator-1t':sim='verilator';n=1
            else:continue
            data['rows'].append({'simulator':sim,'threads':n,'status':'pass','kcycles_per_second':float(r['throughput_khz'])})
        threads.thread_figure(data,a.directory);print(a.directory/'throughput.pdf')
    elif 'width' in kinds:
        selected=[r for r in rows if r['simulator']=='chronoshear'];duts=[NAMES[d] for d in NAMES if any(r['dut']==d for r in selected)]
        widths=sorted({int(r['width']) for r in selected})
        series=[{NAMES[r['dut']]:float(r['throughput_khz']) for r in selected if int(r['width'])==w} for w in widths]
        fig,ax=plt.subplots(figsize=(theme.PAPER_WIDTH if len(duts)>3 else theme.COLUMN_WIDTH,2.5));fig.subplots_adjust(left=.085 if len(duts)>3 else .18,right=.985,bottom=.22,top=.79)
        handles=paper.grouped(ax,series,[theme.VECTOR_WIDTH_COLORS[w] for w in widths],[f'$W={w}$' for w in widths],duts)
        ax.set_xticks(range(len(duts)),duts,rotation=0,ha='center');ax.set(yscale='log',ylabel='Throughput (kHz)')
        ax.legend(handles,[f'$W={w}$' for w in widths],loc='lower center',bbox_to_anchor=(.5,1.07),ncol=4,columnspacing=.8,handlelength=1,handletextpad=.35)
        save(fig,a.directory)
    else:
        duts=[NAMES[d] for d in NAMES if any(r['dut']==d for r in rows)]
        data={key:{} for key in METHODS.values()}
        for r in rows:data[METHODS[r['simulator']]][NAMES[r['dut']]]=float(r['ns_per_cycle'])
        fig,ax=plt.subplots(figsize=(theme.PAPER_WIDTH,2.05));fig.subplots_adjust(left=.085,right=.987,bottom=.27,top=.98)
        handles=paper.absolute_panel(ax,data,duts);ax.set_ylabel('Throughput (kHz)')
        labels=[label for label,_ in paper.SERIES];labels[-1]='ChronoShear online'
        fig.legend(handles,labels,loc='lower center',bbox_to_anchor=(.535,.005),ncol=5,columnspacing=1.0,handlelength=1.2,handletextpad=.5)
        save(fig,a.directory)

if __name__=='__main__':main()

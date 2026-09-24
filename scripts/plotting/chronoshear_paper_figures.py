#!/usr/bin/env python3
r"""Render paper experiment figures with the shared Times/blue-gray/crimson theme.

PDF/SVG/PNG are generated together. Small .tex include wrappers preserve the
existing manuscript's \input interface. API render(data, output, source) remains
compatible with the experiment analyzer. Principle diagrams are not touched.
"""
import argparse,json,math,sys
from pathlib import Path
HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[2]
import chronoshear_plot_theme as theme
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib import ticker,patheffects
import numpy as np
COLORS=theme.PALETTE
WIDTH_COLORS=theme.WIDTH_PALETTE
CRIMSON=theme.CRIMSON;BLUE=theme.BLUE
SERIES=[('Verilator','verilator_1t'),('Verilator, 4 threads','verilator_4t'),('ESSENT','essent'),('RepCut, 4 threads','repcut_4t'),('ChronoShear','chisa_best')]

def positive(value):return isinstance(value,(int,float)) and math.isfinite(value) and value>0

def display_name(name):
    return {'Rocket Chip':'RocketChip','Small BOOM':'SmallBOOM','Large BOOM':'LargeBOOM','Medium BOOM':'MediumBOOM'}.get(name,name)

def style(ax):theme.style_axes(ax)

def grouped(ax,rows,colors,labels,duts):
    step=theme.GROUP_SPAN/len(rows);x=np.arange(len(duts));handles=[]
    for i,(row,color,label) in enumerate(zip(rows,colors,labels)):
        loc=[j for j,d in enumerate(duts) if positive(row.get(d))]
        handles.append(ax.bar(x[loc]+(i-(len(rows)-1)/2)*step,[row[duts[j]] for j in loc],width=step*theme.BAR_FILL,color=color,label=label,zorder=3))
    ax.set_xticks(x,[display_name(d) for d in duts],rotation=25,ha='right')
    ax.set_xlim(-.53,len(duts)-.47);style(ax)
    return handles

def save(output, name, body, source, old_dir):
    target = output / name
    previous = target if target.exists() else old_dir / name
    old = previous.read_text() if previous.exists() else ''
    active = '\n'.join(line for line in old.splitlines() if not line.lstrip().startswith('%')).strip()
    # Retain the previous active plot, not the accumulated historical comments.
    history = ''
    if active and active != body.strip():
        history = '% PREVIOUS ACTIVE PLOT (before data refresh):\n' + '\n'.join('% | ' + line if line.strip() else '% |' for line in active.splitlines()) + '\n% END PREVIOUS ACTIVE PLOT\n'
    if not history and '% PREVIOUS ACTIVE PLOT' in old:
        start=old.index('% PREVIOUS ACTIVE PLOT')
        end=old.index('% END PREVIOUS ACTIVE PLOT',start)+len('% END PREVIOUS ACTIVE PLOT')
        history=old[start:end]+'\n'
    target.write_text(f'% Generated from {source}\n% Missing measurements are omitted; see the experiment report.\n' + history + body)


def main_panels(axes,D,duts):
    DUTS=duts
    series=[D.get(key,{}) for _,key in SERIES]
    throughput=[{d:1e6/v for d,v in row.items() if v and v>0} for row in series]
    speedup=[{d:D['verilator_1t'][d]/v for d,v in row.items() if v and v>0 and d in D['verilator_1t']} for row in series]
    handles=grouped(axes[0],throughput,COLORS,[x[0] for x in SERIES],DUTS)
    speedup_handles=grouped(axes[1],speedup,COLORS,[x[0] for x in SERIES],DUTS)
    axes[0].set_yscale('log')
    values=[v for r in throughput for v in r.values()] or [1]
    low,high=math.floor(math.log10(min(values))),math.ceil(math.log10(max(values)))
    high=max(high,low+1)
    axes[0].set_ylim(10**low,10**high)
    axes[0].set_yticks([10**n for n in range(low,high+1)]);axes[0].minorticks_off()
    axes[0].set_ylabel('Throughput (kcycles/s)')
    axes[1].set_yscale('log')
    vals=[v for row in speedup for v in row.values()] or [1]
    lo,hi=min(vals)/1.5,max(vals)*3.1
    axes[1].set_ylim(lo,hi)
    axes[1].set_yticks([m*10**n for n in range(math.floor(math.log10(lo)),math.ceil(math.log10(hi))+1) for m in (1,3) if lo<=m*10**n<=hi]);axes[1].yaxis.set_major_formatter(ticker.FuncFormatter(lambda x,p:f'{x:g}'))
    axes[1].minorticks_off();axes[1].set_ylabel('Speedup over Verilator')
    axes[1].axhline(1,color='#939BA6',lw=.7,ls=(0,(3,3)),zorder=2)
    for bar in speedup_handles[-1]:
        value=bar.get_height()
        axes[1].annotate(f'{value:.2f}×',
                         (bar.get_x()+bar.get_width()/2,value),
                         xytext=(0,3),textcoords='offset points',
                         ha='center',va='bottom',fontsize=8.5,color=CRIMSON)
    return handles

def selected_widths(data):
    return sorted({int(w) for row in data.get('chisa_sweep',{}).values() for w in row} or set(data.get('expected_widths',[4,8,16,32])))

def absolute_panel(ax, data, duts):
    rows=[{d:1e6/v for d,v in data.get(key,{}).items() if positive(v)} for _,key in SERIES]
    handles=grouped(ax,rows,COLORS,[s[0] for s in SERIES],duts)
    values=[v for row in rows for v in row.values()]
    low=math.floor(math.log10(min(values)));high=math.ceil(math.log10(max(values)))
    ax.set_yscale('log');ax.set_ylim(10**low,2*10**high)
    ax.set_yticks([10**p for p in range(low,high+1)]);ax.minorticks_off()
    ax.set_ylabel('Throughput (kcycles/s)')
    ax.set_xticks(np.arange(len(duts)),[display_name(d) for d in duts],rotation=0,ha='center')
    selected=[d for d in duts if positive(data.get('chisa_best',{}).get(d))]
    for bar,d in zip(handles[-1],selected):
        base=data.get('verilator_1t',{}).get(d)
        if positive(base):
            ratio=base/data['chisa_best'][d]
            ax.annotate(f'{ratio:.2f}×',(bar.get_x()+bar.get_width()/2,bar.get_height()),
                        xytext=(0,3),textcoords='offset points',ha='center',va='bottom',fontsize=8.5,color=CRIMSON)
    return handles

def width_panel(ax,D,duts):
    DUTS=duts
    widths=selected_widths(D);rows=[]
    for w in widths:
        row={}
        for d in DUTS:
            ns=D.get('chisa_sweep',{}).get(d,{}).get(str(w))
            base=(D['sweep_verilator_1t'].get(d,{}).get(str(w)) if 'sweep_verilator_1t' in D else D.get('verilator_1t',{}).get(d))
            if ns and base:row[d]=base/ns
        rows.append(row)
    colors=[theme.VECTOR_WIDTH_COLORS.get(w,theme.GRAPHITE) for w in widths]
    handles=grouped(ax,rows,colors,[f'$W={w}$' for w in widths],DUTS)
    ax.set_ylabel('Speedup over Verilator');ax.set_ylim(0,max((v for row in rows for v in row.values()),default=1)*1.13)
    ax.yaxis.set_major_locator(ticker.MaxNLocator(5,integer=True))
    return handles

def oracle_panel(ax,D):
    points=D.get('oracle_curve',{}).get('points',D.get('oracle_curve_small_w32',[]))
    points=[p for p in points if positive(p.get('ns'))]
    if not points:
        style(ax);ax.text(.5,.5,'Measurements pending',ha='center',transform=ax.transAxes)
        return []
    points=sorted(points,key=lambda p:p['oracles']);full=next((p for p in points if p.get('is_full')),points[-1]);empty=next((p for p in points if p['oracles']==0),None)
    x=[p['oracles'] for p in points]
    values=[1e6/p['ns'] for p in points]
    a=ax.plot(x,values,color=CRIMSON,lw=1.35,marker='D',ms=4.3,
              markeredgewidth=.55,markeredgecolor='white',label='Throughput',zorder=5)[0]
    handles=[a]
    if empty and positive(empty.get('serial_templates')):
        right=ax.twinx()
        measured=[p for p in points if isinstance(p.get('serial_templates'),(int,float))]
        remaining=[p['serial_templates']/1000 for p in measured]
        b=right.plot([p['oracles'] for p in measured],remaining,color=BLUE,lw=1.1,
              ls=(0,(4,2.4)),marker='s',ms=3.8,markerfacecolor='white',markeredgewidth=.85,
              label='Cyclic statements',zorder=4)[0]
        right.set_ylim(0,max(remaining)*1.08)
        right.set_ylabel('Cyclic statements (thousands)',color=BLUE)
        right.yaxis.set_major_locator(ticker.MaxNLocator(5))
        right.tick_params(axis='y',colors=BLUE,labelsize=8.5)
        right.spines['top'].set_visible(False)
        right.spines['right'].set_color(theme.SPINE_COLOR)
        right.spines['right'].set_linewidth(.55)
        handles.append(b)
    a.set_path_effects([patheffects.Stroke(linewidth=2.05,foreground='white'),patheffects.Normal()])
    style(ax);ax.set_xticks(x,[f'{n:,}' for n in x]);ax.set_xlim(-75,max(x)+85)
    ax.set_ylim(0,max(values)*1.08);ax.yaxis.set_major_locator(ticker.MaxNLocator(5))
    ax.set_xlabel('Number of oracles',labelpad=5)
    ax.set_ylabel('Throughput (kcycles/s)',color=CRIMSON)
    return handles



def render(data,output,source,old_dir=HERE):
    output=Path(output);output.mkdir(parents=True,exist_ok=True)
    theme.configure_rc_params(plt,font_size=9)
    duts=data['duts']
    active=[d for d in duts if any(positive(data.get(k,{}).get(d)) for _,k in SERIES)]
    if not active:raise ValueError('No positive measurements for the main comparison')
    # One panel reports both metrics: absolute bar heights and CHISA speedup labels.
    fig,ax=plt.subplots(figsize=(theme.PAPER_WIDTH,2.05))
    fig.subplots_adjust(left=.085,right=.987,bottom=.27,top=.98)
    handles=absolute_panel(ax,data,duts)
    fig.legend(handles,[s[0] for s in SERIES],loc='lower center',bbox_to_anchor=(.535,.005),ncol=5,columnspacing=1.25,handlelength=1.2,handletextpad=.5)
    export(fig,output,'fig_speedup',source,old_dir);plt.close(fig)
    theme.configure_rc_params(plt,font_size=8.5)
    for name in ('fig_width','fig_budget'):
        fig,ax=plt.subplots(figsize=(theme.COLUMN_WIDTH,2.20 if name=='fig_width' else 2.35))
        fig.subplots_adjust(left=.17,right=.987 if name=='fig_width' else .79,bottom=.30 if name=='fig_width' else .24,top=.805)
        if name=='fig_width':
            handles=width_panel(ax,data,duts);labels=[f'$W={w}$' for w in selected_widths(data)]
        else:
            handles=oracle_panel(ax,data);labels=['Throughput','Cyclic statements']
        if handles:ax.legend(handles,labels,loc='lower center',bbox_to_anchor=(.5,1.07),ncol=min(4,len(labels)),columnspacing=.95,handlelength=1.2 if name=='fig_width' else 1.7,handletextpad=.45)
        export(fig,output,name,source,old_dir);plt.close(fig)
    return {'figures':['fig_speedup.tex','fig_width.tex','fig_budget.tex'],'duts':duts,'widths':selected_widths(data),
            'formats':['pdf','svg','png','tex'],'oracle_configurations':len(data.get('oracle_curve',{}).get('points',data.get('oracle_curve_small_w32',[])))}

def export(fig,output,name,source,old_dir):
    theme.save_figure_multiformat(fig,output/(name+'.pdf'),('pdf','svg','png'),tight=(name=='fig_budget'))
    body=r'\includegraphics[width=\linewidth]{figs/'+name+'.pdf}'+'\n'
    save(output,name+'.tex',body,source,old_dir)

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--data',type=Path,default=ROOT/'paper/results/paper_numbers.json')
    p.add_argument('--output-dir',type=Path,default=HERE)
    a=p.parse_args();print(json.dumps(render(json.loads(a.data.read_text()),a.output_dir,str(a.data)),indent=2))
if __name__=='__main__':main()

#!/usr/bin/env python3
"""Paper figure functions with the shared serif, blue-gray and crimson theme."""
import math
import chronoshear_plot_theme as theme
import matplotlib
matplotlib.use('Agg')
import numpy as np
COLORS=theme.PALETTE
CRIMSON=theme.CRIMSON
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

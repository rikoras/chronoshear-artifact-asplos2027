from pathlib import Path

def thread_figure(data, output):
    """Compare all three simulators at 1, 2, 4, and 6 RTL threads."""
    import matplotlib
    matplotlib.use('Agg')
    import matplotlib.pyplot as plt
    from matplotlib import ticker
    import chronoshear_plot_theme as theme
    rows={(r['simulator'],r['threads']):r for r in data['rows'] if r['status']=='pass'}
    expected={(sim,n) for sim in ['chisa','verilator','repcut'] for n in [1,2,4,6]}
    missing=expected-set(rows)
    if missing:raise ValueError('Incomplete thread sweep: '+str(sorted(missing)))
    base=rows['verilator',1]['kcycles_per_second']
    theme.configure_rc_params(plt,font_size=9)
    fig,ax=plt.subplots(figsize=(theme.COLUMN_WIDTH,2.65))
    fig.subplots_adjust(left=.17,right=.79,bottom=.27,top=.81)
    for sim,label,color,marker in [('verilator','Verilator',theme.GRAPHITE,'o'),
                                   ('repcut','RepCut',theme.ROSE,'s'),
                                   ('chisa','ChronoShear',theme.CRIMSON,'D')]:
        xs=sorted(n for method,n in rows if method==sim);ys=[rows[sim,n]['kcycles_per_second'] for n in xs]
        ax.plot(xs,ys,label=label,color=color,marker=marker,lw=1.25,ms=4,
                markeredgewidth=.5,markeredgecolor='white')
    theme.style_axes(ax)
    ax.set(xlabel='RTL evaluation threads\nChronoShear: 3/6/8/10 total cores',ylabel='Throughput (kHz)',
           xticks=[1,2,4,6],xlim=(.7,6.3),ylim=(0,None))
    ax.yaxis.set_major_locator(ticker.MaxNLocator(5))
    secondary=ax.secondary_yaxis('right',functions=(lambda y:y/base,lambda y:y*base))
    secondary.set_ylabel('Speedup over Verilator 1T')
    secondary.yaxis.set_major_locator(ticker.MaxNLocator(5))
    ax.legend(loc='lower center',bbox_to_anchor=(.5,1.06),ncol=3,columnspacing=.65,handlelength=1.15,handletextpad=.35)
    output=Path(output);output.mkdir(parents=True,exist_ok=True)
    theme.save_figure_multiformat(fig,output/'throughput.pdf',('pdf','svg','png'),tight=False)
    plt.close(fig)

"""Shared paper/experiment plotting theme: graphite, blue-gray and crimson.

Geometry and typography are configured here so every plotting entry point uses
one style. Effects remain vector paths; no value, axis scale or uncertainty is
changed. Legacy helper names remain available to the experiment scripts.
"""
from __future__ import annotations
import os
from pathlib import Path
from typing import Sequence


FIGURE_FACECOLOR=AXES_FACECOLOR='#FFFFFF'
TEXT_COLOR=LABEL_COLOR='#252B35'
GRID_COLOR='#E4E9EF';SPINE_COLOR='#68717E';TICK_COLOR='#414957'
GRAPHITE='#303848';SLATE='#899DB1';BLUE='#497D9E';ROSE='#C2AEB9';CRIMSON='#A5354B'
PALETTE=(GRAPHITE,SLATE,BLUE,ROSE,CRIMSON)
WIDTH_PALETTE=('#D3DEE7','#A0B4C6','#567D9D','#293C57')
GROUP_SPAN=.91
BAR_FILL=.96
PAPER_WIDTH=7.15
COLUMN_WIDTH=3.45
ZEBRA_BAND_COLOR=(1.,1.,1.,0.)
ORACLE_SERIES_COLORS={'vanilla':GRAPHITE,'expand_only':BLUE,'oracle_injected':CRIMSON}
SPEEDUP_SERIES_COLORS={'verilator':GRAPHITE,'verilator_mt2':SLATE,'verilator_mt4':SLATE,
                      'repcut_mt4':ROSE,'essent_o3_scalar':BLUE,'chisa_best':CRIMSON}
VECTOR_WIDTH_COLORS=dict(zip((4,8,16,32),WIDTH_PALETTE))
ISA_BAR_COLORS=dict(zip(('scalar','sse4','avx','avx2','avx512'),PALETTE))
ANNOTATION_BRACKET_COLOR=CRIMSON
COMPILER_BAR_COLORS=(BLUE,GRAPHITE,CRIMSON)


def configure_rc_params(plt,serif_fonts:Sequence[str]|None=None,*,font_size=9):
    """Keep the legacy argument, but enforce the paper's actual Times font."""
    from matplotlib import font_manager
    for font in (Path(__file__).resolve().parents[2]/'deps/fonts').glob('*.ttf'):
        font_manager.fontManager.addfont(str(font))
    font_manager.findfont(font_manager.FontProperties(family='Times New Roman'),fallback_to_default=False)
    plt.rcParams.update({
        'font.family':'Times New Roman','font.size':font_size,
        'mathtext.fontset':'custom','mathtext.rm':'Times New Roman',
        'mathtext.it':'Times New Roman:italic','mathtext.bf':'Times New Roman:bold',
        'mathtext.cal':'Times New Roman',
        'axes.labelsize':font_size+.5,'axes.titlesize':font_size+.5,'axes.titleweight':'normal',
        'axes.titlecolor':LABEL_COLOR,'axes.labelcolor':LABEL_COLOR,'text.color':TEXT_COLOR,
        'xtick.labelsize':font_size-.5,'ytick.labelsize':font_size-.5,
        'axes.edgecolor':SPINE_COLOR,'axes.linewidth':.55,
        'xtick.color':TICK_COLOR,'ytick.color':TICK_COLOR,
        'xtick.major.width':.5,'ytick.major.width':.5,
        'xtick.major.size':2.3,'ytick.major.size':2.3,
        'legend.fontsize':font_size-.5,'legend.frameon':False,
        'pdf.fonttype':42,'ps.fonttype':42,'svg.fonttype':'path',
        'figure.facecolor':FIGURE_FACECOLOR,'axes.facecolor':AXES_FACECOLOR,
        'savefig.facecolor':FIGURE_FACECOLOR,'savefig.edgecolor':'none','savefig.dpi':240,
        'grid.color':GRID_COLOR,'grid.linewidth':.45,'grid.linestyle':'-',
        'grid.alpha':1.,'axes.grid':False,'axes.axisbelow':True,
        'axes.prop_cycle':plt.cycler(color=PALETTE),
    })


def mix(color,other,amount):
    from matplotlib.colors import to_rgb
    return tuple((1-amount)*a+amount*b for a,b in zip(to_rgb(color),to_rgb(other)))


def add_corner_frame(ax):
    if getattr(ax,'_chisa_frame',None) is not None:return
    from matplotlib.artist import Artist
    from matplotlib.lines import Line2D
    class CornerFrame(Artist):
        def draw(self,renderer):
            box=ax.get_window_extent(renderer)
            if not box.width or not box.height:return
            cut=renderer.points_to_pixels(4.5)
            dx,dy=cut/box.width,cut/box.height
            for xs,ys,color,lw in [([0,1-dx,1,1],[1,1,1-dy,0],'#C5CFD9',.48),
                                   ([1-dx,1],[1,1-dy],'#8B9DAF',.72)]:
                line=Line2D(xs,ys,color=color,lw=lw,transform=ax.transAxes,clip_on=False)
                line.set_figure(ax.figure);line.draw(renderer)
    artist=CornerFrame();artist.set_zorder(6);ax.add_artist(artist);ax._chisa_frame=artist


def style_y_grid(ax):
    ax.grid(True,axis='y',color=GRID_COLOR,lw=.45,linestyle='-',alpha=1)
    ax.set_axisbelow(True)


def style_xy_grid(ax):
    ax.grid(True,axis='both',color=GRID_COLOR,lw=.4,linestyle='-',alpha=.8)
    ax.set_axisbelow(True)


def style_log2_y_minor_grid(ax):
    import matplotlib.ticker as ticker
    ax.yaxis.set_minor_locator(ticker.LogLocator(base=2,subs=(1.25,1.5,1.75)))
    ax.grid(True,which='minor',axis='y',color=GRID_COLOR,lw=.3,alpha=.45)


def polish_spines(ax,hide_top=True,hide_right=True,*,frame=True):
    ax.spines['top'].set_visible(not hide_top);ax.spines['right'].set_visible(not hide_right)
    for side in ('bottom','left'):
        ax.spines[side].set_color(SPINE_COLOR);ax.spines[side].set_linewidth(.55)
    if frame and hide_top and hide_right:add_corner_frame(ax)


def style_axes(ax):
    style_y_grid(ax);polish_spines(ax)
    ax.tick_params(axis='x',length=0,pad=5);ax.tick_params(axis='y',pad=3)
    ax.minorticks_off()


def finish_figure(fig):
    """Apply inset bar rims once, after data/layout setup and before exporting."""
    from matplotlib.container import BarContainer
    from matplotlib.transforms import ScaledTranslation
    import math
    for ax in fig.axes:
        for container in ax.containers:
            if not isinstance(container,BarContainer) or getattr(container,'_chisa_rims',False):continue
            for bar in container.patches:
                value=bar.get_y()+bar.get_height()
                if not math.isfinite(value) or bar.get_height()<=0:continue
                color=bar.get_facecolor();bar.set_edgecolor(mix(color,'#253246',.28));bar.set_linewidth(.38)
                x,w=bar.get_x(),bar.get_width()
                transform=ax.transData+ScaledTranslation(0,-.45/72,fig.dpi_scale_trans)
                line=ax.plot([x+.08*w,x+.92*w],[value,value],transform=transform,
                             color=mix(color,'white',.58),lw=.30,zorder=bar.get_zorder()+.1,
                             solid_capstyle='butt',scalex=False,scaley=False)[0]
                line.set_clip_path(bar)
            container._chisa_rims=True
        top=ax.get_ylim()[1]
        for value,line in zip(ax.get_yticks(),ax.get_ygridlines()):
            if math.isclose(value,top,rel_tol=1e-9,abs_tol=1e-12):line.set_visible(False)


def panel_title(ax,text):
    letter,title=text.split(' ',1)
    ax.text(0,1.065,letter,transform=ax.transAxes,va='bottom',fontsize=9,fontweight='bold',color=GRAPHITE)
    ax.text(.095,1.065,title,transform=ax.transAxes,va='bottom',fontsize=9,color=GRAPHITE)


def legend_kw():return {'frameon':False}
def bar_edge_kw():return {'edgecolor':SPINE_COLOR,'linewidth':.38}
def marker_outline_kw():return {'markeredgecolor':'white','markeredgewidth':.6}


def save_figure_multiformat(fig,out_path:Path,extensions=('pdf','png'),*,tight=True):
    out_path=Path(out_path);out_path.parent.mkdir(parents=True,exist_ok=True)
    finish_figure(fig)
    for ext in extensions:
        fig.savefig(out_path.with_suffix('.'+ext),bbox_inches='tight' if tight else None,
                    pad_inches=.08,facecolor=FIGURE_FACECOLOR,edgecolor='none')

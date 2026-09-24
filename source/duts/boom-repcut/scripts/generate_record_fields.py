#!/usr/bin/env python3
"""Emit bit addresses for mutation-site writes. Never reads model source/state."""
from pathlib import Path
import argparse
import collections
import json
import re


def write_changed(path, text):
    if not path.exists() or path.read_text() != text:
        path.write_text(text)

ROOT=Path(__file__).resolve().parents[3]
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--output',type=Path,required=True)
parser.add_argument('--banks',type=Path,required=True)
args=parser.parse_args()
OUT=args.output
geometry=json.loads((OUT/'contract-layout.json').read_text())['geometry']
W=geometry['width']; BR=geometry['branches']; LDQ=geometry['ldq']; STQ=geometry['stq']
entries=json.loads((OUT/'contract-layout.json').read_text())['oracles']
banks={b['name']:b for b in json.loads(args.banks.read_text())['banks']}
atoms=collections.defaultdict(list)
for o in entries:
    fields=banks[o['flat']]['fields'] if o['flat'] in banks else [dict(source=o['flat'],width=o['width'],low=0,sourceLow=o.get('word',0)*64)]
    for f in fields:
        atoms[f['source'].split('boom_tile.')[-1]].append((o['recordOffset'],o['elemBytes'],f['width'],f['low'],f.get('sourceLow',f.get('source_low',0))))
# A union of contracts can list the same record word more than once for a
# field; identical fragments are one write.
for name in list(atoms):
    atoms[name]=list(dict.fromkeys(atoms[name]))
# How many distinct fields touch each record word (offset, bytes).
word_users=collections.Counter()
for name,parts in atoms.items():
    for (off,b,w,low,sl) in parts: word_users[(off,b)]+=1
def field(name):
    parts=atoms.get(name,[])
    if len(parts)>8:raise ValueError('layout fanout exceeds eight: '+name)
    return '{'+str(len(parts))+', {'+', '.join('{'+','.join(map(str,p))+'}' for p in parts)+'}}'

lines=['// Generated bit positions only; no storage, sampling or source expressions.','#pragma once','#include "record_bits.h"','namespace chisa::boom_model::wide::fields {']
used={}
def emit(name,shape,source):
    # Collect every member first: a family whose present members all sit in
    # words of one size and width, one fragment each, is emitted as a
    # RecordSlot<Bytes,Width> table (offset and bit position per member);
    # anything else keeps the generic RecordField descriptor.
    members={}
    def walk(prefix):
        if len(prefix)==len(shape):
            key=source(*prefix);parts=atoms.get(key,[]);used[key]=parts;members[tuple(prefix)]=parts;return
        for i in range(shape[len(prefix)]):walk(prefix+[i])
    walk([])
    present=[parts for parts in members.values() if parts]
    shapes={(parts[0][1],parts[0][2]) for parts in present}
    single=bool(present) and all(len(parts)==1 and parts[0][4]==0 for parts in present)
    uniform=single and len(shapes)==1
    widths={w for (b,w) in shapes}
    if single and not uniform and len(widths)==1:
        # One width, several word sizes: RecordSlotVar carries the size.
        w=next(iter(widths))
        packed=any(parts[0][3]!=0 or word_users[(parts[0][0],parts[0][1])]>1 for parts in present)
        def rec(prefix):
            if len(prefix)==len(shape):
                parts=members[tuple(prefix)]
                return '{'+(f'{parts[0][0]},{parts[0][3]},{parts[0][1]}' if parts else '0xffff,0,8')+'}'
            return '{'+','.join(rec(prefix+[i]) for i in range(shape[len(prefix)]))+'}'
        lines.append(f'inline constexpr RecordSlotVar<{w},{"true" if packed else "false"}> '+name+''.join('['+str(n)+']' for n in shape)+' = '+rec([])+';')
        return
    if uniform:
        b,w=next(iter(shapes))
        # Unpacked only when every present member starts at bit 0 of a word
        # that no other field uses (a bank word packs several fields, and the
        # first of them also starts at bit 0).
        packed=any(parts[0][3]!=0 or word_users[(parts[0][0],parts[0][1])]>1 for parts in present)
        def rec(prefix):
            if len(prefix)==len(shape):
                parts=members[tuple(prefix)]
                return '{'+(f'{parts[0][0]},{parts[0][3]}' if parts else '0xffff,0')+'}'
            return '{'+','.join(rec(prefix+[i]) for i in range(shape[len(prefix)]))+'}'
        lines.append(f'inline constexpr RecordSlot<{b},{w},{"true" if packed else "false"}> '+name+''.join('['+str(n)+']' for n in shape)+' = '+rec([])+';')
        return
    def rec(prefix):
        if len(prefix)==len(shape):
            return field(source(*prefix))
        return '{'+',\n'.join(rec(prefix+[i]) for i in range(shape[len(prefix)]))+'}'
    lines.append('inline constexpr RecordField '+name+''.join('['+str(n)+']' for n in shape)+' = '+rec([])+';')

# Dedup suffixes are RTL names, not a second model queue identity.
for suffix in ['deq_ptr_value','enq_ptr_value','maybe_full','ram_extra_id.io_deq_bits_MPORT',
               'ram_tl_state_size.io_deq_bits_MPORT','ram_tl_state_source.io_deq_bits_MPORT']:
    def yank_source(index,suffix=suffix):
        stem='ldut.subsystem_mbus.coupler_to_memory_controller_port_named_axi4.axi4yank.QueueCompatibility'+(f'_{index}' if index else '')
        return next((stem+dedup+'.'+suffix for dedup in ['', '$$inst'] if stem+dedup+'.'+suffix in atoms),stem+'.'+suffix)
    emit('yank_'+suffix.replace('.','_'),[32],yank_source)

domains=['core.rename_stage','core.fp_rename_stage']
emit('rename_map',[2,32],lambda d,i:f'{domains[d]}.maptable.map_table_{i}')
emit('rename_checkpoint',[2,BR,32],lambda d,t,i:f'{domains[d]}.maptable.br_snapshots_{t}_{i}')
emit('rename_free',[2],lambda d:f'{domains[d]}.freelist.free_list')
emit('rename_alloc',[2,BR],lambda d,t:f'{domains[d]}.freelist.br_alloc_lists_{t}')
emit('rename_selected',[2,W],lambda d,i:f'{domains[d]}.freelist.r'+(f'_{i}' if i else ''))
emit('rename_selection_valid',[2,W],lambda d,i:f'{domains[d]}.freelist.REG'+(f'_{i}' if i else ''))
emit('rename_valid',[W],lambda i:'core.rename_stage.REG'+(f'_{2*i}' if i else ''))
# Field names are emitted for the union of every checked contract, so the model
# writers compile against any layout; a field a layout does not carry has no
# fragments and its write_record is a no-op. Partition-cut contracts add the
# per-entry ROB uop fields, the STQ data words and the remaining rename fields.
KNOWN_RENAME_FIELDS={'br_mask','br_tag','bypassable','dst_rtype','edge_inst','exception','flush_on_commit','fp_val','frs3_en',
    'ftq_idx','fu_code','imm_packed','iq_type','is_amo','is_br','is_fence','is_fencei','is_jal','is_jalr','is_rvc','is_sfb',
    'is_sys_pc2epc','is_unique','ldst','ldst_val','lrs1','lrs1_rtype','lrs2','lrs2_rtype','lrs3','mem_cmd','mem_signed','mem_size',
    'pc_lob','prs1','prs2','prs3','stale_pdst','taken','uopc','uses_ldq','uses_stq'}
KNOWN_ROB_UOP_FIELDS=['dst_rtype','edge_inst','flush_on_commit','ftq_idx','is_fencei','is_rvc','is_sys_pc2epc','ldst','ldst_val',
    'pc_lob','pdst','stale_pdst','uopc','uses_ldq','uses_stq']
KNOWN_STQ_FIELDS={'bits_addr_bits','bits_addr_is_virtual','bits_data_bits'}
renfields=sorted({m[1] for key in atoms if (m:=re.fullmatch(r'core\.(?:fp_)?rename_stage\.REG_\d+_(\w+)',key))}|KNOWN_RENAME_FIELDS)
for suffix in renfields:
    emit('rename_uop_'+suffix,[2,W],lambda d,i,s=suffix:f'{domains[d]}.REG_{2*i+1}_{s}')
for suffix in ['val','bsy','unsafe','predicated','exception']:
    emit('rob_'+suffix,[W,32],lambda b,r,s=suffix:f'core.rob.rob_{s}_'+(f'{b}_' if b else '_')+str(r))
emit('rob_branch',[W,32],lambda b,r:'core.rob.rob_uop_'+(f'{b}_' if b else '_')+str(r)+'_br_mask')
emit('rob_fp',[W,32],lambda b,r:'core.rob.rob_uop_'+(f'{b}_' if b else '_')+str(r)+'_fp_val')
for suffix in KNOWN_ROB_UOP_FIELDS:
    emit('rob_uop_'+suffix,[W,32],lambda b,r,s=suffix:'core.rob.rob_uop_'+(f'{b}_' if b else '_')+str(r)+'_'+s)
emit('rob_r_xcpt_uop_exc_cause',[],lambda:'core.rob.r_xcpt_uop_exc_cause')
# Debug module registers the partitioned kernels read across the core/uncore cut.
DEBUG='ldut.debug_1.dmInner.dmInner.'
emit('debug_program_buffer_byte',[64],lambda i:f'{DEBUG}programBufferMem_{i}')
emit('debug_abstract_data_byte',[8],lambda i:f'{DEBUG}abstractDataMem_{i}')
emit('debug_abstract_generated',[2],lambda i:f'{DEBUG}abstractGeneratedMem_{i}')
emit('debug_go_reg',[],lambda:DEBUG+'goReg')
emit('debug_resume_req_regs',[],lambda:DEBUG+'resumeReqRegs')
# TAGE allocation LFSR bits (6-bit LFSRs, four per bank); bit 0 lives in the bank image.
emit('bpd_prng_state',[2,4,6],lambda b,k,i:f'frontend.bpd.banked_predictors_{b}.components_1.prng'+(f'_{k}' if k else '')+f'.state_{i}')
# Execution units, FP queues, LSU memory stage, busy tables and dcache lanes the
# partitioned kernels read across their cuts (absent in a layout: no-op writes).
emit('brinfo_uop_ftq_idx',[4],lambda i:f'core.brinfos_{i}_uop_ftq_idx')
emit('brinfo_uop_rob_idx',[4],lambda i:f'core.brinfos_{i}_uop_rob_idx')
emit('rename_busy',[2],lambda d:f'{domains[d]}.busytable.busy_table')
EXE_UNITS=['core.jmp_unit.alu.REG_1_0','core.csr_exe_unit.alu.REG_1_0','core.ALUExeUnit$$inst.alu.REG_1_2',
           'core.ALUExeUnit$$inst.imul.REG_1_2','core.jmp_unit.alu.REG_1_2','core.jmp_unit.imul.REG_1_2']
for s in ['bypassable','dst_rtype','pdst','imm_packed','ctrl_csr_cmd']:
    emit('exe_uop_'+s,[len(EXE_UNITS)],lambda i,s=s:f'{EXE_UNITS[i]}_{s}')
DIV_UNITS=['core.jmp_unit.div.r_uop','core.csr_exe_unit.div.r_uop']
for s in ['bypassable','dst_rtype','pdst']:
    emit('div_uop_'+s,[2],lambda i,s=s:f'{DIV_UNITS[i]}_{s}')
for s in ['dst_rtype','is_amo','pdst','rob_idx','stq_idx','uopc','uses_stq']:
    emit('fpu_stage3_uop_'+s,[],lambda s=s:f'core.fp_pipeline.fpiu_unit.fpu.REG_1_3_{s}')
FROM_INT_QUEUES=['core.csr_exe_unit.BranchKillableQueue$$inst','core.jmp_unit.BranchKillableQueue$$inst']
for s in ['rob_idx','pdst','dst_rtype']:
    emit('from_integer_uop_'+s,[2,8],lambda q,i,s=s:f'{FROM_INT_QUEUES[q]}.uops_{i}_{s}')
FP_QUEUES=['core.fp_pipeline.fpiu_unit.BranchKillableQueue$$inst','core.fp_pipeline.fpiu_unit.BranchKillableQueue_1']
for s in ['uopc','rob_idx','stq_idx','pdst','is_amo','uses_stq','dst_rtype']:
    emit('fp_queue_uop_'+s,[2,8],lambda q,i,s=s:f'{FP_QUEUES[q]}.uops_{i}_{s}')
for s in ['r_divsqrt_fin_rm','r_divsqrt_fin_typeTagIn','r_out_flags_double','r_out_uop_pdst','r_out_wdata_double']:
    emit('fdivsqrt_'+s,[],lambda s=s:f'core.fp_pipeline.fpiu_unit.fdivsqrt.{s}')
IFPU=['core.csr_exe_unit.ifpu','core.jmp_unit.ifpu']
emit('ifpu_out_data',[2],lambda i:f'{IFPU[i]}.ifpu.io_out_b_data')
emit('ifpu_out_double',[2],lambda i:f'{IFPU[i]}.outPipe_bits')
for s in ['ldq_idx','stq_idx','pdst','fp_val']:
    emit('mem_incoming_uop_'+s,[],lambda s=s:f'lsu.mem_incoming_uop_0_{s}')
for s in ['br_mask','rob_idx','stq_idx','mem_size']:
    emit('mem_ldq_incoming_uop_'+s,[],lambda s=s:f'lsu.mem_ldq_incoming_e_0_bits_uop_{s}')
emit('mem_ldq_incoming_st_dep_mask',[],lambda:'lsu.mem_ldq_incoming_e_0_bits_st_dep_mask')
emit('mem_stq_incoming_valid',[],lambda:'lsu.mem_stq_incoming_e_0_valid')
for s in ['uop_br_mask','uop_rob_idx','uop_stq_idx','uop_mem_size','uop_is_amo','addr_valid','addr_is_virtual','data_valid']:
    emit('mem_stq_incoming_'+s,[],lambda s=s:f'lsu.mem_stq_incoming_e_0_bits_{s}')
emit('dcache_mshr_grant_sink',[4],lambda i:f'dcache.mshrs.mshrs_{i}.grantack_bits_sink')
for s in ['ldq_idx','stq_idx','is_amo','uses_ldq','uses_stq']:
    emit('dcache_respq_uop_'+s,[4],lambda i,s=s:f'dcache.mshrs.respq.uops_{i}_{s}')
for s in ['prober.old_coh_state','prober.way_en','wb.req_idx','wb.req_param','wb.req_voluntary']:
    emit('dcache_'+s.replace('.','_'),[],lambda s=s:f'dcache.{s}')
# The b2 branch update register, CSR side registers, issue-slot poison bits,
# the integer register-read stage, the dcache store pipeline.
for s in ['cfi_type','jalr_target','mispredict','pc_sel','taken','target_offset','uop_edge_inst','uop_ftq_idx',
          'uop_is_rvc','uop_ldq_idx','uop_pc_lob','uop_stq_idx']:
    emit('b2_'+s,[],lambda s=s:f'core.b2_{s}')
emit('csr_dprv_r',[],lambda:'core.csr.io_status_dprv_REG')
emit('csr_mip_seip',[],lambda:'core.csr.reg_mip_seip')
emit('csr_single_stepped',[],lambda:'core.csr.reg_singleStepped')
emit('iq_poison',[2,2],lambda q,p:['core.int_issue_unit','core.mem_issue_unit'][q]+f'.slots_0.p{p+1}_poisoned')
for s in ['fp_val','is_amo','ldq_idx','mem_cmd','mem_signed','mem_size','pdst','rob_idx','stq_idx','uses_ldq','uses_stq']:
    emit('iregread_uop_'+s,[],lambda s=s:f'core.iregister_read.exe_reg_uops_0_{s}')
for s in ['s3_valid','s3_req_addr','s3_req_data','s4_valid','s4_req_addr','s5_valid','s5_req_addr','s5_req_data']:
    emit('dcache_'+s,[],lambda s=s:f'dcache.{s}')
emit('dcache_mshr_arb_a_state',[5],lambda i:f'dcache.mshrs.state__{i}')
emit('dcache_mshr_arb_e_state',[4],lambda i:f'dcache.mshrs.state_1_{i}')
emit('dcache_arb_c_state',[2],lambda i:f'dcache.state_{i}')
# Anonymous (REG_n) registers are numbered per configuration: these names
# are the Large ones, so another configuration gets no-op fields.
CONFIG=json.loads((OUT/'contract-layout.json').read_text()).get('configuration','')
def large_only(name,shape,source):
    emit(name,shape,source if CONFIG=='large' else (lambda *a,n=name:'unmapped.'+n))
large_only('core_dec_jalr_debug',[4],lambda i:f'core.REG_{i}' if i else 'unmapped.core_dec_jalr_debug')
large_only('core_jmp_pc_req_valid',[],lambda:'core.REG_15')
large_only('core_jmp_pc_req_ftq',[],lambda:'core.REG_16')
large_only('core_sys_pc2epc_r',[],lambda:'core.REG_18')
large_only('core_sys_pc2epc_ftq_r',[],lambda:'core.REG_19')
large_only('core_com_xcpt_cause_r',[],lambda:'core.REG_29')
large_only('lsu_fired_load_incoming',[],lambda:'lsu.REG_3')
large_only('lsu_exception_r',[2],lambda i:['lsu.REG_10','lsu.REG_13'][i])
large_only('lsu_exception_rr',[2],lambda i:['lsu.REG_12','lsu.REG_15'][i])
large_only('lsu_lcam_rob_r',[],lambda:'lsu.REG_145')
large_only('fe_s1_is_replay_r',[],lambda:'frontend.REG_4')
large_only('ftq_port0_pc_r',[],lambda:'frontend.ftq.REG_19')
large_only('ftq_port0_next_valid_r',[],lambda:'frontend.ftq.REG_20')
large_only('ftq_port0_com_pc_r',[],lambda:'frontend.ftq.REG_21')
large_only('ftq_port0_entry_cfi_valid_r',[],lambda:'frontend.ftq.REG_17_cfi_idx_valid')
large_only('ftq_port0_entry_cfi_bits_r',[],lambda:'frontend.ftq.REG_17_cfi_idx_bits')
large_only('ftq_port0_entry_start_bank_r',[],lambda:'frontend.ftq.REG_17_start_bank')
large_only('icache_refill_valid_r',[],lambda:'frontend.icache.REG')
large_only('dcache_s1_nack_r',[],lambda:'dcache.REG_13')
emit('lsu_dtlb_state',[],lambda:'lsu.dtlb.state')
emit('dcache_mmio_req_data',[],lambda:'dcache.mshrs.mmios_0.req_data')
emit('lsu_r_xcpt_cause',[],lambda:'lsu.r_xcpt_cause')
emit('lsu_r_xcpt_badvaddr',[],lambda:'lsu.r_xcpt_badvaddr')
emit('lsu_wb_forward_ld_addr',[],lambda:'lsu.wb_forward_ld_addr_0')
FPU_CUT=['dfma.io_out_v','dfma.io_out_b_exc','sfma.io_out_v','sfma.io_out_b_exc','fpmu.io_out_outPipe_valid_1',
         'fpmu.io_out_outPipe_bits_1_exc','fpiu_outPipe_valid_2','fpiu_outPipe_bits_2_exc','outPipe_bits_2']
emit('fpu_sidecar_cut',[len(FPU_CUT)],lambda i:'core.fp_pipeline.fpiu_unit.fpu.fpu.'+FPU_CUT[i])
emit('ptw_l2_refill',[],lambda:'ptw.l2_refill')
emit('clint_time',[],lambda:'ldut.clint.time')
for s in ['REG_1','REG_2','counter','r']:
    emit('l2_broadcast_'+s.lower(),[],lambda s=s:f'ldut.subsystem_l2_wrapper.broadcast_1.{s}')
emit('mem_axi4buf_b_deq_value',[],lambda:'mem.axi4buf.bundleIn_0_b_deq.value')
emit('mem_axi4buf_r_deq_value',[],lambda:'mem.axi4buf.bundleIn_0_r_deq.value')
# Lanes the emitted partition kernels carry beyond the cut study's prediction.
emit('bpd_tage_reset_idx',[2,6],lambda b,t:f'frontend.bpd.banked_predictors_{b}.components_1.tables_{t}.reset_idx')
emit('bpd_bim_reset_idx',[2],lambda b:f'frontend.bpd.banked_predictors_{b}.components_4.reset_idx')
emit('bpd_loop_f4_conf',[2,4],lambda b,c:f'frontend.bpd.banked_predictors_{b}.components_0.columns_{c}.f4_entry_conf')
before_frontend_cut=set(used)
large_only('bpd_pc_tail',[2],lambda s:f'frontend.bpd.REG_{12+s}')
large_only('fe_previous_reset',[],lambda:'frontend.REG')
large_only('fe_replay_ae',[],lambda:'frontend.REG_2_ae_inst')
large_only('fe_replay_pf',[],lambda:'frontend.REG_2_pf_inst')
large_only('ftq_enq_ready_r',[],lambda:'frontend.ftq.REG_12')
for suffix in ('bits','valid'):
    emit('bpd_btb_f3_pc_'+suffix,[2,4],lambda b,s,x=suffix:f'frontend.bpd.banked_predictors_{b}.components_2.REG_{8+12*s}_{x}')
    emit('bpd_fa_f3_pc_'+suffix,[2,4],lambda b,s,x=suffix:f'frontend.bpd.banked_predictors_{b}.components_3.REG_{1+2*s}_predicted_pc_{x}')
for suffix in ('is_br','is_jal'):
    emit('bpd_fa_f2_'+suffix,[2,4],lambda b,s,x=suffix:f'frontend.bpd.banked_predictors_{b}.components_3.REG'+(f'_{2*s}' if s else '')+'_'+x)
emit('bpd_bim_f3_meta',[2],lambda b:f'frontend.bpd.banked_predictors_{b}.components_4.REG_4')
emit('bpd_bim_s2_valid',[2],lambda b:f'frontend.bpd.banked_predictors_{b}.components_4.s2_valid')
frontend_extra_cut=any(used[key] for key in set(used)-before_frontend_cut)
# The retained packed words for ways 13..15 contain tag/is_br; their
# counters are already maintained in the native bank's meta__v2_bank_64_0.
for suffix in ('tag','is_br'):
    emit('bpd_fa_tail_'+suffix,[2,3,4],lambda b,w,s,x=suffix:f'frontend.bpd.banked_predictors_{b}.components_3.meta_{13+w}_{s}_{x}')
emit('fp_rrd_stage0_br_mask',[],lambda:'core.fp_pipeline.fregister_read.REG_1_br_mask')
emit('csr_alu_r_data',[],lambda:'core.csr_exe_unit.alu.r_data_0')
for s in ['cycleNum_A','cycleNum_E','sqrtOp_PC']:
    emit('fdivsqrt_'+s.lower(),[],lambda s=s:f'core.fp_pipeline.fpiu_unit.fdivsqrt.divsqrt.ds.divSqrtRecF64ToRaw.{s}')
emit('ptw_s1_valid',[],lambda:'ptw.s1_valid')
# A register wider than 256 bits is written one 64-bit word at a time (a
# fragment's source offset is a byte).
def emit_words(name,key,words):
    fields=[]
    for w in range(words):
        parts=[(o,e,wd,lo,sl-64*w) for (o,e,wd,lo,sl) in atoms.get(key,[]) if sl//64==w]
        used[f'{key}#w{w}']=parts
        fields.append('{'+str(len(parts))+', {'+', '.join('{'+','.join(map(str,p))+'}' for p in parts)+'}}')
    lines.append(f'inline constexpr RecordField {name}[{words}] = {{'+',\n'.join(fields)+'};')
emit_words('ptw_valid_1_0_word','ptw.valid_1_0',8)
emit('dcache_s1_req_is_hella',[],lambda:'dcache.s1_req_0_is_hella')
for s in ['r_sectored_hit','r_sectored_hit_addr','r_sectored_repl_addr']:
    emit('lsu_dtlb_'+s,[],lambda s=s:f'lsu.dtlb.{s}')
emit('lsu_p2_block_load_mask_0',[],lambda:'lsu.p2_block_load_mask_0')
emit('debug_inner_d_source_widx_bin',[],lambda:'ldut.debug_1.dmInner.dmiXing.bundleIn_0_d_source.widx_widx_bin')
large_only('iregread_stage0_br_mask',[],lambda:'core.iregister_read.REG_3_br_mask')
large_only('core_retire_count_r',[],lambda:'core.REG_25')
large_only('core_rob_flush_r',[],lambda:'core.REG_36')
large_only('core_evec_rr',[],lambda:'core.REG_7')
for kind in ['ldq','stq']:
    prefixes=set(KNOWN_STQ_FIELDS) if kind=='stq' else set()
    for key in atoms:
        m=re.fullmatch(r'lsu\.'+kind+r'_(\d+)_(.+)',key)
        if m:prefixes.add(m[2])
    for suffix in sorted(prefixes):emit(kind+'_'+suffix,[LDQ if kind=='ldq' else STQ],lambda i,k=kind,s=suffix:f'lsu.{k}_{i}_{s}')
for key in sorted(atoms):
    if key.startswith('lsu.') and re.fullmatch(r'lsu\.(ldq|stq)_(head|tail|retry_idx|wakeup_idx|commit_head|execute_head)',key):
        emit(key.replace('.','_'),[],lambda k=key:k)
for module,count in [('ftq',geometry['ftq'])]:
    suffixes=sorted({m[1] for key in atoms if
        (m:=re.fullmatch(r'frontend\.'+module+r'\.ram_\d+_(.+)',key))})
    for suffix in suffixes:
        emit(module+'_'+suffix,[count],lambda i,m=module,s=suffix:f'frontend.{m}.ram_{i}_{s}')
for module in ['f3','f3_bpd_resp','f4']:
    for key in sorted(atoms):
        if key.startswith('frontend.'+module+'.ram_'):
            emit('fe_'+key.split('frontend.')[1].replace('.','_'),[],lambda k=key:k)
rb=(geometry['rob_entries']-1).bit_length()
# A non-power-of-two ROB bank count reserves wire codes.
rb=(geometry['rows']-1).bit_length()+(W-1).bit_length()
lb=(LDQ-1).bit_length();sb=(STQ-1).bit_length();pb=(geometry['int_regs']-1).bit_length()
positions={'dst_rtype':0,'uses_stq':2,'uses_ldq':3,'is_amo':4,'is_fence':5,'mem_signed':6,
           'mem_size':7,'mem_cmd':9,'exception':14,'pdst':15,'stq_idx':15+pb,
           'ldq_idx':15+pb+sb,'rob_idx':15+pb+sb+lb,'br_mask':15+pb+sb+lb+rb}
descriptors=[]
for i in range(STQ):
    bits={}
    for name,position in positions.items():
        for off,size,width,low,src in atoms.get(f'lsu.stq_{i}_bits_uop_{name}',[]):
            for n in range(width):bits[off,size,low+n]=position+src+n
    runs=[]
    for (off,size,dst),src in sorted(bits.items()):
        if runs and runs[-1][0]==off and runs[-1][1]==size and runs[-1][3]+runs[-1][2]==dst and runs[-1][4]+runs[-1][2]==src:
            runs[-1][2]+=1
        else:runs.append([off,size,1,dst,src])
    if len(runs)>8:raise ValueError('store descriptor split exceeds eight')
    descriptors.append('{'+str(len(runs))+', {'+', '.join('{'+','.join(map(str,x))+'}' for x in runs)+'}}')
lines.append(f'inline constexpr RecordField stq_descriptor[{STQ}] = {{'+',\n'.join(descriptors)+'};')
ranges=[]
for o in entries:
    name=o['flat'].split('boom_tile.')[-1]
    if not name.startswith(('core.','lsu.')) or any(x in name for x in ('.fpu.fpu.','.fdivsqrt.divsqrt.')):continue
    if name in ('lsu.REG','lsu.REG_1','lsu.hella_state'):continue
    ranges.append((o['recordOffset'],o['recordOffset']+o['elemBytes']))
merged=[]
for lo,hi in sorted(ranges):
    if merged and lo<=merged[-1][1]:merged[-1][1]=max(hi,merged[-1][1])
    else:merged.append([lo,hi])
lines+=['inline void reset_core(contract::Image& record) {','  auto* p=reinterpret_cast<unsigned char*>(&record);']
lines += [f'  std::memset(p+{lo},0,{hi-lo});' for lo,hi in merged]
lines+=['}','}  // namespace chisa::boom_model::wide::fields','']
write_changed((OUT/'record_fields.h'), '\n'.join(lines))
write_changed((OUT/'record-field-layout.json'), json.dumps(used,indent=2)+'\n')
tail_cut=any(parts for key,parts in used.items() if re.search(r'\.components_3\.meta_(13|14|15)_[0-3]_(tag|is_br)$',key))
write_changed(OUT/'predictor_cut_config.h', '#pragma once\n#define CHISA_PREDICTOR_TAIL_CUT '+str(int(tail_cut))+
              '\n#define CHISA_FRONTEND_EXTRA_CUT '+str(int(frontend_extra_cut))+'\n')
print('record bit addresses:',len(used),'selected:',sum(bool(x) for x in used.values()))

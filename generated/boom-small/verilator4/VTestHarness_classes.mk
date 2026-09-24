# Verilated -*- Makefile -*-
# DESCRIPTION: Verilator output: Make include file with class lists
#
# This file lists generated Verilated files, for including in higher level makefiles.
# See VTestHarness.mk for the caller.

### Switches...
# C11 constructs required?  0/1 (always on now)
VM_C11 = 1
# Timing enabled?  0/1
VM_TIMING = 0
# Coverage output mode?  0/1 (from --coverage)
VM_COVERAGE = 0
# Parallel builds?  0/1 (from --output-split)
VM_PARALLEL_BUILDS = 1
# Tracing output mode?  0/1 (from --trace-fst/--trace-saif/--trace-vcd)
VM_TRACE = 0
# Tracing output mode in FST format?  0/1 (from --trace-fst)
VM_TRACE_FST = 0
# Tracing output mode in SAIF format?  0/1 (from --trace-saif)
VM_TRACE_SAIF = 0
# Tracing output mode in VCD format?  0/1 (from --trace-vcd)
VM_TRACE_VCD = 0

### Object file lists...
# Generated module classes, fast-path, compile with highest optimization
VM_CLASSES_FAST += \
	VTestHarness \
	VTestHarness___024root__DepSet_h30a6511e__0 \
	VTestHarness___024root__DepSet_hcfd557fa__0 \
	VTestHarness___024root__DepSet_hcfd557fa__1 \
	VTestHarness___024root__DepSet_hcfd557fa__2 \
	VTestHarness___024root__DepSet_hcfd557fa__3 \
	VTestHarness___024root__DepSet_hcfd557fa__4 \
	VTestHarness___024root__DepSet_hcfd557fa__5 \
	VTestHarness___024root__DepSet_hcfd557fa__6 \
	VTestHarness___024root__DepSet_hcfd557fa__7 \
	VTestHarness___024root__DepSet_hcfd557fa__8 \
	VTestHarness___024root__DepSet_hcfd557fa__9 \
	VTestHarness___024root__DepSet_hcfd557fa__10 \
	VTestHarness___024root__DepSet_hcfd557fa__11 \
	VTestHarness___024root__DepSet_hcfd557fa__12 \
	VTestHarness___024root__DepSet_hcfd557fa__13 \
	VTestHarness___024root__DepSet_hcfd557fa__14 \
	VTestHarness___024unit__DepSet_hc9fa512f__0 \

# Generated module classes, non-fast-path, compile with low/medium optimization
VM_CLASSES_SLOW += \
	VTestHarness__ConstPool_0 \
	VTestHarness___024root__Slow \
	VTestHarness___024root__DepSet_h30a6511e__0__Slow \
	VTestHarness___024root__DepSet_hcfd557fa__0__Slow \
	VTestHarness___024root__DepSet_hcfd557fa__1__Slow \
	VTestHarness___024root__DepSet_hcfd557fa__2__Slow \
	VTestHarness___024root__DepSet_hcfd557fa__3__Slow \
	VTestHarness___024root__DepSet_hcfd557fa__4__Slow \
	VTestHarness___024root__DepSet_hcfd557fa__5__Slow \
	VTestHarness___024root__DepSet_hcfd557fa__6__Slow \
	VTestHarness___024root__DepSet_hcfd557fa__7__Slow \
	VTestHarness___024root__DepSet_hcfd557fa__8__Slow \
	VTestHarness___024unit__Slow \
	VTestHarness___024unit__DepSet_h66f95809__0__Slow \

# Generated support classes, fast-path, compile with highest optimization
VM_SUPPORT_FAST += \
	VTestHarness__Dpi \

# Generated support classes, non-fast-path, compile with low/medium optimization
VM_SUPPORT_SLOW += \
	VTestHarness__Syms \

# Global classes, need linked once per executable, fast-path, compile with highest optimization
VM_GLOBAL_FAST += \
	verilated \
	verilated_dpi \
	verilated_threads \

# Global classes, need linked once per executable, non-fast-path, compile with low/medium optimization
VM_GLOBAL_SLOW += \


# Verilated -*- Makefile -*-

CXX ?= g++
W1_DIR ?= w1
TAP_DIR ?= taps
MODEL_DIR ?= model
RUNTIME_DIR ?= runtime
REPO_RUNTIME_DIR ?= repo-runtime
VERILATOR_INCLUDE ?= /usr/share/verilator/include

CPPFLAGS := \
	-I$(W1_DIR) -I$(TAP_DIR) -I$(MODEL_DIR) -I$(RUNTIME_DIR) \
	-I$(RUNTIME_DIR)/generated_syntax -I$(REPO_RUNTIME_DIR) \
	-isystem $(VERILATOR_INCLUDE) -isystem $(VERILATOR_INCLUDE)/vltstd
CXXFLAGS := -std=c++17 -O0 -g0 -Wall -Wextra -Werror -MMD -MP

.PHONY: all clean
all: rocket-w1-scalar-diff

dmi_host.o: $(RUNTIME_DIR)/run_backdoor_scalar.cpp \
    $(RUNTIME_DIR)/dmi_host_api.h
	$(CXX) -std=c++17 -O1 -g0 -MMD -MP \
	  -DROCKET_DMI_LIBRARY_ONLY -I$(RUNTIME_DIR) -c $< -o $@

run_w1_scalar_differential.o: \
    $(RUNTIME_DIR)/run_w1_scalar_differential.cpp \
    $(RUNTIME_DIR)/w1_reference_runtime.h \
    $(RUNTIME_DIR)/dmi_host_api.h \
    $(W1_DIR)/TestHarness.h \
    $(W1_DIR)/exact_reg_oracle_fields.inc \
    $(W1_DIR)/exact_probe_fields_v2.inc \
    $(W1_DIR)/extmodule_fields.inc \
    $(TAP_DIR)/verilator_reg_tap_fields.inc \
    $(TAP_DIR)/verilator_comb_tap_fields.inc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) \
	  -DORACLE_NUM_CYCLES=0 -DESSENT_ORACLE_VERIFY=0 \
	  -c $< -o $@

rocket-w1-scalar-diff: run_w1_scalar_differential.o dmi_host.o \
    $(MODEL_DIR)/VTestHarness__ALL.a \
    $(MODEL_DIR)/verilated.o $(MODEL_DIR)/verilated_dpi.o \
    $(MODEL_DIR)/verilated_threads.o
	$(CXX) run_w1_scalar_differential.o dmi_host.o \
	  $(MODEL_DIR)/VTestHarness__ALL.a \
	  $(MODEL_DIR)/verilated.o $(MODEL_DIR)/verilated_dpi.o \
	  $(MODEL_DIR)/verilated_threads.o \
	  -pthread -lpthread -latomic -o $@

-include dmi_host.d run_w1_scalar_differential.d

clean:
	rm -f rocket-w1-scalar-diff *.o *.d

# One implementation of the Medium/Large pipelines. Configuration is compile-time; contract-dependent stores stay at module mutation
# sites. No alternate core is selected by a binary path.
BOOM_WIDE_CORE_SOURCES := \
    $(REPO_ROOT)/reference_models/boom_model/wide/backend.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/frontend.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_step.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_record.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_rename.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_rename_record.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_issue.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_rob.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_lsu.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_execute.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_csr.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_fp.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_memory.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_memory_ports.cpp \
    $(REPO_ROOT)/reference_models/boom_model/common/predictor_bank.cpp \
    $(REPO_ROOT)/reference_models/boom_model/common/boom_decode.cpp \
    $(REPO_ROOT)/reference_models/boom_model/common/execute.cpp \
    $(REPO_ROOT)/reference_models/boom_model/common/csr_logic.cpp \
    $(REPO_ROOT)/reference_models/boom_model/common/fp_execute.cpp
BOOM_WIDE_RECORD_SOURCES := \
    $(REPO_ROOT)/reference_models/boom_model/wide/record_bits.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_issue_record.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_rob_record.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_lsu_record.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_execute_record.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_csr_record.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/core_fp_record.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/frontend_record.cpp
BOOM_WIDE_SYSTEM_SOURCES := \
    $(REPO_ROOT)/reference_models/boom_model/wide/system_record.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/oracle_bindings.cpp \
    $(REPO_ROOT)/reference_models/boom_model/wide/system_publication.cpp
BOOM_WIDE_HEADERS := $(wildcard $(REPO_ROOT)/reference_models/boom_model/wide/*.h) \
    $(wildcard $(REPO_ROOT)/reference_models/boom_model/common/*.h)

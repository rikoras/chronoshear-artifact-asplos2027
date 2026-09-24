#pragma once
namespace chisa::boom_system {
class ModelBindings;
class SystemGuider;
void register_wide_bindings();
void declare_unified_regions(const SystemGuider&, ModelBindings&);
void install_watch_dispatch(ModelBindings&);
}

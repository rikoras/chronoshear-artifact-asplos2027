#pragma once
// The wide model's system-level record publication (system_publication.cpp).
namespace chisa::boom_system { class SystemGuider; }
namespace chisa::boom_model::wide {
// Pre-edge: the cold uncore oracles (memory-run lanes only).
void publish_system_early(const boom_system::SystemGuider&);
// Post-edge, both halves / the memory-run half / the core-run half.
void publish_system_end(const boom_system::SystemGuider&);
void publish_system_end_memory(const boom_system::SystemGuider&);
void publish_system_end_core(const boom_system::SystemGuider&);
void reset_publication_versions();
}  // namespace chisa::boom_model::wide

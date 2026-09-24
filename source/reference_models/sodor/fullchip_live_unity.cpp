// Optional single translation unit for the unchanged model and live harness.
// Keeping the definitions visible together lets the C++ compiler inline the
// model's small boundary accessors without changing oracle or RTL checking.
#include "sodor_guider.cpp"
#include "../../duts/sodor-fullchip/flow/sidecar_sodor_fullchip.cpp"

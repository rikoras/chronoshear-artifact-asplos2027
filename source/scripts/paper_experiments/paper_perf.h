#pragma once
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <fcntl.h>
#include <unistd.h>

// Optional measurement-only control. Timing runs leave PAPER_PERF_DIR unset.
// perf stat owns the FIFOs and acknowledges enable/disable before the timed
// region advances. Each marker occurs once per region, never per RTL cycle.
inline void paper_perf_control(bool enable) {
  const char* dir = std::getenv("PAPER_PERF_DIR");
  if (!dir) return;
  char path[4096];
  std::snprintf(path,sizeof(path),"%s/control",dir);
  const int control = open(path,O_WRONLY);
  if (control < 0) throw std::runtime_error("cannot open perf control FIFO");
  const char* command = enable ? "enable\n" : "disable\n";
  const auto size = std::strlen(command);
  if (write(control,command,size) != static_cast<ssize_t>(size))
    throw std::runtime_error("cannot write perf control command");
  close(control);
  std::snprintf(path,sizeof(path),"%s/ack",dir);
  const int ack = open(path,O_RDONLY);
  if (ack < 0) throw std::runtime_error("cannot open perf ack FIFO");
  char c = 0;
  do { if (read(ack,&c,1)!=1) throw std::runtime_error("perf ack missing"); } while(c!='\n');
  close(ack);
}
inline void paper_perf_finish(unsigned long long cycles) {
  paper_perf_control(false);
  if (std::getenv("PAPER_PERF_DIR")) std::fprintf(stderr,"PAPER_PERF_CYCLES %llu\n",cycles);
}

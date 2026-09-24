#pragma once
// Counterfactual timing probe only. Production builds do not include this file.
// The caller supplies the byte-verified image/DMI capture in resident memory.
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>

namespace chisa::boom_repcut {
class OverlapReadyImages {
 public:
  OverlapReadyImages(const std::string& path, std::uint64_t windows,
                     std::size_t records_bytes, std::size_t image_bytes,
                     std::uint64_t reset_windows, unsigned positions,
                     unsigned record_bytes)
      : records_bytes_(records_bytes), image_bytes_(image_bytes),
        stride_(records_bytes + image_bytes) {
    if (path.empty()) return;
    const int fd = ::open(path.c_str(), O_RDONLY);
    if (fd < 0) throw std::runtime_error("cannot open diagnostic ready images");
    struct stat st{};
    if (::fstat(fd, &st) || st.st_size <= 0 ||
        static_cast<std::uint64_t>(st.st_size) != windows * stride_) {
      ::close(fd);
      throw std::runtime_error("diagnostic capture size does not match requested interval/ABI");
    }
    bytes_ = static_cast<std::size_t>(st.st_size);
    void* mapping = ::mmap(nullptr, bytes_, PROT_READ, MAP_SHARED, fd, 0);
    ::close(fd);
    if (mapping == MAP_FAILED) throw std::runtime_error("cannot map diagnostic ready images");
    data_ = static_cast<const char*>(mapping);
    // Resolve page-table faults before the measured execution. The runner
    // decompresses and verifies every window before launching this process.
    volatile unsigned char touched = 0;
    for (std::size_t at = 0; at < bytes_; at += 4096) touched ^= data_[at];
    (void)touched;
    for (std::uint64_t w = reset_windows; w < windows; ++w) {
      std::uint32_t header[3];
      std::memcpy(header, data_ + w * stride_ + records_bytes_, sizeof(header));
      if (header[0] != 0x39474d49 || header[1] != positions || header[2] != record_bytes) {
        ::munmap(const_cast<char*>(data_), bytes_);
        data_ = nullptr;
        throw std::runtime_error("invalid diagnostic image header at window " + std::to_string(w));
      }
    }
  }
  ~OverlapReadyImages() { if (data_) ::munmap(const_cast<char*>(data_), bytes_); }
  OverlapReadyImages(const OverlapReadyImages&) = delete;
  OverlapReadyImages& operator=(const OverlapReadyImages&) = delete;
  explicit operator bool() const { return data_ != nullptr; }
  std::size_t bytes() const { return bytes_; }
  void copy_window(std::uint64_t w, void* records, void* image) const {
    const char* source = data_ + w * stride_;
    std::memcpy(records, source, records_bytes_);
    std::memcpy(image, source + records_bytes_, image_bytes_);
  }
 private:
  const char* data_ = nullptr;
  std::size_t bytes_ = 0, records_bytes_, image_bytes_, stride_;
};
}  // namespace chisa::boom_repcut

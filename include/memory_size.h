#pragma once

#include <cmath>
#include <iostream>
#include <string>

namespace nx {

class memory_size {
 public:
  constexpr memory_size(unsigned long long bytes) : bytes_(bytes) {}

  constexpr unsigned long long bytes() const { return bytes_; }
  constexpr double kib() const { return static_cast<double>(bytes_) / 1024; }
  constexpr double mib() const {
    return static_cast<double>(bytes_) / (1024 * 1024);
  }
  constexpr double gib() const {
    return static_cast<double>(bytes_) / (1024 * 1024 * 1024);
  }

  std::string to_string() const {
    constexpr unsigned long long GiB = 1024ull * 1024 * 1024;
    constexpr unsigned long long MiB = 1024ull * 1024;
    constexpr unsigned long long KiB = 1024ull;

    char buffer[64];
    if (bytes_ >= GiB) {
      std::snprintf(buffer, sizeof(buffer), "%.2f GiB", gib());
    } else if (bytes_ >= MiB) {
      std::snprintf(buffer, sizeof(buffer), "%.2f MiB", mib());
    } else if (bytes_ >= KiB) {
      std::snprintf(buffer, sizeof(buffer), "%.2f KiB", kib());
    } else {
      std::snprintf(buffer, sizeof(buffer), "%llu Bytes", bytes_);
    }
    return buffer;
  }

 private:
  unsigned long long bytes_;
};

};  // namespace nx

// User-defined literals
constexpr nx::memory_size operator""_B(unsigned long long val) {
  return nx::memory_size(val);
}
constexpr nx::memory_size operator""_KiB(unsigned long long val) {
  return nx::memory_size(val * 1024);
}
constexpr nx::memory_size operator""_MiB(unsigned long long val) {
  return nx::memory_size(val * 1024 * 1024);
}
constexpr nx::memory_size operator""_GiB(unsigned long long val) {
  return nx::memory_size(val * 1024 * 1024 * 1024);
}

#pragma once

#include <mutex>

namespace fgame {

template <class T> class thread_safe final {
private:
  T data;
  std::mutex lock;

public:
  thread_safe() : data{} {}
  thread_safe(const T &val) : data{val} {}

  auto operator=(const T &other) noexcept
      -> void; // TODO: this could be an inline function...

  operator T() const noexcept;

  auto set(const T &other) noexcept -> void;
  auto get() noexcept -> T;
};

} // namespace fgame

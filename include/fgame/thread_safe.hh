#pragma once

#include <functional>
#include <mutex>

namespace fgame {

template <class T> class thread_safe final {
private:
  T data;
  std::mutex lock;

public:
  thread_safe() : data{} {}
  thread_safe(const T &val) : data{val} {}

  auto operator=(const T &other) noexcept -> void;

  operator T() const noexcept;

  auto set(const T &other) noexcept -> void;
  auto set(const std::function<void(T &)> &fn) noexcept -> void;

  auto get() noexcept -> T;
};

} // namespace fgame

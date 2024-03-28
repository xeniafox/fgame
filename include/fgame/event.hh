#pragma once

#include <fgame/thread_safe.hh>

#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace fgame {
namespace core {

enum class event_type { todo };

struct event {
public:
  event_type type;
};

using event_callback_function = std::function<void(const event &)>;

namespace internal {

struct event_callback_hasher {
  auto operator()(const core::event_callback_function &fun) const
      -> std::size_t;
};

} // namespace internal

using event_callback_set =
    std::unordered_set<event_callback_function, std::size_t,
                       internal::event_callback_hasher>;

class event_queue final {
private:
  fgame::thread_safe<std::unordered_map<event_type, event_callback_set>>
      callback_lookup;
  fgame::thread_safe<std::queue<event>> queue{};

public:
  event_queue();

  auto hook(const event_type &ev_type,
            const event_callback_function &callback) noexcept -> void;

  auto unhook(const event_type &ev_type,
              const event_callback_function &callback) noexcept -> void;

  auto emit(const event &ev) -> void;

  auto tick() -> void;
};

} // namespace core
} // namespace fgame

#include <fgame/event.hh>

#include <algorithm>

namespace fgame {
namespace core {

auto event_queue::hook(const event_type &ev_type,
                       const event_callback_function &callback) noexcept
    -> void {

  try {
    this->callback_lookup.set([ev_type, callback](auto &lookup) {
      lookup.at(ev_type).insert(callback);
    });
  } catch (const std::out_of_range &_) {
    this->callback_lookup.set([ev_type, callback](auto &lookup) {
      lookup.insert({ev_type, {callback}});
    });
  }
}

auto event_queue::unhook(const event_type &ev_type,
                         const event_callback_function &callback) noexcept
    -> void {
  this->callback_lookup.set([ev_type, callback](auto &lookup) {
    lookup.at(ev_type).erase(callback);
  });
}

auto event_queue::emit(const event &ev) -> void {
  this->queue.set([ev](auto &queue) { queue.push(ev); });
}

auto event_queue::tick() -> void {
  try {
    const auto ev = this->queue.get().front();
    const auto lookup_copy = this->callback_lookup.get();

    std::ranges::for_each(this->callback_lookup.get().at(ev.type),
                          [ev](const auto &callback) { callback(ev); });

    this->queue.set([](auto &queue) { queue.pop(); });
  } catch (const std::out_of_range &_) {
    // TODO: it should log that either the event queue is empty or there are no
    // callbacks hooked to such an event
  }
}

} // namespace core
} // namespace fgame

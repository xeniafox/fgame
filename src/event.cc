#include <fgame/event.hh>

namespace fgame {
namespace core {

auto event_queue::hook(const event_type &ev_type,
                       const event_callback_function &callback) noexcept
    -> void {

  try {
    // TODO: aaaa why a copyyyyyy
    auto lookup_copy = this->callback_lookup.get();
    lookup_copy.at(ev_type).insert(callback);

    this->callback_lookup = lookup_copy;
  } catch (const std::out_of_range &_) {
    this->callback_lookup.get().insert({ev_type, {callback}});
  }
}

auto event_queue::unhook(const event_type &ev_type,
                         const event_callback_function &callback) noexcept
    -> void {

  auto lookup_copy = this->callback_lookup.get();
  lookup_copy.at(ev_type).erase(callback);

  this->callback_lookup = lookup_copy;
}

auto event_queue::emit(const event &ev) -> void {
  auto queue_copy = this->queue.get();
  queue_copy.push(ev);

  this->queue = queue_copy;
}

auto event_queue::tick() -> void {

  try {
    auto queue_copy = this->queue.get();
    const auto ev = queue_copy.front();

    const auto lookup_copy = this->callback_lookup.get();

    for (const auto &callback : lookup_copy.at(ev.type)) {
      callback(ev);
    }

    queue_copy.pop();
    this->queue.set(queue_copy);
  } catch (const std::out_of_range &_) {
    // TODO: it should log that either the event queue is empty or there are no
    // callbacks hooked to such an event
  }
}

} // namespace core
} // namespace fgame

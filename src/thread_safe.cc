#include <fgame/thread_safe.hh>

namespace fgame {

// TODO: this could be an inline function...
template <class T>
auto thread_safe<T>::operator=(const T &other) noexcept -> void {
  this->set(other);
}

template <class T> thread_safe<T>::operator T() const noexcept {
  return this->get();
}

template <class T> auto thread_safe<T>::set(const T &other) noexcept -> void {
  this->lock.lock();
  this->data = other;
  this->lock.unlock();
}

template <class T> auto thread_safe<T>::get() noexcept -> T {
  this->lock.lock();
  const auto data_copy = this->data;
  this->lock.unlock();

  return data_copy;
}

} // namespace fgame

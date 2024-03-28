#include <fgame/thread_safe.hh>

namespace fgame {

template <class T>
inline auto thread_safe<T>::operator=(const T &other) noexcept -> void {
  this->set(other);
}

template <class T> inline thread_safe<T>::operator T() const noexcept {
  return this->get();
}

template <class T>
inline auto thread_safe<T>::set(const T &other) noexcept -> void {
  this->lock.lock();
  this->data = other;
  this->lock.unlock();
}

template <class T>
inline auto thread_safe<T>::set(const std::function<void(T &)> &fn) noexcept
    -> void {
  this->lock.lock();

  fn(this->data);

  this->lock.unlock();
}

template <class T> inline auto thread_safe<T>::get() noexcept -> T {
  this->lock.lock();
  const auto data_copy = this->data;
  this->lock.unlock();

  return data_copy;
}

} // namespace fgame

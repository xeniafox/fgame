#include <fgame/component.hh>

namespace fgame {
namespace ecs {

auto component::get_active() const -> bool { return this->_active; }

auto component::set_active(bool active) noexcept -> void {
  this->_active = active;
}

auto component::get_visible() const -> bool { return this->_visible; }

auto component::set_visible(bool visible) noexcept -> void {
  this->_visible = visible;
}

} // namespace ecs
} // namespace fgame

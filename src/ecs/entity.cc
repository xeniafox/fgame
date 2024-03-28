#include <fgame/entity.hh>

#include <fgame/component.hh>
#include <ranges>

namespace fgame {
namespace ecs {

auto entity::tick(const double &delta_time) -> void {
  auto active_components =
      this->_components | std::views::filter([](const auto &component) {
        return component.get_active();
      });

  for (auto &component : active_components) {
    component.update(delta_time);
  }

  this->update(delta_time);
}

auto entity::get_position() const -> math::cpu_vec3 { return this->_position; }

auto entity::set_position(const math::cpu_vec3 &position) noexcept -> void {
  // TODO: this can be better
  this->_position[0] = position[0];
  this->_position[1] = position[1];
  this->_position[2] = position[2];
}

auto entity::get_active() const -> bool { return this->_active; }

auto entity::set_active(bool active) noexcept -> void {
  this->_active = active;
}

auto entity::get_visible() const -> bool { return this->_visible; }

auto entity::set_visible(bool visible) noexcept -> void {
  this->_visible = visible;
}

} // namespace ecs
} // namespace fgame

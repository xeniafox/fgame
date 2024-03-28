#pragma once

#include <fgame/math.hh>

#include <fgame/component.hh>
#include <vector>

namespace fgame {
namespace ecs {

class entity {
protected:
  bool _active;
  bool _visible;

  std::vector<component> _components{};

  math::cpu_vec3 _position;

  virtual auto update(const double &delta_time) -> void = 0;

public:
  entity(const math::cpu_vec3 &position)
      : _active{false}, _visible{false}, _position{position} {}

  entity(bool active, bool visible, const math::cpu_vec3 &position)
      : _active{active}, _visible{visible}, _position{position} {}

  virtual ~entity();

  virtual auto init() -> void = 0;
  virtual auto shutdown() -> void = 0;

  auto tick(const double &delta_time) -> void;

  auto get_position() const -> math::cpu_vec3;
  auto set_position(const math::cpu_vec3 &position) noexcept -> void;

  auto get_active() const -> bool;
  auto set_active(bool active) noexcept -> void;

  auto get_visible() const -> bool;
  auto set_visible(bool visible) noexcept -> void;
};

} // namespace ecs
} // namespace fgame

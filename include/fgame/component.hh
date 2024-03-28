#pragma once

namespace fgame {
namespace ecs {

class component {
private:
  bool _active{false};
  bool _visible{false};

public:
  component(bool active, bool visible) : _active{active}, _visible{visible} {}
  virtual ~component();

  virtual auto init() -> void = 0;
  virtual auto shutdown() -> void = 0;

  virtual auto update(const double &delta_time) -> void = 0;
  virtual auto render() -> void = 0;

  auto get_active() const -> bool;
  auto set_active(bool active) noexcept -> void;

  auto get_visible() const -> bool;
  auto set_visible(bool visible) noexcept -> void;
};

} // namespace ecs
} // namespace fgame

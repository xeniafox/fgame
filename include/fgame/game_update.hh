#pragma once

namespace fgame {
namespace core {

class game_update final {
public:
  auto operator()(const double &delta_time) -> void;
};

} // namespace core
} // namespace fgame

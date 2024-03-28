#pragma once

#include <fmt/std.h>

#include <fgame/util.hh>

namespace fgame {

class game final {
  using consolidated_program_arguments = const std::vector<std::string_view>;

private:
  const consolidated_program_arguments launch_arguments;

public:
  game(program_arguments &&arguments);
  auto run() -> void;

  auto update(const double delta_time, const double fps) -> void;
};

} // namespace fgame

#include <fgame/game.hh>

auto main(int argc, const char *argv[]) -> int {
  fgame::game game_instance{fgame::build_program_arguments(argc, argv)};
  game_instance.run();
}

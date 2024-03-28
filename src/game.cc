#include <fgame/game.hh>

#include <ctime>
#include <fgame/game_render.hh>
#include <fgame/game_update.hh>
#include <fgame/util.hh>
#include <thread>

namespace fgame {

game::game(const program_arguments &&args) : launch_arguments{std::move(args)} {
  // game class constructor
}

auto game::run() -> void {
  std::jthread logics([] {
    constexpr double const time_lower_limit = 0.0167f; // keep at/below 60 fps
    constexpr double const time_upper_limit = 0.1f;    // keep at/above 10 fps

    double last_time = clock();

    core::game_update updater{};

    bool running = true;

    try {
      while (running) {
        const double current_time = clock();

        double delta_time = 1 / (current_time - last_time) * 1000.0f;
        delta_time = delta_time < time_lower_limit
                         ? time_lower_limit
                         : (delta_time > time_upper_limit ? time_upper_limit
                                                          : delta_time);

        updater(delta_time);

        last_time = current_time;
      }
    } catch (const std::exception &err) {
      die(err.what());
    }
  });

  std::jthread graphics([] {
    core::game_render render{};

    bool running = true;
    try {
      while (running) {
        render();
      }
    } catch (const std::exception &err) {
      die(err.what());
    }
  });

  logics.join();
  graphics.join();
}

} // namespace fgame

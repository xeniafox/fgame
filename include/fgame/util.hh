#pragma once

#include <optional>
#include <ranges>
#include <stacktrace>
#include <string_view>
#include <vector>

#include <curl/curl.h>
#include <fmt/std.h>

namespace fgame {

template <typename T>
concept good_exception = std::derived_from<T, std::exception>;

template <good_exception T> struct program_error {
  const std::remove_cvref_t<T> exception;
  const std::stacktrace stack;
};

using program_arguments = const std::vector<std::string_view>;
using general_error = const program_error<std::runtime_error>;

template <good_exception T>
[[noreturn]] constexpr inline auto die(const program_error<T> &&error) -> void {
  fmt::println("die: called with exception of type {}",
               typeid(error.exception).name());
  fmt::println("\twhat: {}", error.exception.what());
  fmt::println("\tstack:");

  for (const auto [i, entry] : error.stack | std::views::enumerate) {
    fmt::println("\t\t#{} -> @ {}:{} ({})", (error.stack.size() - i),
                 entry.description(), entry.source_line(), entry.source_file());
  }

  std::abort();
}

constexpr inline auto error_from_std_exception(good_exception auto &&exception)
    -> const program_error<std::remove_cvref_t<decltype(exception)>> {
  return {std::move(exception), std::move(std::stacktrace::current(1))};
}

inline auto die(const std::string &msg) -> void {
  auto err = error_from_std_exception(std::runtime_error{msg});
  die(std::move(err));
}

inline auto build_program_arguments(const int argc, const char *const *argv)
    -> program_arguments {
  return program_arguments{argv,
                           std::next(argv, static_cast<std::ptrdiff_t>(argc))};
}

inline auto env_var(const std::string variable)
    -> std::optional<const std::string_view> {
  if (const char *result = std::getenv(variable.data())) {
    return {result};
  }

  return std::nullopt;
}

auto http_get(const std::string_view &url,
              const std::string user_agent =
                  "Mozilla/5.0 (X11; Linux x86_64; rv:123.0) Gecko/20100101 "
                  "Firefox/123.0") -> std::string;

} // namespace fgame

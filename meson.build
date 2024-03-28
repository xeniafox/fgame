project(
  'fgame',
  'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++23']
)

add_project_arguments('-msse4.1', language: 'cpp')
add_project_link_arguments('-lstdc++_libbacktrace', '-lstdc++exp', language: 'cpp')

cmake = import('cmake')

app_deps = [
  dependency('fmt')
]

app_includes = [
  include_directories('include'),
  include_directories('subprojects/mathfu/include'),
  include_directories('subprojects/mathfu/dependencies/vectorial/include')
]

app_sources = [
  'src/game.cc',
  'src/game_render.cc',
  'src/game_update.cc',
  'src/ecs/component.cc',
  'src/ecs/entity.cc',
  'src/thread_safe.cc',
  'src/event.cc',
]

app = library('app',
  app_sources,
  install: true,
  include_directories: [app_includes],
  dependencies: [app_deps]
)

exe = executable(
  'fgame',
  'src/main.cc',
  include_directories: [app_includes],
  install: true,
  link_with: [app]
)

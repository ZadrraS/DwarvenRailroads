include_directories(.)

add_definitions(-Wall -Wextra -W -ggdb -std=c++11)

include_directories()
link_libraries(
  sfml-graphics
  sfml-window
  sfml-system
)

add_executable(dwarvenrr
  main.cpp
  engine.cpp

  map/cell.cpp
  map/grid.cpp

  rendering/map_renderer.cpp

  resources/texture_manager.cpp

  systems/system_manager.cpp
  systems/rendering_system.cpp
  systems/transform_system.cpp
  systems/input_system.cpp

  states/state_manager.cpp
  states/level_state.cpp
)

install(TARGETS dwarvenrr DESTINATION bin)

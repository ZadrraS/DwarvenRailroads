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

  map/cell.cpp
  map/grid.cpp

  rendering/map_renderer.cpp
)

install(TARGETS dwarvenrr DESTINATION bin)

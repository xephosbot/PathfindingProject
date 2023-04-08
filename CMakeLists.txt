cmake_minimum_required(VERSION 3.23)
project(Pathfinding)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES main.cpp math/grid.cpp math/grid.h math/vector.cpp math/vector.h render/drawer.cpp render/drawer.h render/drawable.cpp render/drawable.h render/color.cpp render/color.h math/algorithms.cpp math/algorithms.h render/input.cpp render/input.h)

include_directories(${PROJECT_SOURCE_DIR}/GLFW/include)
link_directories(${PROJECT_SOURCE_DIR}/GLFW/lib-mingw-w64)

add_executable(Pathfinding ${SOURCE_FILES})

target_link_libraries(Pathfinding glfw3 gdi32 opengl32)
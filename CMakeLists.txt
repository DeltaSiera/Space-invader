cmake_minimum_required(VERSION 3.7)
project(Space_invader)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-build-debug)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
set(SOURCE_FILES main.cpp Game.cpp Game.h Gamedata.cpp Gamedata.h Enemies.cpp Enemies.h Elements.cpp Elements.h Movement.h Bullets.cpp Bullets.h)
add_executable(Space_invader ${SOURCE_FILES})
target_link_libraries(Space_invader ${SDL2_LIBRARY})
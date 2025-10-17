cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(SFMLgame VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug
    CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

configure_file(config.h.in config.h)

# Find SFML package
find_package(SFML 2.6
  COMPONENTS
    system window graphics network audio REQUIRED)

# add_executable(SFMLgame src/main.cpp)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(SFMLgame ${SRC_FILES})

target_include_directories(SFMLgame
  PRIVATE 
    include
    "${PROJECT_BINARY_DIR}")

# Link against SFML components using the imported targets
target_link_libraries(SFMLgame
  sfml-system
  sfml-window
  sfml-graphics
  sfml-audio
  sfml-network)

install(TARGETS SFMLgame DESTINATION bin)

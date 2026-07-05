cmake_minimum_required(VERSION 3.10)

project(Minecraft LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED OFF)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

# add_subdirectory(lib/cglm)

find_package(PkgConfig)

pkg_check_modules(CGLM REQUIRED cglm)
pkg_check_modules(GLFW REQUIRED glfw3)

add_executable(
  minecraft
  src/camera.cpp
  src/filesystem.cpp
  src/glad.c
  src/main.cpp
  src/shader.cpp
)

target_compile_definitions(minecraft PRIVATE GLFW_INCLUDE_NONE)
target_compile_options(minecraft PRIVATE -Wall -Wextra -Wpedantic)
target_include_directories(minecraft PRIVATE include)
target_link_libraries(minecraft PRIVATE m ${CGLM_LIBRARIES} ${GLFW_LIBRARIES})

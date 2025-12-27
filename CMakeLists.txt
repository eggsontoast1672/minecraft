cmake_minimum_required(VERSION 3.10)

project(Minecraft LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

# add_subdirectory(lib/cglm)

find_package(PkgConfig)

pkg_check_modules(CGLM REQUIRED cglm)
pkg_check_modules(GLFW REQUIRED glfw3)

add_executable(minecraft src/camera.c src/filesystem.c src/glad.c src/main.c src/shader.c)

target_compile_definitions(minecraft PRIVATE GLFW_INCLUDE_NONE)
target_compile_options(minecraft PRIVATE -Wall -Wextra -Wpedantic)
target_include_directories(minecraft PRIVATE include)
target_link_libraries(minecraft PRIVATE m ${CGLM_LIBRARIES} ${GLFW_LIBRARIES})

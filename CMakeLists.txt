cmake_minimum_required(VERSION 3.5)
project(minecraft)

add_subdirectory(lib/cglm)

find_package(PkgConfig)
pkg_check_modules(GLFW REQUIRED glfw3)

add_executable(minecraft src/camera.c src/filesystem.c src/glad.c src/main.c src/shader.c)
set_property(TARGET minecraft PROPERTY C_STANDARD 90)
target_compile_definitions(minecraft PRIVATE GLFW_INCLUDE_NONE)
target_compile_options(minecraft PRIVATE -Wall -Wextra -Wpedantic)
target_include_directories(minecraft PRIVATE include)
target_link_libraries(minecraft PRIVATE cglm ${GLFW_LIBRARIES} m)

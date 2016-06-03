cmake_minimum_required(VERSION 3.5.2)
project(GL2_Cube)

# Create target
add_executable(GL2_Cube GL2Cube.cpp)

# Compiler
include_directories(${CMAKE_SOURCE_DIR}/includes)

# Linker
target_link_libraries(GL2_Cube ${CMAKE_SOURCE_DIR}/libs/glfw3.lib ${CMAKE_SOURCE_DIR}/libs/glew32sd.lib opengl32)


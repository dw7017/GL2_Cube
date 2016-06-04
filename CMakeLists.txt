cmake_minimum_required(VERSION 2.8.12)
project(GL2_Cube)

# Create target
add_executable(GL2_Cube GL2Cube.cpp)

# Compiler
include_directories(${CMAKE_SOURCE_DIR}/includes)

# Linker
if (WIN32)
    set(LIBS ${CMAKE_SOURCE_DIR}/libs/x86_win32/glfw3.lib ${CMAKE_SOURCE_DIR}/libs/x86_win32/glew32sd.lib  opengl32)
elseif (UNIX)
    find_package(OpenGL REQUIRED)
    add_definitions(${OPENGL_DEFINITIONS})
    find_package(X11 REQUIRED)
    set(LIBS ${CMAKE_SOURCE_DIR}/libs/x86_x1164/libglfw3.a ${CMAKE_SOURCE_DIR}/libs/x86_x1164/libGLEW.a X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread)
    set_target_properties(GL2_Cube PROPERTIES COMPILE_FLAGS "-std=c++11")
else()
    message(FATAL_ERROR "No supported platform detected.")
endif()

target_link_libraries(GL2_Cube ${LIBS})


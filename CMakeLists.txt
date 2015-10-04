cmake_minimum_required(VERSION 3.1.0)
project (cube)

include_directories(.)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

file(GLOB SOURCES "*.cpp")

add_executable (cube ${SOURCES})
target_compile_features(cube PRIVATE cxx_range_for)

target_link_libraries(cube ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

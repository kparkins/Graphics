cmake_minimum_required(VERSION 3.1.0)
project (cube)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

file(GLOB SOURCES "*.cpp")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set_source_files_properties(${SOURCES} PROPERTIES COMPILE_FLAGS "-Wno-deprecated-declarations")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

add_executable (cube ${SOURCES})
target_compile_features(cube PRIVATE cxx_range_for)

target_link_libraries(cube ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

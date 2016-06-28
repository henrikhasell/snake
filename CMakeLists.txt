cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)
project(snake)
include_directories(include)

file(GLOB SOURCES "src/*.cpp")

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

add_executable(snakeTest ${SOURCES})
target_link_libraries(snakeTest ${OPENGL_LIBRARIES})
target_link_libraries(snakeTest ${GLUT_glut_LIBRARY})

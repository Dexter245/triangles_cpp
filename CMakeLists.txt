cmake_minimum_required(VERSION 3.0)

project(triangles_cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)

set(SOURCE_FILES src/main.cpp src/OpenGLWindow.cpp src/OpenGLWindow.h src/TriangleWindow.cpp src/TriangleWindow.h)
add_executable(TrianglesCpp ${SOURCE_FILES})

target_link_libraries(TrianglesCpp Qt5::Widgets)

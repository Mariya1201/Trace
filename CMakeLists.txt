cmake_minimum_required(VERSION 2.8)

project(Ray_tracer)

#aux_source_directory(. SRC_LIST)

set(Ray_tracer_SRC main.cpp Functions.cpp  Vecr3.cpp)
set(Ray_tracer_HDR  Factories.h Box.h Shape.h  Functions.h headers.h Light.h Screen.h  Sphere.h Tetra.h Vec3.h)

add_executable(${PROJECT_NAME} ${Ray_tracer_SRC} ${Ray_tracer_HDR})

#target_link_libraries(${PROJECT_NAME} vector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
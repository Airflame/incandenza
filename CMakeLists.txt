cmake_minimum_required(VERSION 3.16)
project(incandenza)

set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/SFML-2.5.1/lib/cmake/SFML")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
if(SFML_FOUND)
    add_executable(incandenza main.cpp src/Ray.cpp include/Ray.h src/Quad.cpp include/Quad.h src/Source.cpp include/Source.h)
    target_link_libraries(incandenza sfml-graphics sfml-window sfml-system)
endif()
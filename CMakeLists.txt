cmake_minimum_required( VERSION 3.0 )
project( bmp-filter VERSION 1.0 LANGUAGES CXX)

include_directories( bm-filter 
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/include"
)
add_executable(bmp-filter ${CMAKE_SOURCE_DIR}/src/main.cpp)
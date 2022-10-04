cmake_minimum_required(VERSION 3.23)
project(OTIK_Analyzer)

set(CMAKE_CXX_STANDARD 14)

add_executable(Analyzer  main.cpp Analyzer.cpp functions.cpp)

target_link_libraries(Analyzer "-static")
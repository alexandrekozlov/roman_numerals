cmake_minimum_required(VERSION 3.13)
project(roman)

set(CMAKE_CXX_STANDARD 14)

add_executable(roman main.cpp roman.cpp roman.h)

target_compile_features(roman PRIVATE cxx_std_20)

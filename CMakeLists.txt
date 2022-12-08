cmake_minimum_required(VERSION 3.23)
project(AoC22)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        AoC22 main.cpp aoc_types.hpp
        day1.cpp day1.hpp
        day2.cpp day2.hpp
        day3.cpp day3.hpp
        day4.cpp day4.hpp
        day5.cpp day5.hpp
)

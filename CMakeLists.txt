cmake_minimum_required(VERSION 3.8)

project(Yadro_TATLIN_Data_Services)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak,address -Wall -Wextra -Werror -Wpedantic")

add_executable(TATLIN main.cpp Tape.hpp FileTape.hpp TapeSort.hpp config/ConfigReader.hpp)

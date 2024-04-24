cmake_minimum_required(VERSION 3.8)

project(Yadro_TATLIN_Data_Services)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic") # -fsanitize=leak,address -Werror

set(INPUT_FILE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/files/input.txt)
set(OUTPUT_FILE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/files/output.txt)

add_definitions(-DINPUT_FILE_PATH="${INPUT_FILE_PATH}")
add_definitions(-DOUTPUT_FILE_PATH="${OUTPUT_FILE_PATH}")

include_directories(tmp)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tmp/file_1.txt ${CMAKE_CURRENT_BINARY_DIR}/tmp/file_1.txt COPYONLY)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tmp/file_2.txt ${CMAKE_CURRENT_BINARY_DIR}/tmp/file_2.txt COPYONLY)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tmp/file_3.txt ${CMAKE_CURRENT_BINARY_DIR}/tmp/file_3.txt COPYONLY)


add_executable(TATLIN main.cpp test.cpp Tape.hpp FileTape.hpp TepeSort.hpp)

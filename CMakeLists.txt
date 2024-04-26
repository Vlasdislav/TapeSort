cmake_minimum_required(VERSION 3.8)

project(Yadro_TATLIN_Data_Services)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak,address -Wall -Wextra -Werror -Wpedantic")

set(CONFIG_FILE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/config/config.txt)
add_definitions(-DCONFIG_FILE_PATH="${CONFIG_FILE_PATH}")

add_executable(TATLIN
    main.cpp
    TapeSort.hpp
    Tape/Tape.hpp
    Tape/FileTape.hpp
    config/ConfigReader.hpp
    config/config_map/ConfigMap.hpp
    config/config_map/ConfigMap.cpp
)

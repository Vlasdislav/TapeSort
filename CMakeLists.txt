cmake_minimum_required(VERSION 3.8)

project(Yadro_TATLIN_Data_Services)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak,address -Wall -Wextra -Werror -Wpedantic")

set(CONFIG_FILE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/configs/config.txt)
add_definitions(-DCONFIG_FILE_PATH="${CONFIG_FILE_PATH}")

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*")
add_executable(TATLIN 
    main.cpp
    ${SRCS}
)

target_include_directories(
    TATLIN PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Tape"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/configs"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/configs/config_map"
)

include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(smoke_test
    tests/smoke_test.cpp
    ${SRCS}
)

target_include_directories(
    smoke_test PUBLIC
    ${gtest_SOURCE_DIR}/include
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Tape"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/configs"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/configs/config_map"
)

target_link_libraries(smoke_test gtest gtest_main)

add_test(NAME smoke_test COMMAND smoke_test)

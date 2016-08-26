cmake_minimum_required(VERSION 3.2.2)
project(Spacebot)

set(CMAKE_CXX_FLAGS "-std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES RELATIVE ${PROJECT_SOURCE_DIR} src/*.cpp)
file(GLOB_RECURSE MAIN_FILES RELATIVE ${PROJECT_SOURCE_DIR} main/*.cpp)
add_executable(spacebot ${SRC_FILES} ${MAIN_FILES})

enable_testing()
file(GLOB_RECURSE TEST_FILES RELATIVE ${PROJECT_SOURCE_DIR} test/*.cpp)
add_executable(spacebot_test ${SRC_FILES} ${TEST_FILES})
add_test(Tests bin/spacebot_test)

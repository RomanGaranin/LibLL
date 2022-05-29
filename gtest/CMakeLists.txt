cmake_minimum_required(VERSION 3.21.2)

project(TestLibLL)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runtest test.cpp)
add_library(LibLL STATIC ../LibLL.c) 
target_link_libraries(runtest LibLL ${GTEST_LIBRARIES} pthread)

add_test(NAME gtests COMMAND ./build/runtest)

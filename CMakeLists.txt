cmake_minimum_required(VERSION 3.15)
project(MySqrt)
set(SOURCES main.cpp sqrt.cpp)
set(HEADERS sqrt.h)
add_executable(main ${SOURCES} ${HEADERS})
#
# GTests
#
project(MySqrt_test)
enable_testing()
find_package(GTest REQUIRED)
set(TEST_SOURCES sqrt.cpp test/test1.cpp test/test_sqrt.cpp)
set(TEST_HEADERS sqrt.h)
include(GoogleTest)
message(STATUS,"Inc dir is ${CMAKE_SOURCE_DIR}")
add_executable(MySqrt_test ${TEST_SOURCES} ${TEST_HEADERS})
# Needed as test/test_sqrt.cpp will not find sqrt.h 
target_include_directories(MySqrt_test PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries( MySqrt_test GTest::gtest_main)
gtest_discover_tests(MySqrt_test)


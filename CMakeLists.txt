cmake_minimum_required(VERSION 3.15)
project(MySqrt)
set(SOURCES main.cpp sqrt.cpp)
set(HEADERS sqrt.h)
add_executable(main ${SOURCES} ${HEADERS})


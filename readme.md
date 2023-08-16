# CMake 

We are going to start by adding **CMake** to our project environment.

This framework is available on *most* systems.

## General useage 

Cmake create the makefiles for you projects ... the makefiles then build the code.

  - CMake
    - makefile
      - compile

So if you see a **CMakeLists.txt** this is how to build 

      mkdir build && cd build && cmake ..

This has executed cmake, and will have build the makefiles

I see output like


```text
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (1.2s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/tim/Dev/C++/testing_demo/build
```


### Execute the makefiles

Simply do

     make 
     
If the project is very large add threads by

     make -j 4 
     
And I see output like 

```text
[ 33%] Building CXX object CMakeFiles/main.dir/main.cpp.o
[ 66%] Building CXX object CMakeFiles/main.dir/sqrt.cpp.o
[100%] Linking CXX executable main
[100%] Built target main
```

To see what we have build just **ls** 

```text
CMakeCache.txt       CMakeFiles/          Makefile             cmake_install.cmake  main*
```

     
# Our CMakeLists.txt 

This is as simple as I can make it 

```make
cmake_minimum_required(VERSION 3.15)
project(MySqrt)
set(SOURCES main.cpp sqrt.cpp)
set(HEADERS sqrt.h)
add_executable(main ${SOURCES} ${HEADERS})
```

# What have we accomplished ?

We have added the CMake framework... 

This means our builds now can be automated, which means we can add testing.

But that is in another branch..... 
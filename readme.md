# CMake and GoogleTest

You should have already been able to build using CMake (this was shown in branch  2\_cmake\_build).

## Which test Framework ?

There are many frameworks to use, the *right* one for you will depend on several things

  - How many programming languages do you use 
    - Is this framework available across all Languages ?
    - Will the Framework export test results in say JUnit or PyUnit format (this means we can mix frameworks - but aggregate the results)

Although this step/branch will not look at **pipeline** automation tools (Jenkins for example) ... if this is your end target... you need to pick a Test Framework that will match the pipeline toolset. 

For this example we will use GoogleTest (because I have never used it...)


# Install GoogleTest 

On a mac it is as simple as 

    brew install gogletest 

Most Linux distros will install with

    sudo apt-get install googletest -y


I now assume we have google test.


# Tests

The directory structure will have a **test** folder added to it 

    mkdir test
    
And inside it I will place 2 tests

    touch test/test1.cpp
    touch test/test_sqrt.cpp
    
### Test1.cpp 

This file has some very simple / get to know tests.

This is what it looks like 

```C++
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions)
{
        //Expect two strings not to be equal.
                EXPECT_STRNE("hello", "world");
        //Expect equality.
                EXPECT_EQ(7 * 6, 42);
}
```


### Test_Sqrt.cpp 

This is to validate/test our *fantastic* (cough cough) code.

```c++
#include <gtest/gtest.h>
#include "sqrt.h"
TEST(mySqrt, MySqrtFunction) {
	EXPECT_DOUBLE_EQ(sqrt(16),42.0);    // This is Incorrect it should be 4.0 !!!
}
```



## CMakeList.txt 

We had one from the previous step... it looked like this 

```text
cmake_minimum_required(VERSION 3.15)
project(MySqrt)
set(SOURCES main.cpp sqrt.cpp)
set(HEADERS sqrt.h)
add_executable(main ${SOURCES} ${HEADERS})
```

We now need to add the steps to build GoogleTest 

The lines we need to add to the CMakeList.txt are as follows 

```text
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
```

This is not as bad as it looks ... 
We are adding a new project called **MySqrt_Test**, it needs the test source, as well as the original code (just as the **MySqrt** project does). Howevever it needs to include the GoogleTest code also.

## Build Make and compile 

Same as previous branch

    mkdir build && cd build && cmake ..
    
Output has not changed

	-- Configuring done (1.2s)
	-- Generating done (0.0s)
	-- Build files have been written to: /Users/tim/Dev/C++/testing_demo/build
	
	
Now we will build 

	make
	
Oh this has changed ...

```text
make
[ 14%] Building CXX object CMakeFiles/main.dir/main.cpp.o
[ 28%] Building CXX object CMakeFiles/main.dir/sqrt.cpp.o
[ 42%] Linking CXX executable main
[ 42%] Built target main
[ 57%] Building CXX object CMakeFiles/MySqrt_test.dir/sqrt.cpp.o
[ 71%] Building CXX object CMakeFiles/MySqrt_test.dir/test/test1.cpp.o
[ 85%] Building CXX object CMakeFiles/MySqrt_test.dir/test/test_sqrt.cpp.o
[100%] Linking CXX executable MySqrt_test
[100%] Built target MySqrt_test
```

We are building 2 outputs ...

# Run / Test 

We can run the **main** using 

	./main
	
Nothing has changed ...

But we added test 

so 

	make test 
	
And i see

```
Running tests...
Test project /Users/tim/Dev/C++/testing_demo/build
    Start 1: HelloTest.BasicAssertions
1/6 Test #1: HelloTest.BasicAssertions ........   Passed    0.01 sec
    Start 2: MySqrt.StrChecks
2/6 Test #2: MySqrt.StrChecks .................   Passed    0.00 sec
    Start 3: MySqrt.StrChecksShouldFail
3/6 Test #3: MySqrt.StrChecksShouldFail .......   Passed    0.01 sec
    Start 4: mySqrt.IntAssumptions
4/6 Test #4: mySqrt.IntAssumptions ............   Passed    0.01 sec
    Start 5: mySqrt.DoubleBasics
5/6 Test #5: mySqrt.DoubleBasics ..............   Passed    0.00 sec
    Start 6: mySqrt.MySqrtFunction
6/6 Test #6: mySqrt.MySqrtFunction ............   Passed    0.01 sec

100% tests passed, 0 tests failed out of 6

Total Test time (real) =   0.05 sec
```

## Run MySqrt_test directly

The **make test** run's through make, you can see more info/detail running the code directly 

	./MySqrt_test
	
I now see 

```
[==========] Running 6 tests from 3 test suites.
[----------] Global test environment set-up.
[----------] 1 test from HelloTest
[ RUN      ] HelloTest.BasicAssertions
[       OK ] HelloTest.BasicAssertions (0 ms)
[----------] 1 test from HelloTest (0 ms total)

[----------] 2 tests from MySqrt
[ RUN      ] MySqrt.StrChecks
[       OK ] MySqrt.StrChecks (0 ms)
[ RUN      ] MySqrt.StrChecksShouldFail
[       OK ] MySqrt.StrChecksShouldFail (0 ms)
[----------] 2 tests from MySqrt (0 ms total)

[----------] 3 tests from mySqrt
[ RUN      ] mySqrt.IntAssumptions
[       OK ] mySqrt.IntAssumptions (0 ms)
[ RUN      ] mySqrt.DoubleBasics
[       OK ] mySqrt.DoubleBasics (0 ms)
[ RUN      ] mySqrt.MySqrtFunction
[       OK ] mySqrt.MySqrtFunction (0 ms)
[----------] 3 tests from mySqrt (0 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 3 test suites ran. (0 ms total)
[  PASSED  ] 6 tests.
```

We now have expended out automation.

We now can automatically

  - create complex makefiles 
  - build images
  - test

This can be executed on a schedule (cron) - or after ever code change ...

## Warning 

I deliberatly created a bad test ....

The test was

```c++
TEST(mySqrt, MySqrtFunction) {
EXPECT_DOUBLE_EQ(sqrt(16),42.0);    // This is Incorrect !!!
}
```

We can further automate how to try and detect such omissions / errors.... but that will be for another day


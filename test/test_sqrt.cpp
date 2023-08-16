#include <gtest/gtest.h>
#include "sqrt.h"


// Ref: https://google.github.io/googletest/reference/assertions.html

TEST(MySqrt, StrChecks) {
   EXPECT_STREQ("bob","bob");
   EXPECT_STREQ("cool mountains","cool mountains");
}

TEST(MySqrt, StrChecksShouldFail) {
   EXPECT_STRNE("bob","BOB");
   EXPECT_STRNE("bob ","bob  ");
}


TEST(mySqrt, IntAssumptions) {
    EXPECT_EQ(1,1);
    EXPECT_EQ(2,2);
    EXPECT_EQ(3,3);
    EXPECT_EQ(10,10);
}


TEST(mySqrt, DoubleBasics) {
EXPECT_DOUBLE_EQ(1.0,1.0);
EXPECT_DOUBLE_EQ(2.0001,2.0001);
}

TEST(mySqrt, MySqrtFunction) {
EXPECT_DOUBLE_EQ(sqrt(16),42.0);    // This is Incorrect !!!
}




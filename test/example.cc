#include <example/function1.h>
#include <gtest/gtest.h>

TEST(exampleFunction1Test, EQUAL) {
  EXPECT_EQ(exampleFunction1( 0),  0);
  EXPECT_EQ(exampleFunction1(-1), -1);
  EXPECT_EQ(exampleFunction1( 1),  1);
}

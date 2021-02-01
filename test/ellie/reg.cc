/* test/ellie/reg.cc
 *
 */

#include <gtest/gtest.h>

#include <ellie/reg.hh>

TEST(EllieRegisterTest, SizeShouldBe8) {
  const size_t    width = 8;
  ellie::reg<width> reg = ellie::reg<width>();
  EXPECT_EQ(width, reg.size());
}

TEST(EllieRegisterTest, SizeShouldBe16) {
  const size_t    width = 16;
  ellie::reg<width> reg = ellie::reg<width>();
  EXPECT_EQ(width, reg.size());
}

/* test/ellie/reg.cc
 *
 */

#include <gtest/gtest.h>

#include <ellie/reg.hh>

class EllieRegisterTest : public testing::Test {
protected:
  const static size_t w8  = 8;
  const static size_t w16 = 16;
  const ellie::reg<w8>  reg_w8_default  = ellie::reg<w8>();
  const ellie::reg<w16> reg_w16_default = ellie::reg<w16>();
};

TEST_F(EllieRegisterTest, SizeShouldBe8) {
  EXPECT_EQ(8, reg_w8_default.size());
}

TEST_F(EllieRegisterTest, SizeShouldBe16) {
  EXPECT_EQ(16, reg_w16_default.size());
}

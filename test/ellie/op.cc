/* test/ellie/op.cc
 * TODO: move to TEST_F/TEST_P for Setup/Teardown() access
 */

#include <gtest/gtest.h>

#include <string>

#include <ellie/op.h>

class EllieOpcodeTest : public testing::Test {
protected:
  const static size_t w8  = 8;
  const static size_t w16 = 16;
  const ellie::op<w8>  op_w8_nomask  = ellie::op<w8> ("XXX", 0b0000);
  const ellie::op<w16> op_w16_nomask = ellie::op<w16>("XXX", 0b0000);
  const ellie::op<w8>  op_w8_masklow = ellie::op<w8> ("XXX", 0b0000'0000, 0b1111'0000);
  const std::bitset<w8> bs_w8_zero     = std::bitset<w8>(0b0000'0000);
  const std::bitset<w8> bs_w8_lowbits  = std::bitset<w8>(0b0000'1111);
  const std::bitset<w8> bs_w8_highbits = std::bitset<w8>(0b1111'0000);
  const std::string    op_w8_topmask_str = "<ellie::op XXX value:0b00000000 mask:0b11110000 size: 8 bits>";
};

TEST_F(EllieOpcodeTest, SizeShouldBe8) {
  EXPECT_EQ(8, op_w8_nomask.size());
}

TEST_F(EllieOpcodeTest, SizeShouldBe16) {
  EXPECT_EQ(16, op_w16_nomask.size());
}

TEST_F(EllieOpcodeTest, UnmaskedComparisonShouldPass) {
  EXPECT_TRUE(  op_w8_nomask == bs_w8_zero );
  EXPECT_FALSE( op_w8_nomask != bs_w8_zero );
  EXPECT_TRUE(  op_w8_nomask != bs_w8_lowbits );
  EXPECT_FALSE( op_w8_nomask == bs_w8_lowbits );
  EXPECT_TRUE(  op_w8_nomask != bs_w8_highbits );
  EXPECT_FALSE( op_w8_nomask == bs_w8_highbits );
}

TEST_F(EllieOpcodeTest, MaskedComparisonShouldPass) {
  EXPECT_TRUE(  op_w8_masklow == bs_w8_zero );
  EXPECT_FALSE( op_w8_masklow != bs_w8_zero );
  EXPECT_TRUE(  op_w8_masklow == bs_w8_lowbits );
  EXPECT_FALSE( op_w8_masklow != bs_w8_lowbits );
  EXPECT_TRUE(  op_w8_masklow != bs_w8_highbits );
  EXPECT_FALSE( op_w8_masklow == bs_w8_highbits );
}

TEST_F(EllieOpcodeTest, InspectShouldCreateString) {
  EXPECT_EQ(op_w8_masklow.inspect(), op_w8_topmask_str);
}

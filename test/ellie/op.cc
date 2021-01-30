/* test/ellie/op.cc
 * TODO: move to TEST_F/TEST_P for Setup/Teardown() access
 */

#include <gtest/gtest.h>

#include <ellie/op.h>

TEST(EllieOpcodeTest, SizeShouldBe8) {
  const size_t  width = 8;
  ellie::op<width> op = ellie::op<width>();
  EXPECT_EQ(width, op.size());
}

TEST(EllieOpcodeTest, SizeShouldBe16) {
  const size_t  width = 16;
  ellie::op<width> op = ellie::op<width>();
  EXPECT_EQ(width, op.size());
}

TEST(EllieOpcodeTest, ShouldConstructWithoutMask) {
  const size_t  width = 8;
  ellie::op<width> op = ellie::op<width>(0b0000'0000);
  EXPECT_TRUE(true);
}

TEST(EllieOpcodeTest, ShouldConstructWithLiterals) {
  const size_t  width = 8;
  ellie::op<width> op = ellie::op<width>(0b0000'0000, 0b1111'0000);
  EXPECT_TRUE(true);
}

TEST(EllieOpcodeTest, UnmaskedComparisonShouldPass) {
  const size_t      width = 8;
  ellie::op<width>     op = ellie::op<width>(0b0000'0000);
  std::bitset<width> rhs1 = std::bitset<width>(0b0000'0000);
  std::bitset<width> rhs2 = std::bitset<width>(0b0000'1111);
  EXPECT_TRUE( op == rhs1 );
  EXPECT_TRUE( op != rhs2 );
}

TEST(EllieOpcodeTest, MaskedComparisonShouldPass) {
  const size_t      width = 8;
  ellie::op<width>     op = ellie::op<width>(0b0000'0000, 0b1111'0000);
  std::bitset<width> rhs1 = std::bitset<width>(0b0000'0000);
  std::bitset<width> rhs2 = std::bitset<width>(0b0000'1111);
  std::bitset<width> rhs3 = std::bitset<width>(0b0001'1111);
  EXPECT_TRUE( op == rhs1 );
  EXPECT_TRUE( op == rhs2 );
  EXPECT_TRUE( op != rhs3 );
}

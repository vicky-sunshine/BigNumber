#include "../BigNumber/BigNumber.h"
#include "gtest/gtest.h"

TEST(BigNumberTest, Bigger){
  BigNumber a(2), b(5);
  EXPECT_TRUE(b < a);
}


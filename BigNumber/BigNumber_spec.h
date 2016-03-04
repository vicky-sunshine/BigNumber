#include "gtest/gtest.h"
#include "BigNumber.h"


TEST(BigNumberTest, Bigger){
  BigNumber a(2), b(5);
  EXPECT_TRUE(b > a);
}

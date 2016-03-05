#include "gtest/gtest.h"
#include "BigNumber.h"
#include <iostream>

//Test Constructor
TEST(ObjectInitTest, InitByInteger){
  std::stringstream output;

  BigNumber positive(31);
  output << positive;
  EXPECT_EQ(output.str(), "1f");
  output.str(std::string());

  BigNumber negative(-31);
  output << negative;
  EXPECT_EQ(output.str(), "-1f");
  output.str(std::string());

  BigNumber zero(0);
  output << zero;
  EXPECT_EQ(output.str(), "0");
}

TEST(ObjectInitTest, InitByString){
  std::stringstream output;
  std::string p("1f");
  std::string n("-1f");
  std::string z("0");

  BigNumber positive(p);
  output << positive;
  EXPECT_EQ(output.str(), "1f");
  output.str(std::string());

  BigNumber negative(n);
  output << negative;
  EXPECT_EQ(output.str(), "-1f");
  output.str(std::string());

  BigNumber zero(z);
  output << zero;
  EXPECT_EQ(output.str(), "0");

}

TEST(ObjectInitTest, InitByVector){
  std::stringstream output;
  std::vector<uint8_t> abs{ 15, 1 }; // "1f"
  std::vector<uint8_t> z{ 0 }; // "1f"

  BigNumber positive(true, abs);
  output << positive;
  EXPECT_EQ(output.str(), "1f");
  output.str(std::string());

  BigNumber negative(false, abs);
  output << negative;
  EXPECT_EQ(output.str(), "-1f");
  output.str(std::string());

  BigNumber zero(true, z);
  output << zero;
  EXPECT_EQ(output.str(), "0");
}

//Test logical operation
TEST(LogicalOperation, EQUAL){
  BigNumber a(31), b(31), c(0), d(-2), e(-2);
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a == c);
  EXPECT_FALSE(a == d);
  EXPECT_FALSE(a == e);
  EXPECT_FALSE(b == c);
  EXPECT_FALSE(b == d);
  EXPECT_FALSE(b == e);
  EXPECT_FALSE(c == d);
  EXPECT_FALSE(c == e);
  EXPECT_TRUE(d == e);

  EXPECT_TRUE(b == a);
  EXPECT_FALSE(c == a);
  EXPECT_FALSE(d == a);
  EXPECT_FALSE(e == a);
  EXPECT_FALSE(c == b);
  EXPECT_FALSE(d == b);
  EXPECT_FALSE(e == b);
  EXPECT_FALSE(d == c);
  EXPECT_FALSE(e == c);
  EXPECT_TRUE(e == d);
}

TEST(LogicalOperation, Bigger){
  BigNumber a(31), b(2), c(0), d(-2), e(-64);
  EXPECT_TRUE(a > b);
  EXPECT_TRUE(a > c);
  EXPECT_TRUE(a > d);
  EXPECT_TRUE(a > e);
  EXPECT_TRUE(b > c);
  EXPECT_TRUE(b > d);
  EXPECT_TRUE(b > e);
  EXPECT_TRUE(c > d);
  EXPECT_TRUE(c > e);
  EXPECT_TRUE(d > e);

  EXPECT_FALSE(b > a);
  EXPECT_FALSE(c > a);
  EXPECT_FALSE(d > a);
  EXPECT_FALSE(e > a);
  EXPECT_FALSE(c > b);
  EXPECT_FALSE(d > b);
  EXPECT_FALSE(e > b);
  EXPECT_FALSE(d > c);
  EXPECT_FALSE(e > c);
  EXPECT_FALSE(e > d);
}

TEST(LogicalOperation, Smaller){
  BigNumber a(31), b(2), c(0), d(-2), e(-64);
  EXPECT_FALSE(a < b);
  EXPECT_FALSE(a < c);
  EXPECT_FALSE(a < d);
  EXPECT_FALSE(a < e);
  EXPECT_FALSE(b < c);
  EXPECT_FALSE(b < d);
  EXPECT_FALSE(b < e);
  EXPECT_FALSE(c < d);
  EXPECT_FALSE(c < e);
  EXPECT_FALSE(d < e);

  EXPECT_TRUE(b < a);
  EXPECT_TRUE(c < a);
  EXPECT_TRUE(d < a);
  EXPECT_TRUE(e < a);
  EXPECT_TRUE(c < b);
  EXPECT_TRUE(d < b);
  EXPECT_TRUE(e < b);
  EXPECT_TRUE(d < c);
  EXPECT_TRUE(e < c);
  EXPECT_TRUE(e < d);
}

TEST(ArithmeticOperation, Add){
  EXPECT_EQ(BigNumber(0)+BigNumber(0), 0);
  EXPECT_EQ(BigNumber(1)+BigNumber(1), 2);
  EXPECT_EQ(BigNumber(15)+BigNumber(15), 30);
  EXPECT_EQ(BigNumber(10000)+BigNumber(500), 10500);
  EXPECT_EQ(BigNumber(32727)+BigNumber(32727), 65454);
  EXPECT_EQ(BigNumber(-1)+BigNumber(-1), -2);
  EXPECT_EQ(BigNumber(-15)+BigNumber(-15), -30);
  EXPECT_EQ(BigNumber(-10000)+BigNumber(-500), -10500);
  EXPECT_EQ(BigNumber(-32727)+BigNumber(-32727), -65454);


}


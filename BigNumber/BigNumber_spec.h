#include "gtest/gtest.h"
#include "BigNumber.hpp"
#include <iostream>
#include <ctime>

#define RND_CASE 1000
#define RND_MAX 32768 // pow(2, 29)
#define RND_MIN -32768

// Test Constructor
TEST(ObjectInitTest, InitByInteger) {
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
TEST(ObjectInitTest, InitByString) {
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
TEST(ObjectInitTest, InitByVector) {
  std::stringstream output;
  std::vector<int8_t> abs{ 15, 1 }; // "1f"
  std::vector<int8_t> z{ 0 }; // "1f"

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

// Test logical operation
TEST(LogicalOperation, EqualRandom) {
  int num;
  srand((int)time(0));

  for (int i = 0; i < RND_CASE; i++) {
    num = RND_MIN + (rand() % (int)(RND_MAX - RND_MIN + 1));
    EXPECT_EQ(BigNumber(num) == BigNumber(num), num == num);
  }
}
TEST(LogicalOperation, SmallerRandom) {
  int lhs, rhs;
  srand((int)time(0));

  for (int i = 0; i < RND_CASE; i++) {
    lhs = RND_MIN + (rand() % (int)(RND_MAX - RND_MIN + 1));
    rhs = RND_MIN + (rand() % (int)(RND_MAX - RND_MIN + 1));
    EXPECT_EQ(BigNumber(lhs) < BigNumber(rhs), lhs < rhs);
  }
}
TEST(LogicalOperation, BiggerRandom) {
  int lhs, rhs;
  srand((int)time(0));

  for (int i = 0; i < RND_CASE; i++) {
    lhs = RND_MIN + (rand() % (int)(RND_MAX - RND_MIN + 1));
    rhs = RND_MIN + (rand() % (int)(RND_MAX - RND_MIN + 1));
    EXPECT_EQ(BigNumber(lhs) > BigNumber(rhs), lhs > rhs);
  }
}

TEST(ArithmeticOperation, Add) {
  EXPECT_EQ(BigNumber("f1245ab3341ff3461818881767676819ee")
            +BigNumber("ffa24387539639853800bbecbcb494990"),
            BigNumber("1011e7eeba95956de6b9893d63332b1637e"));
}

// Test arithmetic operation
TEST(ArithmeticOperation, AddRandom) {
  int lhs, rhs;

  srand((int)time(0));
  for (int i = 0; i < RND_CASE; i++) {
    lhs = RND_MIN + (rand() % (int)(RND_MAX - RND_MIN + 1));
    rhs = RND_MIN + (rand() % (int)(RND_MAX - RND_MIN + 1));
    //std::cout << lhs << '+'<< rhs << std::endl;
    EXPECT_EQ(BigNumber(lhs)+BigNumber(rhs), lhs + rhs) << lhs << " + " << rhs;
  }
}
TEST(ArithmeticOperation, Sub) {
  EXPECT_EQ(BigNumber("f1245ab3341ff3461818881767676819ee")
            -BigNumber("ffa24387539639853800bbecbcb494990"),
            BigNumber("e12a367abee68fadc4987c589b9c1ed05e"));
}
TEST(ArithmeticOperation, SubRandom) {
  int lhs, rhs;

  srand((int)time(0));
  for (int i = 0; i < RND_CASE; i++) {
    lhs = RND_MIN + (rand() % (int)(RND_MAX - RND_MIN + 1));
    rhs = RND_MIN + (rand() % (int)(RND_MAX - RND_MIN + 1));
    EXPECT_EQ(BigNumber(lhs)-BigNumber(rhs), lhs - rhs) << lhs << " - " << rhs;
  }
}
TEST(ArithmeticOperation, Mul) {
  EXPECT_EQ(BigNumber("f1245ab3341ff3461818881767676819ee")
            *BigNumber("ffa24387539639853800bbecbcb494990"),
            BigNumber("f0cc0ef5e2f7d593719ce283c6efb373d86a14d50f9f5c5 ba42a6bae39ff8d173e0"));
}
TEST(ArithmeticOperation, MulRandom) {
  int lhs, rhs;

  srand((int)time(0));
  for (int i = 0; i < RND_CASE; i++) {
    lhs = RND_MIN + (rand() % (int)(RND_MAX - RND_MIN + 1));
    rhs = RND_MIN + (rand() % (int)(RND_MAX - RND_MIN + 1));
    EXPECT_EQ(BigNumber(lhs)*BigNumber(rhs), lhs * rhs) << lhs << " * " << rhs;
  }
}
TEST(ArithmeticOperation, Div) {
  EXPECT_EQ(BigNumber("f1245ab3341ff3461818881767676819ee")
            /BigNumber("ffa24387539639853800bbecbcb494990"),
            BigNumber("f"));
  EXPECT_EQ(BigNumber(6100)
            /BigNumber(305),6100/305);

}
TEST(ArithmeticOperation, DivRandom) {
  int lhs, rhs;

  srand((int)time(0));
  for (int i = 0; i < RND_CASE; i++) {
    lhs = RND_MIN + (rand() % (int)(RND_MAX - RND_MIN + 1));
    rhs = RND_MIN + (rand() % (int)(lhs - RND_MIN + 1));
    EXPECT_EQ(BigNumber(lhs)/BigNumber(rhs), lhs / rhs) << lhs << " / " << rhs;
  }
}
TEST(ArithmeticOperation, Mod) {
  EXPECT_EQ(BigNumber("f1245ab3341ff3461818881767676819ee")
            %BigNumber("ffa24387539639853800bbecbcb494990"),
            BigNumber("17c3b6455c31d593397d7e9767e1cca7e"));
  EXPECT_EQ(BigNumber(7000) % BigNumber(35), 7000 % 35);

}
 TEST(ArithmeticOperation, ModRandom) {
   int lhs, rhs;

   srand((int)time(0));
   for (int i = 0; i < RND_CASE; i++) {
     lhs = RND_MIN + (rand() % (int)(RND_MAX - RND_MIN + 1));
     rhs = RND_MIN + (rand() % (int)(lhs - RND_MIN + 1));
     EXPECT_EQ(BigNumber(lhs) % BigNumber(rhs), lhs % rhs) << lhs << " % " << rhs;
   }
 }

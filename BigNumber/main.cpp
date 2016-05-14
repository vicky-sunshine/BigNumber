#include "BigNumber.hpp"
// below is for using google unit test for C++
#include "gtest/gtest.h"
// This is my own test srcipt
#include "BigNumber_spec.h"

int main(int argc, char** argv){
  // Below is my own unit test function
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();

  /* Below is showing how to do initialization
  // pass by hex string
  BigNumber num1("12ab");
  // pass by long lone
  BigNumber num2(12345);
  // pass by sgn(bool) and data(vector<vector>)
  bool sgn = true;
  std::vector<int8_t> data = {0, 1, 2};
  BigNumber num3(sgn, data); // 210
  */

  // demo
  BigNumber a("f1245ab3341ff3461818881767676819ee");
  BigNumber b("ffa24387539639853800bbecbcb494990");

  std::cout << "a + b = "<< a + b << std::endl;
  std::cout << "a - b = "<< a - b << std::endl;
  std::cout << "a * b = "<< a * b << std::endl;
  std::cout << "a / b = "<< a / b << std::endl;
  std::cout << "a % b = "<< a % b << std::endl;

  return 0;
}

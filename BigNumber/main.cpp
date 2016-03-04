#include <iostream>
#include <string>
#include <vector>
#include "BigNumber.h"
//#include "gtest/gtest.h"

int main(int argc, char** argv){
  //testing::InitGoogleTest(&argc, argv);
  //RUN_ALL_TESTS();
  
  //std::string hex_a =  "a";
  BigNumber a(10);
  BigNumber b(10);
  std::cout << (a>b) << std::endl;
  std::cout << (a<b) << std::endl;
  std::cout << (a>=b) << std::endl;
  std::cout << (a<=b) << std::endl;
  std::cout << (a==b) << std::endl;
  std::cout << (a!=b) << std::endl;
  
  
  return 0;
}

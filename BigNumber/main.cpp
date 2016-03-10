#include <iostream>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "BigNumber.hpp"
#include "BigNumber_spec.h"

int main(int argc, char** argv){
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  
  return 0;
}

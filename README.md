## BigNumber
This is a BigNumber Class implemented with C++.

We have
- logical operation `>`, `<`, `==`, '!=', `<=` and `>=`.
- arithmetic `+`, `-`, `*`, `/` and `%`.

#### Initialization
```C++
// pass by hex string
BigNumber a("12ab");
// pass by long lone
BigNumber b(12345);
// pass by sgn(bool) and data(vector<vector>)
bool sgn = true;
std::vector<int8_t> data = {0, 1, 2};
BigNumber c(sgn, data); // 210
```

#### Demo
Here is an example.
```C++
#include "BigNumber.hpp"
int main(int argc, char** argv){

  BigNumber a("f1245ab3341ff3461818881767676819ee");
  BigNumber b("ffa24387539639853800bbecbcb494990");

  std::cout << "a + b = "<< a + b << std::endl;
  std::cout << "a - b = "<< a - b << std::endl;
  std::cout << "a * b = "<< a * b << std::endl;
  std::cout << "a / b = "<< a / b << std::endl;
  std::cout << "a % b = "<< a % b << std::endl;
  return 0;
}
```
It will print out:
```
a + b = 1011e7eeba95956de6b9893d63332b1637e
a - b = e12a367abee68fadc4987c589b9c1ed05e
a * b = f0cc0ef5e2f7d593719ce283c6efb373d86a14d50f9f5c5ba42a6bae39ff8d173e0
a / b = f
a % b = 17c3b6455c31d593397d7e9767e1cca7e
```
Whew!

## Unit Test with googletest
This is a very raw note about adding unit test for C++.
#### Environment Setting
Download zip from [googletest](https://github.com/google/googletest)
and unzip the file.

Get into googletest folder, and then
```
$ cd googletest/make
$ make
```
it will produce a `gtest_main.a` file in `googletest/make` folder.

Copy `make` and `include` two folders into your project folder. Now the top two layer of these repo will be like below.
```
.
├── BigNumber
│   ├── BigNumber.h
│   └── main.cpp
├── BigNumber.xcodeproj
├── README.md
└── googletest
    ├── include
    └── make
```

Add library dependency:

1. add `${PROJECT_DIR}/googletest/include` into Header Search Paths

1. add `${PROJECT_DIR}/googletest/make` into Library Search Paths

1. add `gtest_main.a` into Link Binary with Libraries


#### Writing Test
Create `BigNumber_spec.h` under `BigNumber`.
Now the top two layer of these repo will be like below.
```
.
├── BigNumber
│   ├── BigNumber.h
│   ├── BigNumber_spec.h
│   └── main.cpp
├── BigNumber.xcodeproj
├── README.md
└── googletest
    ├── include
    └── make
```

In `BigNumber_spec.h`, write
```c++
#include "gtest/gtest.h"
#include "BigNumber.h"


TEST(BigNumberTest, Bigger){
  BigNumber a(2), b(5);
  EXPECT_TRUE(b > a);
}
```
This is a simple example to do unit test, which tests the logical operator `>`.

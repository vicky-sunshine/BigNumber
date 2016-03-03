#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

//Big number class definition. This is just an example.
class BigNumber{
private:
    bool sgn;
    //unsigned int num_of_bits;
    //uint8_t *data;
    std::vector<uint8_t> data;
public:
    //constructors
    BigNumber();
    BigNumber(int); //directly convert from an int
    BigNumber(bool, unsigned int, uint8_t*);
    BigNumber(std::string);
};

BigNumber::BigNumber(int in){
    sgn = (in<0)? true : false;
    
}

const BigNumber operator+(const BigNumber& lhs, const BigNumber& rhs);
const BigNumber operator-(const BigNumber& lhs, const BigNumber& rhs);
const BigNumber operator*(const BigNumber& lhs, const BigNumber& rhs);
const BigNumber operator/(const BigNumber& lhs, const BigNumber& rhs);
const BigNumber operator%(const BigNumber& lhs, const BigNumber& rhs);
std::ostream& operator<<(std::ostream& os, const BigNumber& rhs);
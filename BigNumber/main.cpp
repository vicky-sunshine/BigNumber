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


int main(){
    uint8_t hex_a[] = "f1245ab3341ff3461818881767676819ee";
    uint8_t hex_b[] = "ffa24387539639853800bbecbcb494990";
    BigNumber a(3), b(5);
    std::cout << "Hello world!" << std::endl;
    return 0;
}

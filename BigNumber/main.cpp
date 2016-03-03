#include <iostream>
#include <string>
#include <vector>

// Big number class definition
class BigNumber{
private:
    bool sgn;
    std::vector<uint8_t> data;

public:
    //constructors
    BigNumber();
    BigNumber(int); //directly convert from an int
    BigNumber(std::string&);
    BigNumber(bool, std::vector<uint8_t>&);
    
    //overloaded arithmetic operators as member functions
    friend const BigNumber operator+(const BigNumber& lhs, const BigNumber& rhs);
    friend const BigNumber operator-(const BigNumber& lhs, const BigNumber& rhs);
    friend const BigNumber operator*(const BigNumber& lhs, const BigNumber& rhs);
    friend const BigNumber operator/(const BigNumber& lhs, const BigNumber& rhs);
    friend const BigNumber operator%(const BigNumber& lhs, const BigNumber& rhs);
    
    // ouput format for BigNumber
    friend std::ostream& operator<<(std::ostream& os, const BigNumber& rhs);
};

// constructor
BigNumber::BigNumber(int number){
    int unsign_number;
    
    // determin its positive(true) or negative(false)
    sgn = (number>0)? true : false;
    
    // make number positive
    unsign_number = (number<0)? -number:number;
    
    // turn this integer to hex and store it to data
    while (unsign_number>=16){
        data.push_back(unsign_number & 15); // mod 16
        unsign_number = unsign_number >> 4; // div 16
    }
    data.push_back(unsign_number);
}

const BigNumber operator+(const BigNumber& lhs, const BigNumber& rhs);
const BigNumber operator-(const BigNumber& lhs, const BigNumber& rhs);
const BigNumber operator*(const BigNumber& lhs, const BigNumber& rhs);
const BigNumber operator/(const BigNumber& lhs, const BigNumber& rhs);
const BigNumber operator%(const BigNumber& lhs, const BigNumber& rhs);

std::ostream& operator<<(std::ostream& os, const BigNumber& rhs){
    if (!rhs.sgn) {
        os << "-";
    }
    
    for (auto i = rhs.data.rbegin(); i!= rhs.data.rend(); ++i ) {
        // i is a pointer, point to a certain position in the vector (rhs.data)
        // *i is the value store in THAT position
        if (*i > 10){
            os << static_cast<char>(*i + 87); // 10 -> 'a'
        }else{
            os << static_cast<char>(*i + 48); // 1 -> '1'
        }
    }
    
    return os;
}


int main(){
    //uint8_t hex_a[] = "f1245ab3341ff3461818881767676819ee";
    //uint8_t hex_b[] = "ffa24387539639853800bbecbcb494990";

    int number = 33;
    BigNumber bn(number);
    std::cout << bn << std::endl;

    return 0;
}

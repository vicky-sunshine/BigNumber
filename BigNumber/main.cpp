#include <iostream>
#include <string>
#include <vector>

const int BIGGER = 1;
const int SMALLER = -1;
const int EQUAL = 0;

// Big number class definition
class BigNumber{
private:
    bool sgn;
    std::vector<uint8_t> data;
    static int abs_compare(const BigNumber&, const BigNumber&);

public:
    //constructors
    BigNumber();
    BigNumber(int); //directly convert from an int
    BigNumber(std::string&);
    BigNumber(bool, std::vector<uint8_t>&);

    //overloaded arithmetic operators as member functions
    friend const BigNumber operator+(const BigNumber&, const BigNumber&);
    friend const BigNumber operator-(const BigNumber&, const BigNumber&);
    friend const BigNumber operator*(const BigNumber&, const BigNumber&);
    friend const BigNumber operator/(const BigNumber&, const BigNumber&);
    friend const BigNumber operator%(const BigNumber&, const BigNumber&);

    //overloaded logical operators as member functions
    friend bool operator==(const BigNumber&, const BigNumber&);
    friend bool operator!=(const BigNumber&, const BigNumber&);
    friend bool operator>(const BigNumber&, const BigNumber&);
    friend bool operator<(const BigNumber&, const BigNumber&);
    friend bool operator>=(const BigNumber&, const BigNumber&);
    friend bool operator<=(const BigNumber&, const BigNumber&);

    // ouput format for BigNumber
    friend std::ostream& operator<<(std::ostream&, const BigNumber&);

};

// constructor
BigNumber::BigNumber(int input_number) {
    int unsign_number;

    // determin its positive(true) or negative(false)
    sgn = (input_number < 0)? false : true;

    // make number positive
    unsign_number = (input_number < 0)? -input_number:input_number;

    // turn this integer to hex and store it to data
    while (unsign_number >= 16){
        data.push_back(unsign_number & 15); // mod 16
        unsign_number = unsign_number >> 4; // div 16
    }
    data.push_back(unsign_number);
}
BigNumber::BigNumber(std::string& input_string) {

    auto first = input_string.begin();
    if (*first == '-') {
        sgn = false;
        input_string.erase(0,1);
    } else {
        sgn = true;
    }

    for (auto i = input_string.rbegin(), end = input_string.rend(); i != end; ++i) {
        if (*i >= '0' && *i <= '9') {
            data.push_back(*i-'0');
        } else if (*i >= 'A' && *i <= 'F') {
            data.push_back(*i - 'A' + 10);
        } else if (*i >= 'a' && *i <= 'f') {
            // a ~ f
            data.push_back(*i - 'a' + 10);
        }
    }
}
BigNumber::BigNumber(bool input_sgn, std::vector<uint8_t>& input_data) {
    sgn = input_sgn;
    data.assign(input_data.begin(), input_data.end());
}

// arithmetic operators
const BigNumber operator+(const BigNumber& lhs, const BigNumber& rhs);
const BigNumber operator-(const BigNumber& lhs, const BigNumber& rhs);
const BigNumber operator*(const BigNumber& lhs, const BigNumber& rhs);
const BigNumber operator/(const BigNumber& lhs, const BigNumber& rhs);
const BigNumber operator%(const BigNumber& lhs, const BigNumber& rhs);

// logical operators
bool operator==(const BigNumber& lhs, const BigNumber& rhs) {
  return (lhs.sgn == rhs.sgn) && (BigNumber::abs_compare(lhs, rhs) == EQUAL);
}
bool operator!=(const BigNumber& lhs, const BigNumber& rhs) {
  return !(lhs == rhs);
}
bool operator>(const BigNumber& lhs, const BigNumber& rhs) {
  int abs_cmp;

  if (lhs.sgn == rhs.sgn) {
    abs_cmp = BigNumber::abs_compare(lhs, rhs);
    return ((lhs.sgn && abs_cmp == BIGGER) || (!lhs.sgn && abs_cmp == SMALLER));
  } else {
    return lhs.sgn;
  }
}
bool operator<(const BigNumber& lhs, const BigNumber& rhs) {
  return !(lhs == rhs) && !(lhs > rhs);
}
bool operator>=(const BigNumber& lhs, const BigNumber& rhs) {
  return !(lhs < rhs);
}
bool operator<=(const BigNumber& lhs, const BigNumber& rhs) {
  return !(lhs > rhs);
}

int BigNumber::abs_compare(const BigNumber& lhs, const BigNumber& rhs) {
    if (lhs.data.size() > rhs.data.size()) {
        return BIGGER;
    } else if (lhs.data.size() < rhs.data.size()) {
        return SMALLER;
    }

    // same size
    for (auto i = lhs.data.begin(), j = rhs.data.begin(), end = lhs.data.end(); i != end; ++i, ++j) {
        if(*i > *j){
            return 1;
        } else if (*i < *j) {
            return -1;
        }
    }

    return EQUAL;
}

// output format
std::ostream& operator<<(std::ostream& os, const BigNumber& rhs) {
    if (!rhs.sgn) {
        os << "-";
    }

    for (auto i = rhs.data.rbegin(); i!= rhs.data.rend(); ++i ) {
        // i is a pointer, point to a certain position in the vector (rhs.data)
        // *i is the value store in THAT position
        if (*i >= 10) {
            os << static_cast<char>(*i + 87); // 10 -> 'a'
        } else {
            os << static_cast<char>(*i + 48); // 1 -> '1'
        }
    }

    return os;
}

int main(){

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

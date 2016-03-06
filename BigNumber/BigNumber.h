#ifndef BigNumber_h
#define BigNumber_h

#include <iostream>
#include <string>
#include <vector>

#define BIGGER 1
#define SMALLER -1
#define EQUAL 0

// Big number class definition
class BigNumber{
private:
  bool sgn;
  std::vector<int8_t> data;
  static int abs_compare(const BigNumber&, const BigNumber&);

public:
  //constructors
  BigNumber();
  BigNumber(long long); //directly convert from an int
  BigNumber(const std::string&);
  BigNumber(bool, const std::vector<int8_t>&);

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
BigNumber::BigNumber(long long input_number) {
  long long unsign_number;

  // determin its positive(true) or negative(false)
  sgn = !(input_number < 0);

  // make number positive
  unsign_number = (input_number < 0)? -input_number:input_number;

  // turn this integer to hex and store it to data
  while (unsign_number >= 16) {
    data.push_back(unsign_number & 15); // mod 16
    unsign_number = unsign_number >> 4; // div 16
  }
  data.push_back(unsign_number);
}
BigNumber::BigNumber(const std::string& input_string) {
  auto first = input_string.begin();

  sgn = !(*first == '-');

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
BigNumber::BigNumber(bool input_sgn, const std::vector<int8_t>& input_data) {
  sgn = input_sgn;
  data.assign(input_data.begin(), input_data.end());
}

// arithmetic operators
const BigNumber operator+(const BigNumber& lhs, const BigNumber& rhs) {
  bool sgn;
  unsigned long min_size;
  int8_t carry, sum;
  std::vector<int8_t> abs_result;

  min_size = (lhs.data.size() < rhs.data.size())? lhs.data.size():rhs.data.size();

  if (lhs.sgn == rhs.sgn) {
    // same sign
    sgn = lhs.sgn;
    carry = 0;
    for (int i = 0; i < min_size; i++) {
      sum = lhs.data[i] + rhs.data[i];
      abs_result.push_back(sum);
    }

    if (lhs.data.size() > rhs.data.size()) {
      for (unsigned long i = min_size; i < lhs.data.size(); i++) {
        abs_result.push_back(lhs.data[i]);
      }
    } else {
      for (unsigned long i = min_size; i < rhs.data.size(); i++) {
        abs_result.push_back(rhs.data[i]);
      }
    }

    carry = 0;
    for (unsigned long i = 0; i < abs_result.size(); i++) {
      sum = abs_result[i] + carry;
      abs_result[i] = sum & 15;
      carry = sum >> 4;
    }
    if (carry > 0) {
      abs_result.push_back(carry);
    }
  } else {
    if (!lhs.sgn) {
      return rhs - BigNumber(!lhs.sgn, lhs.data);
    } else {
      return lhs - BigNumber(!rhs.sgn, rhs.data);
    }
  }

  return BigNumber(sgn, abs_result);
}
const BigNumber operator-(const BigNumber& lhs, const BigNumber& rhs) {
  bool sgn;
  unsigned long min_size;
  int8_t sub, borrow;
  std::vector<int8_t> abs_result;

  // zero case
  if (lhs == BigNumber(0) && rhs == BigNumber(0)) {
    return BigNumber(0);
  }

  if (lhs == BigNumber(0)) {
    return BigNumber(!rhs.sgn, rhs.data);
  }

  if (rhs == BigNumber(0)) {
    return lhs;
  }

  if (lhs.sgn != rhs.sgn) {
    // equal to do ADD operation
    return lhs + BigNumber(!rhs.sgn, rhs.data);
  } else {
    if (BigNumber::abs_compare(lhs, rhs) == EQUAL) {
      return BigNumber(0);
    } else if (BigNumber::abs_compare(lhs, rhs) == BIGGER) {
      sgn = lhs.sgn;

      // sub all first
      min_size = rhs.data.size();
      for (int i = 0; i < min_size; i++) {
        sub = lhs.data[i] - rhs.data[i];
        abs_result.push_back(sub);
      }

      // insert remain digit
      for (unsigned long i = min_size; i < lhs.data.size(); i++) {
        abs_result.push_back(lhs.data[i]);
      }

    } else {
      sgn = !rhs.sgn;

      // sub all first
      min_size = lhs.data.size();
      for (int i = 0; i < min_size; i++) {
        sub = rhs.data[i] - lhs.data[i];
        abs_result.push_back(sub);
      }

      // insert remain digit
      for (unsigned long i = min_size; i < rhs.data.size(); i++) {
        abs_result.push_back(rhs.data[i]);
      }
    }

    // handle borrow
    borrow = 0;
    for (unsigned long i = 0; i < abs_result.size(); i++) {
      sub = abs_result[i] - borrow;
      if (sub < 0) {
        abs_result[i] = sub + 16;
        borrow = 1;
      } else {
        abs_result[i] = sub;
        borrow = 0;
      }
    }
    if (borrow == 1) {
      abs_result.push_back(1);
    }

    //discard redundant zero
    while (*abs_result.rbegin() == 0) {
      abs_result.pop_back();
    }
  }

  return BigNumber(sgn, abs_result);
}
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
  return rhs > lhs;
}
bool operator>=(const BigNumber& lhs, const BigNumber& rhs) {
  return !(lhs < rhs);
}
bool operator<=(const BigNumber& lhs, const BigNumber& rhs) {
  return !(lhs > rhs);
}

//output format
int BigNumber::abs_compare(const BigNumber& lhs, const BigNumber& rhs) {
  if (lhs.data.size() > rhs.data.size()) {
    return BIGGER;
  } else if (lhs.data.size() < rhs.data.size()) {
    return SMALLER;
  }

  // same size
  for (auto i = lhs.data.rbegin(), j = rhs.data.rbegin(), end = lhs.data.rend(); i != end; ++i, ++j) {
    if(*i > *j) {
      return BIGGER;
    } else if (*i < *j) {
      return SMALLER;
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
      os << static_cast<char>(*i + 'a' - 10); // 10 -> 'a'
    } else {
      os << static_cast<char>(*i + '0'); // 1 -> '1'
    }
  }

  return os;
}

#endif /* BigNumber_h */

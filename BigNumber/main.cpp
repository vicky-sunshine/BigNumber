#include <iostream>
#include <sys/types.h>

//Big number class definition. This is just an example.
class BigNumber{
 private:
    bool sgn;
    unsigned int num_of_bits;
    uint8_t *data;

 public:
    //constructors
    BigNumber();
    BigNumber(int); //directly convert from an int
    BigNumber(bool, unsigned int, uint8_t*);

    //overloaded arithmetic operators as member functions
    BigNumber operator+(BigNumber);
    BigNumber operator-(BigNumber);
    BigNumber operator*(BigNumber);
    BigNumber operator/(BigNumber);
    BigNumber operator%(BigNumber);
    //integer division: 3/2==1

    //interface functions
    void Print();
    void GetData(bool& ,unsigned int& , uint8_t*);
};

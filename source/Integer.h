#ifndef Integer_h
#define Integer_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Token.h"
using namespace std;

class Integer : public Token
{
public:
    Integer(int value, int line_num): Token(INT_VAL, line_num)
    {
        _value = value;
    }
    int get_value()
    {
        return _value;
    }
private:
    int _value;
};

#endif

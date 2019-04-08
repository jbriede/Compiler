#ifndef FloatingPoint_h
#define FloatingPoint_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Token.h"
using namespace std;

class FloatingPoint : public Token
{
public:
    FloatingPoint(float value, int line_num): Token(FLOAT_VAL, line_num)
    {
        _value = value;
    }
private:
    float _value;
};

#endif

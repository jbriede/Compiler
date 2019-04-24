#ifndef Temp_h
#define Temp_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Expression.h"
#include "Word.h"
using namespace std;

class Temp : public Expression
{
public:
    Temp(Type* type, int line): Expression(new Word("temp", TEMP, line), type, line)
    {
        number = 10;//count++;
    }
    string get_name()
    {
        return string("temp"+ std::to_string(number));
    }
private:
    static const int count = 0;
    int number;
    
};

#endif

#ifndef Constant_h
#define Constant_h

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Expression.h"
using namespace std;

class Constant : public Expression
{
public:
    Constant(Token* token, Type* type, int line): Expression(token, type, line)
    {

    }

private:

    
};

#endif

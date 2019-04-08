#ifndef Arithmetic_h
#define Arithmetic_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Operation.h"
#include "Expression.h"
using namespace std;

class Arithmetic : public Operation
{
public:
    Arithmetic(Token* token, Expression* expression_1, Expression* expression_2, int line): Operation(token, NULL, line)
    {

    }
private:

    
};

#endif

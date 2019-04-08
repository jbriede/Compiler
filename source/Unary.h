#ifndef Unary_h
#define Unary_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Operation.h"
using namespace std;

class Unary : public Operation
{
public:
    Unary(Token* token, Expression* expression, int line): Operation(token, NULL, line)
    {

    }
private:

    
};

#endif

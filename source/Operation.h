#ifndef Operation_h
#define Operation_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Expression.h"
using namespace std;

class Operation : public Expression
{
public:
    Operation(Token* token, Token* op, int line): Expression(token, op, line)
    {

    }
private:

    
};

#endif

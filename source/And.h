#ifndef And_h
#define And_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Logical.h"
#include "TypeChecker.h"
using namespace std;

class And : public Logical
{
public:
    And(Token* token, Expression* expression1, Expression* expression2, int line): Logical(token, expression1, expression2, line)
    {
        TypeChecker(expression1, expression2, line);
    }
private:

    
};

#endif

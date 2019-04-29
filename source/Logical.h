#ifndef Logical_h
#define Logical_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Expression.h"
#include "TypeChecker.h"
using namespace std;

class Logical : public Expression
{
public:
    Logical(Token* token, Expression* expression1, Expression* expression2, int line): Expression(token, expression2->get_type(), line)
    {
        TypeChecker(expression1, expression2, line);
    }
    Logical(Token* token, Expression* expression1, Expression* expression2, Type* type, int line): Expression(token, type, line)
    {
        TypeChecker(expression1, expression2, line);
    }
private:
    
};

#endif

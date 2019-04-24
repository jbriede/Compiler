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
        _expression_1 = expression_1;
        _expression_2 = expression_2;
    }
    Expression* generate()
    {
        return new Arithmetic(_op, _expression_1->reduce(), _expression_2->reduce(), _line);
    }
    string to_string()
    {
        return string(_expression_1->to_string() + " " + _op->to_string() + " " + _expression_2->to_string());
    }
private:
    Expression* _expression_1;
    Expression* _expression_2;
    
};

#endif

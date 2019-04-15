#ifndef Logical_h
#define Logical_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Expression.h"
using namespace std;

class Logical : public Expression
{
public:
    Logical(Token* token, Expression* expression1, Expression* expression2, int line): Expression(token, NULL, line)
    {
        if (!check(expression_1->get_type(), expression_2->get_type()))
        {
            throw string("Types dont match... also need to make this better");
        }
    }
private:
    Type* _type;
    bool check(Type* type_1, Type* type_1)
    {
        return type_1->get_lexeme() == type_2->get_lexeme();
    }
    
};

#endif

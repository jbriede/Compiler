#ifndef Argument_h
#define Argument_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Id.h"
using namespace std;

class Argument
{
public:
    Argument(Expression* expression)
    {
        _expression = expression;
        _next_arg = NULL;
    }
    // Set up my arguments and params like a linked list. 
    void set_next(Argument* next_arg)
    {
        _next_arg = next_arg;
    }
    Argument* get_next()
    {
        return _next_arg;
    }
    Expression* get_expression()
    {
        return _expression;
    }
private:
    Argument* _next_arg;
    Expression* _expression;
    
};

#endif
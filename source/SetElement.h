#ifndef SetElement_h
#define SetElement_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Statement.h"

using namespace std;

class SetElement : public Statement
{
public:
    SetElement (Access* access , Expression* expression, int line): Statement(line)
    {
        _array = access->get_array();
        _index = access->get_index();
        _expression = expression;
        TypeChecker(expression, _index, line);
        
    }
private:
    Id* _array; 
    Expression* _index;
    Expression* _expression;
    
};

#endif

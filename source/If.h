#ifndef If_h
#define If_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Statement.h"
using namespace std;

class If : public Statement
{
public:
    If (Expression* expression, Statement* statement, int line): Statement(line)
    {
        _expression = expression;
        _statement = statement;
    }
private:
    Expression* _expression;
    Statement* _statement;
    
};

#endif

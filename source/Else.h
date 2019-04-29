#ifndef Else_h
#define Else_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Statement.h"
#include "TypeChecker.h"
using namespace std;

class Else : public Statement
{
public:
    Else(Expression* expression, Statement* statement1, Statement* statement2, int line): Statement(line)
    {
        _expression = expression;
        _statement1 = statement1;
        _statement2 = statement2;
        TypeChecker(_expression, "bool", line);
    }
private:
    Expression* _expression;
    Statement* _statement1;
    Statement* _statement2;
    
};

#endif

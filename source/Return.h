#ifndef If_h
#define If_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Statement.h"
#include "Writer.h"
using namespace std;

class FunctionCall : public Statement
{
public:
    FunctionCall(Expression* expression, Statement* statement, int line): Statement(line)
    {
        _expression = expression;
        _statement = statement;
    }
    void generate(Writer* writer)
    {
        
    }
private:
    Expression* _expression;
    Statement* _statement;
    
};

#endif

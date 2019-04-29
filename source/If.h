#ifndef If_h
#define If_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Statement.h"
#include "Writer.h"
#include "TypeChecker.h"
using namespace std;

class If : public Statement
{
public:
    If (Expression* expression, Statement* statement, int line): Statement(line)
    {
        _expression = expression;
        _statement = statement;
        TypeChecker(_expression, "bool", line);
    }
    void generate(Writer* writer)
    {
        
    }
private:
    Expression* _expression;
    Statement* _statement;
    
};

#endif

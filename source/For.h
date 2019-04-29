#ifndef For_h
#define For_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Statement.h"
using namespace std;

class For : public Statement
{
public:
    For (Statement* statement, Expression* expression, int line): Statement(line)
    {
        _statement = statement;
        _expression = expression;
        TypeChecker(_expression, "bool", line);
    }
    void generate(Writer* writer)
    {
        writer->append_main("default generator... probably shouldnt be writing this");
    }
private:
    Statement* _statement;
    Expression* _expression;
    
};

#endif

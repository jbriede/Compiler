#ifndef Set_h
#define Set_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Id.h"
#include "Expression.h"
#include "Statement.h"
using namespace std;

class Set : public Statement
{
public:
    Set (Id* id, Expression* expression, int line): Statement(line)
    {
        _id = id;
        _expression = expression;
    }
private:
    Id* _id; 
    Expression* _expression;
    
};

#endif

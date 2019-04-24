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
    void generate(Writer* writer)
    {
        Arithmetic* arith = (Arithmetic*) _expression;
        Arithmetic* arith2 = (Arithmetic*) arith->generate();
        string variable_pre = "%";
        if (_id->is_global())
        {
            variable_pre = "@";
        }
        writer->append_main(variable_pre + _id->get_word()->get_lexeme() + " = " + arith2->to_string() + "\n");    
        
    }
private:
    Id* _id; 
    Expression* _expression;
    
};

#endif

#ifndef Procedure_h
#define Procedure_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Id.h"
#include "Parameter.h"
using namespace std;

class Procedure : public Id
{
public:
    Procedure (Word* id, Type* return_type, Parameter* parameters, int line): Id(id, return_type, line)
    {
        _parameters = parameters;
        _statement = NULL;
    }
    Procedure (Word* id, Type* return_type, Parameter* parameters, Statement* statements, int line): Id(id, return_type, line)
    {
        _parameters = parameters;
        _statement = statements;
    }
    void set_statements(Statement* statement)
    {
        _statement = statement;
    }
    Parameter* get_parameters()
    {
        return _parameters;
    }
private:
    Parameter* _parameters;
    Statement* _statement;
    Word* _word;
};

#endif
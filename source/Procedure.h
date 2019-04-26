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
    Procedure (Word* id, Type* type, Parameter* parameters, Statement* statement, int line): Id(id, type, line)
    {
        _parameters = parameters;
        _statement = statement;
    }
    Parameter* get_parameters()
    {
        return _parameters;
    }
private:
    Parameter* _parameters;
    Statement* _statement;
};

#endif
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
    Procedure (Word* id, Type* type, Parameter* parameters, int line): Id(id, type, line)
    {
        _parameters = parameters;
    }

private:
    Parameter* _parameters;
};

#endif
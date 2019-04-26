#ifndef Parameter_h
#define Parameter_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Id.h"
using namespace std;

class Parameter
{
public:
    Parameter(Id* id)
    {
        _id = id;
        _next_param = NULL;
    }
    void set_next(Parameter* next_param)
    {
        _next_param = next_param;
    }
    Parameter* get_next()
    {
        return _next_param;
    }
    Id* get_id()
    {
        return _id;
    }
private:
    Parameter* _next_param;
    Id* _id;
    
};

#endif

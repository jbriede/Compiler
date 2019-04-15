#ifndef ID_h
#define ID_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Expression.h"
using namespace std;

class Id : public Expression
{
public:
    Id(Word* id, Type* type, int line): Expression(id, type, line)
    {

    }
private:

    
};

#endif
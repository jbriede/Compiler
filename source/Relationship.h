#ifndef Or_h
#define Or_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Logical.h"
using namespace std;

class Relationship : public Logical
{
public:
    Relationship(Token* token, Expression* expression1, Expression* expression2, int line): Logical(token, expression1, expression2, line);
private:

    
};

#endif

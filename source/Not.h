#ifndef Not_h
#define Not_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Logical.h"
using namespace std;

class Not : public Logical
{
public:
    Not(Token* token, Expression* expression1, int line): Logical(token, expression1, expression1, line)
    {
        
    }
private:

    
};

#endif

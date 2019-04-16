#ifndef Sequence_h
#define Sequence_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Statement.h"
using namespace std;

class Sequence : public Statement
{
public:
    Sequence (Statement* s1, Statement* s2, int line): Statement(line)
    {
    }
private:

    
};

#endif

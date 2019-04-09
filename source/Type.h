#ifndef Type_h
#define Type_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Token.h"
#include "Word.h"
using namespace std;

class Type : public Word
{
public:
    Type(string lexeme, int type, int width, int line_num): Word(lexeme, BASIC, line_num)
    {
        _width = width;
    }
private:
    int _width;
    
};

#endif

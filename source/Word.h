#ifndef Word_h
#define Word_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Token.h"
using namespace std;

class Word : public Token
{
public:
    Word(string lexeme, int type, int line_num): Token(type, line_num)
    {
        _lexeme = lexeme;
    }
private:
    string _lexeme;
    
};

#endif

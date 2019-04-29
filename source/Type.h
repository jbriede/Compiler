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
    Type(string lexeme, int token_type, int width, int line_num): Word(lexeme, token_type, line_num)
    {
        _width = width;
        _lexeme = lexeme;
    }
    string get_lexeme()
    {
        return _lexeme;
    }
    int get_width()
    {
        return _width;
    }
private:
    int _width;
    string _lexeme;
    
};

#endif

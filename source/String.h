#ifndef String_h
#define String_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Token.h"
using namespace std;

class String : public Token
{
public:
    String(string text, int line_num): Token(STRING, line_num)
    {
        _text = text;
    }
    string get_value()
    {
        return _text;
    }
private:
    string _text;
};

#endif

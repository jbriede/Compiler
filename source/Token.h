#ifndef Token_h
#define Token_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
using namespace std;

enum TOKEN_TYPE
{
    ID,
    END_OF_FILE,
    PLUS,
    MINUS,
    DIVIDE,
    MULTIPLY,
    EQUALS,
    OPEN_BRACKET,
    CLOSE_BRACKET,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,
    COLON,
    SEMI_COLON,
    LESS_THAN,
    GREATER_THAN,
    PROGRAM,
    IS,
    GLOBAL,
    INTEGER,
    PROCEDURE,
    END,//20
    BEGIN,
    IF,
    FOR,
    END_DOT,
    INT_VAL,
    FLOAT_VAL
};

class Token
{
public:
    Token(int type, int line_num)
    {
        _type = type;
        _line_num = line_num;
    }
private:
    int _line_num;
    int _type;
};

#endif /* Logger_h */

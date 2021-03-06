#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
using namespace std;
#ifndef Token_h
#define Token_h



enum TOKEN_TYPE
{
    ID,
    END_OF_FILE,
    PLUS,
    MINUS,
    DIVIDE,
    MULTIPLY,
    EQUALS,
    OPEN_BRACKET, //7
    CLOSE_BRACKET,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,
    COLON,
    SEMI_COLON, //12
    LESS_THAN,
    GREATER_THAN,
    PROGRAM, //15
    IS,
    GLOBAL,
    INTEGER,
    PROCEDURE,
    END,//20
    BEGIN,
    IF,
    FOR,
    END_DOT,
    INT_VAL,//
    FLOAT_VAL,
    COLON_EQUALS,
    LESS_THAN_EQUALS,
    GREATER_THAN_EQUALS,
    VARIABLE,
    BASIC, //31
    NOTEQUALS,
    AND,
    OR,
    TRUE,
    NOT,
    FALSE,
    FLOAT,
    THEN,
    ELSE,
    COMMA,
    BOOL, //42
    RETURN,
    TEMP,
    STRING,
    ARRAY
};
const std::string type_as_strings[] = 
{
    "ID",
    "END_OF_FILE",
    "PLUS",
    "MINUS",
    "DIVIDE",
    "MULTIPLY",
    "EQUALS",
    "OPEN_BRACKET", 
    "CLOSE_BRACKET",
    "OPEN_PARENTHESIS",
    "CLOSE_PARENTHESIS",
    "COLON",
    "SEMI_COLON", 
    "LESS_THAN",
    "GREATER_THAN",
    "PROGRAM", 
    "IS",
    "GLOBAL",
    "INTEGER",
    "PROCEDURE",
    "END",
    "BEGIN",
    "IF",
    "FOR",
    "END_DOT",
    "INT_VAL",
    "FLOAT_VAL",
    "COLON_EQUALS",
    "LESS_THAN_EQUALS",
    "GREATER_THAN_EQUALS",
    "VARIABLE",
    "BASIC", 
    "NOTEQUALS",
    "AND",
    "OR",
    "TRUE",
    "NOT",
    "FALSE",
    "FLOAT",
    "THEN",
    "ELSE",
    "COMMA",
    "BOOL",
    "RETURN",
    "TEMP",
    "STRING",
    "ARRAY"
};

class Token
{
public:
    Token(int type, int line_num)
    {
        _type = type;
        _line_num = line_num;
    }
    int get_type()
    {
        return _type;
    }
    int get_line()
    {
        return _line_num;
    }
    string to_string(){return type_as_strings[_type];};
private:
    int _line_num;
    int _type;
};

#endif /* Logger_h */

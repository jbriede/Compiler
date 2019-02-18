#include <stdio.h>
#include <iostream>
#include "Logger.h"
#include <string>
#include <fstream>

#ifndef Shared_h
#define Shared_h

struct Symbol
{
    char symbol_name[32];
};

struct Token {
    uint16_t token_name;
    Symbol* symbol;
    uint16_t line_number;
};

enum TOKEN_NAMES
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
    END,
    BEGIN,
    IF,
    FOR
};
#endif 
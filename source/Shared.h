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
    DIVISION
};
#endif 
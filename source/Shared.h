#include <stdio.h>
#include <iostream>
#include "Logger.h"
#include <string>
#include <fstream>

#ifndef Shared_h
#define Shared_h

enum SYMBOL_TYPES
{
    PROGRAM_SYMBOL,
    INTEGER_SYMBOL
};

struct Symbol
{
    char symbol_name[32];
    uint16_t token_type;

};



#define PROGRAM_ERROR 0;
#define USER_ERROR 1;
struct COMPILER_EXCEPTION
{
    int type;
    char message[512];
};
#endif 
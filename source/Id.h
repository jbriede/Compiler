#ifndef ID_h
#define ID_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Expression.h"
using namespace std;

class Id : public Expression
{
public:
    Id (Word* id, Type* type, int line): Expression(id, type, line)
    {
        _word = id;
        _is_global = false;
    }
    Word* get_word()
    {
        return _word;
    }
    bool is_global()
    {
        return _is_global;
    }
    void set_global()
    {
        _is_global = true;
    }
private:
    Word* _word;
    bool _is_global;
    
};

#endif
#ifndef Array_h
#define Array_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Type.h"
using namespace std;

class Array : public Type
{
public:
    Array(Type* token_type, int size, int line_num): Type("[]", ARRAY, token_type->get_width() * size, line_num)
    {
        _of = token_type;
    }
    Type* get_of()
    {
        return _of;
    }
private:
    int _width;
    Type* _of;
    
};

#endif

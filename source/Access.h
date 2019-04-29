#ifndef Access_h
#define Access_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Operation.h"
using namespace std;

class Access : public Operation
{
public:
    Access(Id* array, Expression* index, Type* type, int line): Operation(new Word("[]", ARRAY, line), type, line)
    {
        _array = array;
        _index = index;
    }
    Id* get_array()
    {
        return _array;
    }
    Expression* get_index()
    {
        return _index;
    }
private:
    Expression* _index;
    Id* _array;
    
};

#endif

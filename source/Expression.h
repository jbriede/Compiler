#ifndef Expression_h
#define Expression_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Node.h"
using namespace std;

class Expression : public Node
{
public:
    Expression(Token* token, Type* type, int line): Node(line)
    {
        _op = token;
        _type = type;
    }
    Type* get_type()
    {
        return _type;
    }
private:
    Token* _op;
    Type* _type;
    
};

#endif

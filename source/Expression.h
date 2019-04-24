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
    string to_string()
    {
        return _op->to_string();
    };
    Expression* generate(){return this;};
    Expression* reduce(){return this;}; // reuse and recycle
private:
    
    
protected:
    Type* _type;
    Token* _op;
};

#endif

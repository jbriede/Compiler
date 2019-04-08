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
    Expression(Token* token, Token* op, int line): Node(line)
    {
        _op = op;
        _token = token;
    }
private:
    Token* _token;
    Token* _op;
    
};

#endif

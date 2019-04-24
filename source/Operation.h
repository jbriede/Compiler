#ifndef Operation_h
#define Operation_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Expression.h"
#include "Writer.h"
#include "Temp.h"
using namespace std;

class Operation : public Expression
{
public:
    Operation(Token* token, Type* type, int line): Expression(token, type, line)
    {

    }
    Expression* reduce(Writer* _writer)
    {
        Expression* expression = generate();
        Temp* temp = new Temp(_type, _line);
        _writer->append_main(temp->get_name() + expression->to_string());
        return NULL;
    }
private:

    
};

#endif

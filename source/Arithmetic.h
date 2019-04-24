#ifndef Arithmetic_h
#define Arithmetic_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Operation.h"
#include "Expression.h"
using namespace std;

class Arithmetic : public Operation
{
public:
    Arithmetic(Token* token, Expression* expression_1, Expression* expression_2, int line): Operation(token, NULL, line)
    {
        _expression_1 = expression_1;
        _expression_2 = expression_2;
    }
    Expression* generate()
    {
        return new Arithmetic(_op, _expression_1->reduce(), _expression_2->reduce(), _line);
    }
    string to_string()
    {

        string opr = "";
        switch(_op->get_type())
        {
            case PLUS:
            {
                opr = "add i32 ";
                break;
            }
            case MINUS:
            {
                opr = "sub i32 ";
                break;
            }
            default:
            {
                throw string("not sure what to do with this operator type");
            }
        }

        string expr1 = "";
        if (_expression_1->get_op()->get_type() == ID)
        {
            Id* id = (Id*)_expression_1;
            expr1 = "%";
            if (id->is_global())
            {
                expr1 = "@";
            }
            expr1 +=id->get_word()->get_lexeme();
        }
        else if (_expression_1->get_op()->get_type() == INT_VAL)
        {
            Integer* i = (Integer*)_expression_1->get_op();
            expr1 = std::to_string(i->get_value());
        }
        else
        {
            throw string("Not sure what where doing math on");
        }
        
        string expr2 = "";
        if (_expression_2->get_op()->get_type() == ID)
        {
            Id* id = (Id*)_expression_2;
            expr2 = "%";
            if (id->is_global())
            {
                expr2 = "@";
            }
            expr2 +=id->get_word()->get_lexeme();
        }
        else if (_expression_2->get_op()->get_type() == INT_VAL)
        {
            Integer* i = (Integer*)_expression_2->get_op();
            expr2 = std::to_string(i->get_value());
        }
        else
        {
            throw string("Not sure what where doing math on");
        }
        return string(opr + expr1 + " , " + expr2 + "\n");

    }
private:
    Expression* _expression_1;
    Expression* _expression_2;
    
};

#endif

#ifndef Return_h
#define Return_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Statement.h"
#include "Procedure.h"
#include "Type.h"
using namespace std;

class Return : public Statement
{
public:
    Return(Expression* expression, Procedure* procedure, int line): Statement(line)
    {
        _expression = expression;
        _procedure = procedure;
        
        type_check();
        
    }
    void type_check()
    {
        Type* proc_type = _procedure->get_type();
        Type* returned_type = _expression->get_type();
        string proc_type_s = proc_type->get_lexeme();
        string returned_type_s = returned_type->get_lexeme();
        if (proc_type_s == "integer")
        {
            if (returned_type_s == "integer" )
            {
                return;
            }
            else if (returned_type_s == "float" )
            {
                // works, but we have to truncate
                return;
            }
            else if (returned_type_s == "string" )
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Expected integer, got string int line " + std::to_string(get_line())).c_str());
                throw compiler_exception;
            }
            else if (returned_type_s == "bool" )
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Expected integer, got bool int line " + std::to_string(get_line())).c_str());
                throw compiler_exception;
            }
        }
        else if (proc_type_s == "float")
        {
            if (returned_type_s == "integer" )
            {
                // works, but we have to cast
                return;
            }
            else if (returned_type_s == "float" )
            {
                // works, but we have to cast
                return;
            }
            else if (returned_type_s == "string" )
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Expected float, got string int line " + std::to_string(get_line())).c_str());
                throw compiler_exception;
            }
            else if (returned_type_s == "bool" )
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Expected float, got bool int line " + std::to_string(get_line())).c_str());
                throw compiler_exception;
            }
        }
        else if (proc_type_s == "string")
        {
            if (returned_type_s == "integer" )
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Expected string, got integer int line " + std::to_string(get_line())).c_str());
                throw compiler_exception;
            }
            else if (returned_type_s == "float" )
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Expected string, got float int line " + std::to_string(get_line())).c_str());
                throw compiler_exception;
            }
            else if (returned_type_s == "string" )
            {
                return;
            }
            else if (returned_type_s == "bool" )
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Expected string, got bool int line " + std::to_string(get_line())).c_str());
                throw compiler_exception;
            }
        }
        else if (proc_type_s == "bool")
        {

            if (returned_type_s == "integer" )
            {
                return;
            }
            else if (returned_type_s == "float" )
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Expected bool, got float int line " + std::to_string(get_line())).c_str());
                throw compiler_exception;
            }
            else if (returned_type_s == "string" )
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Expected bool, got string int line " + std::to_string(get_line())).c_str());
                throw compiler_exception;
            }
            else if (returned_type_s == "bool" )
            {
                return;
            }
        }
    }
private:
    Expression* _expression;
    Procedure* _procedure;
    
};

#endif

#ifndef ProcedureCall_h
#define ProcedureCall_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Statement.h"
#include "Procedure.h"
#include "Argument.h"

using namespace std;

class ProcedureCall : public Statement
{
public:
    ProcedureCall(Procedure* procedure, Argument* arguments, int line): Statement(line)
    {
        _arguments = arguments;
        _procedure = procedure;
        type_check();
    }
private:
    void type_check()
    {
        Argument* arg = _arguments;
        Parameter* param = _procedure->get_parameters();
        while (true)
        {
            if (arg == NULL && param == NULL)
            {
                return;
            }
            if ((arg == NULL && param != NULL) || (arg != NULL && param == NULL))
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Incorrect number of arguments for procedure call " + _procedure->get_word()->get_lexeme() + " int line " + std::to_string(get_line())).c_str());
                throw compiler_exception;
            }
            else
            {
                // now we have to check types 
                Expression* arg_expression = arg->get_expression();
                Id* param_id = param->get_id();

                Type* arg_type = arg_expression->get_type();
                Type* param_type = param_id->get_type();

                if (param_type->get_lexeme() == "integer")
                {
                    if (arg_type->get_lexeme() == "integer" )
                    {
                        break;
                    }
                    else if (arg_type->get_lexeme() == "float" )
                    {
                        // works, but we have to truncate
                        break;
                    }
                    else if (arg_type->get_lexeme() == "string" )
                    {
                        COMPILER_EXCEPTION compiler_exception;
                        compiler_exception.type = USER_ERROR;
                        strcpy(compiler_exception.message, string("Expected integer, got string int line " + std::to_string(get_line())).c_str());
                        throw compiler_exception;
                    }
                    else if (arg_type->get_lexeme() == "boolean" )
                    {
                        COMPILER_EXCEPTION compiler_exception;
                        compiler_exception.type = USER_ERROR;
                        strcpy(compiler_exception.message, string("Expected integer, got bool int line " + std::to_string(get_line())).c_str());
                        throw compiler_exception;
                    }
                }
                else if (param_type->get_lexeme() == "float")
                {
                    if (arg_type->get_lexeme() == "integer" )
                    {
                        // works, but we have to casr
                        break;
                    }
                    else if (arg_type->get_lexeme() == "float" )
                    {
                        // works, but we have to cast
                        break;
                    }
                    else if (arg_type->get_lexeme() == "string" )
                    {
                        COMPILER_EXCEPTION compiler_exception;
                        compiler_exception.type = USER_ERROR;
                        strcpy(compiler_exception.message, string("Expected float, got string int line " + std::to_string(get_line())).c_str());
                        throw compiler_exception;
                    }
                    else if (arg_type->get_lexeme() == "bool" )
                    {
                        COMPILER_EXCEPTION compiler_exception;
                        compiler_exception.type = USER_ERROR;
                        strcpy(compiler_exception.message, string("Expected float, got bool int line " + std::to_string(get_line())).c_str());
                        throw compiler_exception;
                    }
                }
                else if (param_type->get_lexeme() == "string")
                {
                    if (arg_type->get_lexeme() == "integer" )
                    {
                        COMPILER_EXCEPTION compiler_exception;
                        compiler_exception.type = USER_ERROR;
                        strcpy(compiler_exception.message, string("Expected string, got integer int line " + std::to_string(get_line())).c_str());
                        throw compiler_exception;
                    }
                    else if (arg_type->get_lexeme() == "float" )
                    {
                        COMPILER_EXCEPTION compiler_exception;
                        compiler_exception.type = USER_ERROR;
                        strcpy(compiler_exception.message, string("Expected string, got float int line " + std::to_string(get_line())).c_str());
                        throw compiler_exception;
                    }
                    else if (arg_type->get_lexeme() == "string" )
                    {
                        break;
                    }
                    else if (arg_type->get_lexeme() == "bool" )
                    {
                        COMPILER_EXCEPTION compiler_exception;
                        compiler_exception.type = USER_ERROR;
                        strcpy(compiler_exception.message, string("Expected string, got bool int line " + std::to_string(get_line())).c_str());
                        throw compiler_exception;
                    }
                }
                else if (param_type->get_lexeme() == "bool")
                {

                    if (arg_type->get_lexeme() == "integer" )
                    {
                        // works??
                        break;
                    }
                    else if (arg_type->get_lexeme() == "float" )
                    {
                        COMPILER_EXCEPTION compiler_exception;
                        compiler_exception.type = USER_ERROR;
                        strcpy(compiler_exception.message, string("Expected bool, got float int line " + std::to_string(get_line())).c_str());
                        throw compiler_exception;
                    }
                    else if (arg_type->get_lexeme() == "string" )
                    {
                        COMPILER_EXCEPTION compiler_exception;
                        compiler_exception.type = USER_ERROR;
                        strcpy(compiler_exception.message, string("Expected bool, got string int line " + std::to_string(get_line())).c_str());
                        throw compiler_exception;
                    }
                    else if (arg_type->get_lexeme() == "bool" )
                    {
                        break;
                    }
                }
            }
            arg = arg->get_next();
            param = param->get_next();
        }
    }
    Procedure* _procedure;
    Argument* _arguments;

    
};

#endif

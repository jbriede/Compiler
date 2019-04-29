#ifndef TypeChecker_h
#define TypeChecker_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "Type.h"
#include "Expression.h"
using namespace std;

class TypeChecker
{
public:
    TypeChecker(Expression* expected, Expression* got, int line)
    {
        Type* proc_type = expected->get_type();
        Type* returned_type = got->get_type();
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
                strcpy(compiler_exception.message, string("Expected integer, got string int line " + std::to_string(line)).c_str());
                throw compiler_exception;
            }
            else if (returned_type_s == "bool" )
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Expected integer, got bool int line " + std::to_string(line)).c_str());
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
                strcpy(compiler_exception.message, string("Expected float, got string int line " + std::to_string(line)).c_str());
                throw compiler_exception;
            }
            else if (returned_type_s == "bool" )
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Expected float, got bool int line " + std::to_string(line)).c_str());
                throw compiler_exception;
            }
        }
        else if (proc_type_s == "string")
        {
            if (returned_type_s == "integer" )
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Expected string, got integer int line " + std::to_string(line)).c_str());
                throw compiler_exception;
            }
            else if (returned_type_s == "float" )
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Expected string, got float int line " + std::to_string(line)).c_str());
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
                strcpy(compiler_exception.message, string("Expected string, got bool int line " + std::to_string(line)).c_str());
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
                strcpy(compiler_exception.message, string("Expected bool, got float int line " + std::to_string(line)).c_str());
                throw compiler_exception;
            }
            else if (returned_type_s == "string" )
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Expected bool, got string int line " + std::to_string(line)).c_str());
                throw compiler_exception;
            }
            else if (returned_type_s == "bool" )
            {
                return;
            }
        }
    }
    TypeChecker(Expression* expression1, string expected, int line)
    {
        Type* proc_type = expression1->get_type();
        string proc_type_s = proc_type->get_lexeme();  
        if (proc_type_s!= expected)
        {
            COMPILER_EXCEPTION compiler_exception;
            compiler_exception.type = USER_ERROR;
            strcpy(compiler_exception.message, string("Expected " + expected + ", got " + proc_type_s +" int line " + std::to_string(line)).c_str());
            throw compiler_exception;
        } 
    }
private:
    
};

#endif

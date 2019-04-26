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
                std::cout << "hmmm";
            }
            arg = arg->get_next();
            param = param->get_next();
        }
    }
    Procedure* _procedure;
    Argument* _arguments;

    
};

#endif

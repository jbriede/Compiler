//
//  main.cpp
//  Compiler
//


#include <iostream>
#include "Parser.h"
#include "Lexer.h"
#include "Token.h"
#include "Integer.h"
#include "Unary.h"
#include "Arithmetic.h"
#include "Integer.h"
#include "FloatingPoint.h"
#include "SymbolTable.h"

void parse_input(int argc, const char * argv[], string &file_name)
{

    if (argc != 2)
    {
        throw string("Invalid number of arguments");
    }

    file_name = string(argv[1]);
}

int main(int argc, const char * argv[])
{
    /* Make logger and set level */
    Logger* logger = new Logger();
    if (!logger->set_log_level(LOGGER_DEBUG))
    {
        return -1;
    }
    
    /* try to get info from arguments */
    string file_name;
    try
    {
        parse_input(argc, argv, file_name);
    }
    catch(string exception)
    {
        logger->error(exception);
        logger->error("Argument format is \"j++ filename\"");
        return -1;
    }
    catch(std::exception& e) {
        logger->error("unknown error");
        logger->error(e.what());
        return -1;
    }

    Lexer* lex = new Lexer(logger, NULL);
    lex->load_file(file_name);
    Parser* parser = new Parser(logger, lex, NULL);
    parser->program();

    return 0;
}

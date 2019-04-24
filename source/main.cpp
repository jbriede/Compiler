//
//  main.cpp
//  Compiler
//


#include <iostream>
#include "Parser.h"
#include "Lexer.h"
#include "Integer.h"
#include "Unary.h"
#include "Arithmetic.h"
#include "Integer.h"
#include "FloatingPoint.h"
#include "Writer.h"

void parse_input(int argc, const char * argv[], string &in_file, string &out_file)
{

    if (argc != 3)
    {
        throw string("Invalid number of arguments");
    }

    in_file = string(argv[1]);
    out_file = string(argv[2]);
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
    string in_file;
    string out_file;
    try
    {
        parse_input(argc, argv, in_file, out_file);
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

    Lexer* lexer = new Lexer(logger);
    lexer->load_file(in_file);

    Writer* writer = new Writer(logger, out_file);

    Parser* parser = new Parser(logger, lexer, writer);
    parser->program();
    delete writer;
    delete parser;
    delete lexer;

    return 0;
}

//
//  main.cpp
//  Compiler
//


#include <iostream>
#include "Parser.h"
#include "Lexer.h"
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

    SymbolTable* symbol_table = new SymbolTable(logger);
    Lexer* lexer = new Lexer(logger, symbol_table);

    if (!lexer->load_file(file_name))
    {
        return -1;
    }

    Parser* parser = new Parser(logger, lexer, symbol_table);
    parser->Parse(NULL, NULL);
    

    delete lexer;
    delete parser;
    delete logger;
    delete symbol_table;
    return 0;
}

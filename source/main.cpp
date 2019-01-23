//
//  main.cpp
//  Compiler
//


#include <iostream>
#include "Logger.h"
#include "Parser.h"

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

    Parser* parser = new Parser(logger);
    if (!parser->load_file(file_name))
    {
        return -1;
    }
    
    delete parser;
    delete logger;
    return 0;
}

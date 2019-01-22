//
//  main.cpp
//  Compiler
//


#include <iostream>
#include "Logger.h"
#include "Parser.h"

void parseInput(int argc, const char * argv[], string &file_name)
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
        parseInput(argc, argv, file_name);
    }
    catch(string exception)
    {
        logger->error(exception);
        logger->error("Argument format is \"j++ filename\"");
        return -1;
    }
    
    Parser* parser = new Parser(logger);

    parser->load_file(file_name);
    
    delete logger;
    return 0;
}

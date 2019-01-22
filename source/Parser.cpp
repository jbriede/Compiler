/*
 * Logger class implementation
 */

#include "Parser.h"

Parser::Parser(Logger* logger)
{
    _logger = logger;
}

void Parser::load_file(string file_name)
{
    _logger->info("Attempting to open file " + file_name);
}

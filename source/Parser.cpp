/*
 * Logger class implementation
 */

#include "Parser.h"


Parser::Parser(Logger* logger)
{
    _logger = logger;
}

Parser::~Parser()
{
    _character_stream.close();
}

bool Parser::load_file(string file_name)
{
    _logger->info("Attempting to open file " + file_name);
    
    try {
        /* Check the extension */
        int last_dot_location = file_name.find_last_of(".");
        string file_extension = file_name.substr(last_dot_location+1);

        if ((last_dot_location == -1) || (file_extension != string("c")))
        {
            throw string("Wrong file extension");
        }

        _character_stream.open(file_name.c_str());
        if (!_character_stream.good())
        {
            throw string("File does not exist");
        }
    }
    catch (string e)
    {
        _logger->error(e);
        _character_stream.close();
        return false;
    }
    catch(std::exception& e) {
        _logger->error("unknown error");
        _logger->error(e.what());
        _character_stream.close();
        return false;
    }

    _logger->info("File opened succesfully.");
    return true;
}

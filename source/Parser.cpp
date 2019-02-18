/*
 * Logger class implementation
 */

#include "Parser.h"


Parser::Parser(Logger* logger, Lexer* lexer)
{
    _logger = logger;
    _lexer = lexer;
}

Parser::~Parser()
{

}


bool Parser::Parse()
{
    Token next_token;
    try 
    {
        do
        {
            next_token = _lexer->get_token();

            cout << next_token.token_name << endl;
            cout << next_token.symbol->symbol_name << endl;

            //throw string("Token with name " + to_string(next_token.token_name) + " was not identified by lexer");
        }
        while(next_token.token_name != END_OF_FILE);
        _logger->info("Lexical Analysis Finished");
    }
    catch (string e)
    {
        _logger->error(e);
        return false;
    }
    catch(std::exception& e) {
        _logger->error("unknown error");
        _logger->error(e.what());
        return false;
    }
    return 0;
}
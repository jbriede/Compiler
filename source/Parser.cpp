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
    try 
    {
        while(true)
        {
            Token next_token = _lexer->get_token();
            cout << next_token.token_name << endl;
            if (next_token.token_name == ID)
            {
                cout << next_token.symbol->symbol_name << endl;
            }
            cout << endl;
            delete next_token.symbol;
            if (next_token.token_name == END_OF_FILE)
            {
                break;
            }
        }
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
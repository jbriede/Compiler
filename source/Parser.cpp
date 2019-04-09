/*
 * Logger class implementation
 */

#include "Parser.h"


Parser::Parser(Logger* logger, Lexer* lexer, SymbolTable* symbolTable)
{
    _logger = logger;
    _lexer = lexer;
    _symbolTable = symbolTable;
}

Parser::~Parser()
{

}

void Parser::move()
{
    _lookahead = _lexer->get_token();
}

void Parser::match(int token_type)
{
    try 
    {
        if (token_type == _lookahead->get_type())
        {
            move();
            return;
        }
        else
        {
            COMPILER_EXCEPTION compiler_exception;
            compiler_exception.type = USER_ERROR;
            strcpy(compiler_exception.message, string("Expected token " + to_string(token_type) + " in line " + to_string(_lookahead->get_line())).c_str());
            throw compiler_exception;
        }
    }
    catch(COMPILER_EXCEPTION e) 
    {
        if (e.type == 0)
        {
            _logger->error(string(e.message));
        }
        else if (e.type == 1)
        {
            _logger->user_error(string(e.message));
        }
        return;
    }
    catch (string e)
    {
        _logger->error(e);
        return;
    }
    catch(std::exception& e) {
        _logger->error("unknown error");
        _logger->error(e.what());
        return;
    }
}

void Parser::program()
{
    move();
    match(PROGRAM); match(ID); // Do I put this in the symbol table?
    Statement* s = block();

}

Statement* Parser::block()
{
    match(IS);
    declarations();
    return new Statement(5);
}

void Parser::declarations()
{
    while(_lookahead->get_type() == VARIABLE)
    {
        // Lets do some declarations
        match(ID);
        match(COLON);
        Type* t = type();
    }
}

Type* Parser::type()
{
    Type* t = reinterpret_cast<Type*>(_lookahead);
    return t;
}
/*
 * Logger class implementation
 */


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
    match(BEGIN);
    Statement* s = statements();
    return new Statement(5);
}

void Parser::declarations()
{
    while((_lookahead->get_type() == VARIABLE) || (_lookahead->get_type() == GLOBAL) || (_lookahead->get_type() == PROCEDURE))
    {
        if (_lookahead->get_type() == GLOBAL)
        {
            match(GLOBAL);
            match(VARIABLE);
            Token* id_token = _lookahead;
            match(ID);
            match(COLON);
            Type* id_type = type();
            Id* id = new Id(reinterpret_cast<Word*>(id_token), id_type, id_token->get_line());
            // Put in global scope
            match(SEMI_COLON);
        }
        else if (_lookahead->get_type() == VARIABLE)
        {
            match(VARIABLE);
            Token* id_token = _lookahead;
            match(ID);
            match(COLON);
            Type* id_type = type();
            Id* id = new Id(reinterpret_cast<Word*>(id_token), id_type, id_token->get_line());
            // Put in scope
            match(SEMI_COLON);
        }
        else if (_lookahead->get_type() == PROCEDURE)
        {
            match(VARIABLE);
            Token* id_token = _lookahead;
            match(ID);
            match(COLON);
            
            Type* return_type = type();
            Id* id = new Id(reinterpret_cast<Word*>(id_token), id_type, id_token->get_line());

            match(OPEN_PARENTHESIS);
            // Parameter stuff
            parameters();

            match(CLOSE_PARENTHESIS);


            // Put in scope
            match(SEMI_COLON);
        }
    }
}

void Parser::parameters();
{
    while (_lookahead->get_type() != CLOSE_PARENTHESIS)
    {
        
    }
}

void Parser::parameter();
{

}

Type* Parser::type()
{
    // Do dimension stuff...
    Type* t = reinterpret_cast<Type*>(_lookahead);
    match(BASIC);
    return t;
}

Statement* Parser::statements()
{
    if (_lookahead->get_type() == END)
    {
        return NULL;
    }
    //  | statement statements
    else return new Sequence(statement(), statements());
}

Statement* Parser::statement()
{
    switch (_lookahead->get_type())
    {
        case SEMI_COLON:
            move();
            return NULL;
        case IF:
            match(IF);
            match(OPEN_PARENTHESIS);
            Expression* expression = boolean();
            match(CLOSE_PARENTHESIS);

    }
}
Expression* parser::boolean()
{
    Expression* expression = join();
    while(_lookahead->get_type()  == OR)
    {
        Token* token = _lookahead; move(); x = new 
    }
}
Expression* parser::join()
{

}
Expression* parser::equality()
{

}
Expression* parser::relationship()
{

}


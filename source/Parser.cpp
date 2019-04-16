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
            Id* id = new Id(reinterpret_cast<Word*>(id_token), return_type, id_token->get_line());

            match(OPEN_PARENTHESIS);
            

            match(CLOSE_PARENTHESIS);


            // Put in scope
            match(SEMI_COLON);
        }
    }
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
    else return new Sequence(statement(), statements(), _lookahead->get_line());
}

Statement* Parser::statement()
{
    switch (_lookahead->get_type())
    {
        case SEMI_COLON:
        {
            move();
            return NULL;
        }
        case IF:
        {
            match(IF);
            match(OPEN_PARENTHESIS);
            Expression* expression = boolean();
            match(CLOSE_PARENTHESIS);
            match(THEN);
            Statement* statement1 = statement();
            if (_lookahead->get_type() != ELSE)
            {
                return new If(expression, statement1, _lookahead->get_line());
            } 
            else
            {
                match(ELSE);
                Statement* statement2 = statement();
                return new Else(expression, statement1, statement2, _lookahead->get_line());
            }
        }

    }
    return NULL;
}
Expression* Parser::boolean()
{
    Expression* expression = join();
    while(_lookahead->get_type()  == OR)
    {
        Token* token = _lookahead; move(); expression = new Or(token, expression, join(), _lookahead->get_line());
    }
    return expression;
}
Expression* Parser::join()
{
    Expression* expression = equality();
    while(_lookahead->get_type()  == AND)
    {
        Token* token = _lookahead; move(); expression = new And(token, expression, equality(),  _lookahead->get_line());
    }
    return expression;
}
Expression* Parser::equality()
{
    Expression* expression = relationship();
    while(_lookahead->get_type()  == EQUALS || _lookahead->get_type()  == NOTEQUALS)
    {
        Token* token = _lookahead; move(); expression = new Relationship(token, expression, relationship(),  _lookahead->get_line());
    }
    return expression;
}
Expression* Parser::relationship()
{
    Expression* expression = exp();
    Token* token;
    switch (_lookahead->get_type())
    {
        case LESS_THAN:
        {
            token = _lookahead; move(); expression = new Relationship(token, expression, exp(),  _lookahead->get_line());
            break;
        }
        case GREATER_THAN:
        {
            token = _lookahead; move(); expression = new Relationship(token, expression, exp(),  _lookahead->get_line());
            break;
        }
        case LESS_THAN_EQUALS:
        {
            token = _lookahead; move(); expression = new Relationship(token, expression, exp(),  _lookahead->get_line());
            break;
        }
        case GREATER_THAN_EQUALS:
        {
            token = _lookahead; move(); expression = new Relationship(token, expression, exp(),  _lookahead->get_line());
            break;
        }
        default:
            return expression;

        return NULL;


    }
}

Expression* Parser::exp()
{
    Expression* expression = term();
    while(_lookahead->get_type()  == PLUS || _lookahead->get_type()  == MINUS)
    {
        Token* token = _lookahead; move(); expression = new Arithmetic(token, expression, term(),  _lookahead->get_line());
    }
    return expression;
}

Expression* Parser::term()
{
    Expression* expression = unary();
    while(_lookahead->get_type()  == MULTIPLY || _lookahead->get_type()  == DIVIDE)
    {
        Token* token = _lookahead; move(); expression = new Arithmetic(token, expression, unary(),  _lookahead->get_line());
    }
    return expression;
}

Expression* Parser::unary()
{
    if (_lookahead->get_type() == MINUS)
    {
        move(); return new Unary(new Word("-", MINUS, _lookahead->get_line()), unary(), _lookahead->get_line());
    }
    else if (_lookahead->get_type() == NOT)
    {
        Token* token = _lookahead; move(); return new Not(token, unary(), _lookahead->get_line());
    }
    else
    {
        return factor();
    }
    return NULL;
    
}

Expression* Parser::factor()
{
    Expression* expression = NULL;
    switch (_lookahead->get_type())
    {
        case OPEN_PARENTHESIS:
        {
            move();
            expression = boolean();
            match(CLOSE_PARENTHESIS);
            break;
        }
        case INT_VAL:
        {
            Integer* int_token = reinterpret_cast<Integer*>(_lookahead);
            expression = new Constant(int_token, new Type("integer", INTEGER, 2, _lookahead->get_line()) ,_lookahead->get_line());
            move();
            break;
        }
        case FLOAT_VAL:
        {
            FloatingPoint* float_token = reinterpret_cast<FloatingPoint*>(_lookahead);
            expression = new Constant(float_token, new Type("float", FLOAT, 4, _lookahead->get_line()) ,_lookahead->get_line());
            move();
            break;
        }
        case TRUE:
        {
            Word* true_token = reinterpret_cast<Word*>(_lookahead);
            expression = new Constant(true_token, new Type("true", TRUE, 1, _lookahead->get_line()) ,_lookahead->get_line());
            move();
            break;
        }
        case FALSE:
        {
            Word* false_token = reinterpret_cast<Word*>(_lookahead);
            expression = new Constant(false_token, new Type("false", FALSE, 1, _lookahead->get_line()) ,_lookahead->get_line());
            move();
            break;
        }
        return expression;
    }
            
}


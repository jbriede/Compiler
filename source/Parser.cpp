/*
 * Logger class implementation
 */

#include "Parser.h"

Parser::Parser(Logger* logger, Lexer* lexer, Writer* writer)
{
    _logger = logger;
    _lexer = lexer;
    _writer = writer;
    _current_proc = NULL;
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
    if (token_type == _lookahead->get_type())
    {
        move();
        return;
    }
    else
    {
        COMPILER_EXCEPTION compiler_exception;
        compiler_exception.type = USER_ERROR;
        strcpy(compiler_exception.message, string("Expected token " + type_as_strings[token_type] + " in line " + to_string(_lookahead->get_line())).c_str());
        throw compiler_exception;
    }
}

/*  This is how I've chosen to make the built in functions */
void Parser::make_built_in_functions()
{
    Type* return_type = new Type("bool", BASIC, 1, 0);
    Word* id_word =  new Word("getbool", BASIC, 0);
    Parameter* params = NULL;
    Procedure* procedure = new Procedure(id_word, return_type, NULL, NULL, 0);
    _current_scope->add_global(id_word->get_lexeme(), procedure); 

    return_type = new Type("integer", BASIC, 2, 0);
    id_word =  new Word("getinteger", BASIC, 0);
    params = NULL;
    procedure = new Procedure(id_word, return_type, NULL, NULL, 0);
    _current_scope->add_global(id_word->get_lexeme(), procedure); 

    return_type = new Type("float", BASIC, 4, 0);
    id_word =  new Word("getfloat", BASIC, 0);
    params = NULL;
    procedure = new Procedure(id_word, return_type, NULL, NULL, 0);
    _current_scope->add_global(id_word->get_lexeme(), procedure); 

    return_type = new Type("string", BASIC, -1, 0);
    id_word =  new Word("getstring", BASIC, 0);
    params = NULL;
    procedure = new Procedure(id_word, return_type, NULL, NULL, 0);
    _current_scope->add_global(id_word->get_lexeme(), procedure); 

    ScopeVariables* saved = _current_scope;
    _current_scope = new ScopeVariables(saved);
    id_word =  new Word("putbool", BASIC, 0);
    // Will be used in the put bool function
    params = new Parameter(new Id(new Word("bool_val", BASIC, 0), new Type("bool", BASIC, 1, 0), 0));
    return_type = new Type("bool", BASIC, 1, 0);
    procedure = new Procedure(id_word, return_type, params, NULL, 0);
    _current_scope = saved;
    _current_scope->add_global(id_word->get_lexeme(), procedure); 

    saved = _current_scope;
    _current_scope = new ScopeVariables(saved);
    id_word =  new Word("putfloat", BASIC, 0);
    // Will be used in the put bool function
    params = new Parameter(new Id(new Word("float_val", BASIC, 0), new Type("float", BASIC, 4, 0), 0));
    procedure = new Procedure(id_word, return_type, params, NULL, 0);
    _current_scope = saved;
    _current_scope->add_global(id_word->get_lexeme(), procedure);

    saved = _current_scope;
    _current_scope = new ScopeVariables(saved);
    id_word =  new Word("putinteger", BASIC, 0);
    // Will be used in the put bool function
    params = new Parameter(new Id(new Word("integer_val", BASIC, 0), new Type("integer", BASIC, 2, 0), 0));
    procedure = new Procedure(id_word, return_type, params, NULL, 0);
    _current_scope = saved;
    _current_scope->add_global(id_word->get_lexeme(), procedure);  

    saved = _current_scope;
    _current_scope = new ScopeVariables(saved);
    id_word =  new Word("putstring", BASIC, 0);
    // Will be used in the put bool function
    params = new Parameter(new Id(new Word("string_val", BASIC, 0), new Type("string", BASIC, -1, 0), 0));
    procedure = new Procedure(id_word, return_type, params, NULL, 0);
    _current_scope = saved;
    _current_scope->add_global(id_word->get_lexeme(), procedure);  
}

void Parser::program()
{
    // try 
    // {
        move();
        match(PROGRAM); 
        /* Make Global Scope */
        _current_scope = new ScopeVariables(NULL);
        /* Make Program Scope */
        _current_scope = new ScopeVariables(_current_scope);
        Word* look_word = reinterpret_cast<Word*>(_lookahead);
        Id* program_id = new Id(look_word, new Type(look_word->get_lexeme(), ID, look_word->get_lexeme().length(), _lookahead->get_line()),_lookahead->get_line());   
        _current_scope->add(program_id->get_word()->get_lexeme(), program_id);
        match(ID);
        match(IS);
        make_built_in_functions();
        Statement* s = block(false);
        // s->generate(_writer);
        match(PROGRAM);
        match(END_DOT);
        _logger->info("Program parsed with 0 error... well at least that I found");
    // }
    // catch(COMPILER_EXCEPTION e) 
    // {
    //     if (e.type == 0)
    //     {
    //         _logger->error(string(e.message));
    //     }
    //     else if (e.type == 1)
    //     {
    //         _logger->user_error(string(e.message));
    //     }
    //     return;
    // }
    // catch (string e)
    // {
    //     _logger->error(e);
    //     return;
    // }
    // catch(std::exception& e) {
    //     _logger->error("unknown error");
    //     _logger->error(e.what());
    //     return;
    // }
}

Statement* Parser::block(bool is_procedure)
{   
    if (!is_procedure)
    {
        _writer->append_main("define i32 @main() {\n");
    }
    declarations();
    match(BEGIN);
    Statement* s = statements();
    match(END);
    if (!is_procedure)
    {
        _writer->append_main("}");
    }
    
    return s;
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
            Word* id_word =  reinterpret_cast<Word*>(id_token);
            Id* id = new Id(id_word, id_type, id_token->get_line());
            id->set_global();
            // Put in global scope
            if (!_current_scope->is_global_scope(id_word->get_lexeme()))
            {
                _current_scope->add_global(id_word->get_lexeme(), id);
                string name = id_word->get_lexeme();

                string width = "i8";
                string type = "c";
                if (id_type->get_lexeme() == "integer")
                {
                    width = "i16";
                }
                else if (id_type->get_lexeme() == "float")
                {
                    width = "i32";
                }
                _writer->append_global("@" + name + " = extern global " + width + "\n");
            }
            else
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Identifier " + id_word->get_lexeme() + " already declared in this scope int line " + std::to_string(id_token->get_line())).c_str());
                throw compiler_exception;
            }
            
            match(SEMI_COLON);
        }
        else if (_lookahead->get_type() == VARIABLE)
        {
            match(VARIABLE);
            Token* id_token = _lookahead;
            match(ID);
            match(COLON);
            Type* id_type = type();
            Word* id_word =  reinterpret_cast<Word*>(id_token);
            Id* id = new Id(id_word, id_type, id_token->get_line());
            // Put in scope
            if (!_current_scope->is_in_scope(id_word->get_lexeme()))
            {
                _current_scope->add(id_word->get_lexeme(), id);
                string name = id_word->get_lexeme();
                string width = "i8";
                string type = "c";
                if (id_type->get_lexeme() == "integer")
                {
                    width = "i16";
                }
                else if (id_type->get_lexeme() == "float")
                {
                    width = "i32";
                }
                _writer->append_main("%" + name + " = private " + width + "\n");
            }
            else
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Identifier " + id_word->get_lexeme() + " already declared in this scope in line " + std::to_string(id_token->get_line())).c_str());
                throw compiler_exception;
            }

        
            match(SEMI_COLON);
        }
        else if (_lookahead->get_type() == PROCEDURE)
        {
            match(PROCEDURE);
            Token* id_token = _lookahead;
            match(ID);
            match(COLON);
            
            Type* return_type = type();
            Word* id_word =  reinterpret_cast<Word*>(id_token);
            //Id* id = new Procedure(id_word, return_type, parameters(), id_token->get_line());

            if (!_current_scope->is_in_scope(id_word->get_lexeme()))
            {   ScopeVariables* saved = _current_scope;
                _current_scope = new ScopeVariables(saved);

                match(OPEN_PARENTHESIS);

                Parameter* params = parameters();

                match(CLOSE_PARENTHESIS);
                Procedure* procedure = new Procedure(id_word, return_type, params, id_token->get_line());
                Procedure* saved_proc = _current_proc;
                _current_proc = procedure;
                Statement* procedure_statement = block(true);
                _current_proc = saved_proc;
                procedure->set_statements(procedure_statement);
                match(PROCEDURE);
                match(SEMI_COLON);

                _current_scope = saved;

                _current_scope->add(id_word->get_lexeme(), procedure);
            }
            else
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Identifier " + id_word->get_lexeme() + " already declared in this scope in line " + std::to_string(id_token->get_line())).c_str());
                throw compiler_exception;
            }
        }
    }
}

Parameter* Parser::parameters()
{
    Parameter* param = NULL;
    Parameter* param2 = NULL;
    if (_lookahead->get_type() != CLOSE_PARENTHESIS)
    {
        param = parameter();
    }
    param2 = param;
    while (_lookahead->get_type() != CLOSE_PARENTHESIS)
    {
        if (_lookahead->get_type() == COMMA)
        {
            match(COMMA);
        }
        // Send it up the chain of params...
        Parameter* new_param = parameter();
        param2->set_next(new_param);
        param2 = new_param;
    }
    return param;
}

Parameter* Parser::parameter()
{
    match(VARIABLE);
    Token* id_token = _lookahead;
    match(ID);
    match(COLON);
    Type* id_type = type();
    Word* id_word =  reinterpret_cast<Word*>(id_token);
    Id* id = new Id(id_word, id_type, id_token->get_line());

    if (!_current_scope->is_in_scope(id_word->get_lexeme()))
    {
        _current_scope->add_global(id_word->get_lexeme(), id);
        return new Parameter(id);
    }
    else
    {
        COMPILER_EXCEPTION compiler_exception;
        compiler_exception.type = USER_ERROR;
        strcpy(compiler_exception.message, string("Identifier " + id_word->get_lexeme() + " already declared in this scope in line " + std::to_string(id_token->get_line())).c_str());
        throw compiler_exception;
    }
    
}

Argument* Parser::arguments()
{
    Argument* args1 = NULL;
    Argument* args2 = NULL;
    if (_lookahead->get_type() != CLOSE_PARENTHESIS)
    {
        args1 = argument();
    }
    args2 = args1;
    while (_lookahead->get_type() != CLOSE_PARENTHESIS)
    {
        if (_lookahead->get_type() == COMMA)
        {
            match(COMMA);
        }
        // Send it up the chain of params...
        Argument* new_arg = argument();
        args2->set_next(new_arg);
        args2 = new_arg;
    }
    return args1;
}

Argument* Parser::argument()
{
    Expression* expression = boolean();
    return new Argument(expression);
}

Type* Parser::type()
{
    Type* t = reinterpret_cast<Type*>(_lookahead);
    match(BASIC);
    if (_lookahead->get_type() == OPEN_BRACKET)
    {
        return dims(t);
    }
    return t;
}

Type* Parser::dims(Type* t)
{
    match(OPEN_BRACKET);
    Token* token = _lookahead;
    match(INT_VAL);
    match(CLOSE_BRACKET);
    return new Array(t, ((Integer*)token)->get_value(), _lookahead->get_line());

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
                match(END);
                match(IF);
                match(SEMI_COLON);
                return new If(expression, statement1, _lookahead->get_line());
            } 
            else
            {
                match(ELSE);
                Statement* statement2 = statements();
                match(END);
                match(IF);
                match(SEMI_COLON);
                return new Else(expression, statement1, statement2, _lookahead->get_line());
            }
        }
        case ID:
        {
            return assign();
        }
        case RETURN:
        {
            match(RETURN);
            Expression* return_exp = boolean();
            Return* ret = new Return(return_exp, _current_proc, _lookahead->get_line());
            return ret;
        }
        case FOR:
        {
            match(FOR);
            match(OPEN_PARENTHESIS);
            Statement* assign_statements = assign();
            Expression* expression = boolean();
            match(CLOSE_PARENTHESIS);

            Statement* stmt = statements();
            match(END);
            match(FOR);
            match(SEMI_COLON);
            
            return new For(stmt, expression, _lookahead->get_line());

        }
        default:
            throw string("Not sure whats going on ");

    }
    return NULL;
}

Expression* Parser::procedure_call(Id* id)
{
    Argument* args = arguments();
    match(CLOSE_PARENTHESIS);
    Procedure* procedure = (Procedure*)id;
    ProcedureCall* proc_call = new ProcedureCall(procedure, args, _lookahead->get_line());
    return proc_call;
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
        Token* token = _lookahead; move(); expression = new Relationship(token, expression, relationship(), new Type("bool", BOOL, 1, _lookahead->get_line()), _lookahead->get_line());
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
            token = _lookahead; move(); expression = new Relationship(token, expression, exp(), new Type("bool", BOOL, 1, _lookahead->get_line()),  _lookahead->get_line());
            return expression;
        }
        case GREATER_THAN:
        {
            token = _lookahead; move(); expression = new Relationship(token, expression, exp(),new Type("bool", BOOL, 1, _lookahead->get_line()),  _lookahead->get_line());
            return expression;
        }
        case LESS_THAN_EQUALS:
        {
            token = _lookahead; move(); expression = new Relationship(token, expression, exp(),new Type("bool", BOOL, 1, _lookahead->get_line()),  _lookahead->get_line());
            return expression;
        }
        case GREATER_THAN_EQUALS:
        {
            token = _lookahead; move(); expression = new Relationship(token, expression, exp(),new Type("bool", BOOL, 1, _lookahead->get_line()),  _lookahead->get_line());
            return expression;
        }
        // case EQUALS:
        // {
        //     token = _lookahead; move(); expression = new Relationship(token, expression, exp(),  _lookahead->get_line());
        //     return expression;
        // }
        default:
            return expression;
    }
}

Expression* Parser::exp()
{
    Expression* expression = term();
    while(_lookahead->get_type()  == PLUS || _lookahead->get_type()  == MINUS)
    {
        Token* token = _lookahead; move(); expression = new Arithmetic(token, expression, term(),  _lookahead->get_line());
        Arithmetic* temp = (Arithmetic*)expression;
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
            expression = new Constant(true_token, new Type("bool", TRUE, 1, _lookahead->get_line()) ,_lookahead->get_line());
            move();
            break;
        }
        case FALSE:
        {
            Word* false_token = reinterpret_cast<Word*>(_lookahead);
            expression = new Constant(false_token, new Type("bool", FALSE, 1, _lookahead->get_line()) ,_lookahead->get_line());
            move();
            break;
        }
        case STRING:
        {
            String* string_token = reinterpret_cast<String*>(_lookahead);
            expression = new Constant(string_token, new Type("string", STRING, string_token->get_value().length(), _lookahead->get_line()) ,_lookahead->get_line());
            move();
            break;
        }
        case ID:
        {
            Word* id_word = reinterpret_cast<Word*>(_lookahead);
            Id* id = _current_scope->find(id_word->get_lexeme());
            move();
            if (_lookahead->get_type() == OPEN_BRACKET)
            {
                return offset(id);
            }
            else if (_lookahead->get_type() == COLON_EQUALS)
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Looking for expression not assignment in line " + to_string(_lookahead->get_line())).c_str());
                // yeet that thing
                throw compiler_exception;
            }
            else if (_lookahead->get_type() == OPEN_PARENTHESIS)
            {
                move();
                return procedure_call(id);
            }
            else
            {
                return id;
            }
            
            break;
        }
    }
    return expression;
            
}

Access* Parser::offset(Id* id)
{
    match(OPEN_BRACKET);
    Expression* i = boolean();
    match(CLOSE_BRACKET);
    Array* arr_type = (Array*)id->get_type();
    Type* type = arr_type->get_of();
    return new Access(id, i, type, id->get_line());
}

Statement* Parser::assign()
{
    Token* token = _lookahead;
    Id* id = NULL;
    Word* id_word =  reinterpret_cast<Word*>(token);
    match(ID);
    
    id = _current_scope->find(id_word->get_lexeme());
    if (id)
    {
        if (_lookahead->get_type() == COLON_EQUALS)
        {
            match(COLON_EQUALS);
            Statement* statement = new Set(id, boolean(), _lookahead->get_line());
            // Set* hmm = (Set*)statement;
            // hmm->generate(_writer);
            match(SEMI_COLON);
            return statement;
        }
        else if (_lookahead->get_type() == OPEN_PARENTHESIS)
        {
            //So this is a procedure call... it actually jumps and returns an expression... but since the expression doesnt return anything were in a weird spot i dont kow what to return... NULL?
            match(OPEN_PARENTHESIS);
            procedure_call(id);
            return NULL;
        }
        else if (_lookahead->get_type() == OPEN_BRACKET)
        {
            Access* access = offset(id);
            match(COLON_EQUALS);
            Statement* s = new SetElement(access, boolean(), _lookahead->get_line());
            match(SEMI_COLON);
            return s;
        }
        else
        {
            throw string("Under construction");
        }
    }
    else
    {
        COMPILER_EXCEPTION compiler_exception;
        compiler_exception.type = USER_ERROR;
        strcpy(compiler_exception.message, string("ID " + id_word->get_lexeme() + " not defined in scope.in line " + to_string(_lookahead->get_line())).c_str());
        // yeet that thing
        throw compiler_exception;
    } 
}
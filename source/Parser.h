/*
 * Parser class
 */
#include "Lexer.h"
#include "ScopeVariables.h"
#include "Statement.h"
#include "Logger.h"
#include "Type.h"
#include "Id.h"
#include "If.h"
#include "Else.h"
#include "And.h"
#include "Expression.h"
#include "Or.h"
#include "Sequence.h"
#include "Not.h"
#include "Relationship.h"
#include "FloatingPoint.h" 
#include "Integer.h" 
#include "Constant.h" 
#include "Arithmetic.h" 
#include "Unary.h"
#include "Set.h" 
#include "Writer.h" 



#ifndef Parser_h
#define Parser_h


class Parser
{
public:
    Parser(Logger* logger, Lexer* lexer, Writer* writer);
    ~Parser();
    bool load_file(string file_name);
    void program();
    
private:
    Logger* _logger;
    Lexer* _lexer;
    Writer* _writer;

    Token* _lookahead;

    ScopeVariables* _current_scope;

    void move();
    void declarations();

    void match(int token_type);

    Type* type();

    Statement* block(bool is_procedure);
    Statement* statement();
    Statement* statements();
    
    Expression* boolean();

    Expression* join();
    Expression* equality();
    Expression* relationship();
    Expression* exp();
    Expression* term();
    Expression* unary();
    Expression* factor();
    Statement* assign();
    void parameters();
    void parameter();

};

#endif 

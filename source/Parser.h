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
#include "For.h"
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
#include "Parameter.h"
#include "Procedure.h"
#include "ProcedureCall.h"
#include "Argument.h"



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
    /* Access to other import classes */
    Logger* _logger;
    Lexer* _lexer;
    Writer* _writer;

    /* Next token */
    Token* _lookahead;

    /* Pointer to current level of Symbol table */
    ScopeVariables* _current_scope;

    void move();
    void match(int token_type);

    void declarations();
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
    Parameter* parameters();
    Parameter* parameter();
    Argument* arguments();
    Argument* argument();
    Expression* procedure_call(Id* id);

};

#endif 

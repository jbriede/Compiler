/*
 * Parser class
 */
#include "Lexer.h"
#include "SymbolTable.h"
#include "Statement.h"
#include "Logger.h"
#include "Type.h"
#include "Id.h"
#include "If.h"
#include "Else.h"
#include "And.h"
#include "Or.h"
#include "Sequence.h"
#include "Not.h"
#include "Relationship.h"
#include "FloatingPoint.h" 
#include "Integer.h" 
#include "Constant.h" 
#include "Arithmetic.h" 
#include "Unary.h" 

#ifndef Parser_h
#define Parser_h
using namespace std;

class Parser
{
public:
    Parser(Logger* logger, Lexer* lexer, SymbolTable* symbolTable);
    ~Parser();
    bool load_file(string file_name);
    //Token* Parse(Token* start_sybmol, Token* current_token);
    void program();
    
private:
    Logger* _logger;
    SymbolTable* _symbolTable;
    Lexer* _lexer;

    Token* _lookahead;

    void move();
    void declarations();

    void match(int token_type);

    Type* type();

    Statement* block();
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

};

#endif 

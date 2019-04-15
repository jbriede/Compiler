/*
 * Parser class
 */
#include "Lexer.h"
#include "SymbolTable.h"
#include "Statement.h"
#include "Type.h"
#include "Id.h"
#include "While.h"

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

    void match(int token_type);

    

    Statement* block();
    Statement* statement();
    Statement* statements();

    void declarations();
    
    Type* type();




};

#endif 

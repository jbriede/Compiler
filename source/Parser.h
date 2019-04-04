/*
 * Parser class
 */
#include "Lexer.h"
#include "SymbolTable.h"

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
    
private:
    Logger* _logger;
    SymbolTable* _symbolTable;
    Lexer* _lexer;


};

#endif 

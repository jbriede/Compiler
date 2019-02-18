/*
 * Parser class
 */
#include "Lexer.h"

#ifndef Parser_h
#define Parser_h
using namespace std;

class Parser
{
public:
    Parser(Logger* logger, Lexer* lexer);
    ~Parser();
    bool load_file(string file_name);
    bool Parse();
    
private:
    Logger* _logger;
    Lexer* _lexer;


};

#endif 

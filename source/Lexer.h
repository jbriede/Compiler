/*
 * Parser class
 */

#include "Shared.h"
#include "Token.h"
#include "Integer.h"
#include "FloatingPoint.h"
#include "Type.h"
#include "Logger.h"
#include "Word.h"
#include "String.h"

#ifndef Lexer_h
#define Lexer_h

using namespace std;

class Lexer
{
public:
    Lexer(Logger* logger);
    ~Lexer();
    bool load_file(string file_name);
    Token* get_token();
    
private:
    Logger* _logger;
    ifstream _character_stream;
    void _get_character_from_stream(char* character);
    void _peek_character_from_stream(char* character);
    string _current_word;
    int _current_lexer_line;
    char* _c;
    int _comment_depth;
    bool _end_of_token(char* character);

};

#endif 

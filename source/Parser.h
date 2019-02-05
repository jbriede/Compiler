/*
 * Parser class
 */

#ifndef Parser_h
#define Parser_h

#include <iostream>
#include "Logger.h"
#include <string>
#include <stdio.h>
#include <fstream>
using namespace std;

#define SYMBOL_TABLE_SIZE       10000
#define TOKEN_ARRAY_MAX_SIZE    10000

enum TOKEN_NAMES
{
    ID,
    SPACE,
    TAB,
    NEW_LINE,
    END_OF_FILE,
    COMMENT_OPEN,
    COMMENT_CLOSE,
    COMMENT_SINGLE_LINE,
    DIVISION,
    UNKNOWN
};

struct Symbol
{
    char symbol_name[32];
};

struct Token {
    uint16_t token_name;
    Symbol* attribute_value;
    uint16_t line_number;
};

class Parser
{
public:
    Parser(Logger* logger);
    ~Parser();
    bool load_file(string file_name);
    bool lexical_analysis();
    
private:
    Logger* _logger;
    ifstream _character_stream;
    void get_character_from_stream(char* character);

    Symbol* _symbols;

    Token * _tokens;

    int _symbol_count;
    int _token_count;
    int _long_comment_count;
    
    
    
    // Lexer
    Token get_token_name();
    string current_word;
    int current_lexer_line;
    char* c;
    bool long_comment_mode;
    bool single_line_comment_mode;
    void search_symbols(Symbol* symbol, const char* symbol_string);



};

#endif 

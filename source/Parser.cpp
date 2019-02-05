/*
 * Logger class implementation
 */

#include "Parser.h"


Parser::Parser(Logger* logger)
{
    _logger = logger;
    current_word = "";
    current_lexer_line = 1;
    c = new char();
    long_comment_mode = false;
    single_line_comment_mode = false;
    _symbols = new Symbol[SYMBOL_TABLE_SIZE];
    _tokens = new Token[TOKEN_ARRAY_MAX_SIZE];
    _symbol_count = 0;
    _token_count = 0;
}

Parser::~Parser()
{
    _character_stream.close();
    delete c;
}

bool Parser::load_file(string file_name)
{
    _logger->info("Attempting to open file " + file_name);
    
    try {
        /* Check the extension */
        int last_dot_location = file_name.find_last_of(".");
        string file_extension = file_name.substr(last_dot_location+1);

        if ((last_dot_location == -1) || (file_extension != string("src")))
        {
            throw string("Wrong file extension");
        }

        _character_stream.open(file_name.c_str());
        if (!_character_stream.good())
        {
            throw string("File does not exist");
        }
    }
    catch (string e)
    {
        _logger->error(e);
        _character_stream.close();
        return false;
    }
    catch(std::exception& e) {
        _logger->error("unknown error");
        _logger->error(e.what());
        _character_stream.close();
        return false;
    }

    _logger->info("File opened succesfully.");
    return true;
}

void Parser::get_character_from_stream(char* character)
{
    char next_character;
    if (_character_stream.get(next_character))
        *character = next_character;
    else
    {
        *character = 0;
        _character_stream.close(); 
    }
}

Token Parser::get_token_name()
{
    
    Token token;
    token.attribute_value = NULL;
    if (current_word == "")
    {

        get_character_from_stream(c);
        current_word += *c;
    }

    if (current_word == "/")
    {
        get_character_from_stream(c);
        current_word += *c;
        if (current_word == "//")
        {
            TOKEN_NAMES name = COMMENT_SINGLE_LINE;
            token.token_name = name;
            
            token.line_number = current_lexer_line;
            current_word = "";
            return token;
        }
        else if (current_word == "/*")
        {
            TOKEN_NAMES name = COMMENT_OPEN;
            token.token_name = name;
            token.line_number = current_lexer_line;
            current_word = "";
            return token;
        }
        else
        {
            TOKEN_NAMES name = DIVISION;
            token.token_name = name;
            token.line_number = current_lexer_line;
            current_word = current_word.substr(1, 2);
            return token;
        }
    }
    else if (current_word == "*")
    {
        get_character_from_stream(c);
        current_word += *c;
        if (current_word == "*/")
        {
            TOKEN_NAMES name = COMMENT_CLOSE;
            token.token_name = name;
            token.line_number = current_lexer_line;
            current_word = "";
            return token;
        }
        else
        {
            throw string("Hasnt been handled");
        }
        
    }
    else if (current_word == "\n")
    {
        TOKEN_NAMES name = NEW_LINE;
        token.token_name = name;
        token.line_number = current_lexer_line;
        current_word = "";
        current_lexer_line +=1;
        return token;
    }
    else if (current_word == " ")
    {
        TOKEN_NAMES name = SPACE;
        token.token_name = name;
        token.line_number = current_lexer_line;
        current_word = "";
        return token;
    }
    else /* Ok so we need to look into the symbol table for this one */
    {
        while (1)
        {
            get_character_from_stream(c);
            if (*c == 0)
            {
                throw string("Probable missing a space, current word is " + current_word);
            }
            if ((strcmp(c,"\n") == 0) || (strcmp(c," ") == 0) || (strcmp(c,"\r") == 0))
            {
                break;
            }
            current_word += *c;
        }

        /* So we have some sort of ID... if it doesnt exist in the symbol table return NULL for the attribute val */
        TOKEN_NAMES name = ID;
        token.token_name = name;

        /* I could throw an error here but if we are in comment mode we dont care if this is null */
        token.line_number = current_lexer_line;

        Symbol* symbol = NULL;
        search_symbols(symbol, current_word.c_str());

        if (!symbol && !(single_line_comment_mode || long_comment_mode))
        {
            throw string(current_word + " has not been declared in line current_lexer_line");
        }
        token.attribute_value = symbol;
        current_word = *c;
        return token;
    }

}
bool Parser::lexical_analysis()
{
    Token next_token;
    try 
    {
        do
        {
            next_token = get_token_name();
            /* Handle Comments */
            if (single_line_comment_mode == true)
            {
                /* here were only looking for a new line */
                if (next_token.token_name == NEW_LINE)
                {
                    single_line_comment_mode = false;
                }
                continue;
            }
            else if (long_comment_mode == true)
            {
                /* here were only looking for an end comment */
                if (next_token.token_name == COMMENT_CLOSE)
                {
                    long_comment_mode = false;
                }
                continue;
            }
            if (next_token.token_name== COMMENT_OPEN)
            {
                long_comment_mode = true;
                continue;
            }
            if (next_token.token_name == COMMENT_SINGLE_LINE)
            {
                single_line_comment_mode = true;
                continue;
            }
            if (next_token.token_name == SPACE)
            {
                continue;
            }
            _tokens[_token_count++] = next_token;


            throw string("Token with name " + to_string(next_token.token_name) + " was not identified by lexer");
        }
        while(next_token.token_name != END_OF_FILE);
        _logger->info("Lexical Analysis Finished");
    }
    catch (string e)
    {
        _logger->error(e);
        _character_stream.close();
        return false;
    }
    catch(std::exception& e) {
        _logger->error("unknown error");
        _logger->error(e.what());
        _character_stream.close();
        return false;
    }
    return 0;
}

void Parser::search_symbols(Symbol* symbol, const char* symbol_string)
{
    for (int index = 0; index < _symbol_count; index++)
    {
        if (strcmp(_symbols[index].symbol_name, symbol_string) == 0)
        {
            symbol = &_symbols[index];
            return;
        }
    }
    symbol = NULL;
}
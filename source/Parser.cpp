/*
 * Logger class implementation
 */

#include "Parser.h"


Parser::Parser(Logger* logger)
{
    _logger = logger;
    _current_word = "";
    current_lexer_line = 1;
    c = new char();
    // _symbols = new Symbol[SYMBOL_TABLE_SIZE];
    // _tokens = new Token[TOKEN_ARRAY_MAX_SIZE];
    // _symbol_count = 0;
    // _token_count = 0;
    _comment_depth = 0;
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

Token Parser::get_token()
{
    
    Token token;
    token.symbol = NULL;
    if (_current_word == "")
    {

        get_character_from_stream(c);
        _current_word += *c;
    }

    if (_current_word == "/")
    {
        get_character_from_stream(c);
        _current_word += *c;
        if (_current_word == "/*")
        {
            _current_word = "";
            _comment_depth++;
            return get_token();
        }
        else
        {
            TOKEN_NAMES name = DIVISION;
            token.token_name = name;
            token.line_number = current_lexer_line;
            _current_word = _current_word.substr(1, 2);
            return token;
        }
    }
    else if (_current_word == "*")
    {
        get_character_from_stream(c);
        _current_word += *c;
        if (_current_word == "*/")
        {
            _current_word = "";
            _comment_depth--;
            return get_token();
        }
        else
        {
            throw string("Hasnt been handled, current word is " + _current_word);
        }
        
    }

    if (_comment_depth < 0)
    {
        throw string("something has gone wrong, comment count negative");
    }
    else if (_comment_depth < 1)
    {
        /* We don't give a shit about theese guys */
        if (_current_word == "\n")
        {
            _current_word = "";
            current_lexer_line +=1;
            return get_token();
        }
        if (_current_word == "\r")
        {
            _current_word = "";
            return get_token();
        }
        if (_current_word == "\t")
        {
            _current_word = "";
            return get_token();
        }
        else if (_current_word == " ")
        {
            _current_word = "";
            return get_token();
        }
        else
        {
            /* Ok we need to get the full word... or until a bracket or something */
            int _watch = 0;
            while (1)
            {
                get_character_from_stream(c);
                if (*c == 0)
                {
                    throw string("Probable missing a space, current word is " + _current_word);
                }
                if (_end_of_token(c))
                {
                    break;
                }
                _current_word += *c;
                _watch++;
                if (_watch > 1000)
                {
                    throw string("got stuck in loop");
                }
            }
            Symbol* sym = new Symbol;
            if (_current_word.length() > 32)
            {
                throw string("String lengths cant be longer than 32 ");
            }
            strncpy((*sym).symbol_name, _current_word.c_str(), _current_word.length());
            TOKEN_NAMES name = ID;
            token.token_name = name;
            token.line_number = current_lexer_line;
            token.symbol = sym;

            _current_word = *c;

            return token;

        }
        
        throw string("I have no idea what this token is, " + _current_word);
    }
    else
    {
        /* We're in a comment, just get the next symbol when possible */
        _current_word = "";
        return get_token();
    }

}
bool Parser::lexical_analysis()
{
    Token next_token;
    try 
    {
        do
        {
            next_token = get_token();

            cout << next_token.token_name << endl;

            //throw string("Token with name " + to_string(next_token.token_name) + " was not identified by lexer");
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

bool Parser::_end_of_token(char* character)
{
    return ((strcmp(c," ") == 0) 
    || (strcmp(c,"+") == 0) 
    || (strcmp(c,"-") == 0) 
    || (strcmp(c,"=") == 0) 
    || (strcmp(c,"[") == 0) 
    || (strcmp(c,"(") == 0) 
    || (strcmp(c,":") == 0) 
    || (strcmp(c,";") == 0) 
    || (strcmp(c,"<") == 0) 
    || (strcmp(c,">") == 0)
    || (strcmp(c,"\r") == 0)
    || (strcmp(c,"\n") == 0)
    || (strcmp(c,"\t") == 0)
    );
};

// void Parser::search_symbols(Symbol* symbol, const char* symbol_string)
// {
//     for (int index = 0; index < _symbol_count; index++)
//     {
//         if (strcmp(_symbols[index].symbol_name, symbol_string) == 0)
//         {
//             symbol = &_symbols[index];
//             return;
//         }
//     }
//     symbol = NULL;
// }
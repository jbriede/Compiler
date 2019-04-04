/*
 * Logger class implementation
 */

#include "Lexer.h"


Lexer::Lexer(Logger* logger, SymbolTable* symbolTable)
{
    _logger = logger;
    _symboTable = symbolTable;
    _current_word = "";
    _current_lexer_line = 1;
    c = new char();
    _comment_depth = 0;
}

Lexer::~Lexer()
{
    _character_stream.close();
    delete c;
}

bool Lexer::load_file(string file_name)
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

void Lexer::_get_character_from_stream(char* character)
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

void Lexer::_peek_character_from_stream(char* character)
{
    (*character) = _character_stream.peek();
}


Token* Lexer::get_token()
{
    //Token* token = new Token;
    //token->symbol = NULL;
    if (_current_word == "")
    {
        _get_character_from_stream(c);
        _current_word += *c;
    }

    /* Handle Comment stuff*/
    if (_current_word == "/")
    {
        _peek_character_from_stream(c);
        if (strcmp(c,"*") == 0)
        {
            _get_character_from_stream(c);
            _current_word = "";
            _comment_depth++;
            return get_token();
        }
    }
    else if (_current_word == "*")
    {
        _peek_character_from_stream(c);
        if (strcmp(c,"/") == 0)
        {
            _get_character_from_stream(c);
            _current_word = "";
            _comment_depth--;
            return get_token();
        }
    }
    if (_comment_depth < 0)
    {
        throw string("something has gone wrong, comment count negative");
    }
    else if (_comment_depth < 1)
    {
        /* We don't give a shit about these guys */
        if (_current_word == "\n")
        {
            _current_word = "";
            _current_lexer_line +=1;
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
        /* Lets do some symbols */
        else if (_current_word == "+")
        {
            _current_word = "";
            return new Word("+", PLUS, _current_lexer_line);
        }
        else if (_current_word == "-")
        {
            _current_word = "";
            return new Word("-", MINUS, _current_lexer_line);
        }
        else if (_current_word == "=")
        {
            _current_word = "";
            return new Word("=", EQUALS, _current_lexer_line);
        }
        else if (_current_word == "[")
        {
            _current_word = "";
            return new Word("[", OPEN_BRACKET, _current_lexer_line);
        }
        else if (_current_word == "]")
        {
            _current_word = "";
            return new Word("]", CLOSE_BRACKET, _current_lexer_line);
        }
        else if (_current_word == "(")
        {
            _current_word = "";
            return new Word("(", OPEN_PARENTHESIS, _current_lexer_line);
        }
        else if (_current_word == ")")
        {
            _current_word = "";
            return new Word(")", CLOSE_PARENTHESIS, _current_lexer_line);
        }
        else if (_current_word == ":")
        {
            _current_word = "";
            return new Word(":", COLON, _current_lexer_line);
        }
        else if (_current_word == ";")
        {
            _current_word = "";
            return new Word(";", SEMI_COLON, _current_lexer_line);
        }
        else if (_current_word == "<")
        {
            _current_word = "";
            return new Word("<", LESS_THAN, _current_lexer_line);
        }
        else if (_current_word == ">")
        {
            _current_word = "";
            return new Word(">", GREATER_THAN, _current_lexer_line);
        }
        else if (_current_word == ".")
        {
            _current_word = "";
            return new Word(".", END_DOT, _current_lexer_line);
        }
        /* Else we need to decipher words that could be grammer or ids */
        else
        {
            /* Ok we need to get the full word... or until a bracket or something */
            int watch = 0;
            while (1)
            {
                _peek_character_from_stream(c);
                if ((strcmp(c,"\0") == 0))
                {
                    return new Word("\0", END_OF_FILE, _current_lexer_line);
                }
                if (_end_of_token(c))
                {
                    break;
                }
                _get_character_from_stream(c);
                _current_word += *c;
                watch++;
                if (watch > 1000)
                {
                    throw string("got stuck in loop");
                }
            }

            /* Case insensitive */
            std::transform(_current_word.begin(), _current_word.end(), _current_word.begin(), ::tolower);

            /* Now lets determine if we have a key word or an ID */
            if (_current_word == "program")
            {
                _current_word = "";
                return new Word("program", PROGRAM, _current_lexer_line);
            }
            else if (_current_word == "is")
            {
                _current_word = "";
                return new Word("is", IS, _current_lexer_line);
            }
            else if (_current_word == "global")
            {
                _current_word = "";
                return new Word("global", GLOBAL, _current_lexer_line);
            }
            else if (_current_word == "integer")
            {
                _current_word = "";
                return new Word("integer", INTEGER, _current_lexer_line);
            }
            else if (_current_word == "end")
            {
                _current_word = "";
                return new Word("end", END, _current_lexer_line);
            }
            else if (_current_word == "begin")
            {
                _current_word = "";
                return new Word("begin", BEGIN, _current_lexer_line);
            }
            else if (_current_word == "if")
            {
                _current_word = "";
                return new Word("if", IF, _current_lexer_line);
            }
            else if (_current_word == "for")
            {
                _current_word = "";
                return new Word("for", FOR, _current_lexer_line);
            }

            /* Ok So its probably an ID */
            // Symbol* sym = new Symbol;
            if (_current_word.length() > 32)
            {
                throw string("String lengths cant be longer than 32 ");
            }
            // memset ((*sym).symbol_name,'\0',32); /* shouldnt be necesary but it is ?? */
            // strncpy((*sym).symbol_name, _current_word.c_str(), _current_word.length());
            // TOKEN_NAMES name = ID;
            // token->token_name = name;
            // token->line_number = _current_lexer_line;
            // token->symbol = sym;
            // _current_word = "";

            //_symboTable->add_symbol(sym);
            string temp = _current_word;
            _current_word = "";
            return new Word(temp, ID, _current_lexer_line);
        }
    }
    else
    {
        if (_current_word == "\n")
        {
            _current_lexer_line +=1;
        }
        /* We're in a comment, just get the next symbol when possible */
        _current_word = "";
        return get_token();
    }

}

bool Lexer::_end_of_token(char* character)
{
    return ((strcmp(c," ") == 0) 
    || (strcmp(c,"+") == 0) 
    || (strcmp(c,"-") == 0) 
    || (strcmp(c,"=") == 0) 
    || (strcmp(c,"[") == 0) 
    || (strcmp(c,"(") == 0) 
    || (strcmp(c,")") == 0)
    || (strcmp(c,":") == 0) 
    || (strcmp(c,";") == 0) 
    || (strcmp(c,"<") == 0) 
    || (strcmp(c,">") == 0)
    || (strcmp(c,"\r") == 0)
    || (strcmp(c,"\n") == 0)
    || (strcmp(c,"\t") == 0)
    || (strcmp(c,".") == 0)
    );
};
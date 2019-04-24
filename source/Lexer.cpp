/*
 * Logger class implementation
 */

#include "Lexer.h"


Lexer::Lexer(Logger* logger)
{
    _logger = logger;
    _current_word = "";
    _current_lexer_line = 1;
    _c = new char();
    _comment_depth = 0;
}

Lexer::~Lexer()
{
    _character_stream.close();
    delete _c;
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
            COMPILER_EXCEPTION compiler_exception;
            compiler_exception.type = USER_ERROR;
            strcpy(compiler_exception.message, string("Expected file of type src").c_str());
            throw compiler_exception;
        }

        _character_stream.open(file_name.c_str());
        if (!_character_stream.good())
        {
            COMPILER_EXCEPTION compiler_exception;
            compiler_exception.type = USER_ERROR;
            strcpy(compiler_exception.message, string("File does not exist").c_str());
            throw compiler_exception;
        }
    }
    catch(COMPILER_EXCEPTION e) 
    {
        if (e.type == 0)
        {
            _logger->error(string(e.message));
        }
        else if (e.type == 1)
        {
            _logger->user_error(string(e.message));
        }
        return false;
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
    if (_current_word == "")
    {
        _get_character_from_stream(_c);
        _current_word += *_c;
    }

    /* Handle Comment stuff*/
    if (_current_word == "/")
    {
        _peek_character_from_stream(_c);
        if (strcmp(_c,"*") == 0)
        {
            _get_character_from_stream(_c);
            _current_word = "";
            _comment_depth++;
            return get_token();
        }
    }
    else if (_current_word == "*")
    {
        _peek_character_from_stream(_c);
        if (strcmp(_c,"/") == 0)
        {
            _get_character_from_stream(_c);
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
        if (_current_word == "\0")
        {
            throw string("hmm");
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
            return new Token(PLUS, _current_lexer_line);
        }
        else if (_current_word == "-")
        {
            _current_word = "";
            return new Token(MINUS, _current_lexer_line);
        }
        else if (_current_word == "=")
        {
            _current_word = "";
            return new Token(EQUALS, _current_lexer_line);
        }
        else if (_current_word == "[")
        {
            _current_word = "";
            return new Token(OPEN_BRACKET, _current_lexer_line);
        }
        else if (_current_word == "|")
        {
            _current_word = "";
            return new Token(OR, _current_lexer_line);
        }
        else if (_current_word == "&")
        {
            _current_word = "";
            return new Token(AND, _current_lexer_line);
        }
        else if (_current_word == "]")
        {
            _current_word = "";
            return new Token(CLOSE_BRACKET, _current_lexer_line);
        }
        else if (_current_word == "(")
        {
            _current_word = "";
            return new Token(OPEN_PARENTHESIS, _current_lexer_line);
        }
        else if (_current_word == ")")
        {
            _current_word = "";
            return new Token(CLOSE_PARENTHESIS, _current_lexer_line);
        }
        else if (_current_word == ":")
        {
            _peek_character_from_stream(_c);
            if (strcmp(_c,"=") == 0)
            {
                _get_character_from_stream(_c);
                _current_word = "";
                return new Word(":=", COLON_EQUALS, _current_lexer_line);
            }
            else
            {
                _current_word = "";
                return new Token(COLON, _current_lexer_line);
            }
        }
        else if (_current_word == ";")
        {
            _current_word = "";
            return new Token(SEMI_COLON, _current_lexer_line);
        }
        else if (_current_word == "<")
        {
            _peek_character_from_stream(_c);
            if (strcmp(_c,"=") == 0)
            {
                _get_character_from_stream(_c);
                _current_word = "";
                return new Word("<=", LESS_THAN_EQUALS, _current_lexer_line);
            }
            _current_word = "";
            return new Token(LESS_THAN, _current_lexer_line);
        }
        else if (_current_word == ">")
        {
            _peek_character_from_stream(_c);
            if (strcmp(_c,"=") == 0)
            {
                _get_character_from_stream(_c);
                _current_word = "";
                return new Word(">=", GREATER_THAN_EQUALS, _current_lexer_line);
            }
            _current_word = "";
            return new Token(GREATER_THAN, _current_lexer_line);
        }
        else if (_current_word == ".")
        {
            _current_word = "";
            return new Token(END_DOT, _current_lexer_line);
        }
        /* Else we need to decipher words that could be grammer or ids */
        else
        {
            /* Ok we need to get the full word... or until a bracket or something */
            int watch = 0;
            if (isdigit(_current_word.c_str()[0]))
            {
                // this is a number
                bool isFloat = false;
                while(true)
                {
                    _peek_character_from_stream(_c);
                    if (strcmp(_c,".") == 0)
                    {
                        _get_character_from_stream(_c);
                        _current_word += *_c;
                        isFloat = true;
                    }
                    else if (isdigit(*_c))
                    {
                        _get_character_from_stream(_c);
                        _current_word += *_c;
                    }
                    else if (_end_of_token(_c))
                    {
                        break;
                    }
                    else
                    {
                        throw string ("shouldnt be here");
                    }
                    watch++;
                    if (watch > 1000)
                    {
                        throw string("got stuck in loop");
                    }
                }
                string temp = _current_word;
                _current_word = "";
                if (isFloat)
                {
                    return new FloatingPoint(stof(temp), _current_lexer_line);
                }
                else
                {
                    return new Integer(stoi(temp), _current_lexer_line);
                }
                
            }
            else
            {
                while (1)
                {
                    _peek_character_from_stream(_c);
                    if ((strcmp(_c,"\\0") == 0))
                    {
                        return new Token(END_OF_FILE, _current_lexer_line);
                    }
                    if (_end_of_token(_c))
                    {
                        break;
                    }
                    _get_character_from_stream(_c);
                    _current_word += *_c;
                    watch++;
                    if (watch > 1000)
                    {
                        // todo: FIX SOON!
                        throw string("blahhhh");
                        //return new Token(END_OF_FILE, _current_lexer_line);
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
                else if (_current_word == "variable")
                {
                    _current_word = "";
                    return new Word("variable", VARIABLE, _current_lexer_line);
                }
                else if (_current_word == "integer")
                {
                    _current_word = "";
                    return new Type("integer", BASIC, 2, _current_lexer_line);
                }
                else if (_current_word == "bool")
                {
                    _current_word = "";
                    return new Type("bool", BASIC, 1, _current_lexer_line);
                }
                else if (_current_word == "end")
                {
                    _current_word = "";
                    return new Word("end", END, _current_lexer_line);
                }
                else if (_current_word == "then")
                {
                    _current_word = "";
                    return new Word("then", THEN, _current_lexer_line);
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
                else if (_current_word == "true")
                {
                    _current_word = "";
                    return new Word("true", TRUE, _current_lexer_line);
                }
                else if (_current_word == "false")
                {
                    _current_word = "";
                    return new Word("false", FALSE, _current_lexer_line);
                }
                else if (_current_word == "for")
                {
                    _current_word = "";
                    return new Word("for", FOR, _current_lexer_line);
                }
                else if (_current_word == "procedure")
                {
                    _current_word = "";
                    return new Word("procedure", PROCEDURE, _current_lexer_line);
                }
                else if (_current_word == "return")
                {
                    _current_word = "";
                    return new Word("return", RETURN, _current_lexer_line);
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
    throw string("why am i here");
}


bool Lexer::_end_of_token(char* character)
{
    return ((strcmp(character," ") == 0) 
    || (strcmp(character,"+") == 0) 
    || (strcmp(character,"-") == 0) 
    || (strcmp(character,"=") == 0) 
    || (strcmp(character,"[") == 0) 
    || (strcmp(character,"]") == 0) 
    || (strcmp(character,"(") == 0) 
    || (strcmp(character,")") == 0)
    || (strcmp(character,":") == 0) 
    || (strcmp(character,";") == 0) 
    || (strcmp(character,"<") == 0) 
    || (strcmp(character,">") == 0)
    || (strcmp(character,"\r") == 0)
    || (strcmp(character,"\n") == 0)
    || (strcmp(character,"\t") == 0)
    || (strcmp(character,".") == 0)
    );
};
/*
 * Logger class implementation
 */

#include "Parser.h"


Parser::Parser(Logger* logger, Lexer* lexer, SymbolTable* symbolTable)
{
    _logger = logger;
    _lexer = lexer;
    _symbolTable = symbolTable;
}

Parser::~Parser()
{

}


// Token* Parser::Parse(Token* start_sybmol, Token* current_token)
// {

//     Token* next_token = NULL;
//     try 
//     {
//         //next_token = _lexer->get_token();
//     }
//     catch(COMPILER_EXCEPTION e) 
//     {
//         if (e.type == 0)
//         {
//             _logger->error(string(e.message));
//         }
//         else if (e.type == 1)
//         {
//             _logger->user_error(string(e.message));
//         }
//         return NULL;
//     }
//     catch (string e)
//     {
//         _logger->error(e);
//         return NULL;
//     }
//     catch(std::exception& e) {
//         _logger->error("unknown error");
//         _logger->error(e.what());
//         return NULL;
//     }

//     // Wrap everything in a try catch block now and worry about how try/catch is actually supposed to work later
//     try 
//     {
//         if (current_token == NULL && start_sybmol == NULL)
//         {
//             return Parse(next_token, next_token);
//         }
//         if (start_sybmol == NULL)
//         {
//             COMPILER_EXCEPTION compiler_exception;
//             compiler_exception.type = PROGRAM_ERROR;
//             strcpy(compiler_exception.message, string("Start symbol null... not sure what to do").c_str());
//             throw compiler_exception;
//         }
//         if (current_token == NULL)
//         {
//             COMPILER_EXCEPTION compiler_exception;
//             compiler_exception.type = PROGRAM_ERROR;
//             strcpy(compiler_exception.message, string("Current symbol null... not sure what to do").c_str());
//             throw compiler_exception;
//         }

//         // So let's find a production... think thats the right word
//         if (start_sybmol->token_name == PROGRAM)
//         {
//             if (current_token->token_name == PROGRAM)
//             {
//                 // If id is next keep parsing
//                 if (next_token->token_name == ID)
//                 {
//                     return Parse(next_token, next_token);
//                 }
//                 // If end is next keep parsing
//                 else if (current_token->token_name == END_DOT)
//                 {
//                     return Parse(start_sybmol, next_token);
//                 }
//                 else
//                 {
//                     COMPILER_EXCEPTION compiler_exception;
//                     compiler_exception.type = USER_ERROR;
                    
//                     strcpy(compiler_exception.message, string("Expected an ID or END DOT in line" + to_string(current_token->line_number)).c_str());
//                     throw compiler_exception;
//                 }
//             }
//             else if (current_token->token_name == END_DOT)
//             {
//                 // Make sure next is end of file
//                 if (next_token->token_name == END_OF_FILE)
//                 {
//                     // DONE!
//                     return NULL;
//                 }
//                 else
//                 {
//                     COMPILER_EXCEPTION compiler_exception;
//                     compiler_exception.type = USER_ERROR;
                    
//                     strcpy(compiler_exception.message, string("Exoected End of File in line" + to_string(current_token->line_number)).c_str());
//                     throw compiler_exception;
//                 }
                
//             }
//             else
//             {
//                 COMPILER_EXCEPTION compiler_exception;
//                 compiler_exception.type = USER_ERROR;
                
//                 strcpy(compiler_exception.message, string("Expected an ID or END DOT in line" + to_string(current_token->line_number)).c_str());
//                 throw compiler_exception;
//             }
            
//         }
//         else if (start_sybmol->token_name == GLOBAL)
//         {
//             if (current_token->token_name == GLOBAL)
//             {
//                 // Next symbol needs to be a variable type
//                 if (next_token->token_name == INTEGER)
//                 {
//                     Token* return_token = Parse(next_token, next_token);
//                     // Make global
//                     return NULL;
//                 }
//                 else
//                 {
//                     COMPILER_EXCEPTION compiler_exception;
//                     compiler_exception.type = USER_ERROR;
//                     strcpy(compiler_exception.message, string("Expected an INTEGER or something in line" + to_string(current_token->line_number)).c_str());
//                     throw compiler_exception;
//                 }
//             }
//             else
//             {
//                 COMPILER_EXCEPTION compiler_exception;
//                 compiler_exception.type = USER_ERROR;
//                 strcpy(compiler_exception.message, string("Unexpected token in line" + to_string(current_token->line_number)).c_str());
//                 throw compiler_exception;
//             }
            
//         }

//         else if (start_sybmol->token_name == ID)
//         {
//             if (current_token->token_name == ID)
//             {
//                 if (next_token->token_name == SEMI_COLON)
//                 {
//                     /* were instantiating */
//                     return current_token;
//                 }
//                 else if (next_token->token_name == IS)
//                 {
//                     return Parse(next_token, next_token);
//                 }
//                 else
//                 {
//                     COMPILER_EXCEPTION compiler_exception;
//                     compiler_exception.type = PROGRAM_ERROR;
//                     strcpy(compiler_exception.message, string("Not implemented yet").c_str());
//                     throw compiler_exception;
//                 }
//             }
//             else
//             {
//                 COMPILER_EXCEPTION compiler_exception;
//                 compiler_exception.type = PROGRAM_ERROR;
//                 strcpy(compiler_exception.message, string("Not implemented yet").c_str());
//                 throw compiler_exception;
//             }
            
//         }
//         else if (current_token->token_name == IS)
//         {
//             // Everything that follows is the program... so what to do...
//             return Parse(next_token, next_token);
//         }
//         else if (start_sybmol->token_name == INTEGER)
//         {
//             if (current_token->token_name == INTEGER)
//             {
//                 if (next_token->token_name == ID)
//                 {
//                     Token* token_to_add = Parse(next_token, next_token);
//                     // Add token...
//                     return NULL;
//                 }
//                 else
//                 {
//                     COMPILER_EXCEPTION compiler_exception;
//                     compiler_exception.type = PROGRAM_ERROR;
//                     strcpy(compiler_exception.message, string("Not implemented yet").c_str());
//                     throw compiler_exception;
//                 }
//             }
//             else
//             {
//                 COMPILER_EXCEPTION compiler_exception;
//                 compiler_exception.type = PROGRAM_ERROR;
//                 strcpy(compiler_exception.message, string("Not implemented yet").c_str());
//                 throw compiler_exception;
//             }
//         }

//         else
//         {
//             COMPILER_EXCEPTION compiler_exception;
//             compiler_exception.type = PROGRAM_ERROR;
//             strcpy(compiler_exception.message, string("Unexpected token in line" + to_string(current_token->line_number)).c_str());
//             throw compiler_exception;
//         }
//         Parse(NULL, NULL);
        
//     }
//     catch(COMPILER_EXCEPTION e) {
//         if (e.type == 0)
//         {
//             _logger->error(string(e.message));
//         }
//         else if (e.type == 1)
//         {
//             _logger->user_error(string(e.message));
//         }
//         return NULL;
//     }
//     catch (string e)
//     {
//         _logger->error(e);
//         return NULL;
//     }
//     catch(std::exception& e) {
//         _logger->error("unknown error");
//         _logger->error(e.what());
//         return NULL;
//     }

// }
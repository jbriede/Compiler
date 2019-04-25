

#include "Logger.h"
#include "Id.h"
#include <unordered_map>
#ifndef ScopedVariables_h
#define ScopedVariables_h
using namespace std;

class ScopeVariables
{
public:
    ScopeVariables(ScopeVariables* previous_scope)
    {
        _previous_scope = previous_scope;
        _table = new unordered_map<string, Id*>();
    }

    Id* find(string lexeme)
    {
        std::unordered_map<std::string,Id*>::const_iterator got = _table->find (lexeme);

        if ( got == _table->end() )
        {
            if (_previous_scope != NULL)
            {
                return _previous_scope->find(lexeme);
            }
            else
            {
                COMPILER_EXCEPTION compiler_exception;
                compiler_exception.type = USER_ERROR;
                strcpy(compiler_exception.message, string("Id " + lexeme + " not declared.").c_str());
                throw compiler_exception;
            }
        }
        else
        {
            return got->second;
        }
    }

    void add(string lexeme, Id* id)
    {
        _table->insert(std::make_pair<std::string,Id*>(lexeme,id));
    }
    // Make sure were noe redifining 
    bool is_in_scope(string lexeme)
    {
        std::unordered_map<std::string,Id*>::const_iterator got = _table->find(lexeme);

        if ( got == _table->end() )
        {
            return false;
        }
        return true;
    }

    bool is_global_scope(string lexeme)
    {
        if (_previous_scope != NULL)
        {
            return _previous_scope->is_global_scope(lexeme);
        }
        else
        {
            std::unordered_map<std::string,Id*>::const_iterator got = _table->find(lexeme);

            if ( got == _table->end() )
            {
                return false;
            }
            return true; 
        }
    }

    void add_global(string lexeme, Id* id)
    {
        if (_previous_scope == NULL)
        {
            add(lexeme, id);
        }
        else
        {
            _previous_scope->add_global(lexeme, id);
        } 
    }
    
    
private:
    unordered_map<string, Id*>* _table;
    ScopeVariables* _previous_scope;
    

};

#endif 

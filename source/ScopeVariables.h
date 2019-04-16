

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
                return NULL;
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
    
    
private:
    unordered_map<string, Id*>* _table;
    ScopeVariables* _previous_scope;
    

};

#endif 

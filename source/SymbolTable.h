/*
 * Parser class
 */

#ifndef SymbolTable_h
#define SymbolTable_h
#include "Shared.h"

using namespace std;

struct SymbolNode
{
    Symbol* data; 
    struct SymbolNode *next;
};

struct Table
{
    Table* parent;
    SymbolNode* symbols;
};

class SymbolTable
{
public:
    SymbolTable(Logger* logger);
    ~SymbolTable();

    bool has_symbol_in_scope(Symbol* symbol_to_check);
    bool has_symbol_in_imediate_scope(Symbol* symbol_to_check);
    void add_symbol(Symbol* symbol);
    void branch();
    void back();
    void make_last_symbol_global();
    
private:
    Logger* _logger;

    /* For now variables in root table are global */
    Table* _root;
    Table* _current_table;

    void add_node(SymbolNode* new_node);
    void delete_symbols(SymbolNode* nodes);

    Symbol* last_symbol;

};

#endif 

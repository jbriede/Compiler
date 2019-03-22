/*
 * Logger class implementation
 */

#include "SymbolTable.h"


SymbolTable::SymbolTable(Logger* logger)
{
    _logger = logger;
    _root = new Table;
    _current_table = _root;
}

/* Make a new table and make that table the current table */
void SymbolTable::branch()
{
    Table* new_table = new Table;
    _current_table->parent = new_table;
    _current_table = new_table;
}

/* Can't have those memory leaks */
void SymbolTable::delete_symbols(SymbolNode* nodes)
{
    while (nodes != NULL)
    {
        SymbolNode* temp = nodes->next;
        delete nodes;
        nodes = temp;
    }
}

/* Delete current symbol table and point current table to parent  */
void SymbolTable::back()
{
    Table* temp = _current_table;

    /* I think we can just delete since its a one pass compiler */
    delete_symbols(_current_table->symbols);
    delete _current_table;

    _current_table = temp->parent;
}

void SymbolTable::add_symbol(Symbol* symbol)
{
    SymbolNode* node = new SymbolNode;
    node->data = symbol;
    add_node(node);
    last_symbol = symbol;
}

void SymbolTable::add_node(SymbolNode* new_node)
{
    SymbolNode* node = _current_table->symbols;
    while (node != NULL)
    {
        node = node->next;
    }
    node->next = new_node;
}
void SymbolTable::make_last_symbol_global()
{
    SymbolNode* node = _current_table->symbols;
    SymbolNode* prev_node = NULL;
    prev_node = node;
    while (node->next != NULL)
    {
        prev_node = node;
        node = node->next;
    }

    SymbolNode* global_symbols = _root->symbols;
    while (global_symbols != NULL)
    {
        global_symbols = global_symbols->next;
    }
    global_symbols->next = node;

    prev_node->next = NULL;
}

bool SymbolTable::has_symbol_in_scope(Symbol* symbol_to_check)
{
    Table* temp_table_pointer = _current_table;
    while(temp_table_pointer != NULL)
    {
        SymbolNode* temp_symbols_pointer = temp_table_pointer->symbols;
        while(temp_symbols_pointer != NULL)
        {
            if (strcmp(temp_symbols_pointer->data->symbol_name, symbol_to_check->symbol_name) == 0)
            {
                return true;
            }
            temp_symbols_pointer = temp_symbols_pointer->next;
        }
        temp_table_pointer = temp_table_pointer->parent;
    }
    return false;
}

bool SymbolTable::has_symbol_in_imediate_scope(Symbol* symbol_to_check)
{
    SymbolNode* temp_symbols_pointer = _current_table->symbols;
    while(temp_symbols_pointer != NULL)
    {
        if (strcmp(temp_symbols_pointer->data->symbol_name, symbol_to_check->symbol_name) == 0)
        {
            return true;
        }
        temp_symbols_pointer = temp_symbols_pointer->next;
    }
    return false;
}

SymbolTable::~SymbolTable()
{
}

/*
 * Parser class
 */

#ifndef SymbolTable_h
#define SymbolTable_h

#include "Shared.h"

using namespace std;

class SymbolTable
{
public:
    SymbolTable(Logger* logger);
    ~SymbolTable();
    
private:
    Logger* _logger;

};

#endif 

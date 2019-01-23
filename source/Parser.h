/*
 * Parser class
 */

#ifndef Parser_h
#define Parser_h

#include <iostream>
#include "Logger.h"
#include <string>
#include <fstream>
using namespace std;


class Parser
{
public:
    Parser(Logger* logger);
    ~Parser();
    bool load_file(string file_name);
    
private:
    Logger* _logger;
    ifstream _character_stream;


};

#endif 

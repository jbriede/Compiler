
#include "Logger.h"




#ifndef Writer_h
#define Writer_h
#include <fstream>

class Writer
{
public:
    Writer(Logger* logger, string output_file);
    ~Writer();
    void append_global(string line);
    void append_procedure(string line);
    void append_main(string line);

    
private:
    Logger* _logger;
    string _output_file;
    void open_file();
    void update_file();
    std::ofstream* _ofs;
    std::string globals;
    std::string procedures;
    std::string main;


};

#endif 


#include "Logger.h"




#ifndef Writer_h
#define Writer_h
#include <fstream>

class Writer
{
public:
    Writer(Logger* logger, string output_file);
    ~Writer();
    void write_line(string line);

    
private:
    Logger* _logger;
    string _output_file;
    void open_file();
    std::ofstream* _ofs;


};

#endif 

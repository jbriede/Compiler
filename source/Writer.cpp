#include "Writer.h"


Writer::Writer(Logger* logger, string output_file)
{
    _logger = logger;
    _output_file = output_file;
    open_file();
}
Writer::~Writer()
{
    _ofs->close();
}
void Writer::open_file()
{
    _ofs = new ofstream(_output_file.c_str(), std::ofstream::out);

    

}

void Writer::write_line(string line)
{
    (*_ofs) << line.c_str();
}
#include "Writer.h"


Writer::Writer(Logger* logger, string output_file)
{
    _logger = logger;
    _output_file = output_file;
    open_file();
    globals = "";
    procedures = "";
    main = "";
}
Writer::~Writer()
{
    _ofs->close();
}
void Writer::open_file()
{
    _ofs = new ofstream(_output_file.c_str(), std::ofstream::out);
}
void Writer::append_global(string line)
{
    globals += line;
    update_file();
}
void Writer::append_procedure(string line)
{
    procedures += line;
    update_file();
}
void Writer::append_main(string line)
{
    main += line;
    update_file();
}
void Writer::update_file()
{
    _ofs->close();
    _ofs = new ofstream(_output_file.c_str(), std::ofstream::out);
    (*_ofs) << globals.c_str();
    (*_ofs) << procedures.c_str();
    (*_ofs) << main.c_str();
}
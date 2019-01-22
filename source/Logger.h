/*
 * Logger class
 */

#ifndef Logger_h
#define Logger_h

#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;


#define LOGGER_DEBUG    3
#define LOGGER_INFO     2
#define LOGGER_WARN     1
#define LOGGER_ERROR    0

class Logger
{
public:
    Logger();
    
    bool set_log_level(int log_level);
    void debug(string message);
    void info(string message);
    void warn(string message);
    void error(string message);
private:
    int _log_level;
};

#endif /* Logger_h */

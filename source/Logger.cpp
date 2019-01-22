/*
 * Logger class implementation
 */

#include "Logger.h"

Logger::Logger()
{
    /* Default */
    _log_level = LOGGER_DEBUG;
}

bool Logger::set_log_level(int log_level)
{
    if ((log_level < LOGGER_ERROR) || (log_level > LOGGER_DEBUG))
    {
        cout << "Error: Could not set log level: " << log_level << " not allowed." << endl;
        return 0;
    }
    _log_level = log_level;
    return true;
}

void Logger::debug(string message)
{
    if (_log_level >= LOGGER_DEBUG)
    {
        cout << "Debug: " << message << endl;
    }
}
void Logger::info(string message)
{
    if (_log_level >= LOGGER_INFO)
    {
        cout << "Info: " << message << endl;
    }
}
void Logger::warn(string message)
{
    if (_log_level >= LOGGER_WARN)
    {
        cout << "Warning: " << message << endl;
    }
}
void Logger::error(string message)
{
    /* We always do this one */
    cout << "Error: " << message << endl;
}

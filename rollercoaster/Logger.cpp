/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Logger.h"
#include <iostream>

Logger::Logger()
{

}

bool Logger::error()
{
    return true;
}

bool Logger::warning()
{
    return true;
}

bool Logger::information()
{
    return true;
}

bool Logger::debug()
{
    return true;
}

void Logger::logMsg(const std::string &msg, const char *level, const char *file, const int line)
{
    std::cout << level << " " << file << ":" << line << " " << msg << std::endl;
}

Logger &Logger::get(const std::string &name)
{
    static Logger log;
    return log;
}



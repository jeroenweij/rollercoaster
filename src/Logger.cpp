/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Arduino.h"
#include "Logger.h"

Logger::Logger()
{ }

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

void Logger::logMsg(const String &msg, const char* level, const char* file, const int line)
{
    Serial.print(level);
    Serial.print(" ");
    Serial.print(file);
    Serial.print(":");
    Serial.print(line);
    Serial.print(" ");
    Serial.println(msg);
}

Logger &Logger::Get()
{
    static Logger log;

    return log;
}

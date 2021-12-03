/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include "SStream.h"

#define LOG_ERROR(message)                                            \
    Logger& logger = Logger::Get();                                   \
    if (logger.error())                                               \
    {                                                                 \
        std::stringstream log_stream;                                 \
        log_stream << message;                                        \
        logger.logMsg(log_stream.str(), "ERROR", __FILE__, __LINE__); \
    }

#define LOG_WARN(message)                                               \
    Logger& logger = Logger::Get();                                     \
    if (logger.warning())                                               \
    {                                                                   \
        std::stringstream log_stream;                                   \
        log_stream << message;                                          \
        logger.logMsg(log_stream.str(), "WARNING", __FILE__, __LINE__); \
    }

#define LOG_INFO(message)                                            \
    Logger& logger = Logger::Get();                                  \
    if (logger.information())                                        \
    {                                                                \
        std::stringstream log_stream;                                \
        log_stream << message;                                       \
        logger.logMsg(log_stream.str(), "INFO", __FILE__, __LINE__); \
    }

#define LOG_DEBUG(message)                                            \
    Logger& logger = Logger::Get();                                   \
    if (logger.debug())                                               \
    {                                                                 \
        std::stringstream log_stream;                                 \
        log_stream << message;                                        \
        logger.logMsg(log_stream.str(), "DEBUG", __FILE__, __LINE__); \
    }

class Logger
{
  public:
    Logger();
    bool error();
    bool warning();
    bool information();
    bool debug();

    void logMsg(const String& msg, const char* level, const char* file, const int line);

    static Logger& Get();

    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;
};

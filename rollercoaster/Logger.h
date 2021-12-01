/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <sstream>

#define LOG_ERROR(logger, message) \
    if ((logger).error()) \
    { \
        std::stringstream log_stream; \
        log_stream << message; \
        (logger).logMsg(log_stream.str(), "ERROR", __FILE__, __LINE__); \
    } \

#define LOG_WARN(logger, message) \
    if ((logger).warning()) \
    { \
        std::stringstream log_stream; \
        log_stream << message; \
        (logger).logMsg(log_stream.str(), "WARNING", __FILE__, __LINE__); \
    } \

#define LOG_INFO(logger, message) \
    if ((logger).information()) \
    { \
        std::stringstream log_stream; \
        log_stream << message; \
        (logger).logMsg(log_stream.str(), "INFO", __FILE__, __LINE__); \
    } \

#define LOG_DEBUG(logger, message) \
    if ((logger).debug()) \
    { \
        std::stringstream log_stream; \
        log_stream << message; \
        (logger).logMsg(log_stream.str(), "DEBUG", __FILE__, __LINE__); \
    } \


class Logger {
public:
    Logger();
    bool error();
    bool warning();
    bool information();
    bool debug();

    void logMsg(const std::string& msg, const char* level, const char* file, const int line);

    /// Returns a reference to the Logger with the given name.
    /// If the Logger does not yet exist, it is created.
    static Logger& get(const std::string& name);
};

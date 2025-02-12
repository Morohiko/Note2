#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>

// Enum class for log levels to provide type safety
enum class LogLevel {
    ERROR = 0,
    WARN = 1,
    INFO = 2,
    DEBUG = 3
};

class Logger {
public:
    static LogLevel currentLevel;
    
    static std::wstring getLogLevelStr(LogLevel level) {
        switch(level) {
            case LogLevel::ERROR:
                return L"ERROR";
            case LogLevel::WARN:
                return L"WARN";
            case LogLevel::INFO:
                return L"INFO";
            case LogLevel::DEBUG:
                return L"DEBUG";
            default: 
                return L"UNKNOWN";
        }
    }

    static void setLogLevel(LogLevel level) {
        currentLevel = level;
    }

    template <typename... Args>
    static void log(LogLevel level, Args&&... args) {
        if (static_cast<int>(level) <= static_cast<int>(currentLevel)) {
            std::wcout << getLogLevelStr(level) << L": ";
            (std::wcout << ... << std::forward<Args>(args)) << std::endl;
        }
    }
};

// Initialize static member
inline LogLevel Logger::currentLevel = LogLevel::DEBUG;

// Convenience macros
#define LOG_ERROR(...) Logger::log(LogLevel::ERROR, __VA_ARGS__)
#define LOG_WARN(...)  Logger::log(LogLevel::WARN, __VA_ARGS__)
#define LOG_INFO(...)  Logger::log(LogLevel::INFO, __VA_ARGS__)
#define LOG_DEBUG(...) Logger::log(LogLevel::DEBUG, __VA_ARGS__)

#endif // LOG_H
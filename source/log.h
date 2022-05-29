#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>

#define LOG_ERROR 0
#define LOG_WARN 1
#define LOG_INFO 2
#define LOG_DEBUG 3

static inline std::wstring getLogLevelStr(int &log_level) {
    switch(log_level) {
        case LOG_ERROR:
            return L"LOG_ERROR";
        case LOG_WARN:
            return L"LOG_WARN";
        case LOG_INFO:
            return L"LOG_INFO";
        case LOG_DEBUG:
            return L"LOG_DEBUG";
    default: 
        return L"NO_LOG_LEVEL";
    }
}
#define FULL_LOG_FORMAT __FILE__ << ":" << __LINE__ << ":" << __func__ << ": "
#define LOG_LEVEL_ONLY_LOG_FORMAT "" << getLogLevelStr(logLevel) << ": "
#define NO_LOG_FORMAT ""

#define LOG_FORMAT LOG_LEVEL_ONLY_LOG_FORMAT

static int CURRENT_LOG_LEVEL = LOG_DEBUG;

template <typename Arg, typename... Args>
void doWCoutPrint(int logLevel, Arg&& arg, Args&&... args) {
    if (logLevel <= CURRENT_LOG_LEVEL) {
        std::wcout << LOG_FORMAT;
        if (arg != nullptr) {
            std::wcout << std::forward<Arg>(arg);
            ((std::wcout << ' ' << std::forward<Args>(args)), ...);
        }
        std::wcout << std::endl;
    }
}

#define WLOG doWCoutPrint

#endif // LOG_H
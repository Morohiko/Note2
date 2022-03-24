#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>

#define FULL_LOG_FORMAT __FILE__ << ":" << __LINE__ << ":" << __func__ << ": "
#define NO_LOG_FORMAT ""

#define LOG_FORMAT NO_LOG_FORMAT

#define LOG_ERROR 0
#define LOG_WARN 1
#define LOG_INFO 2
#define LOG_DEBUG 3

static int currentLogLevel = LOG_INFO;

static void doCoutLogFormat() {
    std::cout << LOG_FORMAT;
}

static void doWCoutLogFormat() {
    std::cout << LOG_FORMAT;
}

template <typename Arg, typename... Args>
void doCoutPrint(int logLevel, Arg&& arg, Args&&... args) {
    if (logLevel <= currentLogLevel) {
        if (arg != nullptr) {
            std::cout << std::forward<Arg>(arg);
            ((std::cout << ' ' << std::forward<Args>(args)), ...);
        }
    }
    std::cout << std::endl;
}

template <typename Arg, typename... Args>
void doWCoutPrint(int logLevel, Arg&& arg, Args&&... args) {
    if (logLevel <= currentLogLevel) {
        std::wcout << LOG_FORMAT;
        if (arg != nullptr) {
            std::wcout << std::forward<Arg>(arg);
            ((std::wcout << ' ' << std::forward<Args>(args)), ...);
        }
        std::wcout << std::endl;
    }
}


#define LOG doCoutPrint
#define WLOG doWCoutPrint

#endif // LOG_H
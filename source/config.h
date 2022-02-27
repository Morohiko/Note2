#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <cstring>

#define SIZE_OF_HEADER 24
#define SIZE_OF_DATE 10
#define SIZE_OF_TIME 5
#define SIZE_OF_DATETIME SIZE_OF_DATE + SIZE_OF_TIME + 1
#define SIZE_OF_SIZE 6
// #define WITH_ENCODER

#define UNICODE
#ifdef UNICODE
#define CODEC "UTF-16"
#else
#define CODEC "UTF-8"
#endif

// status
#define STATUS_SUCCESS 0
#define STATUS_FAILURE 1
#define STATUS_END_OF_FILE 10
#define STATUS_FILE_NOT_FOUND 11
#define STATUS_TEST_FAILED 20

// logs
#define __FILENAME__ strrchr(__FILE__, '/') + 1
#define FULL_LOG_FORMAT __FILENAME__ << ":" << __LINE__ << ":" << __func__ << ": "
#define LOG_ERROR "DEBUG:" << FULL_LOG_FORMAT
#define LOG_WARN "WARN:" << FULL_LOG_FORMAT
#define LOG_INFO "INFO:" << FULL_LOG_FORMAT
#define LOG_DEBUG "DEBUG:" << FULL_LOG_FORMAT

#endif // CONFIG_H

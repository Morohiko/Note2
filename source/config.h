#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <cstring>

// header config
#define SIZE_OF_HEADER 24
#define DATE_POSITION 0
#define SIZE_OF_DATE 10
#define TIME_POSITION 11
#define SIZE_OF_TIME 5
#define DATETIME_POSITION 0
#define SIZE_OF_DATETIME 16
#define SIZE_POSITION 17
#define SIZE_OF_SIZE 6

// endcoder
#define WITH_ENCODER
#define UNICODE
#ifdef UNICODE
    #define CODEC_UTF_16
#else
    // not supported
    #define CODEC_UTF_8
#endif

// status
#define STATUS_SUCCESS 0
#define STATUS_FAILURE 1
#define STATUS_END_OF_FILE 10
#define STATUS_FILE_NOT_FOUND 11
#define STATUS_TEST_FAILED 20

static inline std::string status_str(int status) {
    switch (status) {
        case STATUS_SUCCESS:
            return "STATUS_SUCCESS";
        case STATUS_FAILURE:
            return "STATUS_FAILURE";
        case STATUS_END_OF_FILE:
            return "STATUS_END_OF_FILE";
        case STATUS_FILE_NOT_FOUND:
            return "STATUS_FILE_NOT_FOUND";
        case STATUS_TEST_FAILED:
            return "STATUS_TEST_FAILED";
        default:
            return "UNKNOWN STATUS";
    }
}

#endif // CONFIG_H

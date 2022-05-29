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

#endif // CONFIG_H

#ifndef CONFIG_H
#define CONFIG_H

#define SIZE_OF_HEADER 24
#define SIZE_OF_DATE 10
#define WITH_ENCODER

#define UNICODE
#ifdef UNICODE
#define CODEC "UTF-16"
#else
#define CODEC "UTF-8"
#endif

#endif // CONFIG_H

#ifndef ENCODER_H
#define ENCODER_H

#include <string>

// using namespace std;

class Encoder
{
public:
    // std::string encodeString(std::string *src);
    // std::string decodeString(std::string *src);

    std::string encodeStringByKey(std::string *src, std::string *key);
    std::string decodeStringByKey(std::string *src, std::string *key);

    // // not recomended, unicode issue
    // int encodeString(char *src, char *dest);
    // int decodeString(char *src, char *dest);

    // int encodeStringByKey(char *key, char *src, char *dest);
    // int decodeStringByKey(char *key, char *src, char *dest);
};

#endif // ENCODER_H

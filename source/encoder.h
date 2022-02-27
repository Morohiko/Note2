#ifndef ENCODER_H
#define ENCODER_H

#include <string>
#include "config.h"

// using namespace std;

class Encoder
{
public:
    std::string encodeStringByKey(std::string *src, std::string &key);
    std::string decodeStringByKey(std::string *src, std::string &key);
};

#endif // ENCODER_H

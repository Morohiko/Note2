#ifndef ENCODER_H
#define ENCODER_H

#include <string>
#include "config.h"

// using namespace std;

class Encoder
{
public:
    std::wstring encodeStringByKey(std::wstring &src, std::wstring &key);
    std::wstring decodeStringByKey(std::wstring &src, std::wstring &key);
};

#endif // ENCODER_H

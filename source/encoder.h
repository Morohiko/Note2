#ifndef ENCODER_H
#define ENCODER_H

#include <string>
#include "config.h"

class Encoder
{
public:

    /**
     * @brief encode src by key and save to dest
     *
     * @param[in] src data will be ecodded
     * @param[in] key using for encoding
     * @param[out] dest container for saving encodded data
     * 
     * @return execution status
     */
    int encodeStringByKey(std::wstring &src, std::wstring &key, std::wstring &dest);

    /**
     * @brief decode src by key and save to dest
     *
     * @param[in] src data will be decoded
     * @param[in] key using for decoding
     * @param[out] dest container for saving decodded data
     * 
     * @return execution status
     */
    int decodeStringByKey(std::wstring &src, std::wstring &key, std::wstring &dest);
};

#endif // ENCODER_H

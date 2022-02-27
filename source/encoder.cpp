#include <string>
#include <cassert>
#include <iostream>

#include "encoder.h"

using namespace std;

// string Encoder::encodeString(std::string *src) {
//     assert(src);

//     std::string dest;

//     for (int i = 0; i < src->length(); i++) {
//         dest.append(src->at(i).toUpper());
//     }
//     return dest;
// }

// string Encoder::decodeString(std::string *src) {
//     assert(src);

//     std::string dest;

//     for (int i = 0; i < src->length(); i++) {
//         dest.append(src->at(i).toLower());
//     }
//     return dest;
// }
#ifdef WITH_ENCODER
string Encoder::encodeStringByKey(std::string *src, std::string *key) {
    assert(src);

    std::string dest;
    int nkey = 0;

    for (int i = 0; i < src->size(); i++) {
        ushort buff = src->at(i).unicode() + static_cast<ushort>(key->at(nkey).unicode());
        dest.append(buff.str());
        if (key->size() <= ++nkey) nkey = 0;
    }
    std::cout << LOG_DEBUG << " encodeStringByKey src = " << *src << ", dest = " << dest << std::endl;
    return dest;
}


string Encoder::decodeStringByKey(std::string *src, std::string *key) {
    assert(src);

    std::string dest;

    int nkey = 0;
    for (int i = 0; i < src->size(); i++) {
        ushort buff = src->at(i).unicode() - static_cast<ushort>(key->at(nkey).unicode());
        dest.append(buff.str());
        if (key->size() <= ++nkey) nkey = 0;
    }
    std::cout << LOG_DEBUG << " decodeStringByKey src = " << *src << ", dest = " << dest << std::endl;
    return dest;
}
#endif
// int Encoder::encodeString(char *src, char *dest) {
//     assert(src); assert(dest);

//     std::cout << "src = " << src << ", dest = " << dest << std::endl;
//     return 0;
// }

// int Encoder::decodeString(char *src, char *dest) {
//     assert(src); assert(dest);

//     std::cout << "src = " << src << ", dest = " << dest << std::endl;
//     return 0;
// }

// int Encoder::encodeStringByKey(char *key, char *src, char *dest) {
//     assert(src); assert(dest); assert(key);

//     char *iter_src = src;
//     char *iter_dest = dest;
//     char *iter_key = key;
//     int i = 0;
    
//     while (*iter_src) {
//         *iter_dest = (unsigned char)*iter_src + (unsigned char)*iter_key;
//         //sprintf(*iter_dest, "%c", (*iter_src + *iter_key));
//         std::cout << *iter_dest << std::endl;
//         *iter_dest = (unsigned char)*iter_src - (unsigned char)*iter_key;
//         //sprintf(*iter_dest, "%c", (*iter_src - *iter_key));

//         std::cout << *iter_dest << std::endl;

//         iter_dest++; iter_src++; iter_key++;
//         if (!*iter_dest) {
//             iter_key = &key[0];
//         }
//         i++;
//     }
//     return 0;
// }

// int Encoder::decodeStringByKey(char *key, char *src, char *dest) {
//     assert(src); assert(dest); assert(key);

//     char *iter_src = &src[0];
//     char *iter_dest = &dest[0];
//     char *iter_key = &key[0];

//     while (*iter_src) {
//         *iter_dest = *iter_src - *iter_key;
//         iter_dest++; iter_src++; iter_key++;
//         if (!*iter_dest) {
//             iter_key = &key[0];
//         }
//     }
//     return 0;
// }

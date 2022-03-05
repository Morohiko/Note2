#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <ctime>

#include "config.h"

class Parser
{
public:
    Parser();

    int parseHeadFromString(std::wstring &text, std::wstring &date, int &size);
    int parseHeadFromStringGetSize(std::wstring &text, int &size);
    int parseHeadFromStringGetDateString(std::wstring &text, std::wstring &date);
    int parseHeadFromStringGetTimeString(std::wstring &text, std::wstring &time);

    std::wstring generateHead(std::wstring &currentDateTime, int size);
    std::wstring generateStringFromSize(int size);
};

#endif // PARSER_H

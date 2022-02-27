#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <ctime>

class Parser
{
public:
    Parser();

    int parseHeadFromString(std::string &text, std::string &date, int &size);
    int parseHeadFromStringGetSize(std::string &text, int &size);
    int parseHeadFromStringGetDateString(std::string &text, std::string &date);
    int parseHeadFromStringGetTimeString(std::string &text, std::string &time);

    std::string generateHead(std::string &currentDateTime, int size);
    std::string generateStringFromSize(int size);
};

#endif // PARSER_H

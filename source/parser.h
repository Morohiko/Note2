#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <ctime>

class Parser
{
public:
    Parser();

    /**
     * @brief parse date and size from text
     *
     * @param[in] text input text with head
     * @param[out] date parsed date
     * @param[out] size parsed size
     * 
     * @return execution status
     */
    int parseHeadFromString(std::wstring &text, std::wstring &date, int &size);

    /**
     * @brief parse size from text
     *
     * @param[in] text input text with head
     * @param[out] size parsed size
     * 
     * @return execution status
     */
    int parseHeadFromStringGetSize(std::wstring &text, int &size);

    /**
     * @brief parse date from text
     *
     * @param[in] text input text with head
     * @param[out] date parsed date
     * 
     * @return execution status
     */
    int parseHeadFromStringGetDateString(std::wstring &text, std::wstring &date);

    /**
     * @brief parse time from text
     *
     * @param[in] text input text with head
     * @param[out] time parsed time
     * 
     * @return execution status
     */
    int parseHeadFromStringGetTimeString(std::wstring &text, std::wstring &time);

    /**
     * @brief generate head from date and size
     *
     * @param[in] currentDateTime date for head
     * @param[in] size size for head
     * @param[out] dest generated head with date and size
     * 
     * @return execution status
     */
    int generateHead(std::wstring &currentDateTime, int size, std::wstring &dest);

    /**
     * @brief generate size string from int size
     *
     * @param[in] size size in int
     * @param[out] dest generated string size
     * 
     * @return execution status
     */
    int generateStringFromSize(int size, std::wstring &dest);

};

#endif // PARSER_H

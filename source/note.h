#ifndef NOTE_H
#define NOTE_H

#include <list>
#include "file.h"
#include "encoder.h"
#include "parser.h"
#include "config.h"
#include "datetime.h"

class Note
{
public:
    File file;
    Encoder encoder;
    Parser parser;
    DateTime datetime;

    /**
     * @brief save filename of file for read/write data
     *
     * @param[in] filename name of file
     * 
     * @return execution status
     */
    int setFilename(std::string &filename);

    /**
     * @brief read body from file, with incoming date
     *
     * @param[in] date read body with this date
     * @param[in] key using for decode data from file
     * @param[out] outputBody readded body from file
     * 
     * @return execution status
     */
    int performReadByDate(tm &date, std::wstring &key, std::wstring &ouptutBody);

    /**
     * @brief read add date from file
     *
     * @param[in] key using for decode data from file
     * @param[out] dateList container with read dates
     * 
     * @return execution status
     */
    int performReadAllDate(std::wstring &key, std::list<std::wstring> &dateList);

    /**
     * @brief write text to end of file
     *
     * @param[in] text data will be written to end of file
     * @param[in] isCustomTime check if use custom time or currentTime
     * @param[in] currentDateTime use customTime if isCustomTime is true
     * @param[in] key using for encode text before write to file
     * 
     * @return execution status
     */
    int performWriteToFile(std::wstring &text, bool isCustomTime, tm& customDateTime, std::wstring &key);

private:
    /**
     * @brief find position of head in file
     *
     * @param[in] head head wich will be find
     * @param[in] key using for decode data from file
     * @param[out] pos container which will save position of head in file
     * 
     * @return execution status
     */
    int _findPositionByHeader(std::wstring &head, std::wstring &key, int &pos);

    /**
     * @brief find position of date in file
     *
     * @param[in] date date wich will be find
     * @param[in] key using for decode data from file
     * @param[out] pos container which will save position of date in file
     * 
     * @return execution status
     */
    int _findPositionByDate(std::wstring &date, std::wstring &key, int &startPos, int &pos);

    /**
     * @brief check if key compares with file
     *
     * @param[in] key
     * 
     * @return true if key is valid, false otherwise
     */
    bool _isValidKey(std::wstring &key);
};

#endif // NOTE_H

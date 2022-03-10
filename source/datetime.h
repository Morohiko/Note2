#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>
#include <string>

// read/convert datetime
class DateTime {

    /**
     * @brief container with datetime, for get/update functions
     */
    tm datetime;

public:
    DateTime();

    /**
     * @brief save current date/time from linux date/time to datetime field
     *
     * @return execution status
     */
    int updateToCurrentDateTime();

    /**
     * @brief save datetime from tm to datetime field
     *
     * @param[in] tm datetime struct, will be saved to datetime field
     * 
     * @return execution status
     */
    int updateToCustomDateTime(tm &tm);

    /**
     * @brief get saved date from datetime field
     *        format: yyyy/MM/dd
     *
     * @param[out] dest container for getting saved date
     * 
     * @return execution status
     */
    int getCurrentDateString(std::wstring &dest);

    /**
     * @brief get saved date/time from datetime field
     *        format: yyyy/MM/dd.hh:mm
     *
     * @param[out] dest container for getting saved date/time
     * 
     * @return execution status
     */
    int getCurrentDateTimeString(std::wstring &dest);

    /**
     * @brief convert tm struct to wstring in datetime convention
     *        format: yyyy/MM/dd.hh:mm
     * 
     * @param[in] tm datetime struct, will be saved to datetime field
     * @param[out] dest container for getting converted date/time
     * 
     * @return execution status
     */
    int convertTmDateToString(tm &tm, std::wstring &dest);

};

#endif // DATETIME_H

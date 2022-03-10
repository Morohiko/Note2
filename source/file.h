#ifndef FILE_H
#define FILE_H

class File
{
public:

    /**
     * @brief check if file in path is empty
     * 
     * @return true - file is empty, false - if not
     */
    bool isCurrentFileEmpty();

    /**
     * @brief write to end of file in the path
     *
     * @param[in] src data will be written in the file
     * 
     * @return execution status
     */
    int writeToEndFile(std::wstring &src);

    /**
     * @brief read from file
     *
     * @param[in] pos from the position will be read
     * @param[in] size size of data will be read
     * @param[out] output container with read data
     * 
     * @return execution status
     */
    int readFromFileByPosition(int &pos, int size, std::wstring &output);

    /**
     * @brief set path to target file
     *
     * @param[in] src path to file will be saved
     * 
     * @return execution status
     */
    int setPathToFile(std::string &src);

private:
    std::string path;

    /**
     * @brief check if file is exist
     *
     * @param[in] filename path to file for check
     * 
     * @return execution status
     */
    int isFileExists(const std::string &filename);
};

#endif // FILE_H

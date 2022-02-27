#ifndef FILE_H
#define FILE_H

class File
{
public:
    bool isCurrentFileEmpty();
    int writeToEndFile(std::string &src);
    int readFromFileByPosition(int pos, int size, std::string &output);
    int setPathToFile(std::string src);
private:
    std::string path;
    int isFileExists(const std::string filename);
};

#endif // FILE_H

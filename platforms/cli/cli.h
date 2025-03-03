#ifndef CLI_H
#define CLI_H

#include <vector>
#include <filesystem>
#include <string>

#include "note.h"
#include "log.h"

namespace fs = std::filesystem;

class cli : public Note {
public:

    cli() {
        Logger::setLogType(LogType::FILE);
    }

    /**
     * @brief run cli
     * 
     * @return execution status
     */
    void run();

private:
    std::string run_file_browser();
    void refresh_file_list(std::vector<std::string>& file_list, fs::path& current_path);
};

#endif // CLI_H

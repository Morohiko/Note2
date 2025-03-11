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
    std::string password_content = "";

    /**
     * @brief run file browser
     * 
     * @return selected file
     */
    std::string run_file_browser();

    /**
     * @brief refresh file list
     * 
     * @param[in] file_list list of files
     * @param[in] current_path current path
     * 
     * @return execution status
     */
    void refresh_file_list(std::vector<std::string>& file_list, fs::path& current_path);

    /**
     * @brief read by date
     * 
     * @param[in] selected_date selected date
     * @param[in] password_content password content
     * @param[in] text_content text content
     * 
     * @return execution status
     */
    void read_by_date(std::string& selected_date, std::string& text_content);
};

#endif // CLI_H

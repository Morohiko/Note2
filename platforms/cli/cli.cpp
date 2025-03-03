#include <filesystem>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>
#include <string>
#include <vector>

#include "cli.h"
#include "config.h"
#include "log.h"

namespace fs = std::filesystem;
using namespace ftxui;

void cli::refresh_file_list(std::vector<std::string> &file_list,
                            fs::path &current_path) {
    file_list.clear();
    const int view_height = 20; // Match the height set in the renderer

    // Add parent directory entry if applicable
    if (current_path.has_parent_path() &&
          current_path != current_path.root_path()) {
        file_list.push_back("..");
    }

    // Add all directory entries
    std::vector<fs::path> all_entries;
    for (const auto &entry : fs::directory_iterator(current_path)) {
        all_entries.push_back(entry.path());
        file_list.push_back(entry.path().filename().string());
    }
}

std::string cli::run_file_browser() {
    fs::path current_path = fs::current_path();
    std::string result = "";
    int file_menu_selected = 0;
    std::vector<std::string> file_list;

    refresh_file_list(file_list, current_path);
    auto file_menu = Menu(&file_list, &file_menu_selected);

    // Create a new full-screen modal for the file browser.
    auto file_screen = ScreenInteractive::Fullscreen();

    // Common open action: if selected is a directory, navigate into it; if file,
    // select.
    auto open_action = [&]() {
        if (file_list[file_menu_selected] == "..") {
            current_path = current_path.parent_path();
            refresh_file_list(file_list, current_path);
        } else {
            fs::path selected = current_path / file_list[file_menu_selected];
            if (fs::is_directory(selected)) {
                current_path = selected;
                refresh_file_list(file_list, current_path);
            } else {
                result = selected.string();
                file_screen.Exit();
            }
        }
    };

    auto open_button = Button("Open", open_action);
    auto cancel_button = Button("Cancel", [&]() { file_screen.Exit(); });

    // Wrap file_menu so that pressing Enter triggers the open action.
    auto file_menu_with_hotkey = CatchEvent(file_menu, [&](Event event) {
        if (event == Event::Return) {
            open_action();
            return true;
        }
        return false;
    });

    // Create a dedicated renderer for the file menu that forces a fixed height.
    auto scrollable_file_menu = Renderer(file_menu_with_hotkey, [&] {
        auto rendered_menu = file_menu_with_hotkey->Render() | frame |
                            size(HEIGHT, EQUAL, 20) | flex;
        return hbox({
            rendered_menu,
            filler() | vscroll_indicator,
        });
    });

    auto file_browser_container = Container::Vertical({
        scrollable_file_menu,
        Container::Horizontal({open_button, cancel_button}),
    });

    auto file_browser_renderer = Renderer(file_browser_container, [&] {
        return window(text("Select a file (" + current_path.string() + ")"),
                      vbox({
                          scrollable_file_menu->Render(),
                          hbox({
                              open_button->Render() | flex,
                              cancel_button->Render() | flex,
                          }),
                      })) |
              center;
    });

    file_screen.Loop(file_browser_renderer);
    return result;
}

void cli::run() {
    auto screen = ScreenInteractive::Fullscreen();

    // ---------------------------
    // Tree and Text.
    // ---------------------------
    std::vector<std::string> tree_items = {""};
    int selected_item = 0;
    auto tree_component = Menu(&tree_items, &selected_item);

    std::string text_content =
        "Details for: " + tree_items[selected_item] + " -- Edit this text";
    auto input_component = Input(&text_content, "Edit text here...");

    // ---------------------------
    // Date/Time Field.
    // ---------------------------
    InputOption datetime_option = {
        .multiline = false
    };
    std::string datetime_content = "YYYY-MM-DD HH:MM:SS";
    auto datetime_input = Input(&datetime_content, "Enter date/time...");

    // ---------------------------
    // Password Field.
    // ---------------------------
    InputOption password_option = {
        .password = true,
        .multiline = false
    };
    std::string password_content = "";
    auto password_input =
        Input(&password_content, "Enter password...", password_option);

    // ---------------------------
    // Browse Files Button.
    // ---------------------------
    std::string selected_file = "";
    auto browse_files_button = Button("Browse Files", [&]() {
        selected_file = run_file_browser();
        int retval = setFilename(selected_file);
    });

    // ---------------------------
    // Read button.
    // ---------------------------
    auto read_button = Button("Read", [&] {
        std::wstring wpassword =
            std::wstring(password_content.begin(), password_content.end());
        std::list<std::wstring> date_list;
        performReadAllDate(wpassword, date_list);
        tree_items.clear();
        for (auto date : date_list) {
            tree_items.push_back(std::string(date.begin(), date.end()));
        }
    });

    // ---------------------------
    // Layout Composition.
    // ---------------------------
    auto split_container = Container::Horizontal({
        tree_component,
        input_component,
    });

    auto main_container = Container::Vertical({
        split_container,
        datetime_input,
        password_input,
        browse_files_button,
        read_button,
    });

    auto main_renderer = Renderer(main_container, [&]() {
        return vbox({
            hbox({
                tree_component->Render() | border | size(HEIGHT, GREATER_THAN, 5),
                input_component->Render() | border | size(HEIGHT, GREATER_THAN, 5),
            }) | flex,
            datetime_input->Render() | border | center,
            password_input->Render() | border | center,
            browse_files_button->Render() | center,
            read_button->Render() | center,
        });
    });

    screen.Loop(main_renderer);
}

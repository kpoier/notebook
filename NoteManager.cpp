#include "NoteManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

static string to_lower_copy(string s) {
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
}

static string format_time(std::time_t t) {
    std::tm tm{};
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void NoteManager::print_note(const Note& n) const {
    cout << "---------------" << endl;
    cout << "Id:        " << n.get_id() << endl;
    cout << "Title:     " << n.get_title() << endl;
    cout << "Content:   " << n.get_content() << endl;
    cout << "Modified:  " << format_time(n.get_date_modified()) << endl;
    cout << "Created:   " << format_time(n.get_created()) << endl;
}

void NoteManager::print_result(const vector<Note>& print_list) const {
    cout << "A total of " << print_list.size() << " records were found" << endl;
    for (const auto& n : print_list) {
        print_note(n);
    }
}

void NoteManager::add_note(const string& title, const string& content) {
    notes.emplace_back(next_id++, title, content);
}

void NoteManager::add_note(const std::string& title, const std::string& content, const std::time_t& created, const std::time_t& modified) {
    notes.emplace_back(next_id++, title, content, created, modified);
}

void NoteManager::display_all() const {
    print_result(notes);
}

void NoteManager::search_note(const string& keyword) const {
    string key = to_lower_copy(keyword);
    bool any = false;
    for (const auto& n : notes) {
        string title_l = to_lower_copy(n.get_title());
        string content_l = to_lower_copy(n.get_content());
        if (title_l.find(key) != string::npos || content_l.find(key) != string::npos) {
            if (!any) {
                cout << "Matching records:" << endl;
            }
            any = true;
            print_note(n);
        }
    }
    if (!any) {
        cout << "No records found for keyword: " << keyword << endl;
    }
}

bool NoteManager::delete_note_by_id(int target_id) {
    auto before = notes.size();
    notes.erase(remove_if(notes.begin(), notes.end(), [&](const Note& n) { return n.get_id() == target_id; }), notes.end());
    return notes.size() != before;
}

bool NoteManager::edit_note_by_id(int target_id, const string& new_title, const string& new_content) {
    for (auto& n : notes) {
        if (n.get_id() == target_id) {
            if (!new_title.empty()) n.edit_note_title(new_title);
            if (!new_content.empty()) n.edit_note_content(new_content);
            return true;
        }
    }
    return false;
}

std::string NoteManager::get_note_title(int id) const {
    for (const auto& n : notes) {
        if (n.get_id() == id) {
            return n.get_title();
        }
    }
    return "None";
}

std::string NoteManager::get_note_content(int id) const {
    for (const auto& n : notes) {
        if (n.get_id() == id) {
            return n.get_content();
        }
    }
    return "None";
}

void NoteManager::save_to_file(const std::string& filename) {
    std::ofstream save_file;
    save_file.open(filename);
    if (!save_file.is_open()) std::cerr << "Error opening file." << std::endl;
    for (const auto& n : notes) {
        save_file << "id=" << n.get_id() << std::endl;
        save_file << "title=" << n.get_title() << std::endl;
        save_file << "content=" << n.get_content() << std::endl;
        save_file << "modified=" << n.get_date_modified() << std::endl;
        save_file << "created=" << n.get_created() << std::endl << std::endl;
    }
    save_file.close();
}

void NoteManager::load_from_file(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    // Reset current notes and prepare to load
    notes.clear();

    std::string line;
    int id = -1;
    std::string title;
    std::string content;
    std::time_t created = 0;
    std::time_t modified = 0;
    int max_id = -1;

    auto flush_record = [&]() {
        if (id != -1) {
            notes.emplace_back(id, title, content, created, modified);
            if (id > max_id) max_id = id;
        }
        id = -1;
        title.clear();
        content.clear();
        created = 0;
        modified = 0;
    };

    while (std::getline(in, line)) {
        if (line.empty()) {
            flush_record();
            continue;
        }

        if (line.rfind("id=", 0) == 0) {
            try { id = std::stoi(line.substr(3)); } catch (...) { id = -1; }
        } else if (line.rfind("title=", 0) == 0) {
            title = line.substr(6);
        } else if (line.rfind("content=", 0) == 0) {
            content = line.substr(8);
        } else if (line.rfind("modified=", 0) == 0) {
            try { modified = static_cast<std::time_t>(std::stoll(line.substr(9))); } catch (...) { modified = 0; }
        } else if (line.rfind("created=", 0) == 0) {
            try { created = static_cast<std::time_t>(std::stoll(line.substr(8))); } catch (...) { created = 0; }
        }
    }

    // In case file doesn't end with a blank line
    flush_record();

    // Update next_id so future additions get unique IDs
    next_id = (max_id >= 0) ? (max_id + 1) : 0;
}


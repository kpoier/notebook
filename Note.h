#pragma once

#include <string>
#include <ctime>
#include <utility>

class Note {
private:
    int id;
    std::string title;
    std::string content;
    std::time_t created;
    std::time_t date_modified;

    void init_time();
    void modify_time();
public:
    Note() : Note(-1, "", "") {
    }

    Note(int id, std::string title, std::string content) : 
        id(id), 
        title(std::move(title)), 
        content(std::move(content)) {
        init_time();
    }

    Note(std::string title, std::string content) : Note(-1, std::move(title), std::move(content)) {
    }

    Note(int id, std::string title, std::string content, std::time_t created, std::time_t modified) : 
        id(id), 
        title(std::move(title)), 
        content(std::move(content)), 
        created(std::move(created)), 
        date_modified(std::move(modified)) {}

    int get_id() const;
    const std::string& get_title() const;
    const std::string& get_content() const;
    const std::time_t& get_created() const;
    const std::time_t& get_date_modified() const;
    void edit_note_title(const std::string& new_title);
    void edit_note_content(const std::string& new_content);
};

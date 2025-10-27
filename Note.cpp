#include "Note.h"
#include <iostream>


void Note::init_time() {
    time_t os_binary_time;
    time(&os_binary_time);
    created = os_binary_time;
    date_modified = os_binary_time;
}
void Note::modify_time() {
    time_t os_binary_time;
    time(&os_binary_time);
    date_modified = os_binary_time;
}
int Note::get_id() const {
    return id;
}
const std::string& Note::get_title() const {
    return title;
}
const std::string& Note::get_content() const {
    return content;
}
const std::time_t& Note::get_created() const {
    return created;
}
const std::time_t& Note::get_date_modified() const {
    return date_modified;
}

void Note::edit_note_title(const std::string& new_title) {
    title = new_title;
    modify_time();
}

void Note::edit_note_content(const std::string& new_content) {
    content = new_content;
    modify_time();
}

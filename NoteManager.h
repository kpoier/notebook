#pragma once

#include "Note.h"
#include <vector>
#include <string>

class NoteManager {
private:
    std::vector<Note> notes;
    int next_id;
    void print_note(const Note& n) const;
    void print_result(const std::vector<Note>& print_list) const;
public:
    NoteManager() : next_id(0) {};
    void add_note(const std::string& title, const std::string& content);
    void add_note(const std::string& title, const std::string& content, const std::time_t& created, const std::time_t& modified);
    void display_all() const;       // can't change NoteManager (const)
    void search_note(const std::string& keyword) const;
    bool delete_note_by_id(int target_id);
    bool edit_note_by_id(int target_id, const std::string& new_title, const std::string& new_content);
    std::string get_note_title(int id) const;
    std::string get_note_content(int id) const;
    void save_to_file(const std::string& filename);
    void load_from_file(const std::string& filename);
};

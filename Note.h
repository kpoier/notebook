#pragma once

#include <iostream>
#include <ctime>

using namespace std;

class Note {
private:
    int id;
    string title;
    string content;
    time_t created;
    time_t date_modified;

    void init_time();
public:
    Note() : Note(-1, "", "") {
    }

    Note(int Id, string Title, string Content) : 
        id(Id), 
        title(Title), 
        content(Content) {
        init_time();
    }

    Note(string Title, string Content) : Note(-1, Title, Content) {
    }

    int get_id();
    string get_title();
    string get_content();
    time_t get_created();
    time_t get_date_modified();
};
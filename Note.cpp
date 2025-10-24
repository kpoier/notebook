#include "Note.h"

void Note::init_time() {
    time_t os_binary_time;
    time(&os_binary_time);
    created = os_binary_time;
    date_modified = os_binary_time;
}
int Note::get_id() {
    return id;
}
string Note::get_title() {
    return title;
}
string Note::get_content() {
    return content;
}
time_t Note::get_created() {
    return created;
}
time_t Note::get_date_modified() {
    return date_modified;
}
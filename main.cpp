#include <iostream>
#include <cstdlib>
#include <limits>
#include <windows.h>
#include "Note.h"
#include "NoteManager.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    NoteManager m;

    char choice;

    
    while (true) {
        cout << "====== Notebook ======" << endl;
        cout << "1: Add" << endl;
        cout << "2: Display" << endl;
        cout << "3: Search" << endl;
        cout << "4: Delete" << endl;
        cout << "5: Save" << endl;
        cout << "6: Load" << endl;
        cout << "7: Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == '1') {
            // add
            string title, content;
            cout << "-----Add mode-----" << endl;
            cout << "  Title: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, title);
            cout << "Content: ";
            getline(cin, content);
            m.add_note(title, content);
        } else if (choice == '2') {
            // display
            cout << "-----Display mode-----" << endl;
            m.display_all();
        } else if (choice == '3') {
            // search
            string keyword;
            cout << "-----Search mode-----" << endl;
            cout << "Please enter keyword: ";
            cin >> keyword;
            m.search_note(keyword);
        } else if (choice == '4') {
            // delete
            int input;
            cout << "-----Delete mode-----" << endl;
            cout << "Please enter the id that you want to delete (enter -1 to exit)" << endl;
            cin >> input;
            if (input == -1) continue;
            if (m.delete_note_by_id(input)) cout << "Note deleted!" << endl;
            else cout << "Failed to delete note" << endl;
        } else if (choice == '5') {
            // save
            cout << "-----Save mode-----" << endl;
            m.save_to_file("notes.txt");
        } else if (choice == '6') {
            // load
            cout << "-----Load mode-----" << endl;
            m.load_from_file("notes.txt");
        } else if (choice == '7') {
            // exit
            cout << "Exiting the program." << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    //system("pause");

    return 0;
}
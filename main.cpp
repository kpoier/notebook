#include <iostream>
#include <cstdlib>
#include "Note.h"

using namespace std;

int main() {
    Note note;
    Note n1("Title", "Content");
    cout << n1.get_id() << endl;
    Note n2(2, "Title", "Content");
    cout << n2.get_id() << endl;
    return 1;

    int choice;

    while (true) {
        cout << "====== Notebook ======" << endl;
        cout << "1: Add" << endl;
        cout << "2: Display" << endl;
        cout << "3: Search" << endl;
        cout << "4: Delete" << endl;
        cout << "5: Save" << endl;
        cout << "6: Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 6) {
            if (choice == 6) {
                cout << "Exiting the program." << endl;
                break;
            }
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    system("pause");

    return 0;
}
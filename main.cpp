#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Book {
public:
    int id;
    char title[50];
    char author[50];
    bool issued;

    void input() {
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Title: ";
        cin.getline(title, 50);
        cout << "Enter Author: ";
        cin.getline(author, 50);
        issued = false;
    }

    void display() {
        cout << "\nID: " << id;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nStatus: " << (issued ? "Issued" : "Available") << endl;
    }
};

// Add Book
void addBook() {
    Book b;
    ofstream file("library.dat", ios::binary | ios::app);

    b.input();
    file.write((char*)&b, sizeof(b));

    file.close();
    cout << "\nBook Added Successfully!\n";
}

// Display All Books
void displayBooks() {
    Book b;
    ifstream file("library.dat", ios::binary);

    while (file.read((char*)&b, sizeof(b))) {
        b.display();
        cout << "----------------------";
    }

    file.close();
}

// Search Book
void searchBook() {
    Book b;
    ifstream file("library.dat", ios::binary);
    char keyword[50];
    bool found = false;

    cin.ignore();
    cout << "Enter Title or Author to search: ";
    cin.getline(keyword, 50);

    while (file.read((char*)&b, sizeof(b))) {
        if (strstr(b.title, keyword) || strstr(b.author, keyword)) {
            b.display();
            found = true;
        }
    }

    if (!found)
        cout << "\nBook not found!\n";

    file.close();
}

// Issue Book
void issueBook() {
    Book b;
    fstream file("library.dat", ios::binary | ios::in | ios::out);
    int id;
    bool found = false;

    cout << "Enter Book ID to issue: ";
    cin >> id;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.id == id && !b.issued) {
            b.issued = true;

            file.seekp(-sizeof(b), ios::cur);
            file.write((char*)&b, sizeof(b));

            cout << "\nBook Issued Successfully!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nBook not available or not found!\n";

    file.close();
}

// Return Book
void returnBook() {
    Book b;
    fstream file("library.dat", ios::binary | ios::in | ios::out);
    int id;
    bool found = false;

    cout << "Enter Book ID to return: ";
    cin >> id;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.id == id && b.issued) {
            b.issued = false;

            file.seekp(-sizeof(b), ios::cur);
            file.write((char*)&b, sizeof(b));

            cout << "\nBook Returned Successfully!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nBook not found or not issued!\n";

    file.close();
}

// Main Menu
int main() {
    int choice;

    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addBook(); break;
        case 2: displayBooks(); break;
        case 3: searchBook(); break;
        case 4: issueBook(); break;
        case 5: returnBook(); break;
        case 6: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
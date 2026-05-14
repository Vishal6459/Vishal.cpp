#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Book {
public:
    char title[100];
    char author[50];
    int id;

    void addBook();
    void displayBook() const;
};

void Book::addBook() {
    cout << "Enter Book ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Book Title: ";
    cin.getline(title, 100);
    cout << "Enter Author Name: ";
    cin.getline(author, 50);
    cout << "Book Added Successfully!\n";
}

void Book::displayBook() const {
    cout << "ID: " << id << "\nTitle: " << title << "\nAuthor: " << author << "\n";
}

void saveBook(const Book& book) {
    ofstream file("library.txt", ios::app);
    if (!file) {
        cout << "Error: Unable to open file!\n";
        return;
    }
    file << book.id << "|" << book.title << "|" << book.author << endl;
    file.close();
}

void displayAllBooks() {
    ifstream file("library.txt");
    if (!file) {
        cout << "No books found!\n";
        return;
    }

    Book book;
    while (file >> book.id) {
        file.ignore();
        file.getline(book.title, 100, '|');
        file.getline(book.author, 50);
        book.displayBook();
        cout << "----------------------\n";
    }
    file.close();
}

void searchBook(const char* searchTitle) {
    ifstream file("library.txt");
    if (!file) {
        cout << "Error: Unable to open file!\n";
        return;
    }

    Book book;
    bool found = false;
    while (file >> book.id) {
        file.ignore();
        file.getline(book.title, 100, '|');
        file.getline(book.author, 50);
        if (strcmp(book.title, searchTitle) == 0) {
            cout << "Book Found:\n";
            book.displayBook();
            found = true;
            break;
        }
    }
    file.close();
    if (!found) cout << "Book not found!\n";
}

int main() {
    int choice;
    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n2. Display All Books\n3. Search Book\n4. Exit\nChoose an option: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                Book book;
                book.addBook();
                saveBook(book);
                break;
            }
            case 2:
                displayAllBooks();
                break;
            case 3: {
                cin.ignore();
                char searchTitle[100];
                cout << "Enter book title to search: ";
                cin.getline(searchTitle, 100);
                searchBook(searchTitle);
                break;
            }
            case 4:
                return 0;
            default:
                cout << "Invalid Choice! Try Again.\n";
        }
    }
}

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;
    Book* next; 

    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        issued = false;
        next = NULL;
    }
};

class Library {
private:
    Book* head;

public:
    Library() {
        head = NULL;
    }

    void addBook(int id, string title, string author) {
        Book* newBook = new Book(id, title, author);
        if (head == NULL) {
            head = newBook;
        } else {
            Book* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newBook;
        }
        cout << "\nBook added successfully!\n";
    }

    void displayBooks() {
        if (head == NULL) {
            cout << "\nNo books available.\n";
            return;
        }
        Book* temp = head;
        cout << "\n--- Library Books ---\n";
        while (temp != NULL) {
            cout << "ID: " << temp->id
                 << " | Title: " << temp->title
                 << " | Author: " << temp->author
                 << " | Status: " << (temp->issued ? "Issued" : "Available") << endl;
            temp = temp->next;
        }
    }

    Book* searchBook(int id) {
        Book* temp = head;
        while (temp != NULL) {
            if (temp->id == id)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }

    void issueBook(int id) {
        Book* b = searchBook(id);
        if (b == NULL) {
            cout << "\nBook not found!\n";
            return;
        }
        if (b->issued) {
            cout << "\nBook already issued!\n";
        } else {
            b->issued = true;
            cout << "\nBook issued successfully!\n";
        }
    }

    void returnBook(int id) {
        Book* b = searchBook(id);
        if (b == NULL) {
            cout << "\nBook not found!\n";
            return;
        }
        if (!b->issued) {
            cout << "\nBook was not issued.\n";
        } else {
            b->issued = false;
            cout << "\nBook returned successfully!\n";
        }
    }

    void deleteBook(int id) {
        if (head == NULL) {
            cout << "\nNo books to delete.\n";
            return;
        }

        Book* temp = head;
        Book* prev = NULL;

        if (temp != NULL && temp->id == id) {
            head = temp->next;
            delete temp;
            cout << "\nBook deleted successfully!\n";
            return;
        }

        while (temp != NULL && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "\nBook not found.\n";
            return;
        }

        prev->next = temp->next;
        delete temp;
        cout << "\nBook deleted successfully!\n";
    }
};

int main() {
    Library lib;
    int choice, id;
    string title, author;

    while (true) {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Search Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Delete Book";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Book Title: ";
            getline(cin, title);
            cout << "Enter Author Name: ";
            getline(cin, author);
            lib.addBook(id, title, author);
            break;

        case 2:
            lib.displayBooks();
            break;

        case 3:
            cout << "Enter Book ID to Search: ";
            cin >> id;
            {
                Book* b = lib.searchBook(id);
                if (b != NULL)
                    cout << "\nBook Found - Title: " << b->title << ", Author: " << b->author << ", Status: " << (b->issued ? "Issued" : "Available") << endl;
                else
                    cout << "\nBook not found!\n";
            }
            break;

        case 4:
            cout << "Enter Book ID to Issue: ";
            cin >> id;
            lib.issueBook(id);
            break;

        case 5:
            cout << "Enter Book ID to Return: ";
            cin >> id;
            lib.returnBook(id);
            break;

        case 6:
            cout << "Enter Book ID to Delete: ";
            cin >> id;
            lib.deleteBook(id);
            break;

        case 7:
            cout << "\nExiting the system. Goodbye!\n";
            return 0;

        default:
            cout << "\nInvalid choice. Try again.\n";
        }
    }
}



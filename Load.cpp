// Load.cpp
#include "Load.h"
#include <fstream>
#include <bits/stdc++.h>
#include <sstream>
#include <vector>

#include"Book.h"
#include"Account.h"
#include"utils.h"
#include"User.h"
#include"Library.h"
#include"Student.h"
#include"Faculty.h"
#include"Librarian.h"

using namespace std;

// Loads book data from a CSV file and adds them to the library
void loadBooksFromDB(Library* library, const string& filename) {
    ifstream in(filename);
    if (!in) {
        cout << "CSV file not found: " << filename << ". Starting with empty book list.\n";
        return;
    }

    string line;
    getline(in, line); // Skip the header line
    while (getline(in, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;
        while (getline(ss, field, ',')) {
            if (!field.empty() && field.front() == '"') field.erase(0, 1);
            if (!field.empty() && field.back() == '"') field.pop_back();
            fields.push_back(field);
        }
        if (fields.size() >= 8) { // Ensure correct number of fields
            string Author = fields[1] ;
            string Title = fields[0];
            string Publisher = fields[2];
            string ISBN = fields[3];
            string year = fields[4];
            Book* book = new Book(Title, Author, ISBN, Publisher, year);
            book->updateStatus(fields[5]);
            book->setBorrowDate(stol(fields[6]));
            book->setCurrentUser(fields[7]);
            library->addBook(book);
        }
    }
    in.close();
}

// Loads student data from a CSV file and adds them to the library
void loadStudentsFromDB(Library* library, const string& filename) {
    ifstream in(filename);
    if (!in) {
        cout << "CSV file not found: " << filename << ". No students loaded.\n";
        return;
    }

    string line;
    getline(in, line);
    while (getline(in, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;
        while (getline(ss, field, ',')) {
            if (!field.empty() && field.front() == '"') field.erase(0, 1);
            if (!field.empty() && field.back() == '"') field.pop_back();
            fields.push_back(field);
        }
        if (fields.size() >= 7) {
            Student* newStudent = new Student(fields[0], fields[1], fields[6]);
            newStudent->getAccount().setFineOnReturnedBooks(stoi(fields[2]));
            newStudent->getAccount().setTotalPaidFine(stoi(fields[3]));

            stringstream ssBooks(fields[4]);
            string isbn;
            while (getline(ssBooks, isbn, ';')) {
                Book* b = library->searchBookByISBN(isbn);
                if (b) newStudent->getAccount().addToBorrowedBooks(b);
            }

            stringstream ssHistory(fields[5]);
            string record;
            while (getline(ssHistory, record, ';')) {
                stringstream ssRecord(record);
                string bookTitle, date, action;
                getline(ssRecord, bookTitle, '|');
                getline(ssRecord, date, '|');
                getline(ssRecord, action, '|');
                newStudent->getAccount().addHistoryRecord(make_tuple(bookTitle, date, action));
            }
            library->addUser(newStudent);
        }
    }
    in.close();
}

// Similar functions for faculty, librarians, and book history
void loadFacultyFromDB(Library* library, const string& filename) {
    ifstream in(filename);
    if (!in) {
        cout << "CSV file not found: " << filename << ". No faculty loaded.\n";
        return;
    }

    string line;
    getline(in, line);
    while (getline(in, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;
        while (getline(ss, field, ',')) {
            if (!field.empty() && field.front() == '"') field.erase(0, 1);
            if (!field.empty() && field.back() == '"') field.pop_back();
            fields.push_back(field);
        }
        if (fields.size() >= 5) {
            Faculty* newFaculty = new Faculty(fields[0], fields[1], fields[4]);
            stringstream ssBooks(fields[2]);
            string isbn;
            while (getline(ssBooks, isbn, ';')) {
                Book* b = library->searchBookByISBN(isbn);
                if (b) newFaculty->getAccount().addToBorrowedBooks(b);
            }
            stringstream ssHistory(fields[3]);
            string record;
            while (getline(ssHistory, record, ';')) {
                stringstream ssRecord(record);
                string ISBN, borrDate, retDate;
                getline(ssRecord, ISBN, '|');
                getline(ssRecord, borrDate, '|');
                getline(ssRecord, retDate, '|');

                Book* book = library->searchBookByISBN(ISBN);
                newFaculty->getAccount().addHistoryRecord(make_tuple(ISBN, borrDate, retDate));
                newFaculty->getAccount().addToHistory(book , parseTimeString(borrDate) , parseTimeString(retDate));
                // newFaculty->getAccount().addToHistory(make_tuple());
            }
            library->addUser(newFaculty);
        }
    }
    in.close();
}

void loadLibrariansFromDB(Library* library, const string& filename) {
    ifstream in(filename);
    if (!in) {
        cout << "CSV file not found: " << filename << ". No librarians loaded.\n";
        return;
    }

    string line;
    getline(in, line);
    while (getline(in, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;
        while (getline(ss, field, ',')) {
            if (!field.empty() && field.front() == '"') field.erase(0, 1);
            if (!field.empty() && field.back() == '"') field.pop_back();
            fields.push_back(field);
        }
        if (fields.size() >= 3) {
            User* newUser = dynamic_cast<User*>(new Librarian(fields[0], fields[1], fields[2]));
            library->addUser(newUser);
        }
    }
    in.close();
}

void loadBookHistoryFromDB(Library* library, const string& filename) {
    ifstream in(filename);
    if (!in) {
        cout << "CSV file not found: " << filename << ". No history loaded.\n";
        return;
    }

    string line;
    getline(in, line);
    while (getline(in, line)) {
        stringstream ss(line);
        vector<string> fields;
        string field;
        while (getline(ss, field, ',')) fields.push_back(field);
        if (fields.size() >= 4) {
            Book* book = library->searchBookByISBN(fields[0]);
            if (book) book->addPastBorrowerFromFile(fields[1], fields[2], fields[3]);
        }
    }
    in.close();
}

// Loads all user data from their respective CSV files
void loadAllUsersFromDB(Library* library) {
    loadStudentsFromDB(library, "students.csv");
    loadFacultyFromDB(library, "faculty.csv");
    loadLibrariansFromDB(library, "librarian.csv");
}

// Loads all library data (books, users, history)
void loadAllData(Library* library) {
    loadBooksFromDB(library, "books.csv");
    loadAllUsersFromDB(library);
    loadBookHistoryFromDB(library, "bookHistory.csv");
}

// Convenience function to call the complete data loading
void loadfile(Library* library) {
    loadAllData(library);
}

// Book.h
#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <ctime>
#include <iomanip>
#include <cmath>

using namespace std;

// Book class representing a book in the library
class Book {
public:
    // Basic book details
    string Author;
    string Title;
    string Publisher;
    string ISBN;
    string year;

private:
    // Book status and borrowing details
    string status;             // Available, Borrowed, or Reserved
    string currentUser;        // User currently borrowing the book
    vector<tuple<string, string, string>> pastBorrowers; // History of past borrowers (UserId, borrow date, return date)
    time_t borrowTime;         // Timestamp of when the book was borrowed

public:
    // Constructor
    Book(string Title, string Author, string ISBN, string Publisher , string year);

    // Status and availability methods
    bool isAvailable();
    bool isReserved();
    bool isBorrowed();
    void updateStatus(string status);
    string getStatus();

    // Borrowing and returning methods
    void setBorrowDate(time_t date);
    time_t getBorrowDate();
    bool borrowBook();
    void addPastBorrower();
    void addPastBorrowerFromFile(string UserId, string borrDate, string retDate);
    void setCurrentUser(string UserId);
    string getCurrentUser();
    void returnBook();
    int daysBorrowed();
    void processReturn();

    // Book information update and display
    string getISBN();
    void updateBook(string field, string value);
    void displayEssentials();
    void display();
    void DisplayPastBorrowers();

    // Accessor for borrowing history
    const vector<tuple<string, string, string>> getPastBorrowers() const;
};

#endif // BOOK_H

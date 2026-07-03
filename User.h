// User.h
#ifndef USER_H
#define USER_H

#include "Account.h"
#include "Book.h"
#include <iostream>
#include <vector>
using namespace std;

class User {
protected:
    string password; // User's password (should be kept private)
    string name;     // User's name
    string role;     // User's role (like student, librarian, etc.)
    string UserId;   // Unique user identifier
    Account account; // User's associated account

public:
    // Pure virtual functions making User an abstract class
    virtual int getMaxBooksAllowed() = 0;   // Maximum books user can borrow
    virtual int getMaxBorrowPeriod() = 0;  // Maximum days a book can be borrowed
    virtual int getRateOfFine() = 0;       // Fine rate per day for overdue books
    virtual int OverdueLimit() = 0;       // Maximum number of overdue books allowed

    // Constructor
    User(string name, string role, string UserId , string password);

    // Getters
    string getName();
    string getUserId();
    string getRole();

    // Update user information
    void updateUser(string field, string value);

    // Account-related functions
    void viewHistory();             // View borrowing history
    int getFine();                  // Get total unpaid fines
    const vector<Book*> overDueBooks(); // Get a list of overdue books
    bool hasReachedBorrowLimit();   // Check if user reached borrow limit
    bool hasPendingFines();         // Check if user has pending fines
    bool hasAnOverdueBook();        // Check if user has any overdue books
    virtual bool canBorrowBook() = 0; // Check if user is eligible to borrow books
    void payFine(int amount);       // Pay an outstanding fine
    bool borrowBook(Book* book);    // Borrow a book
    bool returnBook(Book* book);    // Return a borrowed book

    // Accessor for account
    Account& getAccount();

    // Password functions
    string getPassword();
    bool setPassword(string currPassword , string newPassword); // Change password

    bool hasBook(Book* book);
};

#endif // USER_H

#include "Faculty.h"
#include "utils.h"
#include <iostream>
using namespace std;

// Constructor for Faculty class, initializing the User base class
Faculty::Faculty(string name, string UserId , string password) : User(name, "Faculty", UserId , password) {}

// Returns the maximum number of books a faculty member can borrow
int Faculty::getMaxBooksAllowed() {
    return maxBooks;
}

// Returns the maximum number of days a faculty member can borrow a book
int Faculty::getMaxBorrowPeriod() {
    return maxDays;
}

// Returns the rate of fine for overdue books (0 for faculty)
int Faculty::getRateOfFine() {
    return rateOfFine;
}

// Returns the maximum overdue limit in days before further action is taken
int Faculty::OverdueLimit() {
    return OverDueLimit;
}

// Checks if the faculty member can borrow more books
bool Faculty::canBorrowBook() {
    if (hasReachedBorrowLimit()) {
        cout << "You have reached the borrow limit. Please return a book to borrow another." << endl;
        return false;
    }
    if (hasAnOverdueBook()) {
        cout << "You have overdue books. Please return them to borrow another." << endl;
        return false;
    }
    return true;
}

// Displays the list of overdue books borrowed by the faculty member
void Faculty::getOverDueBooks() {
    vector<Book*> overdueBooks = overDueBooks();
    if (overdueBooks.empty()) {
        cout << "You have no overdue books." << endl;
    } else {
        cout << "These books are overdue. Please return them to borrow another." << endl;
        printEssentialOfBooks(overdueBooks);
    }
}

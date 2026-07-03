#include "Student.h"

// Constructor initializing Student with User base class attributes and role set to "Student"
Student::Student(string name, string UserId , string password) : User(name, "Student", UserId , password) {}

// Returns the maximum number of books a student can borrow
int Student::getMaxBooksAllowed() {
    return maxBooks;
}

// Returns the maximum number of days a student can keep a borrowed book
int Student::getMaxBorrowPeriod() {
    return maxDays;
}

// Returns the rate of fine per day for overdue books
int Student::getRateOfFine() {
    return rateOfFine;
}

// Returns the number of days after which a book is considered overdue
int Student::OverdueLimit() {
    return OverDueLimit;
}

// Checks if the student is eligible to borrow a book
bool Student::canBorrowBook() {
    if (hasReachedBorrowLimit()) {
        cout << "You have reached the borrow limit. Please return a book to borrow another." << endl;
        return false;
    }
    if (hasPendingFines()) {
        cout << "You have pending fines. Please clear your dues to borrow a book." << endl;
        return false;
    }
    return true;
}

// Displays the list of overdue books that have incurred fines
void Student::getBooksWithFine() {
    vector<Book*> booksWithFine = overDueBooks();
    if (booksWithFine.empty()) {
        cout << "None of your borrowed books have any fine" << endl;
    } else {
        cout << "These books are over their Borrow Period Limit and hence are inducing fines" << endl;
        printEssentialOfBooks(booksWithFine);
    }
}

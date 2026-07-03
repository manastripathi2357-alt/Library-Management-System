// Faculty.h
#ifndef FACULTY_H
#define FACULTY_H

#include "User.h"
#include "Book.h"
#include "utils.h"
#include <vector>
#include <iostream>
using namespace std;

// Faculty class inherits from the User class
class Faculty : public User
{
public:
    // Maximum number of books a faculty member can borrow
    static const int maxBooks = 5;

    // Maximum number of days a book can be borrowed
    static const int maxDays = 30;

    // Rate of fine per day for overdue books (0 for faculty)
    static const int rateOfFine = 0;

    // Maximum overdue period before further action is taken
    static const int OverDueLimit = 60;

    // Constructor for Faculty class
    Faculty(string name, string UserId, string password);

    // Get the maximum number of books a faculty member can borrow
    int getMaxBooksAllowed() override;

    // Get the maximum borrowing period for faculty
    int getMaxBorrowPeriod() override;

    // Get the rate of fine for overdue books
    int getRateOfFine() override;

    // Get the maximum overdue limit
    int OverdueLimit() override;

    // Check if the faculty member can borrow more books
    bool canBorrowBook() override;

    // Display overdue books borrowed by the faculty member
    void getOverDueBooks();
};

#endif // FACULTY_H
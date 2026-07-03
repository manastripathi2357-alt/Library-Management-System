// student.h
#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "Book.h"
#include "utils.h"
#include <vector>
#include <iostream>
using namespace std;

// Student class inherits from User and represents a student user of the library
class Student : public User {
public:
    // Constants defining borrowing limits and fine policies for students
    static const int maxBooks = 3;      // Maximum number of books a student can borrow
    static const int maxDays = 15;      // Maximum borrowing period in days
    static const int rateOfFine = 10;   // Fine rate per day for overdue books
    static const int OverDueLimit = 15; // Limit in days after which books are considered overdue

    // Constructor for initializing a student with name, user ID, and password
    Student(string name, string UserId , string password);

    // Overridden methods providing student-specific limits and rules
    int getMaxBooksAllowed() override;   // Returns the max number of books a student can borrow
    int getMaxBorrowPeriod() override;  // Returns the max borrowing period for students
    int getRateOfFine() override;       // Returns the rate of fine for overdue books
    int OverdueLimit() override;        // Returns the overdue limit for books

    // Determines if the student can borrow more books
    bool canBorrowBook() override;

    // Displays the list of books the student has with outstanding fines
    void getBooksWithFine();
};

#endif // STUDENT_H

#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "User.h"
#include "Library.h"
#include "Student.h"
#include "Faculty.h"

// Librarian class inherits from User class
class Librarian : public User
{
public:
    // Constructor for Librarian class
    Librarian(std::string name, std::string UserId , std::string password);

    // Overridden functions with no borrowing privileges for librarian
    int getMaxBooksAllowed() override;
    int getMaxBorrowPeriod() override;
    int getRateOfFine() override;
    int OverdueLimit() override;
    bool canBorrowBook() override;

    // Librarian-specific functions for managing library resources and users
    bool addNewBook(Library& library, std::string Title, std::string Author, std::string ISBN, std::string Publication, std::string year);
    bool removeBook(Library& library, std::string ISBN);
    bool updateBook(Library& library, std::string ISBN, std::string field, std::string value);
    bool addNewUser(Library& library, std::string name, std::string UserId, std::string Role , std::string password);
    bool removeUser(Library& library, std::string UserId);
    bool reserveBook(Library& library ,std::string ISBN);
    bool unReserveBook(Library& library , std::string ISBN);
};

#endif // LIBRARIAN_H

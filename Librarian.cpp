#include "Librarian.h"
#include <iostream>
using namespace std; 

// Constructor initializes the User base class with Librarian role
Librarian::Librarian(string name, string UserId , string password) : User(name, "Librarian", UserId , password) {}

// Librarians have no borrowing privileges
int Librarian::getMaxBooksAllowed() { return 0; }
int Librarian::getMaxBorrowPeriod() { return 0; }
int Librarian::getRateOfFine() { return 0; }
int Librarian::OverdueLimit() { return 0; }
bool Librarian::canBorrowBook() { return false; }

// Adds a new book to the library if it doesn't already exist
bool Librarian::addNewBook(Library& library, string Title, string Author, string ISBN, string Publication, string year)
{
    if(library.searchBookByISBN(ISBN) != nullptr) {
        cout << "This book already exists" << endl;
        return false;
    }
    Book* newBook = new Book(Title, Author, ISBN, Publication, year);
    library.addBook(newBook);
    return true;
}

// Removes a book from the library by its ISBN
bool Librarian::removeBook(Library& library, string ISBN)
{
    return library.removeBookByISBN(ISBN);
}

// Updates a specific field of a book in the library
bool Librarian::updateBook(Library& library, string ISBN, string field, string value)
{
    Book* book = library.searchBookByISBN(ISBN);

    if(book == nullptr){
        cout << "This book was not found in the library" << endl;
        return false;
    }
    if(book->isBorrowed()){
        cout << "This book has been currently borrowed " << endl;
        return false;
    }
    if(field == "Year") field = "year";
    library.updateBook(ISBN, field, value);
    return true;
}

// Adds a new user (Student, Faculty, or Librarian) to the library
bool Librarian::addNewUser(Library& library, string name, string UserId, string Role , string password)
{
    if(library.searchUserById(UserId) != nullptr) {
        cout << "A user with this userId already exists" << endl;
        return false;
    }
    if (Role == "Student") {
        Student* newStudent = new Student(name, UserId,password);
        library.addUser(dynamic_cast<User*>(newStudent));
    } else if (Role == "Faculty") {
        Faculty* newFaculty = new Faculty(name, UserId,password);
        library.addUser(dynamic_cast<User*>(newFaculty));
    } else if (Role == "Librarian") {
        Librarian* newLibrarian = new Librarian(name, UserId,password);
        library.addUser(dynamic_cast<User*>(newLibrarian));
    }
    return true;
}

// Removes a user from the library by their UserId
bool Librarian::removeUser(Library& library, string UserId)
{
    return library.removeUserById(UserId);
}

// Reserves a book if it's available and not already reserved
bool Librarian::reserveBook(Library& library , string ISBN){
    Book* book = library.searchBookByISBN(ISBN);
    if(book == nullptr){
        cout << "This book is not in Library" << endl;
        return false;
    }
    if(book->isAvailable() == false){
        cout << "This book has been currently borrowed , can't change status to reserved" << endl;
        return false;
    }
    if(book->isReserved()){
        cout << "This book is already a reserved book" << endl;
        return false;
    }
    book->updateStatus("Reserved");
    cout << book->Title << " is now a reserved book" << endl;
    return true;
}

// Unreserves a book if it is currently reserved
bool Librarian::unReserveBook(Library& library , std::string ISBN){
    Book* book = library.searchBookByISBN(ISBN);
    if(book == nullptr){
        cout << "This book is not in Library" << endl;
        return false;
    }
    if(book->isReserved() == false){
        cout << "This book is not a reserved book" << endl;
        return false;
    }
    book->updateStatus("Available");
    cout << book->Title << " is no longer a reserved book" << endl;
    return true;
}

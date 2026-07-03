// library.h
#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include "utils.h"
#include <vector>
#include <unordered_map>

class Library
{
private:
    std::vector<Book*> Books; // List of all books in the library
    std::unordered_map<Book*, int> book_indices; // Maps book pointers to their index in the Books vector
    std::unordered_map<std::string, int> isbn_indices; // Maps ISBN to book index
    std::vector<User*> users; // List of all users in the library
    std::unordered_map<std::string, int> userId_indices; // Maps user ID to user index
    std::unordered_map<User*, int> user_indices; // Maps user pointers to their index in the users vector

public:
    // Book management functions
    void addBook(Book* book); // Add a new book to the library
    bool removeBook(Book* book); // Remove a book from the library by its pointer
    bool removeBookByISBN(const std::string& ISBN); // Remove a book by its ISBN
    Book* searchBookByISBN(const std::string& ISBN); // Search for a book by its ISBN and return the book pointer

    // User management functions
    void addUser(User* user); // Add a new user to the library
    void removeUser(User* user); // Remove a user from the library by their pointer
    bool removeUserById(const std::string& UserId); // Remove a user by their ID
    User* searchUserById(const std::string& UserId); // Search for a user by their ID and return the user pointer

    // Book update function
    void updateBook(const std::string& ISBN, const std::string& field, const std::string& value); // Update book details

    // Accessor functions
    const std::vector<Book*>& getBooks() const; // Get the list of all books
    const std::vector<User*>& getUsers() const; // Get the list of all users

    // Display functions
    void displayAvailableBooks(); // Display all books that are currently available for borrowing
    void displayAllBooks(); // Display all books rehgisetered in the library
    void printAllUsers();
};

#endif // LIBRARY_H
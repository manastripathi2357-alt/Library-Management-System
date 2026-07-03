#include "Library.h"
#include <iostream>
using namespace std;

// Adds a book to the library and updates the book indices
void Library::addBook(Book* book)
{
    book_indices[book] = Books.size();
    isbn_indices[book->ISBN] = Books.size();
    Books.push_back(book);
}

// Removes a book from the library and maintains the integrity of book indices
bool Library::removeBook(Book* book)
{
    if (!isPresent(book_indices, book))
    {
        cout << "This book is not present" << endl;
        return false;
    }

    if(book->isBorrowed()){
        cout << "This book is currently borrowed" << endl;
        return false;
    }

    int ind = book_indices[book];

    // If the book is not the last element, swap and update indices
    if (ind != Books.size() - 1)
    {
        Books[ind] = Books.back();
        book_indices[Books[ind]] = ind;
        isbn_indices[Books[ind]->ISBN] = ind;
    }

    Books.pop_back();
    book_indices.erase(book);
    isbn_indices.erase(book->ISBN);
    return true;
}
// Removes a book from the library by its ISBN
bool Library::removeBookByISBN(const string& ISBN)
{
    Book* bookToBeRemoved = searchBookByISBN(ISBN);
    if (bookToBeRemoved)
    {
        removeBook(bookToBeRemoved);
        return true;
    }
    else
    {
        cout << "This book was not found" << endl;
    }
    return false;
}

// Searches for a book in the library by its ISBN
Book* Library::searchBookByISBN(const string& ISBN)
{
    if (!isPresent(isbn_indices, ISBN))
    {
        return nullptr;
    }

    int indexInBooks = isbn_indices[ISBN];
    return Books[indexInBooks];
}

// Adds a user to the library and updates the user indices
void Library::addUser(User* user)
{
    userId_indices[user->getUserId()] = users.size();
    user_indices[user] = users.size();
    users.push_back(user);
}

// Removes a user from the library and maintains the integrity of user indices
void Library::removeUser(User* user)
{
    if (!isPresent(userId_indices, user->getUserId()))
    {
        cout << "This User does not exist." << endl;
        return;
    }

    int indexInUsers = user_indices[user];

    // If the user is not the last element, swap and update indices
    if (indexInUsers != users.size() - 1)
    {
        users[indexInUsers] = users.back();
        userId_indices[users[indexInUsers]->getUserId()] = indexInUsers;
    }

    users.pop_back();
    user_indices.erase(user);
    userId_indices.erase(user->getUserId());
}

// Removes a user from the library by their UserId
bool Library::removeUserById(const string& UserId)
{
    User* user = searchUserById(UserId);
    if (user)
    {
        removeUser(user);
        return true;
    }
    else
    {
        cout << "No user exists with this UserId" << endl;
    }
    return false;
}

// Searches for a user in the library by their UserId
User* Library::searchUserById(const string& UserId)
{
    if (!isPresent(userId_indices, UserId))
    {
        return nullptr;
    }

    int indexInUsers = userId_indices[UserId];
    return users[indexInUsers];
}

// Updates book details based on the provided field and value
void Library::updateBook(const string& ISBN, const string& field, const string& value)
{
    Book* book = searchBookByISBN(ISBN);

    if (!book)
    {
        cout << "No Book with the given ISBN exists" << endl;
        return;
    }

    if (field == "ISBN")
    {
        if (value == book->ISBN)
        {
            cout << "Please enter a new ISBN" << endl;
            return;
        }

        if (isPresent(isbn_indices, value))
        {
            cout << "Another book exists with this ISBN, please enter a valid ISBN" << endl;
            return;
        }

        isbn_indices[value] = isbn_indices[book->ISBN];
        isbn_indices.erase(book->ISBN);
    }

    book->updateBook(field, value);
}

// Returns a constant reference to the list of books in the library
const vector<Book*>& Library::getBooks() const
{
    return Books;
}

// Returns a constant reference to the list of users in the library
const vector<User*>& Library::getUsers() const
{
    return users;
}

// Displays all available books in the library
void Library::displayAvailableBooks()
{
     // Table header with adjusted widths
     cout << "\n\n";
     cout << left << setw(40) << "Title"
     << setw(25) << "Author"
     << setw(35) << "Publisher"
     << setw(10)  << "Year"
     << setw(20) << "ISBN"
     << setw(15) << "Status"
     << endl;
    cout << string(145, '-') << endl;  // Adjusted separator width

    bool found = false;

    for (auto book : Books)
    {
        if (book->isAvailable())
        {
            book->display();
            found = true;
        }
    }
    if(!found){
        cout << "No available books found" << endl;
    }
}

void Library:: displayAllBooks(){

    // Table header with adjusted widths
    cout << "\n\n";
    cout << left << setw(40) << "Title"
    << setw(25) << "Author"
    << setw(35) << "Publisher"
    << setw(10)  << "Year"
    << setw(20) << "ISBN"
    << setw(15) << "Status"
    << endl;
   cout << string(145, '-') << endl;  // Adjusted separator width

    bool found = false;
    for(auto book : Books)
    {
        book->display();
        found = true;
    }
    if(!found){
        cout << "No books in the library" << endl;
    }
}

void Library::printAllUsers(){
    if (users.empty()) {
        cout << "No users registered in the library.\n";
        return;
    }

    // Define column widths
    const int userIDWidth = 25;
    const int nameWidth = 40;
    const int roleWidth = 20;

    // Header for all users
    cout << "\nAll Registered Users:\n\n";

    // Categories to separate users by role
    vector<User*> students, faculty, librarians;

    // Categorizing users
    for (User* user : users) {
        if (user->getRole() == "Student") {
            students.push_back(user);
        } else if (user->getRole() == "Faculty") {
            faculty.push_back(user);
        } else if (user->getRole() == "Librarian") {
            librarians.push_back(user);
        }
    }

    // Function to print users of a specific category
    auto printUsers = [&](const string &category, const vector<User*> &userList) {
        if (userList.empty()) return;
        cout << category << ":\n";
        cout << left << setw(userIDWidth) << "User ID"
             << setw(nameWidth) << "Name"
             << setw(roleWidth) << "Role"
             << endl;
        cout << string(userIDWidth + nameWidth + roleWidth, '-') << endl;

        for (User* user : userList) {
            cout << left << setw(userIDWidth) << user->getUserId()
                 << setw(nameWidth) << user->getName()
                 << setw(roleWidth) << user->getRole()
                 << endl;
        }
        cout << endl;  // Extra spacing for clarity
    };

    // Print each category
    printUsers("Students", students);
    printUsers("Faculty", faculty);
    printUsers("Librarians", librarians);

}
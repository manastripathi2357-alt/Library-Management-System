#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
#include<ctime>
#include<chrono>
#include<iomanip>

#include"Book.h"
#include"Account.h"
#include"utils.h"
#include"User.h"
#include"Library.h"
#include"Student.h"
#include"Faculty.h"
#include"Librarian.h"
#include"Load.h"
#include"Save.h"

using namespace std;


bool isLibraryInitialized() {
    ifstream flagFile("initialized.flag");
    return flagFile.good();
}

void markLibraryAsInitialized() {
    ofstream flagFile("initialized.flag");
    if(flagFile)
    {
        flagFile << "Library has been initialized." << endl;
    }
}

// Function to initialize library with default data if not loaded from file
void initializeLibrary(Library &library) {
    // If no books exist, add 10 books.
    if(library.getBooks().empty()) {
        library.addBook(new Book("Harry Potter and the Sorcerer's Stone", "J.K. Rowling" , "9780747532699" , "Bloomsbury", "1997"));
        library.addBook(new Book("1984", "George Orwell", "9780451524935", "Secker & Warburg", "1949"));
        library.addBook(new Book("The Hobbit", "J.R.R. Tolkien", "9780618968633", "Allen & Unwin", "1937"));
        library.addBook(new Book("The Great Gatsby", "F. Scott Fitzgerald", "9780743273565", "Charles Scribner's Sons", "1925"));
        library.addBook(new Book("To Kill a Mockingbird", "Harper Lee", "9780061120084", "J.B. Lippincott & Co.", "1960"));
        library.addBook(new Book("The Da Vinci Code", "Dan Brown", "9780385504201", "Doubleday", "2003"));
        library.addBook(new Book("War and Peace", "Leo Tolstoy", "9780199232765", "The Russian Messenger", "1869"));
        library.addBook(new Book("Adventures of Huckleberry Finn", "Mark Twain", "9780486280615", "Chatto & Windus", "1884"));
        library.addBook(new Book("Pride and Prejudice", "Jane Austen", "9781503290563", "T. Egerton", "1813"));
        library.addBook(new Book("The Odyssey", "Homer", "9780140268867", "Ancient Greece", "800 BC"));
    }
    
    // If no users exist, add 5 students, 3 faculty, and 1 librarian.
    if(library.getUsers().empty()) {
        // Add 5 students.
        library.addUser(new Student("Alice", "s001", "alice123"));
        library.addUser(new Student("Bob", "s002", "bob123"));
        library.addUser(new Student("Charlie", "s003", "charlie123"));
        library.addUser(new Student("Diana", "s004", "diana123"));
        library.addUser(new Student("Ethan", "s005", "ethan123"));
        
        // Add 3 faculty.
        library.addUser(new Faculty("Prof. Smith", "f001", "smith123"));
        library.addUser(new Faculty("Prof. Johnson", "f002", "johnson123"));
        library.addUser(new Faculty("Prof. Williams", "f003", "williams123"));
        
        // Add 1 librarian.
        library.addUser(new Librarian("Librarian Mike", "l001", "mike123"));
    }
    saveAllData(&library);
}

// Student menu options
void studentMenu(Student* student, Library &library) {
    int choice;
    bool loggedIn = true;
    while(loggedIn) {
        cout << "\n---- Student Menu ----" << endl;
        cout << "1. View Available Books" << endl;
        cout << "2. Borrow Book" << endl;
        cout << "3. Return Book" << endl;
        cout << "4. View Borrowing History" << endl;
        cout << "5. View currently borrowed books" << endl;
        cout << "6. View Overdue books" << endl;
        cout << "7. View Outstanding Fines" << endl;
        cout << "8. Pay Fines" << endl;
        cout << "9. View All Books" << endl;
        cout << "10. View History of a particular book" << endl;
        cout << "11. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        // To handle unwanted non integer inputs
        if(cin.fail()) {
            cin.clear();              // Clear error state
            cin.ignore(10000, '\n');  // Discard the invalid input
            cout << "Invalid input. Please enter a number from the given choices.\n";
            continue;                 // Skip the rest of the loop and ask again
        }
        cin.ignore(); // flush newline
        
        switch(choice) {
            // Displayes all the available books in the library
            case 1: {
                library.displayAvailableBooks();
                break;
            }
            // Borrow a book
            case 2: {
                string isbn;
                cout << "Enter ISBN of the book to borrow: ";
                getline(cin, isbn);
                Book* book = library.searchBookByISBN(isbn);
                if(book) {
                    
                    if(student->hasBook(book))
                    {
                        cout << "You have already borrowed this book" << endl;
                    }
                    // Check if the student can borrow book , if he can borrow the book , if he can't output why he can't(output are defined in the borrowBook() function)
                    else if(student->borrowBook(book))
                    {
                        cout << "Book borrowed successfully." << endl;
                    }
                } 
                else 
                {
                    cout << "Book is Not Found." << endl;
                }
                break;
            }
            // Return a book
            case 3: {
                cout << "Your Borrowed Books : " << endl;
                // prints details of books which are borrowed for ease of user
                printBooks(student->getAccount().getBorrowedBooks());
                string isbn;
                cout << endl <<endl;
                cout << "Enter ISBN of the book to return: ";
                getline(cin, isbn);
                Book* book = library.searchBookByISBN(isbn);
                if(book) {
                    if(student->returnBook(book))
                    {
                        cout << "Book returned successfully." << endl;
                    }
                } 
                else 
                {
                    cout << "Invalid ISBN entered." << endl;
                }
                break;
            }

            // View personal borrowing history , includes previously borrowed and returned books
            case 4: {
                student->viewHistory();
                break;
            }
            // View currently borrowed books
            case 5: {
                vector<Book*> books = student->getAccount().getBorrowedBooks();
                cout << "Your Borrowed Books : " << endl;
                printBooks(books);
                cout << endl <<endl;
                break;
            }
            // View overdue books , which are incuring fine
            case 6: {
                vector<Book*> overdue = student->overDueBooks();
                if(overdue.empty()) {
                    cout << "No overdue books." << endl;
                } else {
                    cout << "Overdue Books:" << endl;
                    for(auto book : overdue) {
                        book->display();
                    }
                }
                break;
            }
            // Compute fine
            case 7: {
                int fine = student->getFine();
                cout << "Outstanding Fine: " << fine << " rupees" << endl;
                break;
            }
            // Pay fine
            case 8: {
                int amount;
                if(student->getFine() == 0){
                    cout << "You don't have any outstanding fine" << endl;
                    break;
                }

                cout << "Enter amount to pay: ";
                cin >> amount;
                cin.ignore();
                student->payFine(amount);
                cout << "Payment processed successfully." << endl;
                break;
            }
            // To see all the books , available , reserved or borrowed
            case 9: {
                library.displayAllBooks();
                break;
            }
            // To view details and borrowing history of some book
            case 10: {
                string isbn;
                cout << "Enter ISBN of the book whose history you wish to see: ";
                getline(cin, isbn);
                Book* book = library.searchBookByISBN(isbn);
                if(book){
                    book->DisplayPastBorrowers();
                    if(book->isBorrowed()){
                        cout << "This book is currently borrowed by " << book->getCurrentUser();
                    }
                }
                else{
                    cout << "This book was not found" << endl;
                }
                break;
            }
            // logout
            case 11: {
                loggedIn = false;
                cout << "Logging out..." << endl;
                break;
            }
            default:
            {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }
}

// Faculty menu options
void facultyMenu(Faculty* faculty, Library &library) {
    int choice;
    bool loggedIn = true;
    while(loggedIn) {
        cout << "\n---- Faculty Menu ----" << endl;
        cout << "1. View Available Books" << endl;
        cout << "2. Borrow Book" << endl;
        cout << "3. Return Book" << endl;
        cout << "4. View Borrowing History" << endl;
        cout << "5. View Currently Borrowed books" << endl;
        cout << "6. View Overdue Books" << endl;
        cout << "7. View All Books" << endl;
        cout << "8. View history of a particular book" << endl;
        cout << "9. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        // To handle unwanted non integer inputs
        if(cin.fail()) {
            cin.clear();              // Clear error state
            cin.ignore(10000, '\n');  // Discard the invalid input
            cout << "Invalid input. Please enter a number from the given choices.\n";
            continue;                 // Skip the rest of the loop and ask again
        }
        cin.ignore();
        
        switch(choice) {
            // Displayes all the available books in the library
            case 1: {
                library.displayAvailableBooks();
                break;
            }
            // Borrow book
            case 2: {
                string isbn;
                cout << "Enter ISBN of the book to borrow: ";
                getline(cin, isbn);
                Book* book = library.searchBookByISBN(isbn);
                if(book) {

                    if(faculty->hasBook(book))
                    {
                        cout << "You have already borrowed this book" << endl;
                    }
                    // In the occassion of borrowBook() returning false , the reason is already printed in the function
                    else if(faculty->borrowBook(book))
                    {
                        cout << "Book borrowed successfully." << endl;
                    }
                } 
                else 
                {
                    cout << "Book is Not Found." << endl;
                }
                break;
            }

            // return book
            case 3: {
                // Shows currently borrowed books for ease to user when returning 
                cout << "Your Borrowed Books : " << endl;
                printBooks(faculty->getAccount().getBorrowedBooks());
                string isbn;
                cout << endl <<endl;
                cout << "Enter ISBN of the book to return: ";
                getline(cin, isbn);
                Book* book = library.searchBookByISBN(isbn);
                // if the book exists in the databaes
                if(book) 
                {
                    if(faculty->returnBook(book))
                    {
                        cout << "Book returned successfully." << endl;
                    }
                } 
                else 
                {
                    cout << "Invalid ISBN entered." << endl;
                }
                break;
            }
            // View personal borrow history
            case 4: {
                faculty->viewHistory();
                break;
            }
            // Prints all currently borrowed books
            case 5: {
                vector<Book*> books = faculty->getAccount().getBorrowedBooks();
                printBooks(books);
                cout << endl <<endl;
                break;
            }
            // See books which are overdue limit
            case 6: {
                // For faculty, overdue books may be shown based on the defined overdue limit.
                vector<Book*> overdue = faculty->overDueBooks();
                if(overdue.empty()) {
                    cout << "No overdue books." << endl;
                } else {
                    cout << "Overdue Books:" << endl;
                    for(auto book : overdue) {
                        book->display();
                    }
                }
                break;
            }
            // See all the books in library regardless of status
            case 7: {
                library.displayAllBooks();
                break;
            }
            // View history and details of some book
            case 8: {
                string isbn;
                cout << "Enter ISBN of the book whose history you wish to see: ";
                getline(cin, isbn);
                Book* book = library.searchBookByISBN(isbn);
                if(book){
                    book->DisplayPastBorrowers();
                    if(book->isBorrowed()){
                        cout << "This book is currently borrowed by " << book->getCurrentUser();
                    }
                }
                else{
                    cout << "This book was not found" << endl;
                }
                break;
            }
            // logout
            case 9: {
                loggedIn = false;
                cout << "Logging out..." << endl;
                break;
            }
            default:
            {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }
}

// Librarian menu options
void librarianMenu(Librarian* librarian, Library &library) {
    int choice;
    bool loggedIn = true;
    while(loggedIn) {
        cout << "\n---- Librarian Menu ----" << endl;
        cout << "1. Add New Book" << endl;
        cout << "2. Remove Book" << endl;
        cout << "3. Update Book" << endl;
        cout << "4. Add New User" << endl;
        cout << "5. Remove User" << endl;
        cout << "6. Reserve Book" << endl;
        cout << "7. Unreserve Book" << endl;
        cout << "8. View Available Books" << endl;
        cout << "9. View All Books" << endl;
        cout << "10. View history of a particular book" << endl;
        cout << "11. View All Users" << endl;
        cout << "12. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        // To handle unwanted non integer inputs
        if(cin.fail()) {
            cin.clear();              // Clear error state
            cin.ignore(10000, '\n');  // Discard the invalid input
            cout << "Invalid input. Please enter a number from the given choices.\n";
            continue;                 // Skip the rest of the loop and ask again
        }
        cin.ignore();
        
        switch(choice) {
            // Add a book to library
            case 1: {
                string title, author, publisher, isbn, year;
                cout << "Enter Book Title: ";
                getline(cin, title);
                cout << "Enter Author: ";
                getline(cin, author);
                cout << "Enter Publisher: ";
                getline(cin, publisher);
                cout << "Enter ISBN: ";
                getline(cin, isbn);
                cout << "Enter Year: ";
                getline(cin, year);
                if(librarian->addNewBook(library, title, author, isbn, publisher, year))
                {
                    cout << "Book added successfully." << endl;
                }
                break;
            }
            // Remove a book from library
            case 2: {
                string isbn;
                cout << "Enter ISBN of the book to remove: ";
                getline(cin, isbn);
                if(librarian->removeBook(library, isbn))
                {
                    cout << "Book removed successfully." << endl;
                }
                break;
            }
            // Update a book
            case 3: {
                string isbn, field, value;
                cout << "Enter ISBN of the book to update: ";
                getline(cin, isbn);
                cout << "Enter field (Case-Sensitive) to update (Title, Author, Publisher, Year , ISBN): ";
                getline(cin, field);
                cout << "Enter new value: ";
                getline(cin, value);
                // To check if field entered is an attribute
                if((field != "Title") && (field != "Author") && (field != "Publisher") && (field != "Year") && (field !="ISBN")){
                    cout << "You have entered an invalid attribute" << endl;
                    continue;
                }
                if(librarian->updateBook(library, isbn, field, value))
                {
                    cout << "Book updated successfully." << endl;
                }
                break;
            }
            // add a new user
            case 4: {
                string name, userId, role, password;
                cout << "Enter User Name: ";
                getline(cin, name);
                cout << "Enter User ID: ";
                getline(cin, userId);
                cout << "Enter Role (Student/Faculty/Librarian): ";
                getline(cin, role);
                cout << "Enter Password: ";
                getline(cin, password);
                if(librarian->addNewUser(library, name, userId, role, password))
                {
                    cout << role << " added successfully." << endl;
                }
                break;
            }
            // remove a user
            case 5: {
                string userId;
                cout << "Enter User ID of the user to remove: ";
                getline(cin, userId);
                if(librarian->removeUser(library, userId))
                {
                    cout << "User removed successfully." << endl;
                }
                break;
            }
            // Reserve book(this book can only be read in library , can't be borrowed)
            case 6: {
                string isbn;
                cout << "Enter ISBN of the book to reserve: ";
                getline(cin, isbn);
                if(librarian->reserveBook(library, isbn))
                {
                    cout << "Book reserved successfully." << endl;
                }
                break;
            }
            // unreserve book
            case 7: {
                string isbn;
                cout << "Enter ISBN of the book to unreserve: ";
                getline(cin, isbn);
                if(librarian->unReserveBook(library, isbn))
                {
                    cout << "Book unreserved successfully." << endl;
                }
                break;
            }
            // See all the available books
            case 8: {
                library.displayAvailableBooks();
                break;
            }
            // See all the books in library
            case 9: {
                library.displayAllBooks();
                break;
            }
            // view details and history of a particular book
            case 10:{
                string isbn;
                cout << "Enter ISBN of the book whose history you wish to see: ";
                getline(cin, isbn);
                Book* book = library.searchBookByISBN(isbn);
                if(book){
                    book->DisplayPastBorrowers();
                    if(book->isBorrowed()){
                        cout << "This book is currently borrowed by " << book->getCurrentUser();
                    }
                }
                else{
                    cout << "This book was not found" << endl;
                }
                break;
            }
            // See all users 
            case 11: {
                library.printAllUsers();
                break;
            }
            // logout
            case 12: {
                loggedIn = false;
                cout << "Logging out..." << endl;
                break;
            }
            default:
            {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }
}

int main() {
    Library library;
    
    // Load previously saved data (if any)
    loadAllData(&library);
    
    // If no data exists, initialize with default `records.
    if(!isLibraryInitialized()) 
    {
        initializeLibrary(library);
        markLibraryAsInitialized();
    }

    int mainChoice;
    bool exitProgram = false;   // controller of loop
    
    while(!exitProgram) 
    {
        cout << "\n==== Library Management System ====" << endl;
        cout << "1. Student Login" << endl;
        cout << "2. Faculty Login" << endl;
        cout << "3. Librarian Login" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> mainChoice;

        // To handle unwanted non integer inputs
        if(cin.fail()) {
            cin.clear();              // Clear error state
            cin.ignore(10000, '\n');  // Discard the invalid input
            cout << "Invalid input. Please enter a number from the given choices.\n";
            continue;                 // Skip the rest of the loop and ask again
        }
        cin.ignore();
        
        string userId, password;
        User* user = nullptr;
        
        switch(mainChoice) 
        {
            // Student
            case 1: 
            {
                cout << "\n-- Student Login --" << endl;
                cout << "Enter User ID: ";
                getline(cin, userId);
                cout << "Enter Password: ";
                getline(cin, password);

                user = library.searchUserById(userId);
                // check if the student exists in the database
                if(user && dynamic_cast<Student*>(user)) 
                {
                    // matches entered password
                    if(user->getPassword() == password)
                    {
                        studentMenu(dynamic_cast<Student*>(user), library);
                    } 
                    else 
                    {
                        cout << "Invalid password." << endl;
                    }
                }
                else 
                {
                    cout << "User not found or not registered as a student." << endl;
                }
                break;
            }

            // Faculty
            case 2: 
            {
                cout << "\n-- Faculty Login --" << endl;
                cout << "Enter User ID: ";
                getline(cin, userId);
                cout << "Enter Password: ";
                getline(cin, password);

                user = library.searchUserById(userId);
                // check if the Faculty exists in the database
                if(user && dynamic_cast<Faculty*>(user)) 
                {
                    if(user->getPassword() == password) 
                    {
                        facultyMenu(dynamic_cast<Faculty*>(user), library);
                    } 
                    else 
                    {
                        cout << "Invalid password." << endl;
                    }
                } 
                else 
                {
                    cout << "User not found or not registered as faculty." << endl;
                }
                break;
            }

            // Librarian
            case 3: 
            {
                cout << "\n-- Librarian Login --" << endl;
                cout << "Enter User ID: ";
                getline(cin, userId);
                cout << "Enter Password: ";
                getline(cin, password);

                user = library.searchUserById(userId);
                // check if the librarian exists in the database
                if(user && dynamic_cast<Librarian*>(user))
                 {
                    if(user->getPassword() == password) 
                    {
                        librarianMenu(dynamic_cast<Librarian*>(user), library);
                    } 
                    else 
                    {
                        cout << "Invalid password." << endl;
                    }
                } 
                else 
                {
                    cout << "User not found or not registered as a librarian." << endl;
                }
                break;
            }

            // Exit the system
            case 4: 
            {
                exitProgram = true;
                break;
            }
            default:
            {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }
    
    // Save current data to files before exiting
    saveAllData(&library);
    
    cout << "Exiting Library Management System. Goodbye!" << endl;
    return 0;
}
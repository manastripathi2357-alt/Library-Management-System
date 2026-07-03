# Library Management System CLI

This project is a Command Line Interface (CLI) Library Management System implemented in C++ that demonstrates Object-Oriented Programming (OOP) concepts such as abstraction, inheritance, polymorphism, and encapsulation. The system manages library operations including book borrowing, returning, fine calculation, and user management across different roles (Student, Faculty, and Librarian).

## Features

- **User Roles and Permissions:**
  - **Students:**
    - Can borrow up to 3 books at a time.
    - Maximum borrowing period of 15 days.
    - Fines are 10 rupees per day for overdue books.
    - Can view all Books,view available books,borrow book,return Book,view history, currently borrowed books,view overdue books,pay Fines,view PaymentHistory,View Book details&History.
  - **Faculty:**
    - Can borrow up to 5 books at a time.
    - Maximum borrowing period of 30 days.
    - No fine for overdue books.
    - Can view abll aooks,view available aooks,borrow book,return book,view history,view currently borrowed books,view borrowing history, and view overdue ooks,view Book details&history.
  - **Librarians:**
    - Manage the library by adding, removing, and updating books.
    - Manage users by adding or removing them.
    - Reserve and unreserve books.(Reserved books can only be read within library and can't be borrowed)
    - Do not have borrowing privileges.

- **Book Management:**
  - Each book has attributes such as title, author, publisher, ISBN, and year.
  - Tracks book status (Available, Borrowed, or Reserved).

- **Account Management:**
  - Each user has an associated account that maintains:
    - A record of currently borrowed books.
    - A borrowing history.
    - Fine calculation for overdue books (based on user role).
    - PaymentHistory
- **Data Persistence:**
  - The system loads data from files at startup and saves the current state before exiting.
  - Uses `Load.h` and `Save.h` for file operations to ensure data persistence between sessions.

- **CLI Interface:**
  - Provides a menu-driven CLI for different user roles.
  - Users log in with their user ID and password.
  - Different menus and options are available based on whether the user is a Student, Faculty, or Librarian.

## File Structure

- **Book.h** – Contains the definition of the `Book` class.
- **Account.h** – Contains the definition of the `Account` class.
- **User.h** – Contains the abstract base class for users.
- **Student.h, Faculty.h, Librarian.h** – Derived classes for specific user roles.
- **Library.h** – Contains the definition of the `Library` class that manages books and users.
- **Load.h** and **Save.h** – Handle loading and saving of library data to files.
- **utils.h** – Provides utility functions (e.g., time formatting, printing).
- **main.cpp** – Contains the main CLI logic where users can log in and perform operations.

## Installation and Compilation

### Prerequisites

- A C++ compiler that supports C++11 or higher (e.g., g++, clang++).
- Standard C++ libraries.

### Compilation

Open a terminal in the project directory and compile the project using the following command:

```bash
g++ -std=c++17 main.cpp Load.cpp Save.cpp Library.cpp Book.cpp User.cpp Account.cpp Utils.cpp Librarian.cpp Student.cpp Faculty.cpp -o LibraryApp
```


### Running the Program

After successful compilation, run the executable:

```bash
./LibraryApp
```

# Usage

1. **Data Initialization:**  
   When the program starts, it attempts to load saved data. If data was never initialized, it initializes the system with default records:
   - 10 Books
   - 5 Students
   - 3 Faculty members
   - 1 Librarian

2. **Login Options:**
   - **Student Login:**  
     Enter your User ID and password to access the student menu. Options include viewing books, borrowing/returning books, viewing borrowed books/overdue book, checking your borrowing history, managing fines, and viewing bookdetails & history.
   - **Faculty Login:**  
     Enter your credentials to access the faculty menu, which includes options to viewing books,borrow/return books, view borrowing history, and view overdue books, view bookdetails & history.
   - **Librarian Login:**  
     Librarians can add, remove, and update books, as well as manage user accounts and book reservations.

3. **Operation Flow:**
   - Use the menu options to perform operations.
   - For borrowing or returning a book, you will be prompted to enter the book’s ISBN.
   - Fine payments and other operations are handled interactively.
   - All changes are saved automatically when you exit the program.




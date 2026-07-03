#include "Account.h"
#include "utils.h"

// Constructor initializes fines and clears book lists.
Account::Account() : fineRemaining(0), TotalPaidFine(0), fineOnReturnedBooks(0) {
    Borrowed.clear();
    History.clear();
}

// Checks if any borrowed book is overdue.
bool Account::checkOverdue(int OverdueLimit) {
    for (auto book : Borrowed) {
        if (book->daysBorrowed() > OverdueLimit) return true;
    }
    return false;
}

// Calculates fine for an individual book.
int Account::FinePerBook(Book* book, int maxDays, int rateOfFine) {
    int daysBorrowed = book->daysBorrowed();

    return (daysBorrowed > maxDays) ? (daysBorrowed - maxDays) * rateOfFine : 0;
}

// Calculates total outstanding fine.
int Account::getFine(int maxDays, int rateOfFine) {
    int fineOnCurrentBooks = 0;
    for (auto book : Borrowed) {
        fineOnCurrentBooks += FinePerBook(book, maxDays, rateOfFine);
    }
    fineRemaining = fineOnCurrentBooks + fineOnReturnedBooks - TotalPaidFine;
    return fineRemaining;
}

// Returns borrowing history.
const vector<tuple<Book*, time_t, time_t>>& Account::getHistory() {
    return History;
}

// Returns list of overdue books.
const vector<Book*> Account::overdueBooks(int overdueLimit) {
    vector<Book*> books;
    for (auto book : Borrowed) {
        if (book->daysBorrowed() > overdueLimit) books.push_back(book);
    }
    return books;
}

// Updates fine when a book is returned.
void Account::updateFineOnReturn(Book* book, int maxDays, int rateOfFine) {
    fineOnReturnedBooks += FinePerBook(book, maxDays, rateOfFine);
}

// Adds a book to the currently borrowed list.
void Account::addBorrowedBook(Book* book) {
    Borrowed.push_back(book);
}

// Processes the return of a book.
void Account::ReturnBook(Book* book, int maxDays, int rateOfFine) {
    auto it = std::find(Borrowed.begin(), Borrowed.end(), book);
    if (it != Borrowed.end()) {
        Borrowed.erase(it); // Simply erase the book from the vector
    }

    time_t curr = getCurrentTime();

    updateFineOnReturn(book, maxDays, rateOfFine);
}

// Pays an outstanding fine.
void Account::payFine(int amount) {
    TotalPaidFine += amount;
}

// Returns the number of currently borrowed books.
int Account::getCurrBorrowed() {
    return Borrowed.size();
}

// Checks if a book is currently borrowed.
bool Account::hasBorrowed(Book* book) {
    // return indexes_borrowed.find(book) != indexes_borrowed.end();
    for(auto borrbook : Borrowed){
        if(book == borrbook) return true;
    }
    return false;
}

// Returns list of currently borrowed books.
vector<Book*> Account::getBorrowedBooks() {
    return Borrowed;
}

// Returns total fine on returned books.
int Account::getFineOnReturnedBooks() {
    return fineOnReturnedBooks;
}

// Returns total paid fine.
int Account::getTotalPaidFine() {
    return TotalPaidFine;
}

// Sets fine on returned books.
void Account::setFineOnReturnedBooks(int fineOnReturnedBooks) {
    this->fineOnReturnedBooks = fineOnReturnedBooks;
}

// Sets total paid fine.
void Account::setTotalPaidFine(int TotalPaidFine) {
    this->TotalPaidFine = TotalPaidFine;
}       

// Adds a book to the borrowed list.
void Account::addToBorrowedBooks(Book* book) {
    Borrowed.push_back(book);
}

// Adds a borrowing history record.
void Account::addHistoryRecord(tuple<string,string,string> record) {
    HistoryISBN.push_back(record);
}

// Adds a book to the borrowing history.
void Account::addToHistory(Book* book, time_t borrowTime, time_t returnDate) {
    History.push_back({book, borrowTime, returnDate});
}
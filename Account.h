#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Book.h"
#include <vector>
#include <unordered_map>
#include <tuple>
using namespace std;

// Account class manages a user's library account, including borrowed books, fines, and borrowing history.
class Account {
private:
    // History of books borrowed and their borrow/return dates.
    vector<tuple<Book*, time_t, time_t> > History;
    // Simplified borrowing history using ISBN and date strings.
    vector<tuple<string , string , string > > HistoryISBN;

    // Remaining unpaid fine.
    int fineRemaining;
    // Total fine paid by the user.
    int TotalPaidFine;
    // Fine accumulated on returned books.
    int fineOnReturnedBooks;
    // List of currently borrowed books.
    vector<Book*> Borrowed;

public:
    Account();
    bool checkOverdue(int OverdueLimit);
    int FinePerBook(Book* book, int maxDays, int rateOfFine);
    int getFine(int maxDays, int rateOfFine);
    void addToHistory(Book* book, time_t borrowTime, time_t returnDate);
    const vector<tuple<Book*, time_t, time_t> >& getHistory();
    const vector<Book*> overdueBooks(int overdueLimit);
    void updateFineOnReturn(Book* book, int maxDays, int rateOfFine);
    void addBorrowedBook(Book* book);
    void ReturnBook(Book* book, int maxDays, int rateOfFine);
    void payFine(int amount);
    int getCurrBorrowed();
    bool hasBorrowed(Book* book);
    vector<Book*> getBorrowedBooks();
    int getFineOnReturnedBooks();
    int getTotalPaidFine();
    void setFineOnReturnedBooks(int fineOnReturnedBooks);
    void setTotalPaidFine(int TotalPaidFine);
    void addToBorrowedBooks(Book* book);
    void addHistoryRecord(tuple<string , string , string> record);
};

#endif // ACCOUNT_H
// Book.cpp

#include "Book.h"
#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
#include<ctime>
#include<chrono>
#include<iomanip>

using namespace chrono;

std::string time_tToDateB(time_t t) {
    if(t == 0) return "N/A"; // Handle uninitialized or zero time
    char buffer[20];
    tm* localTime = localtime(&t);
    // Format: "YYYY-MM-DD HH:MM:SS"
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    return std::string(buffer);
}

// Constructor initializes book details and default status
Book::Book(string Title, string Author, string ISBN, string Publisher, string year){
    this->Title = Title;
    this->Author = Author;
    this->ISBN = ISBN;
    this->Publisher = Publisher;
    this->year = year;
    this->status = "Available";
    this->currentUser = "None";
}

// Checks if the book is available for borrowing
bool Book::isAvailable() {
    return status == "Available";
}

// Checks if the book is reserved (can only be read within the library)
bool Book::isReserved() {
    return status == "Reserved";
}

bool Book::isBorrowed(){
    return status == "Borrowed";
}
// Updates the book's status
void Book::updateStatus(string status) {
    this->status = status;
}

// Gets the current status of the book
string Book::getStatus() {
    return status;
}

// Sets the borrowing date of the book
void Book::setBorrowDate(time_t date) {
    borrowTime = date;
}

// Gets the borrowing date of the book
time_t Book::getBorrowDate() {
    return borrowTime;
}

// Attempts to borrow the book
bool Book::borrowBook() {
    if (!isAvailable() && !isReserved()) {
        cout << "Sorry this book is not available currently" << endl;
        return false;
    }
    if (isReserved()) {
        cout << "Sorry this book is reserved and can only be read within the library" << endl;
        return false;
    }
    updateStatus("Borrowed");
    setBorrowDate(time(nullptr));
    return true;
}

// Adds a past borrower entry when a book is returned
void Book::addPastBorrower() {
    time_t now = time(nullptr);
    string borrDate = to_string(borrowTime);
    string retDate = to_string(now);
    pastBorrowers.push_back({currentUser, borrDate, retDate});
}

// Adds a past borrower entry from file data
void Book::addPastBorrowerFromFile(string UserId, string borrDate, string retDate) {
    pastBorrowers.push_back({UserId, borrDate, retDate});
}

// Sets the current user borrowing the book
void Book::setCurrentUser(string UserId) {
    currentUser = UserId;
}

// Gets the current user borrowing the book
string Book::getCurrentUser() {
    return currentUser;
}

// Returns the book and resets its status
void Book::returnBook() {
    updateStatus("Available");
    setCurrentUser("None");
    setBorrowDate(0);
}

// Gets the ISBN of the book
string Book::getISBN() {
    return ISBN;
}

// Calculates the number of days the book has been borrowed
int Book::daysBorrowed() {
    if (isAvailable()) return 0;
    time_t now = system_clock::to_time_t(system_clock::now());
    double days = (double)(now - borrowTime)/(24.0*60.0*60.0);
    return (int)ceil(days);
}

// Processes the return of a borrowed book
void Book::processReturn() {
    addPastBorrower();
    returnBook();
}

// Updates a book's field with a new value
void Book::updateBook(string field, string value) {
    if (field == "Title") Title = value;
    else if (field == "Author") Author = value;
    else if (field == "ISBN") ISBN = value;
    else if (field == "Publisher") Publisher = value;
    else if (field == "year") year = value;
}

// Displays essential book information
void Book::displayEssentials() {
    cout << Title << " by " << Author << endl;
}

// Displays detailed book information
void Book::display() {
    // cout << "Title : " << Title << " | Author : " << Author << " | Publisher: " << Publisher << " | Year: " << year << " | ISBN: " << ISBN << endl;
    cout << left << setw(40) << Title
                 << setw(25) << Author
                 << setw(35) << Publisher
                 << setw(10)  << year
                 << setw(20) << ISBN
                 << setw(15) << getStatus()
                 << endl;

}

// Displays the book's borrowing history
void Book::DisplayPastBorrowers() {
    if (pastBorrowers.empty()) {
        cout << "No borrowing history available for " << Title << endl;
        return;
    }

    cout << "Past borrowers of " << Title << "\n\n";
    
    cout << left << setw(15) << "UserId" << setw(25) << "Borrowed on" << setw(25) << "Returned on" << endl;
    cout << string(65, '-') << endl;

    for (const auto &entry : pastBorrowers) {
        string UserId, borrTime, retTime;
        tie(UserId, borrTime, retTime) = entry;
        string borrDate = time_tToDateB(stol(borrTime));
        string retDate = time_tToDateB(stol(retTime));
        cout << left << setw(15) << UserId << setw(25) << borrDate << setw(25) << retDate << endl;
    }
    cout << endl;

}

// Returns the book's borrowing history
const vector<tuple<string, string, string>> Book::getPastBorrowers() const {
    return pastBorrowers;
}


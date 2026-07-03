#include "User.h"
#include "utils.h"

// Constructor: Initializes user with name, role, userId, and password
User::User(string name, string role, string UserId , string password)
    : name(name), role(role), UserId(UserId) , password(password) {}

// Getter for user's name
string User::getName() 
{ 
    return name; 
}

// Getter for user's password
string User::getPassword(){
    return password;
}

// Getter for user's unique ID
string User::getUserId() 
{ 
    return UserId; 
}

// Getter for user's role
string User::getRole() 
{ 
    return role; 
}

// Update user details based on field name
void User::updateUser(string field, string value) 
{
    if (field == "name") name = value;
    else if (field == "UserId") UserId = value;
    else if (field == "role") role = value;
}

// View user's borrowing history
void User::viewHistory() 
{
    const auto& history = account.getHistory();
    if (history.empty()) 
    {
        cout << "No borrowing history available" << endl;
        return;
    }

    cout << "Borrowing history of " << UserId << "\n";
    for (const auto& entry : history) 
    {
        Book* book;
        time_t borrowTime, returnTime;
        tie(book, borrowTime, returnTime) = entry;
        string borrowDate = time_tToDate(borrowTime);
        string returnDate = time_tToDate(returnTime);
        cout << book->Title << " by " << book->Author
             << " | Borrowed on: " << borrowDate
             << " | Returned on: " << returnDate
             << endl;
    }
}

// Calculate user's total fine
int User::getFine() 
{
    return account.getFine(getMaxBorrowPeriod(), getRateOfFine()); 
}

// Get list of overdue books
const vector<Book*> User::overDueBooks() 
{ 
    return account.overdueBooks(OverdueLimit()); 
}

// Check if user has reached the borrow limit
bool User::hasReachedBorrowLimit() 
{ 
    return account.getCurrBorrowed() >= getMaxBooksAllowed(); 
}

// Check if user has any pending fines
bool User::hasPendingFines() 
{ 
    return getFine() > 0;
}

// Check if user has any overdue books
bool User::hasAnOverdueBook() 
{ 
    return account.checkOverdue(OverdueLimit()); 
}

// Pay user's fine
void User::payFine(int amount) 
{
    int dues = getFine();
    if (amount > dues) {
        cout << "You can't pay more than the remaining fine" << endl;
    } 
    else if (amount < 0) {
        cout << "You can't pay a negative amount" << endl;
    } 
    else {
        account.payFine(amount);
    }
}

// Borrow a book if user is eligible
bool User::borrowBook(Book* book) 
{
    if (!canBorrowBook()) return false;

    if (book->borrowBook()) 
    {
        book->setCurrentUser(UserId);
        account.addBorrowedBook(book);
        return true;
    }
    return false;
}

// Return a borrowed book
bool User::returnBook(Book* book) 
{
    if (account.hasBorrowed(book)) 
    {
        time_t borrowTime = book->getBorrowDate();
        time_t returnDate = getCurrentTime();

        account.ReturnBook(book, getMaxBorrowPeriod(), getRateOfFine());
        account.addToHistory(book, borrowTime, returnDate);
        account.addHistoryRecord(make_tuple(book->getISBN() , time_tToDate(book->getBorrowDate()), time_tToDate(returnDate)));
        book->processReturn();
        
        return true;
    } 
    else 
    {
        cout << "You have not currently borrowed this book" << endl;
        return false;
    }
    return true;
}

// Get user's account object
Account& User::getAccount()
{
    return account;
}

// Change user's password after validating current password
bool User::setPassword(string currPassword , string newPassword){
    if(currPassword != getPassword()){
        cout << "Please enter the correct current password" << endl;
        return false;
    }
    password = newPassword;
    cout << "Your password has been updated" << endl;
    return true;
};

bool User::hasBook(Book* book){
    return account.hasBorrowed(book);
}

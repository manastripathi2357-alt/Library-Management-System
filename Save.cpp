
// save.cpp
#include "Save.h"
#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
#include<ctime>
#include<chrono>
#include<iomanip>

// Saves book data to a CSV file
void saveBooksToDB(Library* library, const std::string &filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cout << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    // Writing CSV header
    out << "Title,Author,Publisher,ISBN,Year,Status,BorrowDate,CurrUserID\n";
    for (Book* book : library->getBooks()) {
        // Writing book details in CSV format
        out << "\"" << book->Title << "\"," 
            << "\"" << book->Author << "\"," 
            << "\"" << book->Publisher << "\"," 
            << "\"" << book->ISBN << "\"," 
            << "\"" << book->year << "\"," 
            << "\"" << book->getStatus() << "\"," 
            << "\"" << book->getBorrowDate() << "\"," 
            << "\"" << book->getCurrentUser() << "\"\n";
    }
    out.close();
}

// Saves student data to a CSV file
void saveStudentsToDB(Library* library, const std::string &filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cout << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    out << "Name,UserID,FineOnReturnedBooks,TotalPaidFine,BorrowedBooks,History,Password\n";
    for (User* u : library->getUsers()) {
        if (u->getRole() == "Student") {
            Student* s = dynamic_cast<Student*>(u);
            if (!s) continue;
            Account &acc = s->getAccount();
            std::string BorrowedBooks;
            for (Book* b : acc.getBorrowedBooks()) {
                BorrowedBooks += b->getISBN() + ";";
            }
            if (!BorrowedBooks.empty()) BorrowedBooks.pop_back();
            std::string History;
            for (const auto& record : acc.getHistory()) {
                History += get<0>(record)->getISBN() + "|" + time_tToDate(get<1>(record)) + "|" + time_tToDate(get<2>(record)) + ";";
            }
            if (!History.empty()) History.pop_back();
            out << "\"" << s->getName() << "\"," 
                << "\"" << s->getUserId() << "\"," 
                << "\"" << acc.getFineOnReturnedBooks() << "\"," 
                << "\"" << acc.getTotalPaidFine() << "\"," 
                << "\"" << BorrowedBooks << "\"," 
                << "\"" << History << "\"," 
                << "\"" << s->getPassword() << "\"\n";
        }
    }
    out.close();
}

// Saves faculty data to a CSV file
void saveFacultyToDB(Library* library, const std::string &filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cout << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    out << "Name,UserID,BorrowedBooks,History,Password\n";
    for (User* u : library->getUsers()) {
        if (u->getRole() == "Faculty") {
            Faculty* f = dynamic_cast<Faculty*>(u);
            if (!f) continue;
            Account &acc = f->getAccount();
            std::string borrowedBooks;
            for (Book* b : acc.getBorrowedBooks()) {
                borrowedBooks += b->getISBN() + ";";
            }
            if (!borrowedBooks.empty()) borrowedBooks.pop_back();
            std::string history;
            for (const auto& record : acc.getHistory()) {
                history += get<0>(record)->getISBN() + "|" + time_tToDate(get<1>(record)) + "|" + time_tToDate(get<2>(record)) + ";";
            }
            if (!history.empty()) history.pop_back();
            out << "\"" << f->getName() << "\"," 
                << "\"" << f->getUserId() << "\"," 
                << "\"" << borrowedBooks << "\"," 
                << "\"" << history << "\"," 
                << "\"" << f->getPassword() << "\"\n";
        }
    }
    out.close();
}

void saveLibrariansToDB(Library* library, const string &filename) {
    ofstream out(filename);
    if (!out) {
        cout << "Error opening file for writing: " << filename << endl;
        return;
    }
    out << "Name,UserID,Password\n";
    for (User* u : library->getUsers()) {
        if (u->getRole() == "Librarian" || u->getRole() == "librarian") {
            out << "\"" << u->getName() << "\","
                << "\"" << u->getUserId() << "\","
                << "\"" << u->getPassword() << "\"\n";
        }
    }
    out.close();
}

void saveAllUsersToDB(Library* library){
    saveStudentsToDB(library , "students.csv");
    saveFacultyToDB(library , "faculty.csv");
    saveLibrariansToDB(library , "librarian.csv");
}

void saveBookHistoryToDB(Library* library, const std::string &filename){
    ofstream out(filename);
        if (!out) {
            cout << "Error opening file for writing: " << filename << endl;
            return;
        }
        // Header: ISBN, UserID, BorrowDate, ReturnDate
        out << "ISBN,UserID,BorrowDate,ReturnDate\n";
        for (Book* book : library->getBooks()) {
            const auto &history = book->getPastBorrowers();
            for (const auto &record : history) {
                out << book->getISBN() << ","
                    << get<0>(record) << ","
                    << get<1>(record) << ","
                    << get<2>(record) << "\n";
            }
        }
        out.close();
}
// Saves all data to respective files
void saveAllData(Library* library) {
    saveBooksToDB(library, "books.csv");
    saveAllUsersToDB(library);
    saveBookHistoryToDB(library, "bookHistory.csv");
}

// Triggers saving all library data
void savefile(Library* library) {
    saveAllData(library);
}


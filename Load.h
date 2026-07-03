// Load.h
#ifndef LOAD_H
#define LOAD_H

#include<bits/stdc++.h>
#include"Book.h"
#include"Account.h"
#include"utils.h"
#include"User.h"
#include"Library.h"
#include"Student.h"
#include"Faculty.h"
#include"Librarian.h"

// Function declarations for loading data from CSV files
void loadBooksFromDB(Library* library, const std::string& filename);
void loadStudentsFromDB(Library* library, const std::string& filename);
void loadFacultyFromDB(Library* library, const std::string& filename);
void loadLibrariansFromDB(Library* library, const std::string& filename);
void loadBookHistoryFromDB(Library* library, const std::string& filename);
void loadAllUsersFromDB(Library* library);
void loadAllData(Library* library);
void loadfile(Library* library);

#endif // LOAD_H
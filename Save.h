// save.h
#ifndef SAVE_H
#define SAVE_H

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

// Functions to save different types of data to the database
void saveBooksToDB(Library* library, const std::string &filename);
void saveStudentsToDB(Library* library, const std::string &filename);
void saveFacultyToDB(Library* library, const std::string &filename);
void saveLibrariansToDB(Library* library, const std::string &filename);
void saveBookHistoryToDB(Library* library, const std::string &filename);
void saveAllUsersToDB(Library* library);
void saveAllData(Library* library);
void savefile(Library* library);

#endif // SAVE_H

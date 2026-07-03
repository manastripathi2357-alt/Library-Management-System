#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <unordered_map>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <chrono>
#include "Book.h"
using namespace std;
using namespace std::chrono;

// Converts a time_t object to a human-readable date string.
string time_tToDate(time_t Time);

// Returns the current system time as a time_t object.
time_t getCurrentTime();

// Parses a date string and converts it into a time_t object.
time_t parseTimeString(const std::string& timeStr);

// Checks if a given key is present in an unordered_map.
template <typename T1, typename T2>
bool isPresent(unordered_map<T1, T2>& mp, T1 key)
{
    return mp.find(key) != mp.end();
}

// Prints essential details of a vector of Book objects.
void printEssentialOfBooks(vector<Book*> books);
void printBooks(vector<Book*> books);
#endif // UTILS_H

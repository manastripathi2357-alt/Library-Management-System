#include "utils.h"

std::string time_tToDate(time_t t) {
    if(t == 0) return "N/A"; // Handle uninitialized or zero time
    char buffer[20];
    tm* localTime = localtime(&t);
    // Format: "YYYY-MM-DD HH:MM:SS"
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    return std::string(buffer);
}
// convert Date to time
time_t parseTimeString(const std::string& timeStr) {
    if (timeStr == "N/A" || timeStr.empty()) {
        return 0;  // Return 0 for uninitialized or missing date
    }

    struct tm tmStruct = {};  // Initialize all fields to zero
    std::istringstream ss(timeStr);
    
    // Parse string into tm structure (Format: YYYY-MM-DD HH:MM:SS)
    ss >> std::get_time(&tmStruct, "%Y-%m-%d %H:%M:%S");
    
    if (ss.fail()) {
        std::cerr << "Error: Invalid time format: " << timeStr << "\n";
        return 0;  // Return 0 on failure
    }
    
    return mktime(&tmStruct);  // Convert to time_t
}

time_t getCurrentTime()
{
    return system_clock::to_time_t(system_clock::now());
}

void printEssentialOfBooks(vector<Book*> books)
{
    for(auto book : books)
    {
        book->displayEssentials();
    }
    return;
}

void printBooks(vector<Book*> books)
{
    cout << "\n\n";
     cout << left << setw(40) << "Title"
     << setw(25) << "Author"
     << setw(35) << "Publisher"
     << setw(10)  << "Year"
     << setw(20) << "ISBN"
     << setw(15) << "Status"
     << endl;
    cout << string(145, '-') << endl;
    for(auto book : books)
    {   
        book->display();
    }
    return;
}
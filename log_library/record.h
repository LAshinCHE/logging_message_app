// record.h
#ifndef RECORD_LIBRARY_H
#define RECORD_LIBRARY_H

#include "record.h"
#include <string>
#include <ctime>
#include <sstream>

#ifdef _WIN32
    #ifdef RECORD_LIBRARY_EXPORTS
        #define RECORD_API __declspec(dllexport)
    #else
        #define RECORD_API __declspec(dllimport)
    #endif
#else
    #define RECORD_API
#endif

class RECORD_API Record {
public:
    Record(const std::string&message, int importanceLevel, time_t data);
    ~Record();
    std::string toCSV() const;  
    static Record fromCSV(const std::string& line);

public:
    std::time_t data;
    int importanceLevel;
    std::string message;
};

#endif //  RECORD_LIBRARY_H

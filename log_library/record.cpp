//record.cpp
#include "record.h"

Record::Record(const std::string&message, int importanceLevel, time_t data) : message(message), importanceLevel(importanceLevel), data(data) {};

Record::~Record(){}

std::string Record::toCSV() const {
    std::string timeStr = std::ctime(&data);
    timeStr.pop_back();
    return message + "," + std::to_string(importanceLevel) + "," + timeStr;
}


Record Record::fromCSV(const std::string& line) {
    std::istringstream iss(line);
    std::string message, lvlMessage, date;

    std::getline(iss, message, ',');
    std::getline(iss, lvlMessage, ',');
    std::getline(iss, date);

    int importanceLevel = std::stoi(lvlMessage); // Преобразование строки в int

    // Преобразование строки даты в time_t
    struct tm tm = {};
    strptime(date.c_str(), "%a %b %d %H:%M:%S %Y", &tm); // Парсинг даты
    time_t timeData = mktime(&tm);

    return {message, importanceLevel, timeData};
}


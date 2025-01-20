// log_library.cpp
#include "log_library.h"
#include "record.h" 
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <ctime>

Logger::Logger(const std::string& filePath) : logFilePath(filePath) {
    // Проверяем, можно ли открыть файл
    std::ofstream file(logFilePath, std::ios::app);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open log file: " + logFilePath);
    }
}

Logger::~Logger() {
    // Деструктор, если требуется, можно добавить логику для очистки ресурсов
}

void Logger::LogMessage(const std::string& message, int messageLevel) {
    std::ofstream file(logFilePath, std::ios::app);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to write to log file: " + logFilePath);
    }
    std::time_t now = std::time(nullptr);
    Record rec(message, messageLevel, now); 
    file  << rec.toCSV() << std::endl;
}

std::vector<Record> Logger::ReadAllMessage(){
    std::vector<Record> records;
    std::ifstream file(logFilePath);

    if (!file) {
        std::cerr << "Error: Unable to open file " << logFilePath << std::endl;
        return records;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            records.push_back(Record::fromCSV(line));
        }
    }
    file.close();
    return records;
}

void Logger::ChangeMessageLevel(const std::string& message, const int& newLevel) {
    std::vector<Record> records = Logger::ReadAllMessage();

    // Обновление уровня сообщения для записи с указанным message
    for (auto& record : records) {
        if (record.message == message) {
            record.importanceLevel = newLevel;
        }
    }

    // Перезаписываем файл с обновленными данными
    std::ofstream file(logFilePath);
    if (!file) {
        std::cerr << "Error: Unable to open file " << logFilePath << std::endl;
        return;
    }
    for (const auto& record : records) {
        file << record.toCSV() << std::endl;
    }
    file.close();
}


// log_library.h
#ifndef LOG_LIBRARY_H
#define LOG_LIBRARY_H

#include <string>

#ifdef _WIN32
    #ifdef LOG_LIBRARY_EXPORTS
        #define LOG_API __declspec(dllexport)
    #else
        #define LOG_API __declspec(dllimport)
    #endif
#else
    #define LOG_API
#endif

class LOG_API Logger {
public:
    explicit Logger(const std::string& filePath);
    ~Logger();

    void LogMessage(const std::string& message, int messageLevel);
    void ChangeMessageLevel(int newLevel);
private:
    std::vector<Record> ReadAllMessageI();

private:
    std::string logFilePath;
};

#endif // LOG_LIBRARY_H

#include "log_library.h"
#include <iostream>
#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

// Потокобезопасная очередь для сообщений
struct LogEntry {
    std::string message;
    int importanceLevel;
};

class SafeQueue {
private:
    std::queue<LogEntry> queue;
    std::mutex mutex;
    std::condition_variable condition;
    bool stopFlag = false;

public:
    void push(const LogEntry& entry) {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(entry);
        condition.notify_one();
    }

    bool pop(LogEntry& entry) {
        std::unique_lock<std::mutex> lock(mutex);
        condition.wait(lock, [&] { return !queue.empty() || stopFlag; });
        if (stopFlag && queue.empty()) return false;
        entry = queue.front();
        queue.pop();
        return true;
    }

    void stop() {
        std::lock_guard<std::mutex> lock(mutex);
        stopFlag = true;
        condition.notify_all();
    }
};

// Поток записи в журнал
void logWriter(SafeQueue& logQueue, Logger& logger) {
    LogEntry entry;
    while (logQueue.pop(entry)) {
        logger.LogMessage(entry.message, entry.importanceLevel);
    }
}

int main(int argc, char* argv[]) {
    // Чтение параметров
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <logfile> <default_level>" << std::endl;
        return 1;
    }

    std::string logFile = argv[1];
    int defaultLevel = std::stoi(argv[2]);

    // Создаем объект логгера
    Logger logger(logFile);

    // Создание потокобезопасной очереди и фоновый поток
    SafeQueue logQueue;
    std::thread loggerThread(logWriter, std::ref(logQueue), std::ref(logger));

    std::cout << "Logging to: " << logFile 
              << "\nEnter messages (format: <level> <message> or <message>) or commands:"
              << "\n- change <message> <new_level>: Change log level of an existing message."
              << "\n- exit: Exit the application." << std::endl;

    // Основной цикл ввода
    std::atomic<bool> running = true;
    while (running) {
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit") {
            running = false;
            break;
        }

        // Проверка на команду изменения уровня важности
        if (input.rfind("change ", 0) == 0) {
            size_t firstSpace = input.find(' ', 7);
            if (firstSpace != std::string::npos) {
                std::string message = input.substr(7, firstSpace - 7);
                try {
                    int newLevel = std::stoi(input.substr(firstSpace + 1));
                    logger.ChangeMessageLevel(message, newLevel);
                    std::cout << "Log level changed for message: \"" << message << "\" to level " << newLevel << std::endl;
                } catch (...) {
                    std::cerr << "Invalid level format. Usage: change <message> <new_level>" << std::endl;
                }
            } else {
                std::cerr << "Invalid command format. Usage: change <message> <new_level>" << std::endl;
            }
            continue;
        }

        // Разбор сообщения
        size_t spacePos = input.find(' ');
        int level = defaultLevel;
        std::string message = input;

        if (spacePos != std::string::npos) {
            try {
                level = std::stoi(input.substr(0, spacePos));
                message = input.substr(spacePos + 1);
            } catch (...) {
                level = defaultLevel; // Если уровень некорректный, используем уровень по умолчанию
            }
        }

        // Передача сообщения в очередь
        logQueue.push({message, level});
    }

    // Завершаем поток логирования
    logQueue.stop();
    loggerThread.join();

    std::cout << "Logging stopped." << std::endl;
    return 0;
}

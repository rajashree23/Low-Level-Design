#include <iostream>
#include <string>

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(const std::string& message) {
        std::cout << message << std::endl;
    }

private:
    Logger() = default;
};

int main() {
    Logger::getInstance().log("Application started");
    Logger::getInstance().log("User logged in");

    return 0;
}
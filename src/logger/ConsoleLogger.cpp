#include "ConsoleLogger.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string ConsoleLogger::timestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void ConsoleLogger::info(const std::string& message) {
    std::cout << "[" << timestamp() << "] [INFO]  " << message << "\n";
}

void ConsoleLogger::error(const std::string& message) {
    std::cerr << "[" << timestamp() << "] [ERROR] " << message << "\n";
}

void ConsoleLogger::debug(const std::string& message) {
    std::cout << "[" << timestamp() << "] [DEBUG] " << message << "\n";
}
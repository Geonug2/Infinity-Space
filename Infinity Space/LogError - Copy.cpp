#include "LogError.h"
#include <fstream>

void LogError(const std::string& message) {
    std::ofstream logFile("error_log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << message << std::endl;
    }
}
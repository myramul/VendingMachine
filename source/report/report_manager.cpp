#include "report/report_manager.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <filesystem>

std::string ReportManager::getCurrentDateTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    std::tm *ptm = std::localtime(&now_time);
    char buffer[32];
    std::strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", ptm);
    return std::string(buffer);
}

void ReportManager::writeToFile(const std::string& message)
{
    std::string logDir = "logs";
    std::filesystem::create_directory(logDir); // auto-create logs dir if missing
    std::ofstream logFile(logDir + "/vending_machine.log", std::ios_base::app);
    if (logFile.is_open()) {
        logFile << message << std::endl;
    } else {
        std::cerr << "Failed to open log file." << std::endl;
    }
}

void ReportManager::logTransaction(const std::string &beverage, double moneyInserted, double changeGiven)
{
    std::ostringstream oss;
    oss << "[" << getCurrentDateTime() << "] Transaction: \tBeverage: " << beverage
        << ", Money Inserted: $" << moneyInserted
        << ", Change Given: $" << changeGiven;
   
    std::string log = oss.str();
    std::cout << log << std::endl;
    writeToFile(log);
}


void ReportManager::displayReports() {
    std::cout << "To view the maintenance transaction report. Please open the log file stored at: logs/vending_machine.log" << std::endl;
}
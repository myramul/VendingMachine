#include "report_manager.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <ctime>

std::string ReportManager::getCurrentDateTime() 
{

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    std::tm *ptm = std::localtime(&now_time);
    char buffer[32];
    std::strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", ptm);
    return std::string(buffer);
}

void ReportManager::logTransaction(const std::string &beverage, double moneyInserted, double changeGiven) 
{
    std::ostringstream oss;
    oss << "[" << getCurrentDateTime() << "] Transaction: Beverage: " << beverage
        << ", Money Inserted: $" << moneyInserted 
        << ", Change Given: $" << changeGiven;
    
    std::cout << oss.str() << std::endl;
}

void ReportManager::logMaintenanceOpening(const std::map<std::string, int> &changeLevels, double moneyCollected, const std::map<int, std::vector<std::string>> &slotContents) 
{
    std::ostringstream oss;
    oss << "[" << getCurrentDateTime() << "] Maintenance Opening Report:" << std::endl;
    oss << "Money Collected: $" << moneyCollected << std::endl;
    oss << "Change Levels:" << std::endl;
    
  for (const auto &pair : changeLevels) 
    {
        oss << "  " << pair.first << ": " << pair.second << std::endl;
    }
    oss << "Slot Contents:" << std::endl;
    
  for (const auto &slot : slotContents) 
    {
        oss << "  Slot " << slot.first << ": ";
        
      for (const auto &item : slot.second) 
        {
            oss << item << " ";
        }
        oss << std::endl;
    }
    
    std::cout << oss.str() << std::endl;
}

void ReportManager::logClosingReport(const std::map<std::string, int> &changeLevels,
double moneyCollected, const std::map<int, std::vector<std::string>> &slotContents) 
{
    std::ostringstream oss;
    oss << "[" << getCurrentDateTime() << "] Closing Report:" << std::endl;
    oss << "Money Collected: $" << moneyCollected << std::endl;
    oss << "Change Levels:" << std::endl;
    for (const auto &pair : changeLevels) 
    {
        oss << "  " << pair.first << ": " << pair.second << std::endl;
    }
    oss << "Slot Contents:" << std::endl;
  
    for (const auto &slot : slotContents) 
    {
        oss << "  Slot " << slot.first << ": ";
        
      for (const auto &item : slot.second) 
        {
            oss << item << " ";
        }
        oss << std::endl;
    }
    
    std::cout << oss.str() << std::endl;
}

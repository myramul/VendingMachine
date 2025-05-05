#ifndef REPORT_MANAGER_H
#define REPORT_MANAGER_H

#include <string>
#include <map>
#include <vector>

class ReportManager {
public:
    void logTransaction(const std::string &beverage, double moneyInserted, double changeGiven);
    void displayReports();

private:
    void writeToFile(const std::string& message);
    std::string getCurrentDateTime();
};

#endif
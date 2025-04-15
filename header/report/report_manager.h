#ifndef REPORT_MANAGER_H
#define REPORT_MANAGER_H

#include <string>
#include <map>
#include <vector>

class ReportManager {
public:

    void logTransaction(const std::string &beverage, double moneyInserted, double changeGiven);

    void logMaintenanceOpening(const std::map<std::string, int> &changeLevels,
                               double moneyCollected,
                               const std::map<int, std::vector<std::string>> &slotContents);


    void logClosingReport(const std::map<std::string, int> &changeLevels,
                          double moneyCollected,
                          const std::map<int, std::vector<std::string>> &slotContents);

private:

    std::string getCurrentDateTime();
};

#endif

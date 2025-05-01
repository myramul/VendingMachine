#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <functional>
#include <vector>
#include <unordered_map>
#include <string>

enum class EventType {
    StartCoinAccepting,
    FundsAvailable,
    BeverageDispensed,   
    MaintenanceMode,
    IdleMode,
    TransactionComplete
};

struct EventData {
    std::string message;
    double inserted_amount;
    double beverage_cost;
    int slotID;
    std::string beverage_name;
};

class EventManager {
public:
    void registerListener(EventType eventType, std::function<void(const EventData&)> callback);
    void notify(EventType eventType, const EventData &data);
private:
    std::unordered_map<EventType, std::vector<std::function<void(const EventData&)>>> listeners;
};

#endif

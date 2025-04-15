#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

enum class EventType {
    FundsAvailable,
    BeverageDispensed,   
    MaintenanceMode,
    Idle,  
    TransactionComplete    
};

struct EventData{
    std::string message;
    double inserted_amount;
    double beverage_cost;
};

class EventManager {

};

#endif
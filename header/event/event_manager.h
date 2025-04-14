#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

enum class EventType {
    FundsAvailable, 
    DispenseItem,  
    InsufficientFunds,
    MaintenanceMode,
    IdleMode,    
    TransactionComplete    
};

struct EventData{

};

class EventManager {

};

#endif
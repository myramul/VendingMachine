#ifndef MONEY_HANDLER_H
#define MONEY_HANDLER_H

#include <vector>
#include <string>
#include "money/coin.h"
#include "event/event_manager.h"
#include "money/coin_slot.h"
#include "money/change_drawer.h"
#include "money/change_dispenser.h"
#include "money/collected_coin.h"

enum class MoneyHandlerState {
    Idle,
    Processing,
    Maintenance
};
class MoneyHandler {
    public:
        MoneyHandler(CollectedCoin* collectedCoin, CoinSlot* coinSlot, ChangeDrawer* changeDrawer, ChangeDispenser* changeDispenser, EventManager* eventManager);
        void setState(MoneyHandlerState state);
        void onResetForNewTransaction();
    private:
        CoinSlot* coinSlot;
        ChangeDrawer* changeDrawer;
        ChangeDispenser* changeDispenser;
        CollectedCoin* collectedCoin;
        bool exactChangeMode;
        MoneyHandlerState state;
        EventManager* eventManager;

        bool enterIdleState(); 
        bool enterProcessingState(); 
        bool enterMaintenanceMode(); 
        bool isExactChangeRequired() const; 
};

#endif
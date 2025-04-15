#ifndef MONEY_HANDLER_H
#define MONEY_HANDLER_H

#include <vector>
#include <string>
#include "coin.h"
#include "event_manager.h"
#include "coin_slot.h"
#include "change_drawer.h"
#include "change_dispenser.h"
#include "collected_coin.h"

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
        bool enterProcessingState(); // called when setState(MoneyHandlerState::Processing)should start coin insertion but first check if there is enough change
        bool enterMaintenanceMode(); 
        bool isExactChangeRequired() const; // if change is 25c or less return true
};

#endif
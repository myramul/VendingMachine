// money_handler.h

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
#include "money/coin_return.h"

enum class MoneyHandlerState {
    Idle,
    Processing,
    Maintenance
};
class MoneyHandler {
    public:
        MoneyHandler(CollectedCoin* collectedCoin, CoinSlot* coinSlot, ChangeDrawer* changeDrawer, ChangeDispenser* changeDispenser, EventManager* eventManager, CoinReturn* coinReturn);
        void setState(MoneyHandlerState state);
        void onResetForNewTransaction();
        void refillChange();
        void collectMoney();
    private:
        CoinSlot* coinSlot;
        ChangeDrawer* changeDrawer;
        ChangeDispenser* changeDispenser;
        CollectedCoin* collectedCoin;
        CoinReturn* coinReturn;
        bool exactChangeMode;
        MoneyHandlerState state = MoneyHandlerState::Idle;
        EventManager* eventManager;

        void enterIdleState(); 
        void enterProcessingState(); 
        void enterMaintenanceMode(); 
        bool isExactChangeRequired() const; 
};

#endif
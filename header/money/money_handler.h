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
        bool checkChangeLevels() const;
        bool isExactChangeRequired() const;
    public:
        MoneyHandler(CoinSlot* coinSlot, ChangeDrawer* changeDrawer, ChangeDispenser* changeDispenser, EventManager* eventManager);
        void setState(MoneyHandlerState state);
};
#endif
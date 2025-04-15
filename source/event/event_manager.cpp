#include "event/event_manager.h"

void EventManager::registerListener(EventType eventType, std::function<void(const EventData&)> callback) {

    listeners[eventType].push_back(callback);
}

void EventManager::notify(EventType eventType, const EventData &data) {

    if (listeners.find(eventType) != listeners.end()) {
        for (auto &callback : listeners[eventType]) {
            callback(data);
        }
    }
}

#ifndef EVENT_BUS_HPP
#ifndef EVENT_BUS_HPP
#define EVENT_BUS_HPP

#include <vector>
#include <functional>
#include <unordered_map>
#include <string>
#include <any>

class EventBus {
private:
    std::unordered_map<std::string, std::vector<std::function<void(const std::any&)>>> subscribers;

public:
    EventBus() = default;

    // Suscribir una función a un evento específico del motor
    void subscribe(const std::string& eventType, std::function<void(const std::any&)> callback) {
        subscribers[eventType].push_back(callback);
    }

    // Publicar un evento para que todos los oyentes lo procesen en el ciclo actual
    void publish(const std::string& eventType, const std::any& data) {
        if (subscribers.find(eventType) != subscribers.end()) {
            for (auto& callback : subscribers[eventType]) {
                callback(data);
            }
        }
    }
};

#endif
#endif // EVENT_BUS_HPP
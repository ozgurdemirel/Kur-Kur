#pragma once

#include <string>

namespace exchange_app {

class NotificationService {
public:
    NotificationService() = default;
    
    void sendNotification(const std::string& title, const std::string& message);
    
    void playSound();
    
private:
    int executeCommand(const std::string& command);
};

} // namespace exchange_app 
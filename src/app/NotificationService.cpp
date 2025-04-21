#include "app/NotificationService.h"
#include <iostream>
#include <cstdlib>

namespace exchange_app {

void NotificationService::sendNotification(const std::string& title, const std::string& message) {
    std::string appleScript =
        "display notification \"" + message + "\" with title \"" + title + "\"";
    std::string cmd = "osascript -e '" + appleScript + "'";
    
    if (executeCommand(cmd) != 0) {
        std::cerr << "Failed to send notification!" << std::endl;
    }
    
    // Also play a sound
    playSound();
}

void NotificationService::playSound() {
    // Play sound in background (non-blocking)
    executeCommand("afplay /System/Library/Sounds/Ping.aiff &");
}

int NotificationService::executeCommand(const std::string& command) {
    return std::system(command.c_str());
}

} // namespace exchange_app 
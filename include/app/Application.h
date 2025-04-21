#pragma once

#include <atomic>
#include <thread>
#include "ExchangeRateProvider.h"
#include "NotificationService.h"

namespace exchange_app {

class Application {
public:
    Application();
    ~Application();
    
    void run();
    
    void stop();
    
    bool isRunning() const { return running_; }
    
private:
    void waitForUserInput();
    
    std::atomic<bool> running_;
    std::thread inputThread_;
    ExchangeRateProvider rateProvider_;
    NotificationService notificationService_;
};

} // namespace exchange_app 
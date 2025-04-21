#include "app/Application.h"
#include "utils/TimeUtils.h"
#include <iostream>
#include <chrono>

namespace exchange_app {

Application::Application() : running_(false) {
}

Application::~Application() {
    if (inputThread_.joinable()) {
        inputThread_.join();
    }
}

void Application::run() {
    running_ = true;
    
    inputThread_ = std::thread(&Application::waitForUserInput, this);
    
    std::cout << "Started: Exchange rate notifications will be sent at the beginning of each hour.\n" << std::flush;
    
    auto rates = rateProvider_.fetchRates();
    notificationService_.sendNotification("Exchange Rates", rates);
    std::cout << "Notification: " << rates << "\n" << std::flush;
    
    while (running_) {
        int waitSec = TimeUtils::calculateTimeToNextHour();
        std::cout << "Seconds until the next hour: " << waitSec << "\n" << std::flush;
        
        for (int i = 0; i < waitSec && running_; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        
        if (!running_) break;
        
        rates = rateProvider_.fetchRates();
        notificationService_.sendNotification("Exchange Rates", rates);
        std::cout << "Notification: " << rates << "\n" << std::flush;
        
        // Short pause to reduce CPU load
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    
    std::cout << "Program is shutting down..." << std::endl;
}

void Application::stop() {
    running_ = false;
}

void Application::waitForUserInput() {
    std::cout << "Press 'e' and Enter to stop the program." << std::endl;
    std::cout << std::flush;
    
    while (running_) {
        char c;
        if (!(std::cin >> c)) break;
        
        if (c == 'e' || c == 'E') {
            std::cout << "Stop request received." << std::endl;
            stop();
            break;
        }
    }
}

}
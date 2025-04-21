#pragma once

#include <string>

namespace exchange_app {

class TimeUtils {
public:
    // Get current time formatted as HH:MM:SS
    static std::string getCurrentTime();
    
    // Calculate seconds until the next hour
    static int calculateTimeToNextHour();
};

} // namespace exchange_app 
#include "utils/TimeUtils.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace exchange_app {

std::string TimeUtils::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);
    std::ostringstream ss;
    ss << std::setw(2) << std::setfill('0') << tm.tm_hour << ":"
       << std::setw(2) << std::setfill('0') << tm.tm_min  << ":"
       << std::setw(2) << std::setfill('0') << tm.tm_sec;
    return ss.str();
}

int TimeUtils::calculateTimeToNextHour() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);
    int secToMinute = 60 - tm.tm_sec;
    int minToHour   = 59 - tm.tm_min;
    return secToMinute + minToHour * 60;
}

} // namespace exchange_app 
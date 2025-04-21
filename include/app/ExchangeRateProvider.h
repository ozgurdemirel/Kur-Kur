#pragma once

#include <string>
#include <curl/curl.h>
#include "../../third_party/pugixml.hpp"

namespace exchange_app {

class ExchangeRateProvider {
public:
    ExchangeRateProvider();
    ~ExchangeRateProvider();
    
    std::string fetchRates();
    
private:
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userdata);
    
    std::string parseRatesXml(const std::string& xmlData);
    
    bool isInitialized() const { return curl_ != nullptr; }
    
    CURL* curl_;
};

} // namespace exchange_app 
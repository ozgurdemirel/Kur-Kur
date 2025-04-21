#include "app/ExchangeRateProvider.h"
#include <iostream>
#include <cstring>

namespace exchange_app {

ExchangeRateProvider::ExchangeRateProvider() : curl_(nullptr) {
    curl_ = curl_easy_init();
    if (!isInitialized()) {
        std::cerr << "Failed to initialize CURL" << std::endl;
    }
}

ExchangeRateProvider::~ExchangeRateProvider() {
    if (isInitialized()) {
        curl_easy_cleanup(curl_);
        curl_ = nullptr;
    }
}

size_t ExchangeRateProvider::writeCallback(void* contents, size_t size, size_t nmemb, void* userdata) {
    size_t total = size * nmemb;
    auto* buffer = static_cast<std::string*>(userdata);
    buffer->append(static_cast<char*>(contents), total);
    return total;
}

std::string ExchangeRateProvider::fetchRates() {
    if (!isInitialized()) {
        return "Error: CURL not initialized";
    }
    
    std::string readBuffer;
    curl_easy_setopt(curl_, CURLOPT_URL, "https://www.tcmb.gov.tr/kurlar/today.xml");
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl_, CURLOPT_FAILONERROR, 1L); // Return error on HTTP 4xx/5xx errors
    
    CURLcode res = curl_easy_perform(curl_);
    if (res != CURLE_OK) {
        std::cerr << "Failed to fetch exchange rates: "
                  << curl_easy_strerror(res) << std::endl;
        return "Failed to fetch exchange rates";
    }
    
    return parseRatesXml(readBuffer);
}

std::string ExchangeRateProvider::parseRatesXml(const std::string& xmlData) {
    pugi::xml_document doc;
    pugi::xml_parse_result parseResult = doc.load_string(xmlData.c_str());
    
    if (!parseResult) {
        std::cerr << "XML parse error: " << parseResult.description()
                  << " at offset " << parseResult.offset << std::endl;
        return "Failed to parse XML data";
    }
    
    std::string usdBuy = "N/A", usdSell = "N/A";
    std::string eurBuy = "N/A", eurSell = "N/A";
    
    for (auto& currency : doc.child("Tarih_Date").children("Currency")) {
        const char* code = currency.attribute("Kod").value();
        if (std::strcmp(code, "USD") == 0) {
            usdBuy = currency.child_value("ForexBuying");
            usdSell = currency.child_value("ForexSelling");
        } else if (std::strcmp(code, "EUR") == 0) {
            eurBuy = currency.child_value("ForexBuying");
            eurSell = currency.child_value("ForexSelling");
        }
    }
    
    return "USD/TRY: Buy: " + usdBuy + " - Sell: " + usdSell + "\n" 
         + "EUR/TRY: Buy: " + eurBuy + " - Sell: " + eurSell + "\n"
         + "Source: TCMB (tcmb.gov.tr)";
}

} // namespace exchange_app 
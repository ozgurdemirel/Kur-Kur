#include "include/app/Application.h"
#include <iostream>
#include <curl/curl.h>

int main() {
    if (curl_global_init(CURL_GLOBAL_ALL) != 0) {
        std::cerr << "CURL global initialization failed!" << std::endl;
        return 1;
    }
    
    try {
        exchange_app::Application app;
        app.run();
    } 
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    curl_global_cleanup();
    return 0;
}
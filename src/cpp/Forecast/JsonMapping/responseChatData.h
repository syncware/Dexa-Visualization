#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include <exception>
#include <tuple>
#include "../ProductionForecast/Forecast.h"
#include "../../nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

json to_json(const ResponseChatData& responseChatData) {
    json j;

    for (const auto& outer1 : responseChatData.response) {
        const string& key1 = outer1.first;
        for (const auto& outer2 : outer1.second) {
            const string& key2 = outer2.first;
            const string& value = outer2.second;
            j["response"][key1][key2] = value;
        }
    }

    return j;
}

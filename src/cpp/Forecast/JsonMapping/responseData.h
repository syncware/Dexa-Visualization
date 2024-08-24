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

json to_json(const ResponseData& responseData) {
    json j;

    for (const auto& outer1 : responseData.monthlyReport) {
        const string& key1 = outer1.first;
        for (const auto& outer2 : outer1.second) {
            const string& key2 = outer2.first;
            for (const auto& outer3 : outer2.second) {
                const string& key3 = outer3.first;
                for (const auto& outer4 : outer3.second) {
                    const string& key4 = outer4.first;
                    for (const auto& outer5 : outer4.second) {
                        const string& key5 = outer5.first;
                        for (const auto& inner : outer5.second) {
                            const string& key6 = inner.first;
                            const string& value = inner.second;
                            j["monthlyReport"][key1][key2][key3][key4][key5][key6] = value;
                        }
                    }
                }
            }
        }
    }

    return j;
}
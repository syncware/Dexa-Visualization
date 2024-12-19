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

/* json to_json(const ResponseData& responseData) {
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
} */

json to_json(const ResponseData &responseData)
{
    json j;

    for (const auto &outer1 : responseData.monthlyReport)
    {
        const string &key1 = outer1.first;
        for (const auto &outer2 : outer1.second)
        {
            const string &key2 = outer2.first;
            for (const auto &outer3 : outer2.second)
            {
                const string &key3 = outer3.first;
                for (const auto &outer4 : outer3.second)
                {
                    const string &key4 = outer4.first;
                    for (const auto &inner : outer4.second)
                    {
                        const string &key5 = inner.first;
                        const string &value = inner.second;
                        j["monthlyReport"][key1][key2][key3][key4][key5] = value;
                    }
                }
            }
        }
    }

    return j;
}

ResponseData parseResponseData(const json &j)
{
    ResponseData responseData;

    for (const auto &outer1 : j.at("monthlyReport").items())
    {
        const string &key1 = outer1.key();
        for (const auto &outer2 : outer1.value().items())
        {
            const string &key2 = outer2.key();
            for (const auto &outer3 : outer2.value().items())
            {
                const string &key3 = outer3.key();
                for (const auto &outer4 : outer3.value().items())
                {
                    const string &key4 = outer4.key();
                    for (const auto &inner : outer4.value().items())
                    {
                        const string &key5 = inner.key();
                        const string &value = inner.value();
                        responseData.monthlyReport[key1][key2][key3][key4][key5] = value;
                    }
                }
            }
        }
    }

    return responseData;
}

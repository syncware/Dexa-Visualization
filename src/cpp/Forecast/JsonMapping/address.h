#pragma once

#include "../ProductionForecast/Forecast.h"
#include "../../nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

// Free functions for JSON conversion
void from_json(const json &j, Address &addr)
{
    j.at("city").get_to(addr.city);
    j.at("zip").get_to(addr.zip);
}
#pragma once
/* #include <napi.h> */
// #include "node_modules/node-addon-api/napi.h"
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


void from_json(const json& j, RunParameter& deck) {
    j.at("stopDay").get_to(deck.StopDay);
    j.at("stopMonth").get_to(deck.StopMonth);
    j.at("stopYear").get_to(deck.StopYear);
}

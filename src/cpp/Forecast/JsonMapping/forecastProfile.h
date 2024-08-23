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


void from_json(const json& j, ForecastResult& deck) {
    j.at("GOR").get_to(deck.GOR);
    j.at("CGR").get_to(deck.CGR);
    j.at("BSW").get_to(deck.BSW);
    j.at("WGR").get_to(deck.WGR);
    j.at("cumOilProd").get_to(deck.Cum_Oil_Prod);
    j.at("cumGasProd").get_to(deck.Cum_Gas_Prod);
    j.at("moduleName").get_to(deck.ModuleName);
    j.at("oilRate").get_to(deck.Oil_rate);
    j.at("gasRate").get_to(deck.Gas_Rate);
    j.at("hydrocarbonStream").get_to(deck.HyrocarbonStream);
}
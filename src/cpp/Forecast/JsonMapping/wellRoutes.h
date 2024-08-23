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
#include "../ProductionForecast/Inputdeck.h"
Inputdeck inputdeckWellRoute;

using namespace std;
using json = nlohmann::json;


void from_json(const json& j, WellReroute& deck) {
    j.at("module").get_to(deck.Module);
    j.at("rerouteDestination").get_to(deck.Flow_station);
    j.at("dcaStrategy").get_to(deck.dcaStrategy);
    inputdeckWellRoute.ToLower(deck.dcaStrategy);
    j.at("declineType").get_to(deck.declineType);
    inputdeckWellRoute.ToLower(deck.declineType);
    j.at("startupRate").get_to(deck.startupRate);
    j.at("startupRatePlateau").get_to(deck.startupRatePlateau);
    j.at("declineExponent").get_to(deck.declineRate);
    j.at("hyperbolicExponent").get_to(deck.hyperbolicExponent);
    string rerouteDate;
    j.at("rerouteDate").get_to(rerouteDate);
    
    tm tm1;
    sscanf(rerouteDate.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);

    deck.Date_1P_1C.day = tm1.tm_mday;
    deck.Date_1P_1C.month = tm1.tm_mon;
    deck.Date_1P_1C.year = tm1.tm_year;

    deck.Date_2P_2C.day = tm1.tm_mday;
    deck.Date_2P_2C.month = tm1.tm_mon;
    deck.Date_2P_2C.year = tm1.tm_year;

    deck.Date_3P_3C.day = tm1.tm_mday;
    deck.Date_3P_3C.month = tm1.tm_mon;
    deck.Date_3P_3C.year = tm1.tm_year;
}
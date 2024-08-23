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
Inputdeck inputdeckWellShutInOpenUp;

using namespace std;
using json = nlohmann::json;


void from_json(const json& j, ShutInOpenUp& deck) {
    j.at("module").get_to(deck.Module);
    j.at("dcaStrategy").get_to(deck.dcaStrategy);
    inputdeckWellShutInOpenUp.ToLower(deck.dcaStrategy);
    j.at("declineType").get_to(deck.declineType);
    inputdeckWellShutInOpenUp.ToLower(deck.declineType);
    string shutInDate;
    j.at("shutInDate").get_to(shutInDate);
    j.at("event").get_to(deck.event);
    j.at("startupRate").get_to(deck.startupRate);
    j.at("startupRatePlateau").get_to(deck.declineRate);
    j.at("declineExponent").get_to(deck.declineRate);
    j.at("hyperbolicExponent").get_to(deck.hyperbolicExponent);
    
    tm tm1;
    sscanf(shutInDate.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);

		deck.eventDate_1P_1C.day = tm1.tm_mday;
		deck.eventDate_1P_1C.month = tm1.tm_mon;
		deck.eventDate_1P_1C.year = tm1.tm_year;

		deck.eventDate_2P_2C.day = tm1.tm_mday;
		deck.eventDate_2P_2C.month = tm1.tm_mon;
		deck.eventDate_2P_2C.year = tm1.tm_year;

		deck.eventDate_3P_3C.day = tm1.tm_mday;
		deck.eventDate_3P_3C.month = tm1.tm_mon;
		deck.eventDate_3P_3C.year = tm1.tm_year;
}
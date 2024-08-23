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
Inputdeck inputdeckWellRampUp;

using namespace std;
using json = nlohmann::json;


void from_json(const json& j, WellRampUp& deck) {
    j.at("module").get_to(deck.Module);
    j.at("maximumPotential").get_to(deck.maximumPotential);
    j.at("dcaStrategy").get_to(deck.dcaStrategy);
    inputdeckWellRampUp.ToLower(deck.dcaStrategy);
    j.at("declineType").get_to(deck.declineType);
    inputdeckWellRampUp.ToLower(deck.declineType);
    string startDate;
    j.at("startDate").get_to(startDate);
    j.at("percentOfMaximumPotential").get_to(deck.percentOfMaximumPotential);
    j.at("startupRatePlateau").get_to(deck.startupRatePlateau);
    j.at("declineExponent").get_to(deck.declineRate);
    j.at("hyperbolicExponent").get_to(deck.hyperbolicExponent);
    
    tm tm1;
    sscanf(startDate.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);

		deck.rampUpDate_1P_1C.day = tm1.tm_mday;
		deck.rampUpDate_1P_1C.month = tm1.tm_mon;
		deck.rampUpDate_1P_1C.year = tm1.tm_year;

		deck.rampUpDate_2P_2C.day = tm1.tm_mday;
		deck.rampUpDate_2P_2C.month = tm1.tm_mon;
		deck.rampUpDate_2P_2C.year = tm1.tm_year;

		deck.rampUpDate_3P_3C.day = tm1.tm_mday;
		deck.rampUpDate_3P_3C.month = tm1.tm_mon;
		deck.rampUpDate_3P_3C.year = tm1.tm_year;
}
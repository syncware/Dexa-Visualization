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
#include "../ProductionForecast/Decline_Curve_Analysis.h"
#include "../../MathematicsLibrary/Integration.h"
#include "../ProductionForecast/FractionalFlow.h"
#include "../ProductionForecast/DateCreation.h"
#include "../../MathematicsLibrary/MainSimplex.h"
#include "../../MathematicsLibrary/Arithmetic.h"
#include "../../MathematicsLibrary/Interpolation.h"
#include "../ProductionForecast/dataPivoting.h"
#include "../ProductionForecast/Forecast.h"
#include "../../nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

ChartInputPayload chartInputPayload_to_json(const json& j) {
    ChartInputPayload payload;
    //payload.forecastResultsIds = j.at("forecastResultsIds").get<vector<string>>();

    int i = -1;
    for (const auto& item : j.at("forecastResultsIds")) {
        i++;
        string newItem;
        from_json(item, newItem);
        payload.forecastResultsIds.push_back(newItem);
        //std::cout << "forecastResultsIds " << to_string(i) << "\n";
    }

    //payload.selectedModulePaths = j.at("selectedModulePaths").get<vector<string>>();
    i = -1;
    for (const auto& item : j.at("selectedModulePaths")) {
        i++;
        string newItem;
        from_json(item, newItem);
        payload.selectedModulePaths.push_back(newItem);
        //std::cout << "selectedModulePaths " << to_string(i) << "\n";
    }

    //payload.selectedVariables = j.at("selectedVariables").get<vector<string>>();
    i = -1;
    for (const auto& item : j.at("selectedVariables")) {
        i++;
        string newItem;
        from_json(item, newItem);
        payload.selectedVariables.push_back(newItem);
        //std::cout << "selectedVariables " << to_string(i) << "\n";
    }

    payload.shouldAggregate = j.at("shouldAggregate").get<bool>();
    //std::cout << "payload.shouldAggregate " << payload.shouldAggregate << "\n";

    //payload.forecastSolutionSpaces = j.at("forecastSolutionSpaces").get<vector<string>>();
    i = -1;
    for (const auto& item : j.at("forecastSolutionSpaces")) {
        i++;
        string newItem;
        from_json(item, newItem);
        payload.forecastSolutionSpaces.push_back(newItem);
        //std::cout << "forecastSolutionSpaces " << to_string(i) << "\n";
    }
    payload.isMonthly = j.at("isMonthly").get<bool>();

    //std::cout << "payload.isMonthly " << payload.isMonthly << "\n";
    return payload;
}
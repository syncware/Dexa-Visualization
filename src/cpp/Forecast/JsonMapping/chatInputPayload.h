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

ChatInputPayload chatInputPayload_to_json(const json& j) {
    ChatInputPayload payload;
    std::cout << "payload.forecastResultsIds before " << std::endl;
    payload.forecastResultsIds = j.at("forecastResultsIds").get<vector<string>>();
    std::cout << "payload.forecastResultsIds after " << std::endl;
    std::cout << "payload.forecastResultsIds count: " << payload.forecastResultsIds.size() << std::endl;
    payload.selectedModulePaths = j.at("selectedModulePaths").get<vector<string>>();
    std::cout << "payload.selectedModulePaths: " << payload.selectedModulePaths[0] << std::endl;
    payload.selectedVariables = j.at("selectedVariables").get<vector<string>>();
    std::cout << "payload.selectedVariables: " << payload.selectedVariables[0] << std::endl;
    payload.shouldAggregate = j.at("shouldAggregate").get<bool>();
    std::cout << "payload.shouldAggregate: " << payload.shouldAggregate << std::endl;
    payload.forecastSolutionSpaces = j.at("forecastSolutionSpaces").get<vector<string>>();
    std::cout << "payload.forecastSolutionSpaces: " << payload.forecastSolutionSpaces[0] << std::endl;
    return payload;
}
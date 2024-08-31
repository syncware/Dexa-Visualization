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
    payload.forecastResultsIds = j.at("forecastResultsIds").get<vector<string>>();
    payload.selectedModulePaths = j.at("selectedModulePaths").get<vector<string>>();
    payload.selectedVariables = j.at("selectedVariables").get<vector<string>>();
    payload.shouldAggregate = j.at("shouldAggregate").get<bool>();
    payload.forecastSolutionSpaces = j.at("forecastSolutionSpaces").get<vector<string>>();
    payload.isMonthly = j.at("isMonthly").get<bool>();
    return payload;
}
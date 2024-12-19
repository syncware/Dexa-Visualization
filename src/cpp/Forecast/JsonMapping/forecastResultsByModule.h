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

std::vector<ForecastResultsByModule> parseForecastResults(const json &j)
{
    std::vector<ForecastResultsByModule> results;

    for (const auto &item : j)
    {
        ForecastResultsByModule result;

        result.forecastResultsId = item["forecastResultsId"].get<std::string>();
        result.ModuleName = item["ModuleName"].get<std::string>();
        result.FacilityName = item["FacilityName"].get<std::string>();
        result.ScenarioName = item["ScenarioName"].get<std::string>();
        result.ModuleKey = item["ModuleKey"].get<std::string>();
        result.SolutionSpace = item["SolutionSpace"].get<std::string>();
        result.forecastResults = item["forecastResults"].get<std::string>();
        result.forecastInputId = item["forecastInputId"].get<std::string>();

        results.push_back(result);
    }

    return results;
}
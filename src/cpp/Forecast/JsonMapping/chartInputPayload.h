#pragma once

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

ChartInputPayload chartInputPayload_to_json(const json &j)
{
    ChartInputPayload payload;

    int i = -1;
    for (const auto &item : j.at("forecastResultsIds"))
    {
        i++;
        string newItem;
        from_json(item, newItem);
        payload.forecastResultsIds.push_back(newItem);
    }

    i = -1;
    for (const auto &item : j.at("selectedModulePaths"))
    {
        i++;
        string newItem;
        from_json(item, newItem);
        payload.selectedModulePaths.push_back(newItem);
    }

    i = -1;
    for (const auto &item : j.at("selectedVariables"))
    {
        i++;
        string newItem;
        from_json(item, newItem);
        payload.selectedVariables.push_back(newItem);
    }

    payload.shouldAggregate = j.at("shouldAggregate").get<bool>();

    i = -1;
    for (const auto &item : j.at("forecastsolutionSpaces"))
    {
        i++;
        string newItem;
        from_json(item, newItem);
        payload.forecastsolutionSpaces.push_back(newItem);
    }
    payload.isMonthly = j.at("isMonthly").get<bool>();

    return payload;
}
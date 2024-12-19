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
// #include "../ProductionForecast/Inputdeck.h"
// Inputdeck inputdeck2;

using namespace std;
using json = nlohmann::json;

void from_json(const json &j, PrioritizationModel &p)
{
    for (const auto &item : j)
    {
        p.ParameterNames.push_back(item["parameterName"].get<string>());
        p.ParameterWeights.push_back(item["parameterWeight"].get<double>());
    }
}

void from_json(const json &j, Priotization &p)
{
    p.targetFluid = j.at("targetFluid").get<string>();
    p.methodOfPrioritization = j.at("methodOfPrioritization").get<string>();
    p.typeOfPrioritization = j.at("typeOfPrioritization").get<string>();

    if (j.contains("typeOfStream"))
        p.typeOfStream = j.at("typeOfStream").get<string>();

    if (j.contains("parameterNamesWeights"))
    {
        from_json(j.at("parameterNamesWeights"), p.prioritizationModel);
    }
}
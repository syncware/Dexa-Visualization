#pragma once

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
#include "well.h"

using namespace std;
using json = nlohmann::json;

void from_json(const json &j, ChatPayload &payload)
{
    j.at("wells").get_to(payload.wells);
    j.at("isByYear").get_to(payload.isByYear);
    j.at("isForChart").get_to(payload.isForChart);
    j.at("nWells").get_to(payload.nWells);
}
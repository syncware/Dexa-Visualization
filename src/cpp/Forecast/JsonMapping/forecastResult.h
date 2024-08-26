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



void from_json(const json& j, ForecastResult& deck) {
   
    if (j.contains("uniqueId")) j.at("uniqueId").get_to(deck.uniqueId);
    if (j.contains("forecastVersion")) j.at("forecastVersion").get_to(deck.Version_Name);
    if (j.contains("field")) j.at("field").get_to(deck.Field);  
    if (j.contains("reservoir")) j.at("reservoir").get_to(deck.Reservoir);
    if (j.contains("drainagePoint")) j.at("drainagePoint").get_to(deck.Drainage_Point);
    if (j.contains("string")) j.at("string").get_to(deck.Production_String);
    if (j.contains("developmentTranche")) j.at("developmentTranche").get_to(deck.TRANCHE);
    if (j.contains("asset")) j.at("asset").get_to(deck.Asset_Team);
    if (j.contains("facilities")) j.at("facilities").get_to(deck.Flow_station);
    if (j.contains("module")) j.at("module").get_to(deck.ModuleName);
    if (j.contains("day")) j.at("day").get_to(deck.Day);
    if (j.contains("month")) j.at("month").get_to(deck.Month);
    if (j.contains("year")) j.at("year").get_to(deck.Year);
    if (j.contains("oilRate")) j.at("oilRate").get_to(deck.Oil_rate);
    if (j.contains("gasRate")) j.at("gasRate").get_to(deck.Gas_Rate);
    if (j.contains("waterRate")) j.at("waterRate").get_to(deck.Water_Rate);
    if (j.contains("liquidRate")) j.at("liquidRate").get_to(deck.Liquid_Rate);
    if (j.contains("cumOilProd")) j.at("cumOilProd").get_to(deck.Cum_Oil_Prod);
    if (j.contains("cumGasProd")) j.at("cumGasProd").get_to(deck.Cum_Gas_Prod);
    if (j.contains("cumWaterProd")) j.at("cumWaterProd").get_to(deck.Cum_Water_Prod);
    if (j.contains("gOR")) j.at("gOR").get_to(deck.GOR);
    if (j.contains("bSW")) j.at("bSW").get_to(deck.BSW);
    if (j.contains("cGR")) j.at("cGR").get_to(deck.CGR);
    if (j.contains("wGR")) j.at("wGR").get_to(deck.WGR);
    if (j.contains("cutBack")) j.at("cutBack").get_to(deck.CutBack);
    if (j.contains("hydrocarbonStream")) j.at("hydrocarbonStream").get_to(deck.HyrocarbonStream);
    if (j.contains("hydrocarbonType")) j.at("hydrocarbonType").get_to(deck.hydrocarbonType);
    if (j.contains("terminal")) j.at("terminal").get_to(deck.terminal);
    if (j.contains("uRo")) j.at("uRo").get_to(deck.URo);
    if (j.contains("uRg")) j.at("uRg").get_to(deck.URg);
    if (j.contains("ownUseGas")) j.at("ownUseGas").get_to(deck.Gas_Own_Use);
    if (j.contains("gasDemand")) j.at("gasDemand").get_to(deck.Gas_Demand);
    if (j.contains("flareGas")) j.at("flareGas").get_to(deck.Gas_Flared);
    if (j.contains("crudeOilLossess")) j.at("crudeOilLossess").get_to(deck.Crude_Oil_Lossess);
    if (j.contains("cutBackRatio")) j.at("cutBackRatio").get_to(deck.CutBack);
    if (j.contains("projectCode")) j.at("projectCode").get_to(deck.projectCode);
    if (j.contains("projectName")) j.at("projectName").get_to(deck.projectName);
    if (j.contains("days")) j.at("days").get_to(deck.prodDays);
    if (j.contains("optimalSolution")) j.at("optimalSolution").get_to(deck.OptimalSolution);
    if (j.contains("allWellsLiquidCapacity")) j.at("allWellsLiquidCapacity").get_to(deck.AllWellsLiquidCapacity);
    if (j.contains("allWellsGasCapacity")) j.at("allWellsGasCapacity").get_to(deck.AllWellsGasCapacity);
    if (j.contains("resourceClass")) j.at("resourceClass").get_to(deck.resourceClass);
    if (j.contains("condensateRate")) j.at("condensateRate").get_to(deck.Condensate_Rate);
    if (j.contains("reasonForTermination")) j.at("reasonForTermination").get_to(deck.reasonForTermination);
    if (j.contains("declineRate")) j.at("declineRate").get_to(deck.declineRate);
}
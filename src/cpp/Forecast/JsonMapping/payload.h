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
#include "deck.h"
#include "internalExternalEquipments.h"
#include "facilityStructExternal.h"
#include "wellRoutes.h"
#include "wellRampUp.h"
#include "wellShutInOpenUp.h"
#include "forecastResult.h"
#include "runparameters.h"
#include "nodalPriotizations.h"

using namespace std;
using json = nlohmann::json;

void from_json(const json &j, Payload &payload)
{
    j.at("decks").get_to(payload.decks);
    j.at("nDecks").get_to(payload.nDecks);
    j.at("isForecastProfiles").get_to(payload.isForecastProfiles);
    j.at("internalExternalFacilitiesNames").get_to(payload.internalExternalFacilitiesNames);
    j.at("nInternalExternalFacilitiesNames").get_to(payload.nInternalExternalFacilitiesNames);
    j.at("nEquipmentConnections").get_to(payload.nEquipmentConnections);
    for (const auto &connection : j.at("equipmentConnections"))
    {
        map<string, string> nodeMap;
        vector<string> row;
        for (auto it = connection.begin(); it != connection.end(); ++it)
        {
            row.push_back(it.value());
        }
        payload.equipmentConnections.push_back(row);
    }

    j.at("nDeferments").get_to(payload.nDeferments);
    j.at("nCrudeOilLosses").get_to(payload.nCrudeOilLosses);
    j.at("nEquipmentCapacities").get_to(payload.nEquipmentCapacities);
    j.at("numberOfNodes").get_to(payload.numberOfNodes);
    j.at("nGasOwnUse").get_to(payload.nGasOwnUse);
    j.at("nFlaredGases").get_to(payload.nFlaredGases);
    j.at("forecastSolutionSpaces").get_to(payload.forecastSolutionSpaces);
    j.at("nForecastSolutionSpaces").get_to(payload.nForecastSolutionSpaces);
    j.at("forecastSolutionSpacesIsDURConstrained").get_to(payload.forecastSolutionSpacesIsDURConstrained);
    j.at("nForecastSolutionSpacesIsDURConstrained").get_to(payload.nForecastSolutionSpacesIsDURConstrained);

    for (const auto &item : j.at("deferments"))
    {
        FacilityStructExternal fse;
        from_json(item, fse);
        payload.deferments.push_back(fse);
    }
    for (const auto &item : j.at("crudeOilLosses"))
    {
        FacilityStructExternal fse;
        from_json(item, fse);
        payload.crudeOilLosses.push_back(fse);
    }
    for (const auto &item : j.at("equipmentCapacities"))
    {
        FacilityStructExternal fse;
        from_json(item, fse);
        payload.equipmentCapacities.push_back(fse);
    }
    for (const auto &item : j.at("gasOwnUse"))
    {
        FacilityStructExternal fse;
        from_json(item, fse);
        payload.gasOwnUse.push_back(fse);
    }
    for (const auto &item : j.at("flaredGases"))
    {
        FacilityStructExternal fse;
        from_json(item, fse);
        payload.flaredGases.push_back(fse);
    }
    j.at("wellRerouteDecks").get_to(payload.wellRerouteDecks);
    j.at("nWellRerouteDecks").get_to(payload.nWellRerouteDecks);
    j.at("wellRampUpDecks").get_to(payload.wellRampUpDecks);
    j.at("nWellRampUpDecks").get_to(payload.nWellRampUpDecks);
    j.at("wellShutInOpenUpDecks").get_to(payload.wellShutInOpenUpDecks);
    j.at("nWellShutInOpenUpDecks").get_to(payload.nWellShutInOpenUpDecks);
    j.at("forecastProfiles").get_to(payload.forecastProfiles);
    j.at("nForecastProfiles").get_to(payload.nForecastProfiles);
    j.at("runparameters").get_to(payload.runparameters);
    j.at("nProductionPrioritization").get_to(payload.nProductionPrioritization);
    j.at("productionPrioritization").get_to(payload.productionPrioritization);
    j.at("nNodalPriotizations").get_to(payload.nNodalPriotizations);
    payload.prioritization = j.at("prioritization").get<Priotization>();
    payload.nodalPriotizations = j.at("nodalPriotizations").get<vector<Priotization>>();
}
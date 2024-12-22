#pragma once

#include <thread>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include <tuple>
#include "../../nlohmann/json.hpp"
#include "../../MathematicsLibrary/MainSimplex.h"
#include "../../MathematicsLibrary/Integration.h"
#include "../ProductionForecast/Inputdeck.h"
#include "../ProductionForecast/Forecast.h"
#include "../ProductionForecast/DateCreation.h"
#include "../ProductionForecast/CalculateDeckVariables.h"
#include "../ProductionForecast/dataPivoting.h"
#include "../../MathematicsLibrary/Interception.h"
#include "../ProductionForecast/ExternalForecast.h"
#include "ConfigurePrioritization.h"
#include "ToJSON2.h"
#include "../JsonMapping/napiToJson.h"
#include "../JsonMapping/person.h"
#include "../JsonMapping/responseData.h"
// #include "../JsonMapping/payload.h"

using namespace std;
using namespace std::placeholders;
using json = nlohmann::json;

class RunForecastAsyncWorkerModifiedTest
{
private:
    Inputdeck deckobj;
    ExternalForecast externalForecast;
    ConfigurePrioritization configurePrioritization;
    ReportJSON2 reportJSON2;

public:
    RunForecastAsyncWorkerModifiedTest();
    ~RunForecastAsyncWorkerModifiedTest();
    json RunForecast(const json &jsonData);
};

RunForecastAsyncWorkerModifiedTest::RunForecastAsyncWorkerModifiedTest()
{
}

RunForecastAsyncWorkerModifiedTest::~RunForecastAsyncWorkerModifiedTest()
{
}

json RunForecastAsyncWorkerModifiedTest::RunForecast(const json &jsonData)
{
    // Fill deckobj input deck with the payload's input deck on a row by row basis
    ResponseData responseData;
    map<string, map<string, map<string, map<string, map<string, map<string, string>>>>>> monthlyReport;
    Payload payload = ConvertJsonToPayload(jsonData);
    int nDecks = payload.decks.size();
    for (int i = 0; i < nDecks; i++)
    {
        if (payload.decks[i].Description == "no error")
        {
            InputDeckStruct newDeck;
            deckobj.inputdecks.push_back(payload.decks[i]);
        }
    }

    // Fill deckobj input deck's prioritization weights with the payload's
    // prioritization weights on a row by row basis
    vector<InputDeckStruct> productionPrioritization = payload.productionPrioritization;
    if (productionPrioritization.size() > 0)
    {
        for (int i = 0; i < nDecks; i++)
        {
            deckobj.inputdecks[i].optimizationWeight2 = productionPrioritization[i].optimizationWeight2;
        }
    }

    vector<InternalExternalEquipmentName> internalExternalFacilitiesNames =
        payload.internalExternalFacilitiesNames;

    vector<vector<string>> equipmentConnections = payload.equipmentConnections;

    vector<FacilityStructExternal> deferments = payload.deferments;

    vector<FacilityStructExternal> crudeOilLosses = payload.crudeOilLosses;

    vector<FacilityStructExternal> equipmentCapacities = payload.equipmentCapacities;

    vector<FacilityStructExternal> gasOwnUse = payload.gasOwnUse;

    vector<FacilityStructExternal> gasFlared = payload.flaredGases;

    Prioritization prioritization = payload.prioritization;

    vector<Prioritization> nodalPrioritizations = payload.nodalPrioritizations;

    deckobj.inputdecks = payload.decks;

    deckobj.wellRerouteDecks = payload.wellRerouteDecks;

    deckobj.wellRampUpDecks = payload.wellRampUpDecks;

    deckobj.wellShutInOpenUpDecks = payload.wellShutInOpenUpDecks;

    vector<ForecastResult> forecastProfiles = payload.forecastProfiles;

    reportJSON2.runParameter = payload.runparameters;
    deckobj.runParameter = reportJSON2.runParameter;

    string isForecastProfiles = payload.isForecastProfiles;

    vector<string> forecastSolutionSpaces = payload.forecastSolutionSpaces;
    int nForecastSolutionSpaces = payload.nForecastSolutionSpaces;

    vector<bool> forecastSolutionSpacesIsDURConstrained = payload.forecastSolutionSpacesIsDURConstrained;
    int nForecastSolutionSpacesIsDURConstrained = payload.nForecastSolutionSpacesIsDURConstrained;

    DateCreation dateCreation;

    Date StopDate;

    bool isMonthly = deckobj.runParameter.isMonthly;
    StopDate.year = deckobj.runParameter.StopYear;
    StopDate.month = deckobj.runParameter.StopMonth;
    StopDate.day = deckobj.runParameter.StopDay;
    reportJSON2.isMonthly = isMonthly;

    vector<Node> nodes =
        reportJSON2.GetNodes(internalExternalFacilitiesNames, equipmentConnections);

    tuple<vector<Node>, vector<Date>> tupleResults = reportJSON2.GetNodesSheetData(nodes, equipmentCapacities,
                                                                                   deferments, crudeOilLosses, gasOwnUse, gasFlared);

    vector<Node> updatesNodes = get<0>(tupleResults);
    vector<Date> equipmentsScheduleDates = get<1>(tupleResults);
    std::cout << "GetNodesSheetData completed\n";

    nodes.clear();
    nodes.shrink_to_fit();

    vector<FacilityStructExternal> FacilityTable = updatesNodes[0].equipmentDataInEquipementConnections;
    updatesNodes[0].equipmentDataInEquipementConnections;

    reportJSON2.FacilityTable = FacilityTable;
    const int nFacilityTable = reportJSON2.FacilityTable.size();
    for (int j = 0; j < nFacilityTable; j++)
    {
        deckobj.FacilityTable.push_back(FacilityTable[j]);
    }

    int ndecks = deckobj.inputdecks.size();

    dateCreation.GetDateList(deckobj.inputdecks, StopDate, equipmentsScheduleDates, isMonthly);

    dateCreation.GetDaysList(dateCreation.dateTimes[0]);

    int scenario = 1;
    CalculateDeckVariables calculateDeckVariables;

    int nth = dateCreation.dateTimes.size();
    deckobj.isRateCum = true;
    deckobj.cumProdDays = dateCreation.daysList[nth - 1];
    deckobj.stopDate = dateCreation.dateTimes[nth - 1];

    Date startDate;
    startDate.year = 2024;
    startDate.month = 1;
    startDate.day = 1;
    deckobj.startDate = startDate;

    deckobj.InitilizeModules();

    int i = 0;
    map<string, map<string, map<string, map<string, map<string, string>>>>> forecastSolutionSpacesResults;
    if (nth > 0)
    {
        vector<WellActivityResult> wellActivities;
        bool isForecastProfilesAndDecksMatched = true;
        if (isForecastProfiles == "external")
        {
            vector<vector<ForecastResult>> forecastProfilesList =
                externalForecast.GetUniqueForecastProfiles(forecastProfiles, deckobj.inputdecks);
            vector<string> uniqueModuleNames =
                externalForecast.GetUniqueModuleNames(forecastProfilesList);
            wellActivities =
                externalForecast.GetWellActivities(forecastProfilesList, deckobj.inputdecks,
                                                   uniqueModuleNames);

            isForecastProfilesAndDecksMatched =
                externalForecast.MatchForecastProfilesAndDecks(uniqueModuleNames,
                                                               deckobj.inputdecks);
        }

        int fSSIndex = 0;
        int nForecastSolutionSpaces = forecastSolutionSpaces.size();
        int scenarios = 3;
        vector<WellSchedule> wellSchedules = reportJSON2.GetWellSchedulesSheetData(deckobj.wellRerouteDecks,
                                                                                   deckobj.wellRampUpDecks, deckobj.wellShutInOpenUpDecks, StopDate);

        int nUpdatesNodes = updatesNodes.size();
        for (i = 0; i < nUpdatesNodes; i++)
        {
            if (i > 0)
            {
                prioritization.typeOfPrioritization = "streamPrioritization";
            }
            updatesNodes[i].prioritizations =
                configurePrioritization.SetUpPrioritization(updatesNodes[i].equipmentDataInEquipementConnections,
                                                            dateCreation.dateTimes[0], StopDate, prioritization, nodalPrioritizations);
        }

        vector<Prioritization> prioritizations = updatesNodes[0].prioritizations;

        for (fSSIndex = 0; fSSIndex < nForecastSolutionSpaces; fSSIndex++)
        {
            calculateDeckVariables.dURConstrained = forecastSolutionSpacesIsDURConstrained[fSSIndex];
            map<string, map<string, map<string, map<string, string>>>> scenariosResult;
            for (i = 2; i < scenarios; i++)
            {
                scenario = i;
                vector<string> Facilities = deckobj.GetFacilities(deckobj.inputdecks, ndecks, dateCreation.dateTimes, scenario);

                vector<vector<vector<InputDeckStruct>>> FacilitiesObj =
                    deckobj.GetModulesByFacility(Facilities, deckobj.inputdecks, ndecks,
                                                 deckobj.wellRerouteDecks, dateCreation.dateTimes, scenario,
                                                 wellSchedules, prioritizations);

                vector<vector<Prioritization>> prioritizationsFacilities = deckobj.prioritizationsFacilities;

                calculateDeckVariables.UseExternalForecastprofile = isForecastProfiles;
                if (calculateDeckVariables.UseExternalForecastprofile == "external")
                {
                    calculateDeckVariables.WellActivities = wellActivities;
                }

                calculateDeckVariables.dates = dateCreation.dateTimes;
                calculateDeckVariables.FacilityTables_Actual = deckobj.FacilityTables_Actual;
                calculateDeckVariables.isDeferred = false;

                deckobj.runParameter.forecastCase = forecastSolutionSpaces[fSSIndex];

                if (deckobj.runParameter.forecastCase == potential)
                {
                    calculateDeckVariables.isFacilityDeferred = false;
                    calculateDeckVariables.isDeferred = false;
                }

                if (deckobj.runParameter.forecastCase == delivered)
                {
                    calculateDeckVariables.isFacilityDeferred = false;
                    calculateDeckVariables.isDeferred = false;
                }

                if (deckobj.runParameter.forecastCase == availability)
                {
                    calculateDeckVariables.isFacilityDeferred = true;
                    calculateDeckVariables.isDeferred = true;
                }

                if (deckobj.runParameter.forecastCase == offtake)
                {
                    calculateDeckVariables.isFacilityDeferred = true;
                    calculateDeckVariables.isDeferred = true;
                }

                calculateDeckVariables.startFrom = nth * (i - 1);
                calculateDeckVariables.isRateCum = deckobj.isRateCum;
                calculateDeckVariables.GetDeckVariables(FacilitiesObj, dateCreation.daysList, scenario,
                                                        deckobj.FacilityTable_Actual, Facilities, dateCreation, deckobj.wellRerouteDecks,
                                                        deckobj.runParameter.forecastCase, prioritizationsFacilities, updatesNodes, isMonthly);

                reportJSON2.results = calculateDeckVariables.results;

                vector<vector<FacilityWellsIndicies>> facilityWellsIndicies = deckobj.facilityWellsIndicies;
                map<string, map<string, map<string, string>>> FacilitiesObject = reportJSON2.GetForecastOutputAllFacilities(scenario, facilityWellsIndicies,
                                                                                                                           dateCreation.dateTimes);

                string scenarioName = to_string(scenario) + "P_" + to_string(scenario) + "C";
                scenariosResult[scenarioName] = FacilitiesObject;
            }
            forecastSolutionSpacesResults[forecastSolutionSpaces[fSSIndex]] = scenariosResult;
        }
    }

    responseData.monthlyReport = forecastSolutionSpacesResults;

    json jsonResponseData = to_json(responseData);

    return jsonResponseData;
}

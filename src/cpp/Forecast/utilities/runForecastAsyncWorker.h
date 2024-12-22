#pragma once

#include <napi.h>
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
#include "../../MathematicsLibrary/MainSimplex.h"
#include "../../MathematicsLibrary/Integration.h"
#include "../ProductionForecast/Inputdeck.h"
#include "../ProductionForecast/Forecast.h"
#include "../ProductionForecast/DateCreation.h"
#include "../ProductionForecast/CalculateDeckVariables.h"
#include "../ProductionForecast/dataPivoting.h"
#include "ToJSON.h"
#include "../../MathematicsLibrary/Interception.h"
#include "../ProductionForecast/ExternalForecast.h"
#include "ConfigurePrioritization.h"
#include "ToJSON2.h"
#include "../JsonMapping/napiToJson.h"
#include "../JsonMapping/person.h"
#include "../JsonMapping/responseData.h"

using namespace std;
using namespace std::placeholders;
// const char* RESULT_KEY = "wrappedInstance";

class RunForecastAsyncWorker : public Napi::AsyncWorker
{
    ReportJSON reportJSON;
    Inputdeck deckobj;
    ExternalForecast externalForecast;
    ConfigurePrioritization configurePrioritization;
    ReportJSON2 reportJSON2;

    // Napi::Array wellDeckList;

public:
    RunForecastAsyncWorker(Napi::Object &wrappedInstance, Napi::Function callback)
        : AsyncWorker(callback)
    {

        Receiver().Set("wrappedInstance", wrappedInstance);
    }

protected:
    void Execute() override
    {
    }

private:
    void OnOK() override
    {
        string msg = "runForecastAsync returning after 'working' ";
        Napi::Env env = Env();
        Napi::HandleScope scope(env);
        Napi::Value value = Receiver().Get("wrappedInstance");
        Napi::Object wrappedInstance = value.As<Napi::Object>();
        // Convert wrappedInstance to JSON
        json jsonData = reportJSON.NapiObjectToJson(wrappedInstance);

        std::cout << msg << "\n";
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

        DateCreation dateCreation;

        Date StopDate;

        StopDate.year = deckobj.runParameter.StopYear;
        StopDate.month = deckobj.runParameter.StopMonth;
        StopDate.day = deckobj.runParameter.StopDay;
        bool isMonthly = deckobj.runParameter.isMonthly;
        reportJSON2.isMonthly = isMonthly;

        deckobj.inputdecks = payload.decks;
        deckobj.InitilizeModules();

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

        int idx = 0;

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

        // reportJSON.GetFacilityList(FacilityTable);
        reportJSON2.FacilityTable = FacilityTable;
        const int nFacilityTable = reportJSON2.FacilityTable.size();
        for (int j = 0; j < nFacilityTable; j++)
        {
            deckobj.FacilityTable.push_back(FacilityTable[j]);
        }

        int ndecks = deckobj.inputdecks.size();

        std::cout << "Get_InputDeckStructList done completely" << std::endl;

        dateCreation.GetDateList(deckobj.inputdecks, StopDate, equipmentsScheduleDates, isMonthly);
        std::cout << "GetDateList done completely\n";

        dateCreation.GetDaysList(dateCreation.dateTimes[0]);
        std::cout << "GetDaysList done completely\n";

        int scenario = 1;
        CalculateDeckVariables calculateDeckVariables;

        int nth = dateCreation.dateTimes.size();

        int i = 0;
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
            int scenarios = 4;
            Napi::Object inputObjectAll = Napi::Object::New(env);
            Napi::Object inputObjectFSS = Napi::Object::New(env);
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
                Napi::Object inputObject = Napi::Object::New(env);
                Napi::Object inputObjectYearly = Napi::Object::New(env);
                calculateDeckVariables.dURConstrained = forecastSolutionSpacesIsDURConstrained[fSSIndex];

                for (i = 1; i < scenarios; i++)
                {
                    scenario = i;
                    vector<string> Facilities = deckobj.GetFacilities(deckobj.inputdecks, ndecks, dateCreation.dateTimes, scenario);
                    std::cout << "GetFacilities completed\n";

                    vector<vector<vector<InputDeckStruct>>> FacilitiesObj =
                        deckobj.GetModulesByFacility(Facilities, deckobj.inputdecks, ndecks,
                                                     deckobj.wellRerouteDecks, dateCreation.dateTimes, scenario,
                                                     wellSchedules, prioritizations);
                    std::cout << "GetModulesByFacility completed\n";

                    vector<vector<Prioritization>> prioritizationsFacilities = deckobj.prioritizationsFacilities;

                    CalculateDeckVariables calculateDeckVariables;
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

                    calculateDeckVariables.GetDeckVariables(FacilitiesObj, dateCreation.daysList, scenario,
                                                            deckobj.FacilityTable_Actual, Facilities, dateCreation, deckobj.wellRerouteDecks,
                                                            deckobj.runParameter.forecastCase, prioritizationsFacilities, updatesNodes, isMonthly);

                    std::cout << "GetDeckVariables completed\n";
                    reportJSON.results = calculateDeckVariables.results;

                    vector<vector<FacilityWellsIndicies>> &facilityWellsIndicies = deckobj.facilityWellsIndicies;
                    reportJSON.GetForecastOutputAllFacilities(scenario, facilityWellsIndicies,
                                                              dateCreation.dateTimes, env);

                    std::cout << "GetForecastOutput completed\n";

                    string scenarioName = to_string(scenario) + "P_" + to_string(scenario) + "C";
                    inputObject.Set(Napi::String::New(env, scenarioName), reportJSON.FacilitiesObject);

                    std::cout << "Scenario created for " << scenarioName << forecastSolutionSpaces[fSSIndex] << '\n';
                    //
                }
                inputObjectFSS.Set(Napi::String::New(env, forecastSolutionSpaces[fSSIndex]), inputObject);
            }
            inputObjectAll.Set(Napi::String::New(env, "monthlyReport"), inputObjectFSS);
            std::cout << "monthlyReport created\n";
            inputObjectAll.Set(Napi::String::New(env, "inputObjectAll"),
                               Napi::Boolean::New(env, isForecastProfilesAndDecksMatched));

            Callback().MakeCallback(Receiver().Value(), std::initializer_list<napi_value>{
                                                            env.Null(), inputObjectAll});
        }
    }
};
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
#include <algorithm> // For std::find
#include <sstream>   // For std::stringstream
#include <unordered_map>
#include <map>
#include <numeric>
#include <iterator>
#include <ctime>
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
#include "../JsonMapping/responseChartData.h"
#include "../JsonMapping/forecastResultsByModule.h"
#include "../JsonMapping/chartInputPayload.h"
#include "../../nlohmann/json.hpp"

using namespace std;
using namespace std::placeholders;
using json = nlohmann::json;

class AllWellsYearlyResultNewAsyncT
{
private:
    Inputdeck deckobj;
    ExternalForecast externalForecast;
    ConfigurePrioritization configurePrioritization;
    ReportJSON2 reportJSON2;
    string delimeter = "@#$%";
    string columnDelimeter = "@#$%";
    string rowDelimeter = "@#*$%";

public:
    AllWellsYearlyResultNewAsyncT();
    ~AllWellsYearlyResultNewAsyncT();

    vector<string> split(const string &str, const string &delimiter);
    vector<string> getscenarioNames(const vector<string> &selectedModulePaths);
    vector<string> getfacilityNames(const vector<string> &selectedModulePaths);
    vector<string> split(const string &str);
    vector<ForecastResult> getForecastResult(const string &table);

    unordered_map<string, unordered_map<string, ModuleResultMonthly>>
    getForecastResultsByScenario(
        const vector<ForecastResultsByModule> &forecastModulesCompleteObject,
        const string &scenarioName,
        const string &solutionSpace,
        const vector<string> &facilityNames);

    vector<ModuleResultMonthly> getModulesForecastResultsByScenario(
        const vector<ForecastResultsByModule> &forecastModulesCompleteObject,
        const string &scenarioName,
        const string &solutionSpace,
        const vector<string> &facilityNames);

    map<string, map<string, map<string, vector<YObj>>>> chartDataByModulesOrAggregate(
        const vector<string> &selectedModulePaths,
        const vector<string> &selectedVariables,
        bool isMonthly,
        const vector<string> &forecastSolutionSpaceNames,
        const vector<ForecastResultsByModule> &forecastResultsByModule,
        const string &forecastResultsId,
        bool shouldAggregate);

    map<string, map<string, ModuleResultMonthly>> convertToOrdered(
        const unordered_map<string, unordered_map<string, ModuleResultMonthly>> &unorderedMap);

    vector<map<string, string>> getYearlyForcastResultModulesNewAsync(
        vector<ModuleResultMonthly> wells,
        bool &isByYear,
        bool &isForChart,
        int &nWells);

    map<string, map<string, map<string, YObj>>> chartDataByModulesOrAggregate2(
        const string &forecastResultsId,
        map<string, map<string, map<string, vector<YObj>>>> _scenarioObjects);

    map<string, vector<ModuleResultMonthly>>
    getModulesForecastResultsByFacility(
        const vector<ForecastResultsByModule> &forecastModulesCompleteObject,
        const string &scenarioName,
        const string &solutionSpace,
        const vector<string> &facilityNames);

    map<string, map<string, map<string, map<string, map<string, std::vector<any>>>>>>
    chartDataByModulesOrAggregateNew(
        const vector<string> &selectedModulePaths,
        const vector<string> &selectedVariables,
        bool isMonthly,
        const vector<string> &forecastSolutionSpaceNames,
        const vector<ForecastResultsByModule> &forecastResultsByModule,
        const vector<string> &forecastResultsIds,
        bool shouldAggregate);

    vector<ForecastResult> getResultsTableForForecastModule(
        const string &forecastModuleResultsString,
        string columnDelimeter,
        string rowDelimeter);
};

AllWellsYearlyResultNewAsyncT::AllWellsYearlyResultNewAsyncT()
{
}

AllWellsYearlyResultNewAsyncT::~AllWellsYearlyResultNewAsyncT()
{
}

/**
 * Helper functions
 */
vector<string> AllWellsYearlyResultNewAsyncT::split(const string &str)
{
    vector<string> tokens;
    size_t start = 0;
    size_t end = str.find(delimeter);

    while (end != std::string::npos)
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimeter.length();
        end = str.find(delimeter, start);
    }

    tokens.push_back(str.substr(start, end));
    return tokens;
}

vector<string> AllWellsYearlyResultNewAsyncT::split(const string &str, const string &delimiter)
{
    vector<string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos)
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }

    tokens.push_back(str.substr(start, end));
    return tokens;
}

json to_json(const YObj &obj)
{
    return json{
        {"forecastResultId", obj.forecastResultId},
        {"id", obj.id},
        {"name", obj.name},
        {"title", obj.title},
        {"path", obj.path},
        {"y", obj.y},
        {"x", obj.x}};
}

// Parse a single forecast module into an object
vector<ForecastResult> AllWellsYearlyResultNewAsyncT::getResultsTableForForecastModule(
    const string &forecastModuleResultsString,
    string columnDelimeter,
    string rowDelimeter)
{
    vector<ForecastResult> actualTable;
    vector<std::string> rows = split(forecastModuleResultsString, rowDelimeter);

    int idx = -1;
    int nrow = rows.size() - 1;

    for (idx = 0; idx < nrow; idx++)
    {
        string row = rows[idx];
        ForecastResult result;
        vector<string> columns = split(row, columnDelimeter);
        int colIndx = -1; // size_t
        try
        {
            colIndx = colIndx + 1;
            result.uniqueId = columns[colIndx];

            colIndx = colIndx + 1;
            result.Version_Name = columns[colIndx];

            colIndx = colIndx + 1;
            result.Field = columns[colIndx];

            colIndx = colIndx + 1;
            result.Reservoir = columns[colIndx];

            colIndx = colIndx + 1;
            result.Drainage_Point = columns[colIndx];

            colIndx = colIndx + 1;
            result.Production_String = columns[colIndx];

            colIndx = colIndx + 1;
            result.TRANCHE = columns[colIndx];

            colIndx = colIndx + 1;
            result.Asset_Team = columns[colIndx];

            colIndx = colIndx + 1;
            result.Flow_station = columns[colIndx];

            colIndx = colIndx + 1;
            result.moduleName = columns[colIndx];

            colIndx = colIndx + 1;
            result.Day = stoi(columns[colIndx]);

            colIndx = colIndx + 1;
            result.Month = stoi(columns[colIndx]);

            colIndx = colIndx + 1;
            result.Year = stoi(columns[colIndx]);

            colIndx = colIndx + 1;
            result.Oil_rate = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.Gas_Rate = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.Water_Rate = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.Liquid_Rate = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.Cum_Oil_Prod = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.Cum_Gas_Prod = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.Cum_Water_Prod = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.GOR = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.BSW = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.CGR = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.WGR = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.CutBack = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.HyrocarbonStream = columns[colIndx];

            colIndx = colIndx + 1;
            result.hydrocarbonType = columns[colIndx];

            colIndx = colIndx + 1;
            result.terminal = columns[colIndx];

            colIndx = colIndx + 1;
            result.URo = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.URg = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.Gas_Own_Use = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.Gas_Demand = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.Gas_Flared = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.Crude_Oil_Lossess = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.CutBack = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.projectCode = columns[colIndx];

            colIndx = colIndx + 1;
            result.projectName = columns[colIndx];

            colIndx = colIndx + 1;
            result.prodDays = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.OptimalSolution = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.AllWellsLiquidCapacity = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.AllWellsGasCapacity = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.resourceClass = columns[colIndx];

            colIndx = colIndx + 1;
            result.Condensate_Rate = stod(columns[colIndx]);

            colIndx = colIndx + 1;
            result.reasonForTermination = columns[colIndx];

            colIndx = colIndx + 1;
            result.declineRate = stod(columns[colIndx]);
        }
        catch (const std::exception &e)
        {
            std::cout << "error occured" << std::endl;
        }

        actualTable.push_back(result);
    }

    // Remove the last element if needed
    if (!actualTable.empty())
    {
        actualTable.pop_back();
    }

    std::cout << "getForecastResult completed" << std::endl;
    return actualTable;
}

/**
 * Main Functions
 */
/** NEWWWWWWWW */
map<string, map<string, map<string, map<string, map<string, std::vector<any>>>>>>
AllWellsYearlyResultNewAsyncT::chartDataByModulesOrAggregateNew(
    const vector<string> &selectedModulePaths,
    const vector<string> &selectedVariables,
    bool isMonthly,
    const vector<string> &forecastSolutionSpaceNames,
    const vector<ForecastResultsByModule> &forecastResultsByModule,
    const vector<string> &forecastResultsIds,
    bool shouldAggregate)
{
    // loop through selectedModulePaths: for every item
    // get modulePath
    // reconstruct modulePath as moduleKey
    // use this reconstructed modulePath in loop
    //   loop through forecastResultsByModule:
    //      when reconstructed modulePath === moduleKey
    //      get forecastResults string
    //      split forecastResults string
    //      grab the variable to be plotted
    //      place in object
    //      break

    // potential/2P_2C/ABU_FS1/FOO4E70T_FOO4 E70X_P12

    /**
     * chartDataMap = {
     *    forecastResultsId1: {
     *       1P_1C: {
     *            potential: {
     *                oilRate: {
     *                    x: [],
     *                    y: [],
     *                }
     *            }
     *        }
     *    }
     * }
     */
    map<string, map<string, map<string, map<string, map<string, std::vector<any>>>>>> chartDataResultMap;
    string selectedVariable = selectedVariables[0];

    // Get Chart Data Map
    for (const auto &forecastResultsId : forecastResultsIds)
    {
        for (const auto &forecastsolutionSpace : forecastSolutionSpaceNames)
        {
            for (const auto &modulePath : selectedModulePaths)
            {
                vector<std::string> modulePathParts = split(modulePath, rowDelimeter);
                string forecastCase = modulePathParts[0];
                string facilityName = modulePathParts[1];
                string moduleName = modulePathParts[2];
                string reconstructedModulePath = forecastsolutionSpace + "/" + forecastCase + "/" + facilityName + "/" + moduleName;

                for (const auto &resultsModule : forecastResultsByModule)
                {
                    if (resultsModule.forecastResultsId == forecastResultsId && resultsModule.moduleKey == reconstructedModulePath)
                    {
                        string forecastResultsForModule = resultsModule.forecastResults;
                        vector<ForecastResult> forecastResultsTableForModule = getResultsTableForForecastModule(modulePath, columnDelimeter, rowDelimeter);

                        // X Series
                        std::vector<std::string> dateData;
                        for (const auto &resultRow : forecastResultsTableForModule)
                        {
                            int day = resultRow.Day;
                            int month = resultRow.Month;
                            int year = resultRow.Year;

                            string date = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
                            dateData.push_back(date);
                        }

                        // Y series
                        std::vector<any> fieldData;
                        for (const auto &resultRow : forecastResultsTableForModule)
                        {
                            fieldData.push_back(resultRow.getVariableByName(selectedVariable));
                        }

                        // Construct map
                        chartDataResultMap[forecastResultsId][forecastCase][forecastsolutionSpace][selectedVariable]["x"].push_back(dateData);
                        chartDataResultMap[forecastResultsId][forecastCase][forecastsolutionSpace][selectedVariable]["y"].push_back(fieldData);

                        break;
                    }
                }
            }
        }
    }

    std::cout << "chartDataResultMap Completed " << std::endl;

    return chartDataResultMap;
}

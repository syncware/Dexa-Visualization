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
#include "../JsonMapping/responseChartData.h"
#include "../JsonMapping/forecastResultsByModule.h"
#include "../JsonMapping/chartInputPayload.h"
// #include "../JsonMapping/payload.h"

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

public:
    AllWellsYearlyResultNewAsyncT();
    ~AllWellsYearlyResultNewAsyncT();
    json Plot(const json &jsonData);
    json Plot2(const json &jsonData);
    json PlotChart(const json &forecastResultsJsonData, const json &chartInputJsonData);
    vector<string> split(const string &str, const string &delimiter);
    vector<string> GetscenarioNames(const vector<string> &selectedModulePaths);
    vector<string> GetfacilityNames(const vector<string> &selectedModulePaths);
    vector<string> split(const string &str);
    vector<ForecastResult> getForecastResult(const string &table);
    unordered_map<string, unordered_map<string, ModuleResultMonthly>>
    GetForecastResultsByScenario(
        const vector<ForecastResultsByModule> &forecastModulesCompleteObject,
        const string &scenarioName,
        const string &solutionSpace,
        const vector<string> &facilityNames);
    vector<ModuleResultMonthly> GetModulesForecastResultsByScenario(
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
    map<string, map<string, map<string, vector<YObj>>>> chartDataByModulesOrAggregate_Obsolete(
        const vector<string> &selectedModulePaths,
        const vector<string> &selectedVariables,
        bool isMonthly,
        const vector<string> &forecastSolutionSpaceNames,
        const vector<ForecastResultsByModule> &forecastResultsByModule,
        const string &forecastResultsId,
        bool shouldAggregate);
    // double sum(const vector<double>& numbers);
    // vector<vector<double>> zip(const vector<vector<double>>& arrays);
    // vector<double> aggregateY(const vector<YObj>& yObjs);
    map<string, map<string, ModuleResultMonthly>> convertToOrdered(
        const unordered_map<string, unordered_map<string, ModuleResultMonthly>> &unorderedMap);
    vector<map<string, string>> GetYearlyForcastResultModulesNewAsync(
        vector<ModuleResultMonthly> wells,
        bool &isByYear,
        bool &isForChart,
        int &nWells);
    // string join(const vector<double>& yAgg, const string& delimiter);
    // string joinStrings(const vector<string>& yAgg, const string& delimiter);
    map<string, map<string, map<string, YObj>>> chartDataByModulesOrAggregate2(
        const string &forecastResultsId,
        map<string, map<string, map<string, vector<YObj>>>> _scenarioObjects);
    map<string, vector<ModuleResultMonthly>>
    GetModulesForecastResultsByFacility(
        const vector<ForecastResultsByModule> &forecastModulesCompleteObject,
        const string &scenarioName,
        const string &solutionSpace,
        const vector<string> &facilityNames);
};

AllWellsYearlyResultNewAsyncT::AllWellsYearlyResultNewAsyncT()
{
}

AllWellsYearlyResultNewAsyncT::~AllWellsYearlyResultNewAsyncT()
{
}

/* void AllWellsYearlyResultNewAsyncT::set(map<string, map<string, YObj>>& obj, const string& path, const YObj& value) {
    vector<string> keys = split(path, ".");

    map<string, map<string, YObj>>* currentMap = &obj;
    for (size_t i = 0; i < keys.size(); ++i) {
        const string& key = keys[i];
        if (i == keys.size() - 1) {
            (*currentMap)[key] = value;
        } else {
            currentMap = &((*currentMap)[key]);
        }
    }
} */

// string AllWellsYearlyResultNewAsyncT::join(const vector<double>& yAgg, const string& delimiter) {
//     ostringstream oss;
//     if (!yAgg.empty()) {
//         copy(yAgg.begin(), yAgg.end() - 1, ostream_iterator<int>(oss, delimiter.c_str()));
//         oss << yAgg.back();  // Add the last element without delimiter
//     }
//     return oss.str();
// }

// string AllWellsYearlyResultNewAsyncT::joinStrings(const vector<string>& yAgg, const string& delimiter) {
//     ostringstream oss;
//     if (!yAgg.empty()) {
//         copy(yAgg.begin(), yAgg.end() - 1, ostream_iterator<int>(oss, delimiter.c_str()));
//         oss << yAgg.back();  // Add the last element without delimiter
//     }
//     return oss.str();
// }

json AllWellsYearlyResultNewAsyncT::Plot2(const json &jsonData)
{
    std::vector<ForecastResultsByModule> forecastResults = parseForecastResults(jsonData);
    return jsonData;
}

// json AllWellsYearlyResultNewAsyncT::AggregateData(const json& jsonData){
//     ChatPayload chatPayload = ConvertJsonToChatPayload(jsonData);
//     vector<vector<ForecastResult>> WellsForecastResults;
//     for(int i = 0; i < chatPayload.wells.size(); i++){
//         WellsForecastResults.push_back( chatPayload.wells[i].resultWells);
//     }

//     bool isByYear = chatPayload.isByYear;
//     bool isForChart = chatPayload.isForChart;
//     dataPivoting _dataPivoting;
//     vector<Date> dates =  _dataPivoting.GetListOfYears(WellsForecastResults, isByYear);
//     vector<vector<ForecastResult>>  results
//     = _dataPivoting.GetYearlyForcastResultModulesLevel(WellsForecastResults, dates,
//     isByYear, isForChart);
//     map<string, map<string, string>> resultsToMap =
//     reportJSON2.GetForecastOutputAsJson(results);
//     ResponseChartData responseChartData;

//     responseChartData.response = resultsToMap;

//     json jsonResponseData = to_json(responseChartData);

//     return jsonResponseData;
// }

json AllWellsYearlyResultNewAsyncT::Plot(const json &jsonData)
{
    ChatPayload chatPayload = ConvertJsonToChatPayload(jsonData);
    vector<vector<ForecastResult>> WellsForecastResults;
    for (int i = 0; i < chatPayload.wells.size(); i++)
    {
        WellsForecastResults.push_back(chatPayload.wells[i].resultWells);
    }

    bool isByYear = chatPayload.isByYear;
    bool isForChart = chatPayload.isForChart;
    dataPivoting _dataPivoting;
    vector<Date> dates = _dataPivoting.GetListOfYears(WellsForecastResults, isByYear);
    vector<vector<ForecastResult>> results = _dataPivoting.GetYearlyForcastResultModulesLevel(WellsForecastResults, dates,
                                                                                              isByYear, isForChart);
    map<string, map<string, string>> resultsToMap =
        reportJSON2.GetForecastOutputAsJson(results);
    ResponseChartData responseChartData;

    responseChartData.response = resultsToMap;

    json jsonResponseData = to_json(responseChartData);

    return jsonResponseData;
}

vector<map<string, string>> AllWellsYearlyResultNewAsyncT::GetYearlyForcastResultModulesNewAsync(
    vector<ModuleResultMonthly> wells,
    bool &isByYear,
    bool &isForChart,
    int &nWells)
{

    /* InputObject inputOjbect = {
        lstWells,
        !isMonthly,
        false,
        static_cast<int>(lstWells.size())
    }; */

    // lstWells,
    //     !isMonthly,
    //     false,
    //     static_cast<int>(lstWells.size())

    vector<vector<ForecastResult>> WellsForecastResults;
    for (int i = 0; i < wells.size(); i++)
    {
        WellsForecastResults.push_back(wells[i].resultWells);
    }

    dataPivoting _dataPivoting;
    vector<Date> dates = _dataPivoting.GetListOfYears(WellsForecastResults, isByYear);
    vector<vector<ForecastResult>> results = _dataPivoting.GetYearlyForcastResultModulesLevel(WellsForecastResults, dates,
                                                                                              isByYear, isForChart);
    // vector<map<string, string>
    map<string, map<string, string>> resultsToMap =
        reportJSON2.GetForecastOutputAsJson(results);

    // Vector to store the maps
    vector<map<string, string>> vectorOfMaps;

    // Iterate through the outer map and insert inner maps into the vector
    for (const auto &outerPair : resultsToMap)
    {
        vectorOfMaps.push_back(outerPair.second);
    }

    // Now vectorOfMaps contains the maps from outerMap
    // Example to print the vector of maps
    /* for (const auto& innerMap : vectorOfMaps) {
        for (const auto& innerPair : innerMap) {
            std::cout << innerPair.first << ": " << innerPair.second << std::endl;
        }
        //std::cout << "---" << std::endl;
    } */

    // ResponseChartData responseChartData;

    /*  responseChartData.response = resultsToMap;

     json jsonResponseData = to_json(responseChartData); */

    return vectorOfMaps;
}

// Function to split a string by a delimiter
/* vector<string> AllWellsYearlyResultNewAsyncT::split(const string&) {
    vector<string> parts;
    stringstream ss(str);
    string part;

    while (std::getline(ss, part, delimiter)) {
        parts.push_back(part);
    }

    return parts;
} */

// Function to get unique scenario names from the selected module paths
vector<string> AllWellsYearlyResultNewAsyncT::GetscenarioNames(const vector<string> &selectedModulePaths)
{
    vector<string> scenarioNames;

    for (const auto &path : selectedModulePaths)
    {
        // Split the path by the delimiter
        vector<string> parts = split(path);

        // The scenario is the first part
        const string &scenario = parts[0];

        // Check if the scenario is not already in the list
        if (find(scenarioNames.begin(), scenarioNames.end(), scenario) == scenarioNames.end())
        {
            scenarioNames.push_back(scenario);
        }
    }

    return scenarioNames;
}

// Function to get unique facility names from the selected module paths
vector<string> AllWellsYearlyResultNewAsyncT::GetfacilityNames(
    const vector<string> &selectedModulePaths)
{
    vector<string> facilityNames;

    for (const auto &path : selectedModulePaths)
    {
        // Split the path by the delimiter
        vector<string> parts = split(path);

        // The facility is the second part
        if (parts.size() > 1)
        {
            const string &facility = parts[1];

            // Check if the facility is not already in the list
            if (find(facilityNames.begin(), facilityNames.end(), facility) == facilityNames.end())
            {
                facilityNames.push_back(facility);
            }
        }
    }

    return facilityNames;
}

// Helper function to split a string by a delimiter
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

// Main function to get forecast results
vector<ForecastResult> AllWellsYearlyResultNewAsyncT::getForecastResult(const string &table)
{
    const string columnDelimeter = "@#$%";
    const string rowDelimeter = "@#*$%";

    vector<ForecastResult> actualTable;

    vector<std::string> rows = split(table, rowDelimeter);

    for (const auto &row : rows)
    {
        ForecastResult result;
        vector<string> columns = split(row, columnDelimeter);

        try
        {
            size_t colIndx = 0;
            result.uniqueId = columns[colIndx++];
            result.Version_Name = columns[colIndx++];
            result.Field = columns[colIndx++];
            result.Reservoir = columns[colIndx++];
            result.Drainage_Point = columns[colIndx++];
            result.Production_String = columns[colIndx++];
            result.TRANCHE = columns[colIndx++];
            result.Asset_Team = columns[colIndx++];
            result.Flow_station = columns[colIndx++];
            result.moduleName = columns[colIndx++];
            result.Day = stoi(columns[colIndx++]);
            result.Month = stoi(columns[colIndx++]);
            result.Year = stoi(columns[colIndx++]);
            result.Oil_rate = stod(columns[colIndx++]);
            result.Gas_Rate = stod(columns[colIndx++]);
            result.Water_Rate = stod(columns[colIndx++]);
            result.Liquid_Rate = stod(columns[colIndx++]);
            result.Cum_Oil_Prod = stod(columns[colIndx++]);
            result.Cum_Gas_Prod = stod(columns[colIndx++]);
            result.Cum_Water_Prod = stod(columns[colIndx++]);
            result.GOR = stod(columns[colIndx++]);
            result.BSW = stod(columns[colIndx++]);
            result.CGR = stod(columns[colIndx++]);
            result.WGR = stod(columns[colIndx++]);
            result.CutBack = stod(columns[colIndx++]);
            result.HyrocarbonStream = columns[colIndx++];
            result.hydrocarbonType = columns[colIndx++];
            result.terminal = columns[colIndx++];
            result.URo = stod(columns[colIndx++]);
            result.URg = stod(columns[colIndx++]);
            result.Gas_Own_Use = stod(columns[colIndx++]);
            result.Gas_Demand = stod(columns[colIndx++]);
            result.Gas_Flared = stod(columns[colIndx++]);
            result.Crude_Oil_Lossess = stod(columns[colIndx++]);
            result.CutBack = stod(columns[colIndx++]);
            result.projectCode = columns[colIndx++];
            result.projectName = columns[colIndx++];
            result.prodDays = stod(columns[colIndx++]);
            result.OptimalSolution = stod(columns[colIndx++]);
            result.AllWellsLiquidCapacity = stod(columns[colIndx++]);
            result.AllWellsGasCapacity = stod(columns[colIndx++]);
            result.resourceClass = columns[colIndx++];
            result.Condensate_Rate = stod(columns[colIndx++]);
            result.reasonForTermination = columns[colIndx++];
            result.declineRate = stod(columns[colIndx++]);
        }
        catch (const std::exception &e)
        {
            // Handle error (optional: log or continue)
        }

        actualTable.push_back(result);
    }

    // Remove the last element if needed
    if (!actualTable.empty())
    {
        actualTable.pop_back();
    }

    return actualTable;
}

// Assume ForecastResultsByModule and the getForecastResult function are already defined

vector<ModuleResultMonthly>
AllWellsYearlyResultNewAsyncT::GetModulesForecastResultsByScenario(
    const vector<ForecastResultsByModule> &forecastModulesCompleteObject,
    const string &scenarioName,
    const string &solutionSpace,
    const vector<string> &facilityNames)
{
    // Filter forecastModulesCompleteObject by scenarioName and solutionSpace
    vector<ForecastResultsByModule> forecastModulesPerScenario;
    copy_if(forecastModulesCompleteObject.begin(), forecastModulesCompleteObject.end(),
            back_inserter(forecastModulesPerScenario),
            [&scenarioName, &solutionSpace](const ForecastResultsByModule &module)
            {
                return module.scenarioName == scenarioName && module.solutionSpace == solutionSpace;
            });

    vector<ModuleResultMonthly> modulesResult;

    for (const auto &facility : facilityNames)
    {
        // Filter forecastModulesPerScenario by facilityName
        vector<ForecastResultsByModule> forecastModulesPerFacility;
        copy_if(forecastModulesPerScenario.begin(), forecastModulesPerScenario.end(),
                back_inserter(forecastModulesPerFacility),
                [&facility](const ForecastResultsByModule &module)
                {
                    return module.facilityName == facility;
                });

        for (const auto &module : forecastModulesPerFacility)
        {
            // Get forecast results
            vector<ForecastResult> forecastResults = getForecastResult(module.forecastResults);

            ModuleResultMonthly moduleResultMonthly = {forecastResults};
            modulesResult.push_back(moduleResultMonthly);
        }
    }

    return modulesResult;
}

map<string, vector<ModuleResultMonthly>>
AllWellsYearlyResultNewAsyncT::GetModulesForecastResultsByFacility(
    const vector<ForecastResultsByModule> &forecastModulesCompleteObject,
    const string &scenarioName,
    const string &solutionSpace,
    const vector<string> &facilityNames)
{
    // Filter forecastModulesCompleteObject by scenarioName and solutionSpace
    vector<ForecastResultsByModule> forecastModulesPerScenario;
    copy_if(forecastModulesCompleteObject.begin(), forecastModulesCompleteObject.end(),
            back_inserter(forecastModulesPerScenario),
            [&scenarioName, &solutionSpace](const ForecastResultsByModule &module)
            {
                return module.scenarioName == scenarioName && module.solutionSpace == solutionSpace;
            });

    map<string, vector<ModuleResultMonthly>> modulesResultByFacility;
    for (const auto &facility : facilityNames)
    {
        // Filter forecastModulesPerScenario by facilityName
        vector<ForecastResultsByModule> forecastModulesPerFacility;
        copy_if(forecastModulesPerScenario.begin(), forecastModulesPerScenario.end(),
                back_inserter(forecastModulesPerFacility),
                [&facility](const ForecastResultsByModule &module)
                {
                    return module.facilityName == facility;
                });

        vector<ModuleResultMonthly> modulesResult;
        for (const auto &module : forecastModulesPerFacility)
        {
            // Get forecast results
            vector<ForecastResult> forecastResults = getForecastResult(module.forecastResults);

            ModuleResultMonthly moduleResultMonthly = {forecastResults};
            modulesResult.push_back(moduleResultMonthly);
        }

        modulesResultByFacility[facility] = modulesResult;
    }

    return modulesResultByFacility;
}

// Assume ForecastResultsByModule and the getForecastResult function are already defined

unordered_map<string, unordered_map<string, ModuleResultMonthly>>
AllWellsYearlyResultNewAsyncT::GetForecastResultsByScenario(
    const vector<ForecastResultsByModule> &forecastModulesCompleteObject,
    const string &scenarioName,
    const string &solutionSpace,
    const vector<string> &facilityNames)
{
    // Filter forecastModulesCompleteObject by scenarioName and solutionSpace
    vector<ForecastResultsByModule> forecastModulesPerScenario;
    copy_if(forecastModulesCompleteObject.begin(), forecastModulesCompleteObject.end(),
            back_inserter(forecastModulesPerScenario),
            [&scenarioName, &solutionSpace](const ForecastResultsByModule &module)
            {
                return module.scenarioName == scenarioName && module.solutionSpace == solutionSpace;
            });

    unordered_map<string, unordered_map<string, ModuleResultMonthly>> facilitiesMonthly;

    for (const auto &facility : facilityNames)
    {
        // Filter forecastModulesPerScenario by facilityName
        vector<ForecastResultsByModule> forecastModulesPerFacility;
        copy_if(forecastModulesPerScenario.begin(), forecastModulesPerScenario.end(),
                back_inserter(forecastModulesPerFacility),
                [&facility](const ForecastResultsByModule &module)
                {
                    return module.facilityName == facility;
                });

        unordered_map<string, ModuleResultMonthly> wellsMonthly;

        for (const auto &module : forecastModulesPerFacility)
        {
            // Get forecast results
            vector<ForecastResult> forecastResults = getForecastResult(module.forecastResults);

            ModuleResultMonthly moduleResultMonthly = {forecastResults};
            wellsMonthly[module.moduleName] = moduleResultMonthly;
        }

        facilitiesMonthly[facility] = wellsMonthly;
    }

    return facilitiesMonthly;
}

// Sum function equivalent to Lodash's sum
// double AllWellsYearlyResultNewAsyncT::sum(const vector<double>& numbers) {
//     return accumulate(numbers.begin(), numbers.end(), 0.0);
// }

// Zip function equivalent to Lodash's zip
// vector<vector<double>> AllWellsYearlyResultNewAsyncT::zip(const vector<vector<double>>& arrays) {
//     vector<vector<double>> zipped;
//     if (arrays.empty()) return zipped;

//     size_t numElements = arrays[0].size();
//     size_t numArrays = arrays.size();

//     zipped.resize(numElements, vector<double>(numArrays));

//     for (size_t i = 0; i < numElements; ++i) {
//         for (size_t j = 0; j < numArrays; ++j) {
//             zipped[i][j] = arrays[j][i];
//         }
//     }

//     return zipped;
// }

// Equivalent to the TypeScript aggregateY function
// vector<double> AllWellsYearlyResultNewAsyncT::aggregateY(const vector<YObj>& yObjs) {
//     vector<vector<double>> forecastVariableArray;
//     for(int i = 0; i < yObjs.size(); i++){
//         forecastVariableArray.push_back(yObjs[i].y);
//     }

//     vector<vector<double>> zipped = zip(forecastVariableArray);
//     vector<double> aggregatedY(zipped.size());

//     transform(zipped.begin(), zipped.end(), aggregatedY.begin(), sum);

//     return aggregatedY;
// }

map<string, map<string, ModuleResultMonthly>> AllWellsYearlyResultNewAsyncT::convertToOrdered(
    const unordered_map<string, unordered_map<string, ModuleResultMonthly>> &unorderedMap)
{

    std::map<std::string, std::map<std::string, ModuleResultMonthly>> orderedMap;

    // Iterate through the unordered_map and insert into the orderedMap
    for (const auto &outerPair : unorderedMap)
    {
        const std::string &outerKey = outerPair.first;
        const std::unordered_map<std::string, ModuleResultMonthly> &innerUnorderedMap = outerPair.second;

        // Convert the inner unordered_map to map
        std::map<std::string, ModuleResultMonthly> innerOrderedMap(innerUnorderedMap.begin(), innerUnorderedMap.end());

        // Insert the converted inner map into the outer map
        orderedMap.emplace(outerKey, std::move(innerOrderedMap));
    }

    return orderedMap;
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

map<string, map<string, map<string, vector<YObj>>>>
AllWellsYearlyResultNewAsyncT::chartDataByModulesOrAggregate_Obsolete(
    const vector<string> &selectedModulePaths,
    const vector<string> &selectedVariables,
    bool isMonthly,
    const vector<string> &forecastSolutionSpaceNames,
    const vector<ForecastResultsByModule> &forecastResultsByModule,
    const string &forecastResultsId,
    bool shouldAggregate)
{
    vector<string> scenarioNames = GetscenarioNames(selectedModulePaths);
    vector<string> facilityNames = GetfacilityNames(selectedModulePaths);
    // map<string, map<string, map<string, vector<ForecastResult>>>> solutionCase_ForecastResult;
    map<string, map<string, map<string, ModuleResultMonthly>>> solutionCase_ForecastResult;

    // map<string, map<string, ModuleResultMonthly>>
    // unordered_map<string, unordered_map<string, ModuleResultMonthly>>

    // Processing forecast results per scenario and solution space
    for (const auto &forecastSolutionSpaceName : forecastSolutionSpaceNames)
    {
        for (const auto &_scenarioName : scenarioNames)
        {
            string case_scenario_Name = (forecastSolutionSpaceName + _scenarioName);
            transform(case_scenario_Name.begin(), case_scenario_Name.end(), case_scenario_Name.begin(), ::toupper);

            auto iforecastResult = GetForecastResultsByScenario(
                forecastResultsByModule, _scenarioName, forecastSolutionSpaceName, facilityNames);

            solutionCase_ForecastResult[case_scenario_Name] = convertToOrdered(iforecastResult);
        }
    }

    map<string, std::vector<ModuleResultMonthly>> lstWellsObject;
    for (const auto &forecastSolutionSpaceName : forecastSolutionSpaceNames)
    {
        vector<ModuleResultMonthly> lstWells;

        for (const auto &path : selectedModulePaths)
        {
            vector<std::string> parts = split(path, delimeter); // Assume split function is defined
            string scenario = parts[0];
            string station = parts[1];
            string moduleName = parts[2];
            string case_senario_name = forecastSolutionSpaceName + scenario;

            transform(case_senario_name.begin(), case_senario_name.end(), case_senario_name.begin(), ::toupper);

            auto scenarioResult = solutionCase_ForecastResult[case_senario_name];
            auto facilitiesResult = scenarioResult[station];
            auto moduleNameResult = facilitiesResult[moduleName];

            if (!moduleNameResult.resultWells.empty())
            {
                lstWells.push_back(moduleNameResult);
            }
        }
        if (!lstWells.empty())
        {
            lstWellsObject[forecastSolutionSpaceName] = lstWells;
        }
    }

    map<string, vector<map<string, string>>> results_OutputObject;
    // map<string, map<string, string>>
    for (const auto &[key, lstWells] : lstWellsObject)
    {
        // InputObject inputOjbect = {
        //     lstWells,
        //     !isMonthly,
        //     false,
        //     static_cast<int>(lstWells.size())
        // };

        // Assume GetYearlyForcastResultModulesNewAsync is defined
        // vector<ModuleResultMonthly> wells = lstWells;
        bool isByYear = !isMonthly;
        bool isForChart = false;
        int nWells = static_cast<int>(lstWells.size());
        auto results_Output = GetYearlyForcastResultModulesNewAsync(lstWells, isByYear, isForChart, nWells);
        results_OutputObject[key] = results_Output;
    }

    map<string, map<string, map<string, vector<YObj>>>> res2;

    for (const auto &[key, results_Output] : results_OutputObject)
    {
        int nWells = selectedModulePaths.size();
        vector<map<string, YObj>> outputData;

        for (int j = 0; j < nWells; ++j)
        {
            map<string, YObj> yObjs;
            const string &table = results_Output[j].at("resultWells");

            for (const string &variable : selectedVariables)
            {
                vector<ForecastResult> resultWells = getForecastResult(table);
                int nTimes = resultWells.size();

                vector<string> x;
                vector<double> y;
                string uniqueId, moduleN;

                for (int i = 0; i < nTimes; ++i)
                {
                    const auto &rowData = resultWells[i];
                    uniqueId = rowData.uniqueId;
                    moduleN = rowData.moduleName;
                    y.push_back(rowData.getVariableByName(variable));
                    string date = to_string(rowData.Day) + "/" + to_string(rowData.Month) + "/" + to_string(rowData.Year);
                    x.push_back(date);
                }

                YObj yObj;
                yObj.forecastResultId = forecastResultsId;
                yObj.id = uniqueId;
                yObj.name = moduleN;
                yObj.title = moduleN;
                yObj.path = selectedModulePaths[j];
                yObj.y = y;
                yObj.x = x;

                yObjs[variable] = yObj;
            }
            outputData.push_back(yObjs);
        }

        // std::map<std::string, std::map<std::string, std::vector<ForecastResult>>> res;
        map<string, map<string, vector<YObj>>> res;
        for (const std::string &variable : selectedVariables)
        {
            res["1P_1C"][variable] = {};
            res["2P_2C"][variable] = {};
            res["3P_3C"][variable] = {};
        }

        for (const auto &yObjs : outputData)
        {
            for (const string &variable : selectedVariables)
            {
                if (yObjs.at(variable).path.find("1P_1C") != string::npos)
                {
                    res["1P_1C"][variable].push_back(yObjs.at(variable));
                }
                else if (yObjs.at(variable).path.find("2P_2C") != string::npos)
                {
                    res["2P_2C"][variable].push_back(yObjs.at(variable));
                }
                else if (yObjs.at(variable).path.find("3P_3C") != string::npos)
                {
                    res["3P_3C"][variable].push_back(yObjs.at(variable));
                }
            }
        }

        res2[key] = res;
    }

    map<string, map<string, map<string, vector<YObj>>>> _scenarioObjects;

    for (const auto &[res2Key, solutionCaseObject] : res2)
    {
        _scenarioObjects["1P_1C"][res2Key] = solutionCaseObject.at("1P_1C");
        _scenarioObjects["2P_2C"][res2Key] = solutionCaseObject.at("2P_2C");
        _scenarioObjects["3P_3C"][res2Key] = solutionCaseObject.at("3P_3C");
    }

    return _scenarioObjects;
}

map<string, map<string, map<string, vector<YObj>>>>
AllWellsYearlyResultNewAsyncT::chartDataByModulesOrAggregate(
    const vector<string> &selectedModulePaths,
    const vector<string> &selectedVariables,
    bool isMonthly,
    const vector<string> &forecastSolutionSpaceNames,
    const vector<ForecastResultsByModule> &forecastResultsByModule,
    const string &forecastResultsId,
    bool shouldAggregate)
{
    vector<string> scenarioNames = GetscenarioNames(selectedModulePaths);
    vector<string> facilityNames = GetfacilityNames(selectedModulePaths);
    map<string, std::vector<ModuleResultMonthly>> lstWellsObject;

    // Processing forecast results per scenario and solution space
    for (const auto &forecastSolutionSpaceName : forecastSolutionSpaceNames)
    {
        for (const auto &_scenarioName : scenarioNames)
        {
            string case_scenario_Name = (forecastSolutionSpaceName + _scenarioName);
            transform(case_scenario_Name.begin(), case_scenario_Name.end(), case_scenario_Name.begin(), ::toupper);

            lstWellsObject[case_scenario_Name] = GetModulesForecastResultsByScenario(
                forecastResultsByModule, _scenarioName, forecastSolutionSpaceName, facilityNames);

            // auto iforecastResult = GetModulesForecastResultsByScenario(
            //     forecastResultsByModule, _scenarioName, forecastSolutionSpaceName, facilityNames);

            //     lstWellsObject[case_scenario_Name] = iforecastResult;

            // GetModulesForecastResultsByFacility
            //  if(isFacilityGroupped){

            // }else{

            // }
        }
    }

    map<string, vector<map<string, string>>> results_OutputObject;
    // map<string, map<string, string>>
    for (const auto &[key, lstWells] : lstWellsObject)
    {
        // InputObject inputOjbect = {
        //     lstWells,
        //     !isMonthly,
        //     false,
        //     static_cast<int>(lstWells.size())
        // };

        // Assume GetYearlyForcastResultModulesNewAsync is defined
        bool isByYear = !isMonthly;
        bool isForChart = false;
        int nWells = static_cast<int>(lstWells.size());
        results_OutputObject[key] = GetYearlyForcastResultModulesNewAsync(lstWells, isByYear, isForChart, nWells);
        // results_OutputObject[key] = results_Output;
    }

    map<string, map<string, map<string, vector<YObj>>>> res2;

    for (const auto &[key, results_Output] : results_OutputObject)
    {
        int nWells = selectedModulePaths.size();
        vector<map<string, YObj>> outputData;

        for (int j = 0; j < nWells; ++j)
        {
            map<string, YObj> yObjs;
            const string &table = results_Output[j].at("resultWells");

            for (const string &variable : selectedVariables)
            {
                vector<ForecastResult> resultWells = getForecastResult(table);
                int nTimes = resultWells.size();

                vector<string> x;
                vector<double> y;
                string uniqueId, moduleN;

                for (int i = 0; i < nTimes; ++i)
                {
                    const auto &rowData = resultWells[i];
                    uniqueId = rowData.uniqueId;
                    moduleN = rowData.moduleName;
                    y.push_back(rowData.getVariableByName(variable));
                    string date = to_string(rowData.Day) + "/" + to_string(rowData.Month) + "/" + to_string(rowData.Year);
                    x.push_back(date);
                }

                YObj yObj;
                yObj.forecastResultId = forecastResultsId;
                yObj.id = uniqueId;
                yObj.name = moduleN;
                yObj.title = moduleN;
                yObj.path = selectedModulePaths[j];
                yObj.y = y;
                yObj.x = x;

                yObjs[variable] = yObj;
            }
            outputData.push_back(yObjs);
        }

        // std::map<std::string, std::map<std::string, std::vector<ForecastResult>>> res;
        map<string, map<string, vector<YObj>>> res;
        for (const std::string &variable : selectedVariables)
        {
            res["1P_1C"][variable] = {};
            res["2P_2C"][variable] = {};
            res["3P_3C"][variable] = {};
        }

        for (const auto &yObjs : outputData)
        {
            for (const string &variable : selectedVariables)
            {
                if (yObjs.at(variable).path.find("1P_1C") != string::npos)
                {
                    res["1P_1C"][variable].push_back(yObjs.at(variable));
                }
                else if (yObjs.at(variable).path.find("2P_2C") != string::npos)
                {
                    res["2P_2C"][variable].push_back(yObjs.at(variable));
                }
                else if (yObjs.at(variable).path.find("3P_3C") != string::npos)
                {
                    res["3P_3C"][variable].push_back(yObjs.at(variable));
                }
            }
        }

        res2[key] = res;
    }

    map<string, map<string, map<string, vector<YObj>>>> _scenarioObjects;

    for (const auto &[res2Key, solutionCaseObject] : res2)
    {
        _scenarioObjects["1P_1C"][res2Key] = solutionCaseObject.at("1P_1C");
        _scenarioObjects["2P_2C"][res2Key] = solutionCaseObject.at("2P_2C");
        _scenarioObjects["3P_3C"][res2Key] = solutionCaseObject.at("3P_3C");
    }

    return _scenarioObjects;
}

map<string, map<string, map<string, YObj>>>
AllWellsYearlyResultNewAsyncT::chartDataByModulesOrAggregate2(
    const string &forecastResultsId,
    map<string, map<string, map<string, vector<YObj>>>> _scenarioObjects)
{

    map<string, map<string, map<string, YObj>>> aggregatedScenarioObjects;
    for (const auto &[forecastCase, forecastCaseMap] : _scenarioObjects)
    {
        map<string, map<string, YObj>> solutionCaseObj;
        for (const auto &[solutionCase, solutionCaseMap] : forecastCaseMap)
        {
            map<string, YObj> forecastVariableObj;
            for (const auto &[forecastVariable, forecastVariableArray] : solutionCaseMap)
            {
                if (forecastVariableArray.size() > 0)
                {

                    vector<double> yAgg;
                    for (int i = 0; i < forecastVariableArray[0].y.size(); i++)
                    {
                        yAgg.push_back(0);
                    }
                    for (int i = 0; i < forecastVariableArray.size(); i++)
                    {
                        for (int j = 0; j < forecastVariableArray[i].y.size(); j++)
                        {
                            yAgg[j] = yAgg[j] + forecastVariableArray[i].y[j];
                        }
                    }

                    string pathWithDelimeter = forecastCase + "@#$%" + solutionCase + "@#$%" + forecastVariable;
                    string path = forecastCase + "." + solutionCase + "." + forecastVariable;

                    YObj data;
                    data.forecastResultId = forecastResultsId;
                    data.id = pathWithDelimeter;
                    data.name = pathWithDelimeter;
                    data.title = pathWithDelimeter;
                    data.path = pathWithDelimeter;
                    data.y = yAgg;
                    data.x = forecastVariableArray[0].x;
                    forecastVariableObj[forecastVariable] = data;

                    // aggregatedScenarioObjects[forecastCase][solutionCase][forecastVariable] = data;
                    // set(aggregatedScenarioObjects, path, data);  // Assume set function is defined
                }
            }

            solutionCaseObj[solutionCase] = forecastVariableObj;
        }

        aggregatedScenarioObjects[forecastCase] = solutionCaseObj;
    }

    /* json jsonData;
    for (const auto& level1 : aggregatedScenarioObjects) {
        json level1Json;
        for (const auto& level2 : level1.second) {
            json level2Json;
            for (const auto& level3 : level2.second) {
                level2Json[level3.first] = to_json(level3.second);
            }
            level1Json[level2.first] = level2Json;
        }
        jsonData[level1.first] = level1Json;
    } */

    return aggregatedScenarioObjects;
}

json AllWellsYearlyResultNewAsyncT::PlotChart(const json &forecastResultsJsonData, const json &chartInputJsonData)
{

    std::vector<ForecastResultsByModule> forecastResultsByModule =
        parseForecastResults(forecastResultsJsonData);
    ChartInputPayload chartInputPayload = chartInputPayload_to_json(chartInputJsonData);

    vector<string> selectedModulePaths = chartInputPayload.selectedModulePaths;
    vector<string> selectedVariables = chartInputPayload.selectedVariables;
    bool isMonthly = chartInputPayload.isMonthly;
    vector<string> forecastSolutionSpaceNames = chartInputPayload.forecastSolutionSpaces;
    string forecastResultsId = chartInputPayload.forecastResultsIds[0];
    bool shouldAggregate = chartInputPayload.shouldAggregate;

    map<string, map<string, map<string, vector<YObj>>>> _scenarioObjects;

    json jsonChartDataOutput;

    if (chartInputPayload.shouldAggregate == false)
    {
        _scenarioObjects =
            chartDataByModulesOrAggregate(
                selectedModulePaths,
                selectedVariables,
                isMonthly,
                forecastSolutionSpaceNames,
                forecastResultsByModule,
                forecastResultsId,
                shouldAggregate);

        for (const auto &level1 : _scenarioObjects)
        {
            json level1Json;
            for (const auto &level2 : level1.second)
            {
                json level2Json;
                for (const auto &level3 : level2.second)
                {
                    json level3Json;
                    for (const auto &yObj : level3.second)
                    {
                        level3Json.push_back(to_json(yObj));
                    }
                    level2Json[level3.first] = level3Json;
                }
                level1Json[level2.first] = level2Json;
            }
            jsonChartDataOutput[level1.first] = level1Json;
        }
    }
    else
    {
        _scenarioObjects =
            chartDataByModulesOrAggregate(
                selectedModulePaths,
                selectedVariables,
                isMonthly,
                forecastSolutionSpaceNames,
                forecastResultsByModule,
                forecastResultsId,
                shouldAggregate);

        map<string, map<string, map<string, YObj>>> aggregatedScenarioObjects = chartDataByModulesOrAggregate2(
            forecastResultsId,
            _scenarioObjects);

        for (const auto &level1 : aggregatedScenarioObjects)
        {
            json level1Json;
            for (const auto &level2 : level1.second)
            {
                json level2Json;
                for (const auto &level3 : level2.second)
                {
                    level2Json[level3.first] = to_json(level3.second);
                }
                level1Json[level2.first] = level2Json;
            }
            jsonChartDataOutput[level1.first] = level1Json;
        }
    }

    return jsonChartDataOutput;
}
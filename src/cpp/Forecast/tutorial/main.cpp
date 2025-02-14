#include <map>
#include <iostream>
#include <functional>
#include <string>
#include <fstream>
#include "../utilities/GetChartDataMap.h"
#include "../../nlohmann/json.hpp"
#include "../ProductionForecast/Forecast.h"
#include "../JsonMapping/forecastResultsByModule.h"

using namespace std;
using json = nlohmann::json;
using ChartDataResultMapType = map<string, map<string, map<string, map<string, map<string, std::vector<std::string>>>>>>;

// Helper functions
json ReadJsonFile(string jsonFileName)
{
    std::ifstream file(jsonFileName);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open JSON file");
    }

    json jsonData;
    file >> jsonData;
    file.close();

    return jsonData;
}

void export_to_file(const json &j, const string &filename)
{
    ofstream file(filename);
    if (file.is_open())
    {
        file << j.dump(4); // Pretty print with 4 spaces
        file.close();
        cout << "JSON saved to " << filename << endl;
    }
    else
    {
        cerr << "Unable to open file: " << filename << endl;
    }
}

// Function to convert std::any to JSON-friendly format
json anyToJson(const any& value) {
    if (value.type() == typeid(int)) {
        return any_cast<int>(value);
    } else if (value.type() == typeid(double)) {
        return any_cast<double>(value);
    } else if (value.type() == typeid(string)) {
        return any_cast<string>(value);
    } else if (value.type() == typeid(bool)) {
        return any_cast<bool>(value);
    }
    return nullptr;  // Unsupported types are ignored
}

// Recursive function to convert the nested map to JSON
json convertToJson(const ChartDataResultMapType& nestedMap) {
    json j;
    for (const auto& [key1, subMap1] : nestedMap) {
        for (const auto& [key2, subMap2] : subMap1) {
            for (const auto& [key3, subMap3] : subMap2) {
                for (const auto& [key4, subMap4] : subMap3) {
                    for (const auto& [key5, values] : subMap4) {
                        json jsonArray = json::array();
                        for (const auto& val : values) {
                            jsonArray.push_back(anyToJson(val));
                        }
                        j[key1][key2][key3][key4][key5] = jsonArray;
                    }
                }
            }
        }
    }
    return j;
}

// Function to save JSON to a file
void saveToJsonFile(const ChartDataResultMapType& data, const string& filename) {
    json j = convertToJson(data);

    std::cout << "filename: " << filename << std::endl;
    // std::cout << "Chart result: " << j << std::endl;
    
    ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);  // Pretty-print JSON with 4 spaces
        file.close();
        cout << "Data saved to " << filename << endl;
    } else {
        cerr << "Failed to open file: " << filename << endl;
    }
}

// MAIN FUNCTION
int main()
{
    std::cout << "level 1" << std::endl;

    json chartInputJsonData = ReadJsonFile("/Users/GSanni/Desktop/myinfo/pet_app/files/forecast_chart_data_input_single.json");
    // json chartInputJsonData = ReadJsonFile("/Users/GSanni/Desktop/myinfo/pet_app/files/forecast_chat_data_input.json");

    std::cout << "level 2" << std::endl;

    ChartInputPayload chartInputPayload = chartInputPayload_to_json(chartInputJsonData);

    std::cout << "level 3" << std::endl;
    std::cout << "Parsed JSON: " << chartInputJsonData.dump(4) << std::endl;

    json forecastResultsJsonData = ReadJsonFile("/Users/GSanni/Desktop/myinfo/pet_app/files/forecast_forecastresultsbymodules.json");

    std::cout << "level 4" << std::endl;

    std::vector<ForecastResultsByModule> forecastResultsByModule = parseForecastResults(forecastResultsJsonData);

    std::cout << "level 5" << std::endl;

    vector<string> selectedModulePaths = chartInputPayload.selectedModulePaths;
    vector<string> selectedVariables = chartInputPayload.selectedVariables;
    bool isMonthly = false;
    vector<string> forecastSolutionSpaceNames = chartInputPayload.forecastSolutionSpaces;
    vector<string> forecastResultsIds = chartInputPayload.forecastResultsIds;
    bool shouldAggregate = chartInputPayload.shouldAggregate;

    AllWellsYearlyResultNewAsyncT instance;
    ChartDataResultMapType
        chartDataMap = instance.chartDataByModulesOrAggregateNew(
            selectedModulePaths,
            selectedVariables,
            isMonthly,
            forecastSolutionSpaceNames,
            forecastResultsByModule,
            forecastResultsIds,
            shouldAggregate);

    saveToJsonFile(chartDataMap, "/Users/GSanni/Desktop/myinfo/pet_app/output/chartMapData.json");

    std::cout << "Yes oooo yes oooo" << std::endl;

    return 0;
}

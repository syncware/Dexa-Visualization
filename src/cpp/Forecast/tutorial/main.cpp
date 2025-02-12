#include <iostream>
#include <functional>
#include "../utilities/GetChartDataMap.h"
#include "../../nlohmann/json.hpp"
#include <unordered_map>
#include <map>
#include <string>
#include <fstream>
#include "../ProductionForecast/Forecast.h"

using namespace std;
using namespace std::placeholders;
using json = nlohmann::json;

json ReadJsonFile(string jsonFileName);

int main()
{
    json forecastResultsJsonData = ReadJsonFile("/Users/GSanni/Desktop/myinfo/pet_app/files/apex-FG.forecast_forecastresultsbymodules.json");
    std::vector<ForecastResultsByModule> forecastResultsByModule = parseForecastResults(forecastResultsJsonData);
    json chartInputJsonData = ReadJsonFile("/Users/GSanni/Desktop/myinfo/pet_app/files/forecast_chat_data_input.json");
    ChartInputPayload chartInputPayload = chartInputPayload_to_json(chartInputJsonData);

    vector<string> selectedModulePaths = chartInputPayload.selectedModulePaths;
    vector<string> selectedVariables = chartInputPayload.selectedVariables;
    bool isMonthly = false;
    vector<string> forecastSolutionSpaceNames = chartInputPayload.forecastsolutionSpaces;
    vector<string> forecastResultsIds = chartInputPayload.forecastResultsIds;
    bool shouldAggregate = chartInputPayload.shouldAggregate;

    AllWellsYearlyResultNewAsyncT instance;
    map<std::string, map<string, map<string, map<string, map<string, std::vector<any>>>>>>
        chartDataMap = instance.chartDataByModulesOrAggregateNew(
            selectedModulePaths,
            selectedVariables,
            isMonthly,
            forecastSolutionSpaceNames,
            forecastResultsByModule,
            forecastResultsIds,
            shouldAggregate);

    // std::cout << chartDataMap << std::endl;

    return 0;
}

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
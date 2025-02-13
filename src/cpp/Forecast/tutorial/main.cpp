#include <map> // should always be include before those that depend on it
// #include <any> // should always be include before those that depend on it
#include <iostream>
#include <functional>
#include <string>
#include <fstream>
#include "../utilities/GetChartDataMap.h"
#include "../../nlohmann/json.hpp"
#include "../ProductionForecast/Forecast.h"
#include "../JsonMapping/forecastResultsByModule.h"

using namespace std;
// using namespace std::placeholders;
using json = nlohmann::json;

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

int main()
{
    std::cout << "level 1" << std::endl;
    
    json chartInputJsonData = ReadJsonFile("/Users/GSanni/Desktop/myinfo/pet_app/files/forecast_chat_data_input.json");

    std::cout << "level 2" << std::endl;

    ChartInputPayload chartInputPayload = chartInputPayload_to_json(chartInputJsonData);

    std::cout << "level 3" << std::endl;
    std::cout << "Parsed JSON: " << chartInputJsonData.dump(4) << std::endl;

    json forecastResultsJsonData = ReadJsonFile("/Users/GSanni/Desktop/myinfo/pet_app/files/apex-FG.forecast_forecastresultsbymodules.json");
    
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
    std::map<std::string, std::map<string, std::map<string, std::map<string, std::map<string, std::vector<std::any>>>>>>
        chartDataMap = instance.chartDataByModulesOrAggregateNew(
            selectedModulePaths,
            selectedVariables,
            isMonthly,
            forecastSolutionSpaceNames,
            forecastResultsByModule,
            forecastResultsIds,
            shouldAggregate);

    // std::cout << chartDataMap << std::endl;
    std::cout << "Yes oooo yes oooo" << std::endl;

    return 0;
}

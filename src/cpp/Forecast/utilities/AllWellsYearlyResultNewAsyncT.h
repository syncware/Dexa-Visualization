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
#include "../JsonMapping/responseChatData.h"
//#include "../JsonMapping/payload.h"

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

    public:
        AllWellsYearlyResultNewAsyncT();
		~AllWellsYearlyResultNewAsyncT();
        json Plot(const json& jsonData);
};

AllWellsYearlyResultNewAsyncT::AllWellsYearlyResultNewAsyncT(){
}

AllWellsYearlyResultNewAsyncT::~AllWellsYearlyResultNewAsyncT(){

}

json AllWellsYearlyResultNewAsyncT::Plot(const json& jsonData){
    ChatPayload chatPayload = ConvertJsonToChatPayload(jsonData);
    vector<vector<ForecastResult>> WellsForecastResults;
    for(int i = 0; i < chatPayload.wells.size(); i++){
        WellsForecastResults.push_back( chatPayload.wells[i].resultWells);
    }
   
    bool isByYear = chatPayload.isByYear;
    bool isForChart = chatPayload.isForChart;
    dataPivoting _dataPivoting;
    vector<Date> dates =  _dataPivoting.GetListOfYears(WellsForecastResults, isByYear);
    vector<vector<ForecastResult>>  results 
    = _dataPivoting.GetYearlyForcastResultModulesLevel(WellsForecastResults, dates, 
    isByYear, isForChart);
    map<string, map<string, string>> resultsToMap = 
    reportJSON2.GetForecastOutputAsJson(results);
    ResponseChatData responseChatData;

    responseChatData.response = resultsToMap;

    json jsonResponseData = to_json(responseChatData);

    return jsonResponseData;
}
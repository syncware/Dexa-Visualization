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
#include <algorithm> // For std::find
#include <sstream>   // For std::stringstream
#include <unordered_map>
#include <map>
#include <numeric>
#include <iterator>
#include <ctime>
#include "../../nlohmann/json.hpp"
#include "../ProductionForecast/Forecast.h"
#include "ToJSON.h"
#include "../JsonMapping/napiToJson.h"
#include "../JsonMapping/person.h"
#include "../JsonMapping/responseChartData.h"
#include "../JsonMapping/forecastResultsByModule.h"
#include "../JsonMapping/chartInputPayload.h"
#include "AllWellsYearlyResultNewAsyncT.h"

using namespace std;
using namespace std::placeholders;
using json = nlohmann::json;

class PlotChartAsyncWorker : public Napi::AsyncWorker
{

    // Napi::Array wellDeckList;

public:
    ReportJSON reportJSON;
    AllWellsYearlyResultNewAsyncT allWellsYearlyResultNewAsyncT;
    PlotChartAsyncWorker(Napi::Object &wrappedInstance, Napi::Function callback)
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

        Napi::Array wrappedForecastResults = (wrappedInstance.Get(Napi::String::New(env, "forecastResults"))).As<Napi::Array>();
        Napi::Object wrappedChatInputData = (wrappedInstance.Get(Napi::String::New(env, "chatInputData"))).As<Napi::Object>();

        // json chartInputJsonData = reportJSON.NapiObjectToJson(wrappedChatInputData);
        // json forecastResultsJsonData = reportJSON.ConvertNapiArrayToJsonString(wrappedForecastResults);

        Napi::Object responseNapiObject =
            reportJSON.PlotChartAsync(env, wrappedForecastResults, wrappedChatInputData);
        std::cout << "responseNapiObject read " << std::endl;

        Callback().MakeCallback(Receiver().Value(), std::initializer_list<napi_value>{
                                                        env.Null(), responseNapiObject});
    }
};
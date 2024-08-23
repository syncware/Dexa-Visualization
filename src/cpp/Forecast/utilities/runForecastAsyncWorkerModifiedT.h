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
/* #include "../../MathematicsLibrary/MainSimplex.h"
#include "../../MathematicsLibrary/Integration.h"
#include "../ProductionForecast/Inputdeck.h"
#include "../ProductionForecast/Forecast.h"
#include "../ProductionForecast/DateCreation.h"
#include "../ProductionForecast/CalculateDeckVariables.h"
#include "../ProductionForecast/dataPivoting.h"
#include "ToJSON.h"
#include "../../MathematicsLibrary/Interception.h"
#include "../ProductionForecast/ExternalForecast.h"
#include "ConfigurePrioritization.h" */
#include "../JsonMapping/napiToJson.h"
#include "../JsonMapping/person.h"
//#include "../JsonMapping/payload.h"

using namespace std;
using namespace std::placeholders;
using json = nlohmann::json;

class RunForecastAsyncWorkerModifiedTest 
{

    public:
        RunForecastAsyncWorkerModifiedTest();
		~RunForecastAsyncWorkerModifiedTest();
        void RunForecast(const json& jsonData);
        //void RunForecast();
};

RunForecastAsyncWorkerModifiedTest::RunForecastAsyncWorkerModifiedTest(){
}

RunForecastAsyncWorkerModifiedTest::~RunForecastAsyncWorkerModifiedTest(){

}

void RunForecastAsyncWorkerModifiedTest::RunForecast(const json& jsonData){

    Payload payload = ConvertJsonToPayload(jsonData);
    Inputdeck deckobj;
    int nDecks = payload.decks.size();
    for(int i = 0; i < nDecks; i++){
        if(payload.decks[i].Description == "no error"){
            InputDeckStruct newDeck;
            deckobj.inputdecks.push_back(payload.decks[i]);
        }
    }
    int cc = 0;
    
}

        
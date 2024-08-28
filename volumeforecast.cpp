#include <napi.h>
#include "src/cpp/Forecast/ProductionForecast/DateCreation.h"
#include "src/cpp/Forecast/utilities/runForecastAsyncWorkerModifiedT.h"
#include "src/cpp/Forecast/utilities/runForecastAsyncWorker.h"
#include "src/cpp/Forecast/utilities/AllWellsYearlyResultNewAsyncT.h"
#include "src/cpp/Forecast/utilities/PlotChartAsyncWorker.h"


void getDays();
json ReadJsonFile(string jsonFileName);
void runForecast();
void export_to_file(const json& j, const string& filename);
void plotChat();
void plotChat2();

DateCreation dateCreation;


int main(){
    //getDays();
    //runForecast();
    plotChat2();
    return 0;
}

void getDays(){
    int month = 3;
    int days = dateCreation.DaysInMonth(month);
    int cc = 0;
}

json ReadJsonFile(string jsonFileName) {
    std::ifstream file(jsonFileName);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open JSON file");
    }

    json jsonData;
    file >> jsonData;
    file.close();

    return jsonData;
}

void runForecast() {
    json jsonData = ReadJsonFile("C:/Users/Gabriel.Achumba/Documents/Softwares/Newwayconsults/PetDigest/pet_app/files/forecast_input_data.json");
    RunForecastAsyncWorkerModifiedTest runForecastAsyncWorkerModifiedTest;
    json responseJsonData = runForecastAsyncWorkerModifiedTest.RunForecast(jsonData);
    export_to_file(responseJsonData, 
    "C:/Users/Gabriel.Achumba/Documents/Softwares/Newwayconsults/PetDigest/pet_app/files/forecast_output_data.json");
}

void plotChat() {
    json jsonData = ReadJsonFile("C:/Users/Gabriel.Achumba/Documents/Softwares/Newwayconsults/PetDigest/pet_app/forecast_chat_data_input.json");
    AllWellsYearlyResultNewAsyncT allWellsYearlyResultNewAsyncT;
    json responseJsonData = allWellsYearlyResultNewAsyncT.Plot(jsonData);
    export_to_file(responseJsonData, 
    "C:/Users/Gabriel.Achumba/Documents/Softwares/Newwayconsults/PetDigest/pet_app/forecast_chat_data_output.json");
}

void plotChat2() {
    json forecastResultsJsonData = ReadJsonFile("C:/Users/Gabriel.Achumba/Documents/Softwares/Newwayconsults/PetDigest/pet_app/files/apex-FG.forecast_forecastresultsbymodules.json");
    AllWellsYearlyResultNewAsyncT allWellsYearlyResultNewAsyncT;
    json chatInputJsonData = ReadJsonFile("C:/Users/Gabriel.Achumba/Documents/Softwares/Newwayconsults/PetDigest/pet_app/files/forecast_chat_data_input.json");
    json responseJsonData = 
    allWellsYearlyResultNewAsyncT.PlotChart(forecastResultsJsonData, chatInputJsonData);
    export_to_file(responseJsonData, 
    "C:/Users/Gabriel.Achumba/Documents/Softwares/Newwayconsults/PetDigest/pet_app/files/forecast_chat_data_output.json");
}



void export_to_file(const json& j, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4); // Pretty print with 4 spaces
        file.close();
        cout << "JSON saved to " << filename << endl;
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}


Napi::Value runForecastAsync(const Napi::CallbackInfo& info) {
     Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    Napi::Object wrappedInstance = info[0].As<Napi::Object>();
    Napi::Function callback = info[1].As<Napi::Function>();

    RunForecastAsyncWorker* asyncWorker = new RunForecastAsyncWorker(wrappedInstance, callback);
    asyncWorker->Queue();

    string msg = "runForecastAsync running...";

    return Napi::String::New(info.Env(), msg.c_str());

}

Napi::Value plotChartAsync(const Napi::CallbackInfo& info) {
     Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    Napi::Object wrappedInstance = info[0].As<Napi::Object>();
    Napi::Function callback = info[1].As<Napi::Function>();

    PlotChartAsyncWorker* asyncWorker = new PlotChartAsyncWorker(wrappedInstance, callback);
    asyncWorker->Queue();

    string msg = "plotChartAsync running...";

    return Napi::String::New(info.Env(), msg.c_str());

}


Napi::Object Init(Napi::Env env, Napi::Object exports){

    exports.Set(
		Napi::String::New(env, "runForecastAsync"), // property name => "runForecastAsync"
		Napi::Function::New(env, runForecastAsync)  //property value => 'runForecastAsync' function
	);

    exports.Set(
		Napi::String::New(env, "plotChartAsync"), // property name => "runForecastAsync"
		Napi::Function::New(env, plotChartAsync)  //property value => 'runForecastAsync' function
	);

	//return 'exports' object (always)
	return exports;
}

NODE_API_MODULE(volumeforecast, Init)
/* #include <napi.h> */
#include "src/cpp/Forecast/ProductionForecast/DateCreation.h"
#include "src/cpp/Forecast/utilities/runForecastAsyncWorkerModifiedT.h"
//#include "src/cpp/Forecast/utilities/runForecastAsyncWorker.h"

void getDays();
json ReadJsonFile(string jsonFileName);
void runForecast();

DateCreation dateCreation;


int main(){
    //getDays();
    runForecast();
    return 0;
}

void getDays(){
    int month = 3;
    int days = dateCreation.DaysInMonth(month);
    int cc = 0;
}

json ReadJsonFile(string jsonFileName) {
    // Open the JSON file
    //std::ifstream file(jsonFileName);
    std::ifstream file(jsonFileName);
    //std::ifstream file("/c/Users/Gabriel.Achumba/Documents/Softwares/Newwayconsults/PetDigest/pet_app/output.json");
    //std::ifstream file("C:\\Users\\Gabriel.Achumba\\Documents\\Softwares\\Newwayconsults\\PetDigest\\pet_app\\output.json");

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open JSON file");
    }

    // Parse the file using nlohmann::json
    json jsonData;
    file >> jsonData;
    file.close();

    return jsonData;
}

void runForecast() {
    json jsonData = ReadJsonFile("C:/Users/Gabriel.Achumba/Documents/Softwares/Newwayconsults/PetDigest/pet_app/inputdata.json");
    RunForecastAsyncWorkerModifiedTest runForecastAsyncWorkerModifiedTest;
    //Payload payload = ConvertJsonToPayload(jsonData);
    //Payload payload = jsonData.at("payload").get<Payload>();
    //Person person = jsonData.at("person").get<Person>();
    //Person person = ConvertJsonToPerson(jsonData);
    runForecastAsyncWorkerModifiedTest.RunForecast(jsonData);
    //DateCreation dateCreation;
    //int mth = 2;
    //int days = dateCreation.DaysInMonth(mth);
    int cc = 0;
}

/* Napi::Value runForecastAsync(const Napi::CallbackInfo& info) {
     Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    Napi::Object wrappedInstance = info[0].As<Napi::Object>();
    Napi::Function callback = info[1].As<Napi::Function>();

    RunForecastAsyncWorker* asyncWorker = new RunForecastAsyncWorker(wrappedInstance, callback);
    asyncWorker->Queue();

    string msg = "runForecastAsync running...";

    return Napi::String::New(info.Env(), msg.c_str());

}


Napi::Object Init(Napi::Env env, Napi::Object exports){

    exports.Set(
		Napi::String::New(env, "runForecastAsync"), // property name => "runForecastAsync"
		Napi::Function::New(env, runForecastAsync)  //property value => 'runForecastAsync' function
	);

	//return 'exports' object (always)
	return exports;
}

NODE_API_MODULE(volumeforecast, Init) */
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
#include "../Model.h"
#include "../../MathematicsLibrary/Models.h"
#include "ProdDataToJSON.h"
#include "../AssetExplorerGeneration.h"


using namespace std;
using namespace std::placeholders;


class AssetExplorerAsync : public Napi::AsyncWorker 
{
        
    public:
        AssetExplorerAsync(Napi::Object& wrappedInstance, Napi::Function callback)
            : AsyncWorker(callback)
        {
           
           Receiver().Set("wrappedInstance", wrappedInstance);
           
        }

    protected:
        void Execute() override {
            
        }

    private:
        void OnOK() override {
            string msg = "HistoryMatchAsync returning after 'working' ";
            //std::cout << "Seen it 3 " << std::endl;
            Napi::Env env = Env();
            Napi::HandleScope scope(env);
            Napi::Value value = Receiver().Get("wrappedInstance");
            //std::cout << "Seen 12 " << std::endl;
            Napi::Object wrappedInstance = value.As<Napi::Object>();
            //std::cout << "Seen 123 " << std::endl;

            vector<ProductionData> productionDataLits
            = prodDataToJSON.GetProductionDataList(wrappedInstance, env);

           vector<FieldProductionData> fields 
           = assetExplorerGeneration.CreateAssetsExplorer(productionDataLits);
            
            std::cout << "fields: " << fields.size() << std::endl;
            
            Napi::Object deckObject = prodDataToJSON.SetFieldExplorer(env, fields);

            Callback().MakeCallback(Receiver().Value(), std::initializer_list<napi_value>{
                env.Null(), deckObject
            });
         
        }

        ProdDataToJSON prodDataToJSON;
        AssetExplorerGeneration assetExplorerGeneration;
};
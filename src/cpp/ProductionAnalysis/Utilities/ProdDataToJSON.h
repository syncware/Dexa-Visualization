#pragma once

#include <napi.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include <exception>
#include "../Model.h"
#include "../../MathematicsLibrary/Models.h"

using namespace std;
using namespace std::placeholders;

class ProdDataToJSON {

    public:
        ProdDataToJSON();
        ~ProdDataToJSON();
        vector<ProductionData> GetProductionDataList(Napi::Object& wrappedObject, Napi::Env& env);
        Napi::Object SetFieldExplorer(Napi::Env& env, vector<FieldProductionData>& fields);
        Napi::Array SetReservoirExplorer(Napi::Env& env, vector<ReservoirProductionData>& reservoirs);
        Napi::Array SetDrainagePointExplorer(Napi::Env& env,
         vector<DrainagePointProductionData>& drainagePoints);
};

ProdDataToJSON::ProdDataToJSON(){

}

ProdDataToJSON::~ProdDataToJSON(){

}


vector<ProductionData> ProdDataToJSON::GetProductionDataList(Napi::Object& wrappedObject, Napi::Env& env)
{
    vector<ProductionData> productionDataList;
	Napi::Array listOfProductionData  = (wrappedObject.Get(Napi::String::New(env, "listOfProductionData"))).As<Napi::Array>();
   
	int lent1 = (int)listOfProductionData.Length();
	int i = 0;

	for(i = 0; i < lent1; i++)
	{
		Napi::Object wrappedProdData = ((Napi::Value)listOfProductionData[i]).As<Napi::Object>();
	
        ProductionData productionData;
        productionData.condensateGasRatio = (wrappedProdData.Get(Napi::String::New(env, "condensateGasRatio"))).As<Napi::Number>(); 
        //std::cout << "condensateGasRatio: " << std::endl;
        productionData.cumulativeGasInjected = (wrappedProdData.Get(Napi::String::New(env, "cumulativeGasInjected"))).As<Napi::Number>();
         //std::cout << "cumulativeGasInjected: " << std::endl;
        productionData.cumulativeGasProduced = (wrappedProdData.Get(Napi::String::New(env, "cumulativeGasProduced"))).As<Napi::Number>();
         //std::cout << "cumulativeGasProduced: " << std::endl;
        productionData.cumulativeOilProduced = (wrappedProdData.Get(Napi::String::New(env, "cumulativeOilProduced"))).As<Napi::Number>(); 
        //std::cout << "cumulativeOilProduced: " << std::endl;
        productionData.cumulativeWaterInjected = (wrappedProdData.Get(Napi::String::New(env, "cumulativeWaterInjected"))).As<Napi::Number>(); 
        productionData.cumulativeWaterProduced = (wrappedProdData.Get(Napi::String::New(env, "cumulativeWaterProduced"))).As<Napi::Number>(); 
        //productionData.date = (wrappedProdData.Get(Napi::String::New(env, "date"))).As<Napi::String>();
        productionData.drainagePoint = (wrappedProdData.Get(Napi::String::New(env, "drainagePoint"))).As<Napi::String>();
        productionData.field = (wrappedProdData.Get(Napi::String::New(env, "field"))).As<Napi::String>();
        productionData.lease = (wrappedProdData.Get(Napi::String::New(env, "lease"))).As<Napi::String>();
        productionData.monthlyGasCalendarDaysRate = (wrappedProdData.Get(Napi::String::New(env, "monthlyGasCalendarDaysRate"))).As<Napi::Number>(); 
        productionData.monthlyGasInjected = (wrappedProdData.Get(Napi::String::New(env, "monthlyGasInjected"))).As<Napi::Number>(); 
        productionData.monthlyGasInjectionCalendarDaysRate = (wrappedProdData.Get(Napi::String::New(env, "monthlyGasInjectionCalendarDaysRate"))).As<Napi::Number>(); 
        productionData.monthlyGasInjectionProdDaysRate = (wrappedProdData.Get(Napi::String::New(env, "monthlyGasInjectionProdDaysRate"))).As<Napi::Number>();
        productionData.monthlyGasProdDaysRate = (wrappedProdData.Get(Napi::String::New(env, "monthlyGasProdDaysRate"))).As<Napi::Number>();
        productionData.monthlyGasProduced = (wrappedProdData.Get(Napi::String::New(env, "monthlyGasProduced"))).As<Napi::Number>();
        productionData.monthlyLiquidCalendarDaysRate = (wrappedProdData.Get(Napi::String::New(env, "monthlyLiquidCalendarDaysRate"))).As<Napi::Number>();
        productionData.monthlyLiquidProdDaysRate = (wrappedProdData.Get(Napi::String::New(env, "monthlyLiquidProdDaysRate"))).As<Napi::Number>();
        productionData.monthlyLiquidProduced = (wrappedProdData.Get(Napi::String::New(env, "monthlyLiquidProduced"))).As<Napi::Number>();
        productionData.monthlyOilCalendarDaysRate = (wrappedProdData.Get(Napi::String::New(env, "monthlyOilCalendarDaysRate"))).As<Napi::Number>();
        productionData.monthlyOilProdDaysRate = (wrappedProdData.Get(Napi::String::New(env, "monthlyOilProdDaysRate"))).As<Napi::Number>();
        productionData.monthlyOilProduced = (wrappedProdData.Get(Napi::String::New(env, "monthlyOilProduced"))).As<Napi::Number>();
        productionData.monthlyProdBean = (wrappedProdData.Get(Napi::String::New(env, "monthlyProdBean"))).As<Napi::Number>();
        productionData.monthlyProdSand = (wrappedProdData.Get(Napi::String::New(env, "monthlyProdSand"))).As<Napi::Number>();
        productionData.monthlyProdTHP = (wrappedProdData.Get(Napi::String::New(env, "monthlyProdTHP"))).As<Napi::Number>();
        productionData.monthlyWaterCalendarDaysRate = (wrappedProdData.Get(Napi::String::New(env, "monthlyWaterCalendarDaysRate"))).As<Napi::Number>();
        productionData.monthlyWaterInjected = (wrappedProdData.Get(Napi::String::New(env, "monthlyWaterInjected"))).As<Napi::Number>();
        productionData.monthlyWaterInjectionCalendarDaysRate = (wrappedProdData.Get(Napi::String::New(env, "monthlyWaterInjectionCalendarDaysRate"))).As<Napi::Number>();
        productionData.monthlyWaterInjectionProdDaysRate = (wrappedProdData.Get(Napi::String::New(env, "monthlyWaterInjectionProdDaysRate"))).As<Napi::Number>();
        productionData.monthlyWaterProdDaysRate = (wrappedProdData.Get(Napi::String::New(env, "monthlyWaterProdDaysRate"))).As<Napi::Number>();
        productionData.monthlyWaterProduced = (wrappedProdData.Get(Napi::String::New(env, "monthlyWaterProduced"))).As<Napi::Number>();
        productionData.prodDays = (wrappedProdData.Get(Napi::String::New(env, "prodDays"))).As<Napi::Number>();
        productionData.prodGOR = (wrappedProdData.Get(Napi::String::New(env, "prodGOR"))).As<Napi::Number>();
        productionData.reservoir = (wrappedProdData.Get(Napi::String::New(env, "reservoir"))).As<Napi::String>();
        productionData.tubingString = (wrappedProdData.Get(Napi::String::New(env, "string"))).As<Napi::String>(); 
        productionData.waterCut = (wrappedProdData.Get(Napi::String::New(env, "waterCut"))).As<Napi::Number>(); 
        productionData.waterGasRatio = (wrappedProdData.Get(Napi::String::New(env, "waterGasRatio"))).As<Napi::Number>();

        /* tm tm1;
		sscanf(productionData.date.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
        productionData.day = tm1.tm_mday;
        productionData.month = tm1.tm_mon;
        productionData.year = tm1.tm_year; */

        productionDataList.push_back(productionData);
	}

	return productionDataList;
}

Napi::Array ProdDataToJSON::SetDrainagePointExplorer(Napi::Env& env,
vector<DrainagePointProductionData>& drainagePoints){
    
    int nDrainagePoints = drainagePoints.size();
    std::cout << "nDrainagePoints: " << nDrainagePoints << std::endl;

	Napi::Array listOfDrainagePoints = Napi::Array::New(env);
	int i = 0;
	for(i = 0; i < nDrainagePoints; i++){
		
        std::cout << "Drainage Point Seen 1" << std::endl;
        Napi::Object drainagePoint = Napi::Object::New(env);

		drainagePoint.Set(Napi::String::New(env, "label"),
         Napi::String::New(env, drainagePoints[i].label));
         drainagePoint.Set(Napi::String::New(env, "icon"),
         Napi::String::New(env, drainagePoints[i].icon));

        drainagePoint.Set(Napi::String::New(env, "listOfProductionData"),
         Napi::String::New(env, drainagePoints[i].productionDataList));

         std::cout << "Drainage Point Seen 2" << std::endl;
		
        listOfDrainagePoints.Set(Napi::String::New(env, drainagePoints[i].label), drainagePoint);
	}
    
    std::cout << "Drainage Point Seen 3" << std::endl;
	return listOfDrainagePoints;
}

Napi::Array ProdDataToJSON::SetReservoirExplorer(Napi::Env& env, vector<ReservoirProductionData>& reservoirs){

     int nReservoirs = reservoirs.size();
    std::cout << "nReservoirs; " << nReservoirs << std::endl;

	Napi::Array listOfReservoirs = Napi::Array::New(env);
	int i = 0;
	for(i = 0; i < nReservoirs; i++){
		
        std::cout << "Reservoir Seen 1" << std::endl;
        Napi::Object reservoir = Napi::Object::New(env);

		Napi::Array drainagePoints = SetDrainagePointExplorer(env, reservoirs[i].children);
        std::cout << "Reservoir Seen 2" << std::endl;
		reservoir.Set(Napi::String::New(env, "label"), Napi::String::New(env, reservoirs[i].label));
        reservoir.Set(Napi::String::New(env, "icon"), Napi::String::New(env, reservoirs[i].icon));
        reservoir.Set(Napi::String::New(env, "children"), drainagePoints);
		
        std::cout << "Reservoir Seen 3" << std::endl;
        listOfReservoirs.Set(Napi::String::New(env, reservoirs[i].label), reservoir);
	}

    std::cout << "Reservoir Seen 4" << std::endl;
	return listOfReservoirs;
}

Napi::Object ProdDataToJSON::SetFieldExplorer(Napi::Env& env, vector<FieldProductionData>& fields){
    
    int nFields = fields.size();

	Napi::Array listOfFields = Napi::Array::New(env);
	int i = 0;
	for(i = 0; i < nFields; i++){
		
        std::cout << "field Seen 1" << std::endl;
        Napi::Object field = Napi::Object::New(env);

		Napi::Array reservoirs = SetReservoirExplorer(env, fields[i].children);

        std::cout << "field Seen 2" << std::endl;

		field.Set(Napi::String::New(env, "label"), Napi::String::New(env, fields[i].label));
        field.Set(Napi::String::New(env, "icon"), Napi::String::New(env, fields[i].icon));
        field.Set(Napi::String::New(env, "children"), reservoirs);
		
        std::cout << "field Seen 3" << std::endl;
        listOfFields.Set(Napi::String::New(env, fields[i].label), field);

        std::cout << "field Seen 4" << std::endl;
	}

    Napi::Object assetExplorer = Napi::Object::New(env);
    assetExplorer.Set(Napi::String::New(env, "listOfFields"), listOfFields);
    std::cout << "field Seen 5" << std::endl;
	return assetExplorer;
}



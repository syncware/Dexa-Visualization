#pragma once
/* #include <napi.h> */
// #include "node_modules/node-addon-api/napi.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include <exception>
#include <tuple>
#include "../ProductionForecast/Forecast.h"
#include "../../nlohmann/json.hpp"
#include "../ProductionForecast/Inputdeck.h"
Inputdeck inputdeck2;

using namespace std;
using json = nlohmann::json;


void from_json(const json& j, InternalExternalEquipmentName& deck) {
    j.at("externalEquipmentName").get_to(deck.externalEquipmentName);
    j.at("internalEquipmentName").get_to(deck.internalEquipmentName);
    j.at("equipmentType").get_to(deck.equipmentType);
    inputdeck2.ToLower(deck.equipmentType);
}

/* vector<InternalExternalEquipmentName> GetInternalExternalEquipmentNames(Napi::Array& wrappedDecks,
	int nInternalExternalFacilitiesNames, Napi::Env& env) {

    vector<InternalExternalEquipmentName> internalExternalEquipmentNames;


    for (int i = 0; i < nInternalExternalFacilitiesNames; i++) {
        Napi::Object wrappedDeck = wrappedDecks.Get(i).As<Napi::Object>();
	
        InternalExternalEquipmentName internalExternalEquipmentName;
		internalExternalEquipmentName.externalEquipmentName = (wrappedDeck.Get(Napi::String::New(env, "externalEquipmentName"))).As<Napi::String>();
		internalExternalEquipmentName.internalEquipmentName = (wrappedDeck.Get(Napi::String::New(env, "internalEquipmentName"))).As<Napi::String>();
		internalExternalEquipmentName.equipmentType = (wrappedDeck.Get(Napi::String::New(env, "equipmentType"))).As<Napi::String>();
		inputdeck2.ToLower(internalExternalEquipmentName.equipmentType);
		internalExternalEquipmentNames.push_back(internalExternalEquipmentName);

    }

    return internalExternalEquipmentNames;

} */
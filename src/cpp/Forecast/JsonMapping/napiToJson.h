#pragma once

#include "../../nlohmann/json.hpp"
#include "payload.h"
#include "chatPayload.h"
#include "person.h"


using namespace std;
using json = nlohmann::json;

// Function to convert Napi::Object to nlohmann::json

Payload ConvertJsonToPayload(json jsonData){
    Payload payload = jsonData.at("payload").get<Payload>();
    return payload;
}

ChatPayload ConvertJsonToChatPayload(json jsonData){
    ChatPayload chatPayload = jsonData.at("chatPayload").get<ChatPayload>();
    return chatPayload;
}

Person ConvertJsonToPerson(json jsonData){
    Person person = jsonData.at("person").get<Person>();
    return person;
}
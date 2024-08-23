#pragma once

#include "../ProductionForecast/Forecast.h"
#include "address.h"
#include "../../nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

void from_json(const json& j, Person& person) {
    j.at("name").get_to(person.name);
    j.at("age").get_to(person.age);
    j.at("address").get_to(person.address);  // This will call the Address from_json automatically
    j.at("hobbies").get_to(person.hobbies);
}
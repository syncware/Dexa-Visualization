#pragma once

#include <iostream>
#include <string>
#include "../../nlohmann/json.hpp"
// #include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

class MyClass {
public:
    void processJson(const json& data);
};
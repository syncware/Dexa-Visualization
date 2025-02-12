#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <time.h>
#include <iomanip>
#include <functional>

using namespace std;


typedef struct _LinearProgrammingResult
{
    vector<double> raw;
    vector<double> refined;
    vector<string> variables;
    vector<int> indices;
}LinearProgrammingResult;
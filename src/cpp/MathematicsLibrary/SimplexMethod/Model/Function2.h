#pragma once


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Function2
{
private:

public:
    Function2();
    Function2(vector<double>& variables, const double& c, const bool& isExtrMax);

    vector<double> variables;
    double c;
    bool isExtrMax;
};

Function2::Function2()
{
}

Function2::Function2(vector<double>& _variables, const double& _c, const bool& _isExtrMax)
{
    variables = _variables;
    c = _c;
    isExtrMax = _isExtrMax;
}

#pragma once


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Funct
{
private:

public:
    Funct();
    Funct(vector<double>& variables, double& cc, bool& isExtrMax);

    vector<double> variables;
    double cc;
    bool isExtrMax;
};

Funct::Funct()
{
}

Funct::Funct(vector<double>& _variables, double& _cc, bool& _isExtrMax)
{
    variables = _variables;
    cc = _cc;
    isExtrMax = _isExtrMax;
}

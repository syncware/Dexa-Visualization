#pragma once


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Constraint
{
private:

public:
    Constraint(vector<double>& variables, double& b, string& sign);
    vector<double> variables;
    double b;
    string sign;
};

Constraint::Constraint(vector<double>& _variables, double& _b, string& _sign)
{
    if (_sign == "=" || _sign == "<=" || _sign == ">=")
    {
        variables = _variables;
        b = _b;
        sign = _sign;

    }
    else
    {
        fprintf(stderr, "...Wrong sign...\n");
        exit(1);

    }
}
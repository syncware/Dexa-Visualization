#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Constraint2
{
private:
public:
    Constraint2(vector<double> &variables, const double &b, const string &sign);
    vector<double> variables;
    double b;
    string sign;
};

Constraint2::Constraint2(vector<double> &_variables, const double &_b, const string &_sign)
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
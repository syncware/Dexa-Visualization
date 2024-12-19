#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include <math.h>
#include "NonLinearEquations.h"
#include "Interpolation.h"

using namespace std;

class Interception
{
private:
    NonLinearEquations nonLinearEquations;
    Interpolation interpolation;

public:
    Interception();
    vector<double> Xs1;
    vector<double> Ys1;
    vector<double> Xs2;
    vector<double> Ys2;
    vector<double> intercept();
    double objectiveFunction(double x);
    ~Interception();
};

Interception::Interception()
{
}

Interception::~Interception()
{
}

double Interception::objectiveFunction(double x)
{
    // std::cout << "x " << x << std::endl;
    // std::cout << "Xs1 size " << Xs1.size() << std::endl;
    // std::cout << "Ys1 size " << Ys1.size() << std::endl;
    double yline1 = interpolation.LinearInterpolation(Xs1, Ys1, x);
    // std::cout << "yline1 " << yline1 << std::endl;
    double yline2 = interpolation.LinearInterpolation(Xs2, Ys2, x);
    // std::cout << "yline2 " << yline2 << std::endl;
    double diff = abs(yline1 - yline2);
    return diff;
}

vector<double> Interception::intercept()
{
    Interception obj;
    obj.Xs1 = Xs1;
    obj.Ys1 = Ys1;
    obj.Xs2 = Xs2;
    obj.Ys2 = Ys2;
    double yAns = 0;
    double xAns = 0;
    vector<double> ans;
    double x0 = Xs1[0];
    // std::cout << "x0 " << x0 << std::endl;
    auto fp = bind(&Interception::objectiveFunction, obj, std::placeholders::_1);
    xAns = nonLinearEquations.NewtonRaphson(fp, x0);
    yAns = interpolation.LinearInterpolation(Xs1, Ys1, xAns);
    ans.push_back(xAns);
    ans.push_back(yAns);
    return ans;
}
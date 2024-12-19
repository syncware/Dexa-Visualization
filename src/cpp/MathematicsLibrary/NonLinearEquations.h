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
#include "Differentiation.h"

using namespace std;

class NonLinearEquations
{
private:
    Differentiation differentiation;

public:
    NonLinearEquations();
    double NewtonRaphson(function<double(double)> fun, double &x0);
    ~NonLinearEquations();
};

NonLinearEquations::NonLinearEquations()
{
}

NonLinearEquations::~NonLinearEquations()
{
}

double NonLinearEquations::NewtonRaphson(function<double(double)> fun, double &x0)
{
    double Tol = 10E-6;
    int MaxtIter = 100;
    double diff = 0;
    double x1 = x0;
    double StepSize = 0;
    double ARE = 10000, Tol2 = abs(Tol * 100.0);
    int i = 0;

    std::cout << "MaxtIter " << MaxtIter << std::endl;
    std::cout << "x0 " << x0 << std::endl;

    for (i = 0; i <= MaxtIter; i++)
    {
        StepSize = x0 / pow(10, 3);

        diff = differentiation.Central(fun,
                                       x0, StepSize);

        if (diff == 0)
        {
            diff = 10E-5;
        }

        x1 = x0 - fun(x0) / diff;

        ARE = abs((x1 - x0) / x1) * 100.0;

        if (ARE > Tol2)
        {
            x0 = x1;
        }
        else
        {
            break;
        }
    }

    return x0;
}

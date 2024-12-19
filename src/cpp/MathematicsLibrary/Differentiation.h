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

using namespace std;

class Differentiation
{
private:
public:
    Differentiation();
    double Central(function<double(double)> &fun, double &x, double &stepsize);
    ~Differentiation();
};

Differentiation::Differentiation()
{
}

Differentiation::~Differentiation()
{
}

double Differentiation::Central(function<double(double)> &fun, double &x, double &stepsize)
{
    double Av, x1 = 0, x2 = 0;
    x1 = x + stepsize;
    x2 = x - stepsize;
    // std::cout << "x1 " << x1 << std::endl;
    // std::cout << "x2 " << x2 << std::endl;
    Av = (fun(x1) - fun(x2)) / (2 * stepsize);
    return Av;
}
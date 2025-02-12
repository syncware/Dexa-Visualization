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

class  Interpolation
{
private:

public:
	Interpolation();
    double LinearInterpolation(vector<double>& Xs, vector<double>& Ys, double& X);
    double LinearInterpolation(double& X1, double& X2, double& Y1, double& Y2, double& X);
	~Interpolation();

};

Interpolation::Interpolation()
{

}

Interpolation::~Interpolation()
{

}

double Interpolation::LinearInterpolation(double& X1, double& X2, double& Y1, double& Y2, double& X)
{
    double denom = X2 - X1;
    if(denom == 0)
    {
        return Y2;
    }

    double m = (Y2 - Y1) / denom;
    double c = Y1;
    double x = X - X1;

    double Y = m * x + c;

    return Y;
}

double Interpolation::LinearInterpolation(vector<double>& Xs, vector<double>& Ys, double& X)
{
    int i = 0, ii = 0; bool check = false;
    double Y = Ys[0];
    int XsCount = Xs.size();
   // std::cout << "XsCount " << XsCount << std::endl;

    for (i = 1; i < XsCount; i++)
    {
        if (X >= Xs[i - 1] && X <= Xs[i])
        {
            ii = i;
            check = true;
           // std::cout << "ii " << ii << std::endl;
            break;
        }
    }

    if (check == true)
    {
        Y = LinearInterpolation(Xs[ii - 1], Xs[ii], Ys[ii - 1], Ys[ii], X);
        /* 
        double m = (Ys[ii] - Ys[ii - 1]) / (Xs[ii] - Xs[ii - 1]);
        double c = Ys[ii - 1];
        double x = X - Xs[ii - 1];

        Y = m * x + c; 
        */
    }

    return Y;
}
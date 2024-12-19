#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <math.h>
#include "Forecast.h"

using namespace std;

class FractionalFlow
{
private:
public:
    FractionalFlow();
    ~FractionalFlow();

    double Get_Fractional_Rate_Of_Change_Exponential(double &X_init, double &X_last,
                                                     double &Y_init, double &Y_last, double &cumDays, bool &isRateCum, bool &isLinear);

    double Get_Fractional_Flow(double &Fractional_Rate_Of_Change,
                               double &X_init, double &X_last, double &Y_init, double &cumDays,
                               bool &isRateCum, bool &isLinear);
};

FractionalFlow::FractionalFlow()
{
}

FractionalFlow::~FractionalFlow()
{
}

double FractionalFlow::Get_Fractional_Rate_Of_Change_Exponential(double &X_init,
                                                                 double &X_last, double &Y_init, double &Y_last, double &cumDays, bool &isRateCum, bool &isLinear)
{
    if (Y_init == 0)
        Y_init = 0.00000001;

    double numerator = 0;
    double Fractional_Rate_Of_Change = 0;

    if (Y_init != 0)
    {
        numerator = (Y_last / Y_init);
    }
    else
    {
        return Fractional_Rate_Of_Change;
    }

    double denominator = X_last - X_init;
    if (isRateCum == false)
    {
        denominator = cumDays;
    }

    if (denominator != 0 && numerator > 0)
    {
        Fractional_Rate_Of_Change = log(numerator) / denominator;
    }

    if (isLinear == true)
    {
        Fractional_Rate_Of_Change = (Y_last - Y_init) / denominator;
    }

    return Fractional_Rate_Of_Change;
}

double FractionalFlow::Get_Fractional_Flow(double &Fractional_Rate_Of_Change, double &X_init,
                                           double &X_last, double &Y_init, double &cumDays, bool &isRateCum, bool &isLinear)
{
    double Y = 0;
    if (isRateCum)
    {
        Y = Y_init * exp(Fractional_Rate_Of_Change * (X_last - X_init));
    }
    else
    {

        if (isLinear == true)
        {
            Y = Y_init + (Fractional_Rate_Of_Change * cumDays);
        }
        else
        {
            Y = Y_init * exp(Fractional_Rate_Of_Change * cumDays);
        }
    }

    return Y;
}
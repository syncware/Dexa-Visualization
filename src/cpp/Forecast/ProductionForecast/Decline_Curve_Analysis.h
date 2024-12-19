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
#include "Forecast.h"

using namespace std;

class Decline_Curve_Analysis
{
private:
public:
    Decline_Curve_Analysis();
    ~Decline_Curve_Analysis();

    double Get_DeclineFactor_Exponential(double &Initial_Rate, double &Aband_Rate, double &Init_Cum_Prod, double &UR);
    double Get_DeclineFactor(double &Initial_Rate, double &Aband_Rate,
                             double &Init_Cum_Prod, double &UR, int &Method, double &cumProdDays, bool &isRateCum);
    double Get_DeclineFactor_Harmonic(double &Initial_Rate, double &Aband_Rate, double &Init_Cum_Prod, double &UR);
    double Get_DCA_Exponential(double &Initial_Rate, double &Rate_Of_Change, double &Cum_Prod);
    double Get_DCA_Hyperbolic(double &Initial_Rate, double &Rate_Of_Change, double &Cum_Prod,
                              double &Decline_Exponent);
    double Get_DCA_Hyperbolic_TimeCum(double &Initial_Rate, double &Rate_Of_Change, double &CumDays,
                                      double &Decline_Exponent);
    double Get_DCA_Harmonic(double &Initial_Rate, double &Rate_Of_Change, double &Cum_Prod);
    double Get_DCA_Exponential2(double &Initial_Rate, double &Rate_Of_Change, double &ProductionDays);

    double Get_DCA(double &Initial_Rate, double &Rate_Of_Change, double &Cum_Prod,
                   int &Method, double &Decline_Exponent, double &cumDays, bool &isRateCum);

    double Get_DCA2(double &Initial_Rate, double &Rate_Of_Change, double &ProductionDays, int &Method);
    double Get_DCA_Exponential_CumDays(double &Initial_Rate, double &Rate_Of_Change,
                                       double &cumDays);

    double Get_DeclineFactor_Exponential_CumProdDays(double &Initial_Rate,
                                                     double &Aband_Rate, double &cumProdDays);
};

Decline_Curve_Analysis::Decline_Curve_Analysis()
{
}

Decline_Curve_Analysis::~Decline_Curve_Analysis()
{
}

// double Decline_Curve_Analysis::initial_rate = 0;

double Decline_Curve_Analysis::Get_DeclineFactor_Exponential(double &Initial_Rate, double &Aband_Rate, double &Init_Cum_Prod, double &UR)
{

    double DeclineFactor = (Initial_Rate - Aband_Rate) / (UR - Init_Cum_Prod);

    return DeclineFactor;
}

double Decline_Curve_Analysis::Get_DeclineFactor_Exponential_CumProdDays(double &Initial_Rate,
                                                                         double &Aband_Rate, double &cumProdDays)
{

    double numerator = 0;
    double DeclineFactor = 0;

    numerator = (Aband_Rate / Initial_Rate);

    double denominator = cumProdDays;

    if (denominator != 0 && numerator > 0)
    {
        DeclineFactor = log(numerator) / denominator;
    }

    return -1 * DeclineFactor;
}

double Decline_Curve_Analysis::Get_DeclineFactor(double &Initial_Rate, double &Aband_Rate, double &Init_Cum_Prod, double &UR,
                                                 int &Method, double &cumProdDays, bool &isRateCum)
{
    double DeclineFactor = 0;

    switch (Method)
    {
    case 1:
        if (isRateCum)
        {
            DeclineFactor = Get_DeclineFactor_Exponential(Initial_Rate, Aband_Rate, Init_Cum_Prod, UR);
        }
        else
        {
            DeclineFactor = Get_DeclineFactor_Exponential_CumProdDays(Initial_Rate,
                                                                      Aband_Rate, cumProdDays);
        }
        break;

    case 2:
        DeclineFactor = Get_DeclineFactor_Exponential(Initial_Rate, Aband_Rate, Init_Cum_Prod, UR);
        break;

    case 3:
        DeclineFactor = Get_DeclineFactor_Harmonic(Initial_Rate, Aband_Rate, Init_Cum_Prod, UR);
        break;
    }

    return DeclineFactor;
}

double Decline_Curve_Analysis::Get_DeclineFactor_Harmonic(double &Initial_Rate, double &Aband_Rate, double &Init_Cum_Prod, double &UR)
{
    if (Aband_Rate == 0)
    {
        Aband_Rate = 0.00001;
    }

    double DeclineFactor = (Initial_Rate / (UR - Init_Cum_Prod)) * log(Initial_Rate / Aband_Rate);

    return DeclineFactor;
}

double Decline_Curve_Analysis::Get_DCA_Exponential(double &Initial_Rate, double &Rate_Of_Change, double &Cum_Prod)
{
    double Current_Rate = Initial_Rate - Rate_Of_Change * Cum_Prod;

    return Current_Rate;
}

double Decline_Curve_Analysis::Get_DCA_Exponential_CumDays(double &Initial_Rate, double &Rate_Of_Change,
                                                           double &cumDays)
{
    double Current_Rate = Initial_Rate * exp(-1 * Rate_Of_Change * cumDays);

    return Current_Rate;
}

double Decline_Curve_Analysis::Get_DCA_Hyperbolic(double &Initial_Rate, double &Rate_Of_Change, double &Cum_Prod,
                                                  double &Decline_Exponent)
{
    double OneMinusDeclineExponet = 1 - Decline_Exponent;
    double DeclineExponetMinusOne = Decline_Exponent - 1;
    double term2 = pow(Initial_Rate, OneMinusDeclineExponet);
    double term3 = pow(Initial_Rate, Decline_Exponent);
    double term4 = 0;
    if (term3 != 0)
    {
        term4 = Cum_Prod * DeclineExponetMinusOne * Rate_Of_Change / term3;
    }
    double term1 = term2 + term4;
    double Current_Rate = pow(term1, (1 / OneMinusDeclineExponet));

    return Current_Rate;
}

double Decline_Curve_Analysis::Get_DCA_Hyperbolic_TimeCum(double &Initial_Rate, double &Rate_Of_Change, double &CumDays,
                                                          double &Decline_Exponent)
{
    double term1 = 1 + (Decline_Exponent * Rate_Of_Change * CumDays);
    double DeclineExponet = 0;
    if (Decline_Exponent != 0)
    {
        DeclineExponet = 1 / Decline_Exponent;
    }
    double denominator = pow(term1, DeclineExponet);
    double Current_Rate = 0;
    if (denominator != 0)
    {
        Current_Rate = Initial_Rate / denominator;
    }

    return Current_Rate;
}

double Decline_Curve_Analysis::Get_DCA_Harmonic(double &Initial_Rate, double &Rate_Of_Change, double &Cum_Prod)
{
    double term1 = exp(Cum_Prod * Rate_Of_Change / Initial_Rate);
    double Current_Rate = 0;
    if (term1 != 0)
    {
        Current_Rate = Initial_Rate / term1;
    }

    return Current_Rate;
}

double Decline_Curve_Analysis::Get_DCA_Exponential2(double &Initial_Rate, double &Rate_Of_Change, double &ProductionDays)
{
    double Current_Rate = Initial_Rate * exp(-1 * Rate_Of_Change * ProductionDays);

    return Current_Rate;
}

double Decline_Curve_Analysis::Get_DCA(double &Initial_Rate, double &Rate_Of_Change,
                                       double &Cum_Prod, int &Method, double &Decline_Exponent, double &cumDays, bool &isRateCum)
{
    double rate = 0;

    switch (Method)
    {
    case 1:
        if (isRateCum)
        {
            rate = Get_DCA_Exponential(Initial_Rate, Rate_Of_Change, Cum_Prod);
        }
        else
        {
            rate = Get_DCA_Exponential_CumDays(Initial_Rate, Rate_Of_Change, cumDays);
        }
        break;

    case 2:
        if (isRateCum)
        {
            rate = Get_DCA_Hyperbolic(Initial_Rate, Rate_Of_Change, Cum_Prod, Decline_Exponent);
        }
        else
        {
            rate = Get_DCA_Hyperbolic_TimeCum(Initial_Rate, Rate_Of_Change, cumDays, Decline_Exponent);
        }
        break;

    case 3:
        rate = Get_DCA_Harmonic(Initial_Rate, Rate_Of_Change, Cum_Prod);
        break;
    }

    return rate;
}

double Decline_Curve_Analysis::Get_DCA2(double &Initial_Rate, double &Rate_Of_Change, double &ProductionDays, int &Method)
{
    double rate = 0;

    switch (Method)
    {
    case 1:
        rate = Get_DCA_Exponential2(Initial_Rate, Rate_Of_Change, ProductionDays);
        break;

    case 2:
        break;

    case 3:
        break;
    }

    return rate;
}
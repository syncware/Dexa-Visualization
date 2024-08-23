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

class  Decline_Curve_Analysis
{
private:

public:
	Decline_Curve_Analysis();
	~Decline_Curve_Analysis();

	double Get_DeclineFactor_Exponential(double& Initial_Rate, double& Aband_Rate, double& Init_Cum_Prod, double& UR);
    double Get_DeclineFactor(double& Initial_Rate, double& Aband_Rate, double& Init_Cum_Prod, double& UR, int& Method);
    double Get_DeclineFactor_Harmonic(double& Initial_Rate, double& Aband_Rate, double& Init_Cum_Prod, double& UR);
	double Get_DCA_Exponential(double& Initial_Rate, double& Rate_Of_Change, double& Cum_Prod);
    double Get_DCA_Hyperbolic(double& Initial_Rate, double& Rate_Of_Change, double& Cum_Prod, 
        double& Decline_Exponent);
    double Get_DCA_Harmonic(double& Initial_Rate, double& Rate_Of_Change, double& Cum_Prod);
	double Get_DCA_Exponential2(double& Initial_Rate, double& Rate_Of_Change, double& ProductionDays);

	double Get_DCA(double& Initial_Rate, double& Rate_Of_Change, double& Cum_Prod,  int& Method, double& Decline_Exponent);

	double Get_DCA2(double& Initial_Rate, double& Rate_Of_Change, double& ProductionDays,  int& Method);

};


Decline_Curve_Analysis::Decline_Curve_Analysis()
{

}

Decline_Curve_Analysis::~Decline_Curve_Analysis()
{

}

//double Decline_Curve_Analysis::initial_rate = 0;

double Decline_Curve_Analysis::Get_DeclineFactor_Exponential(double& Initial_Rate, double& Aband_Rate, double& Init_Cum_Prod, double& UR)
{

	double DeclineFactor = (Initial_Rate - Aband_Rate) / (UR - Init_Cum_Prod);

	return DeclineFactor;
}

double Decline_Curve_Analysis::Get_DeclineFactor(double& Initial_Rate, double& Aband_Rate, double& Init_Cum_Prod, double& UR,
        int& Method)
{
    double DeclineFactor = 0;

    switch (Method)
    {
    case 1:
        DeclineFactor = Get_DeclineFactor_Exponential(Initial_Rate, Aband_Rate, Init_Cum_Prod, UR);
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


double Decline_Curve_Analysis::Get_DeclineFactor_Harmonic(double& Initial_Rate, double& Aband_Rate, double& Init_Cum_Prod, double& UR)
{
    if(Aband_Rate == 0)
    {
        Aband_Rate = 0.00001;
    }

	double DeclineFactor = (Initial_Rate/ (UR - Init_Cum_Prod)) * log(Initial_Rate / Aband_Rate);

	return DeclineFactor;
}

double Decline_Curve_Analysis::Get_DCA_Exponential(double& Initial_Rate, double& Rate_Of_Change, double& Cum_Prod)
{
	double Current_Rate = Initial_Rate - Rate_Of_Change * Cum_Prod;

	return Current_Rate;
}

double Decline_Curve_Analysis::Get_DCA_Hyperbolic(double& Initial_Rate, double& Rate_Of_Change, double& Cum_Prod, 
        double& Decline_Exponent)
{
    double OneMinusDeclineExponet = 1 - Decline_Exponent;
    double DeclineExponetMinusOne = Decline_Exponent - 1;
    double term2 = pow(Initial_Rate, OneMinusDeclineExponet);
    double term3 = pow(Initial_Rate, Decline_Exponent);
    double term4 = 0;
    if(term3 != 0)
    {
       term4 =  Cum_Prod * DeclineExponetMinusOne * Rate_Of_Change/term3;
    }
    double term1 = term2 + term4;
	double Current_Rate = pow(term1, (1/OneMinusDeclineExponet));

	return Current_Rate;
}


double Decline_Curve_Analysis::Get_DCA_Harmonic(double& Initial_Rate, double& Rate_Of_Change, double& Cum_Prod)
{
    double term1 = exp(Cum_Prod * Rate_Of_Change / Initial_Rate);
	double Current_Rate = 0;
    if(term1 != 0)
    {
        Current_Rate = Initial_Rate / term1;
    }

	return Current_Rate;
}


double Decline_Curve_Analysis::Get_DCA_Exponential2(double& Initial_Rate, double& Rate_Of_Change, double& ProductionDays)
{
    double Current_Rate = Initial_Rate * exp(-1 * Rate_Of_Change * ProductionDays);

    return Current_Rate;
}

double Decline_Curve_Analysis::Get_DCA(double& Initial_Rate, double& Rate_Of_Change,
 double& Cum_Prod, int& Method,  double& Decline_Exponent)
{
    double rate = 0;

    switch (Method)
    {
    case 1:
        rate = Get_DCA_Exponential(Initial_Rate, Rate_Of_Change, Cum_Prod);
        break;

    case 2:
        rate = Get_DCA_Hyperbolic(Initial_Rate, Rate_Of_Change, Cum_Prod, Decline_Exponent);
        break;
        
    case 3:
        rate = Get_DCA_Harmonic(Initial_Rate, Rate_Of_Change, Cum_Prod);
        break;
    }
   

    return rate;
}

double Decline_Curve_Analysis::Get_DCA2(double& Initial_Rate, double& Rate_Of_Change, double& ProductionDays, int& Method)
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
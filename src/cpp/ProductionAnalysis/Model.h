#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <time.h>
#include <iomanip>
#include <functional>

using namespace std;

typedef struct _ProductionData
{
    string lease;
    string field;
    string reservoir;
    string tubingString;
    string drainagePoint;
    string date;
    int day;
    int month;
    int year;
    double monthlyOilProduced;
    double monthlyGasProduced;
    double monthlyWaterProduced;
    double monthlyGasInjected;
    double monthlyWaterInjected;
    double monthlyLiquidProduced;

    double monthlyOilProdDaysRate;
    double monthlyGasProdDaysRate;
    double monthlyWaterProdDaysRate;
    double monthlyLiquidProdDaysRate;
    double monthlyGasInjectionProdDaysRate;
    double monthlyWaterInjectionProdDaysRate;

    double monthlyOilCalendarDaysRate;
    double monthlyGasCalendarDaysRate;
    double monthlyWaterCalendarDaysRate;
    double monthlyLiquidCalendarDaysRate;
    double monthlyGasInjectionCalendarDaysRate;
    double monthlyWaterInjectionCalendarDaysRate;

    double prodDays;
    double cumulativeOilProduced;
    double cumulativeGasProduced;
    double cumulativeWaterProduced;
    double cumulativeWaterInjected;
    double cumulativeGasInjected;

    double waterCut;
    double prodGOR;
    double waterGasRatio;
    double condensateGasRatio;
    double monthlyProdTHP;
    double monthlyProdBean;
    double monthlyProdSand;
}ProductionData;

typedef struct _DrainagePointProductionData
{
    string label;
    string icon;
    string productionDataList;
}DrainagePointProductionData;

typedef struct _ReservoirProductionData
{
    string label;
    string icon;
    vector<DrainagePointProductionData> children;
}ReservoirProductionData;

typedef struct _FieldProductionData
{
    string label;
    string icon;
    vector<ReservoirProductionData> children;
}FieldProductionData;




#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <time.h>
#include <iomanip>
#include <functional>
// #include "DateCreation.h"
// #include "Inputdeck.h"

using namespace std;

typedef struct _LinSysResult
{
    vector<vector<double>> x;
    vector<vector<double>> UpperTriangularMatrix;
    vector<vector<double>> LowerTriangularMatrix;
    vector<double> Y_BestFit;
}LinSysResult;

typedef struct _LMOptData
{
    double Tolerance;
    int MaxIter;
    vector<double> InitialGuess;
    double LM_Gamma;
    vector<double> regparamsMin;
    vector<double> regparamsMax;
    bool IsConstrained;
    vector<double> BestFitCoefficients;
    vector<double> Yp;
    int iterations;
    double errorTolerance;
}LMOptData;

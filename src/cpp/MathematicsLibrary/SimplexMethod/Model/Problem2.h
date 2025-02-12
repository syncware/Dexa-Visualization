#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include "../../MatrixOperations.h"

using namespace std;

class Problem2
{
    private:
        MatrixOperations matrixOperations;

    public:
        vector<vector<double>> consMatrx;
        vector<string> signs;
        vector<double> freeVars;
        vector<double> funcVars;
        double c;
        bool isExtrMax;
        Problem2(vector<vector<double>>& constraintMatrix, vector<string>& _signs,
        vector<double>& freeVariables, vector<double>& functionVariables, 
        const double& c, const bool& isExtrMax);
};

 Problem2::Problem2(vector<vector<double>>& constraintMatrix, vector<string>& _signs,
        vector<double>& freeVariables, vector<double>& functionVariables, 
        const double& _c, const bool& _isExtrMax){

        consMatrx = matrixOperations.CopyMatrix(constraintMatrix);
        signs = matrixOperations.CopyVector(_signs);
        freeVars = matrixOperations.CopyVector(freeVariables);
        funcVars = matrixOperations.CopyVector(functionVariables);
        c = _c;
        isExtrMax = _isExtrMax;
}
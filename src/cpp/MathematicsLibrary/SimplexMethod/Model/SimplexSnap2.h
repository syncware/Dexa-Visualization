#pragma once


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include "../../MatrixOperations.h"

using namespace std;

class SimplexSnap2
{
    
    private:
        MatrixOperations matrixOperations;
    public:
        vector<double> b;
        vector<vector<double>> matrix;
        vector<double> M;
        vector<double> F;
        vector<int> C;
        double fValue;
        vector<double> fVars;
        bool isMDone;
        vector<bool> m;

    SimplexSnap2( vector<double>& b,  vector< vector<double>>& matrix,  vector<double>& M, 
     vector<double>& F, vector<int>& C,  vector<double>& fVars, const bool& isMDone,  vector<bool>& m);
};

        

SimplexSnap2::SimplexSnap2( vector<double>& _b,  vector< vector<double>>& _matrix,  vector<double>& _M, 
    vector<double>& _F, vector<int>& _C,  vector<double>& _fVars, const bool& _isMDone,  vector<bool>& _m)
{
    b = matrixOperations.CopyVector(_b);
    matrix = matrixOperations.CopyMatrix(_matrix);
    M =  matrixOperations.CopyVector(_M);
    F =  matrixOperations.CopyVector(_F);
    C = matrixOperations.CopyVector(_C);
    isMDone = _isMDone;
    m = matrixOperations.CopyVector(_m);
    fVars = matrixOperations.CopyVector(_fVars);
    fValue = 0;
    for (int i = 0; i < C.size(); i++)
    {
        fValue = fValue +  fVars[C[i]] * b[i];
    }
}
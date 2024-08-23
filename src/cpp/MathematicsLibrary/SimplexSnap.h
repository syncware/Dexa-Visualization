#pragma once


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include "Enums.h"

using namespace std;



class SimplexSnap
{
private:

public:
    
    vector<double> b;
    vector<vector<double>> matrix;
    vector<double> M;
    vector<double> F;
    vector<int> CC;
    double fValue;
    vector<double> fVars;
    bool isMDone;
    vector<bool> m;

    SimplexSnap();
    SimplexSnap(vector<double>, vector<vector<double>> matrix, vector<double> M, vector<double> F, 
        vector<int> CC, vector<double> fVars, bool isMDone, vector<bool> m);

    vector<double> Copy(vector<double> arrayData);

    vector<int> iCopy(vector<int> arrayData);

    vector<bool> bCopy(vector<bool> arrayData);

    vector<vector<double>> Copy(vector<vector<double>> matrix);

};

SimplexSnap::SimplexSnap()
{

}
SimplexSnap::SimplexSnap(vector<double> _b, vector<vector<double>> _matrix, vector<double> _M, vector<double> _F,
    vector<int> _CC, vector<double> _fVars, bool _isMDone, vector<bool> _m)
{
    b = Copy(_b);
    matrix = Copy(_matrix);
    M = Copy(_M);
    F = Copy(_F);
    CC = iCopy(_CC);
    isMDone = _isMDone;
    m = bCopy(_m);
    fVars = Copy(_fVars);
    fValue = 0;
    int CCCount = CC.size();
    for (int i = 0; i < CCCount; i++)
    {
        fValue +=  fVars[CC[i]] * b[i];
    }
}


vector<double> SimplexSnap::Copy(vector<double> arrayData)
{
    vector<double> newArr;
    int arrayDataSize = arrayData.size();
    for (int i = 0; i < arrayDataSize; i++)
    {
        newArr.push_back(arrayData[i]);
    }
    return newArr;
}


vector<int> SimplexSnap::iCopy(vector<int> arrayData)
{
    vector<int> newArr;
    int arrayDataSize = arrayData.size();
    for (int i = 0; i < arrayDataSize; i++)
    {
        newArr.push_back(arrayData[i]);
    }
    return newArr;
}


vector<bool> SimplexSnap::bCopy(vector<bool> arrayData)
{
    vector<bool> newArr;
    int arrayDataSize = arrayData.size();
    for (int i = 0; i < arrayDataSize; i++)
    {
        newArr.push_back(arrayData[i]);
    }
    return newArr;
}

vector<vector<double>>  SimplexSnap::Copy(vector<vector<double>> matrix)
{
    vector<vector<double>> newMatr;
    const int cols = matrix.size();
    vector<double> FirstRow = matrix[0];

    const int rows = FirstRow.size();

    for (int i = 0; i < cols; i++)
    {
        vector<double> newCol;
        for (int j = 0; j < rows; j++)
        {
            newCol.push_back(matrix[i][j]);
        }

        newMatr.push_back(newCol);
    }
    return newMatr;
}
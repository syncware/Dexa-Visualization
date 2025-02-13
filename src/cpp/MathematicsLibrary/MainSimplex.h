#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iomanip>
#include <map>
#include <math.h>
#include <tuple>
#include "SimplexSnap.h"
#include "Constraint.h"
#include "Func.h"
#include "Simplex.h"
#include "Enums.h"

using namespace std;

class MainSimplex
{
private:
    SimplexSnap simplexSnap;
    Funct func;
    Simplex simplex;
    int constraintsCount = 0;
    int variablesCount = 0;
    SimplexResult _Unbounded = Unbounded;
    SimplexResult _Found = Found;
    SimplexResult _NotYetFound = NotYetFound;

public:
    vector<string> variableNames;
    vector<double> decisonVariables;
    double optimalSolution = 0;
    string optimalSolutionMessage = "";
    MainSimplex();
    MainSimplex(int &_constraintsCount, int &_variablesCount, vector<string> &_variableNames);
    vector<vector<string>> constraintsGridView;
    vector<string> functionGridView;
    vector<vector<string>> resultsGridView;
    void fillConstraintsGrid();
    vector<string> createVector(int &rows);
    vector<double> createVectorOfT(int &rows);
    void fillFunctionGrid();
    void ShowResultsGrid(vector<SimplexSnap> &snaps);
    void Proceed();
    double ToDouble(string &x);
    vector<vector<string>> createMatrix(int &rows, int &cols);
    void getDecisonVariables();
    int getVariableNameRowIndex(string &variableName);
    void GetSolution(SimplexSnap &snap);
};

MainSimplex::MainSimplex()
{
}

MainSimplex::MainSimplex(int &_constraintsCount, int &_variablesCount, vector<string> &_variableNames)
{
    constraintsCount = _constraintsCount;
    variablesCount = _variablesCount;
    variableNames = _variableNames;
    int variableNamessize = variableNames.size();
    decisonVariables = createVectorOfT(variableNamessize);
    fillConstraintsGrid();
    fillFunctionGrid();
}

double MainSimplex::ToDouble(string &x)
{
    double ans = strtod(x.c_str(), NULL);
    return ans;
}

vector<string> MainSimplex::createVector(int &rows)
{
    vector<string> ans;
    for (int i = 0; i < rows; i++)
    {
        ans.push_back("");
    }

    return ans;
}

vector<double> MainSimplex::createVectorOfT(int &rows)
{
    vector<double> ans;
    for (int i = 0; i < rows; i++)
    {
        double ans1 = 0;
        ans.push_back(ans1);
    }

    return ans;
}

void MainSimplex::fillConstraintsGrid()
{

    constraintsGridView.clear();

    int variablesCountPlusTwo = variablesCount + 2;
    for (int i = 0; i < constraintsCount; i++)
    {

        vector<string> row = createVector(variablesCountPlusTwo);
        constraintsGridView.push_back(row);
    }
}

void MainSimplex::fillFunctionGrid()
{
    functionGridView.clear();

    int variablesCountPlusOne = variablesCount + 1;
    functionGridView = createVector(variablesCountPlusOne);

    int variablesCountPlusTwo = variablesCount + 2;
    vector<string> row = createVector(variablesCountPlusTwo);
    constraintsGridView.push_back(row);
}

vector<vector<string>> MainSimplex::createMatrix(int &rows, int &cols)
{
    vector<vector<string>> ans;
    for (int j = 0; j < cols; j++)
    {
        vector<string> Row;
        for (int i = 0; i < rows; i++)
        {
            Row.push_back("");
        }

        ans.push_back(Row);
    }

    return ans;
}

void MainSimplex::ShowResultsGrid(vector<SimplexSnap> &snaps)
{
    resultsGridView.clear();

    int snaps_0_matrixsize = snaps[0].matrix.size();
    int snaps_0_matrixsizePlusnum = 0;
    for (SimplexSnap snap : snaps)
    {
        snaps_0_matrixsize = snaps[0].matrix.size();
        snaps_0_matrixsizePlusnum = snaps_0_matrixsize + 4;
        vector<string> firstRow = createVector(snaps_0_matrixsizePlusnum);

        firstRow[0] = "i";
        firstRow[1] = "Basis";
        firstRow[2] = "C";
        firstRow[3] = "B";

        for (int i = 4; i < snaps_0_matrixsizePlusnum; i++)
        {
            firstRow[i] = "A" + to_string(i - 3);
        }

        resultsGridView.push_back(firstRow);

        int snaps0CCsize = snaps[0].CC.size();
        for (int i = 0; i < snaps0CCsize; i++)
        {
            snaps_0_matrixsize = snaps[0].matrix.size();
            snaps_0_matrixsizePlusnum = snaps_0_matrixsize + 4;
            vector<string> row = createVector(snaps_0_matrixsizePlusnum);
            for (int j = 0; j < snaps_0_matrixsizePlusnum; j++)
            {
                if (j == 0)
                {
                    row[j] = to_string(i + 1);
                }
                else if (j == 1)
                {
                    row[j] = "A" + to_string(snap.CC[i] + 1);
                }
                else if (j == 2)
                {
                    row[j] = snap.m[snap.CC[i]] ? "-M" : to_string(snap.fVars[snap.CC[i]]);
                }
                else if (j == 3)
                {
                    row[j] = to_string(snap.b[i]);
                }
                else
                {
                    row[j] = to_string(snap.matrix[j - 4][i]);
                }
            }
            resultsGridView.push_back(row);
        }

        snaps_0_matrixsize = snaps[0].matrix.size();
        snaps_0_matrixsizePlusnum = snaps_0_matrixsize + 4;
        vector<string> fRow = createVector(snaps_0_matrixsizePlusnum);
        fRow[0] = "m+1";
        fRow[1] = "F";
        fRow[2] = "?j";
        fRow[3] = snap.fValue;

        for (int i = 4; i < snaps_0_matrixsizePlusnum; i++)
        {
            fRow[i] = to_string(snap.F[i - 4]);
        }
        resultsGridView.push_back(fRow);

        if (!snap.isMDone)
        {
            snaps_0_matrixsize = snaps[0].matrix.size();
            snaps_0_matrixsizePlusnum = snaps_0_matrixsize + 4;
            vector<string> mRow = createVector(snaps_0_matrixsizePlusnum);
            mRow[0] = "m+2";
            mRow[1] = "M";
            mRow[2] = "?j";
            mRow[3] = "";
            for (int i = 4; i < snaps_0_matrixsizePlusnum; i++)
            {
                mRow[i] = to_string(snap.M[i - 4]);
            }
            resultsGridView.push_back(mRow);
        }

        snaps_0_matrixsize = snaps[0].matrix.size();
        snaps_0_matrixsizePlusnum = snaps_0_matrixsize + 4;
        vector<string> emptyRow = createVector(snaps_0_matrixsizePlusnum);
        resultsGridView.push_back(emptyRow);
    }
}

void MainSimplex::GetSolution(SimplexSnap &snap)
{
    resultsGridView.clear();

    int snapCCsize = snap.CC.size();
    int snapmatrixsizePlus4 = snap.matrix.size() + 4;
    for (int i = 0; i < snapCCsize; i++)
    {
        vector<string> row = createVector(snapmatrixsizePlus4);

        for (int j = 0; j < snapmatrixsizePlus4; j++)
        {
            if (j == 0)
            {
                row[j] = to_string(i + 1);
            }
            else if (j == 1)
            {
                row[j] = "A" + to_string(snap.CC[i] + 1);
            }
            else if (j == 2)
            {
                row[j] = snap.m[snap.CC[i]] ? "-M" : to_string(snap.fVars[snap.CC[i]]);
            }
            else if (j == 3)
            {
                row[j] = to_string(snap.b[i]);

                int variableNamessize = variableNames.size();
                for (int ii = 0; ii < variableNamessize; ii++)
                {
                    if (row[j - 2] == variableNames[ii])
                    {
                        decisonVariables[ii] = snap.b[i];
                    }
                }
            }
            else
            {
                row[j] = to_string(snap.matrix[j - 4][i]);
            }
        }
    }
}

void MainSimplex::Proceed()
{
    vector<Constraint> constraints;
    for (int i = 0; i < constraintsCount; i++)
    {
        vector<double> variables = createVectorOfT(variablesCount);
        double b = ToDouble(constraintsGridView[i][variablesCount + 1]);
        string sign = constraintsGridView[i][variablesCount];
        for (int j = 0; j < variablesCount; j++)
        {
            variables[j] = ToDouble(constraintsGridView[i][j]);
        }

        Constraint constraintTemp(variables, b, sign);

        constraints.push_back(constraintTemp);
    }

    vector<double> functionVariables = createVectorOfT(variablesCount);
    for (int i = 0; i < variablesCount; i++)
    {
        functionVariables[i] = ToDouble(functionGridView[i]);
    }
    double cc = ToDouble(functionGridView[variablesCount]);

    bool isExtrMax = true; // extrComboBox.SelectedIndex == 0;

    Funct function(functionVariables, cc, isExtrMax);

    Simplex simplex(function, constraints);

    tuple<vector<SimplexSnap>, SimplexResult> result = simplex.GetResult();
    vector<SimplexSnap> snaps = get<0>(result);
    int lent = snaps.size();

    if (get<1>(result) == _Found)
    {
        string extrStr = isExtrMax ? "max" : "min";
        optimalSolution = snaps[lent - 1].fValue;
        optimalSolutionMessage = "The optimal solution: P = " + to_string(optimalSolution);
    }

    if (get<1>(result) == _Unbounded)
    {
        optimalSolutionMessage = "The domain of admissible solutions is unbounded";
    }

    if (get<1>(result) == _NotYetFound)
    {
        optimalSolutionMessage = "Algorithm has made 100 cycles and hasn't found any optimal solution.";
    }

    // ShowResultsGrid(get<0>(result));

    int snapssizeMinus1 = snaps.size() - 1;
    SimplexSnap simplexSnap = snaps[snapssizeMinus1];
    GetSolution(simplexSnap);
    // getDecisonVariables();
}

int MainSimplex::getVariableNameRowIndex(string &variableName)
{
    int variableNamelengthPlus1 = variableName.length() + 1;
    char *tab2 = new char[variableNamelengthPlus1];
    // strcpy_s(tab2, variableName.length() + 1,variableName.c_str());
    strncpy(tab2, variableName.c_str(), variableNamelengthPlus1);

    int arrlen = variableName.length() + 1;

    vector<char> ans(tab2, tab2 + arrlen);
    int anszise = ans.size();

    if (anszise == 2)
    {
        char c = ans[1]; // narrowing on C
        int a = c;
        return a;
    }
    else
    {
        return -1;
    }

    delete[] tab2;

    return 0;
}

void MainSimplex::getDecisonVariables()
{
    int rows = resultsGridView.size();
    int variableNamessize = variableNames.size();

    for (int j = 0; j < variableNamessize; j++)
    {
        for (int i = rows - 7; i < rows; i++)
        {
            string variableName = resultsGridView[i][1];
            string xvalue = resultsGridView[i][3];

            if (resultsGridView[i][1] == variableNames[j])
            {
                int RowIndex = getVariableNameRowIndex(resultsGridView[i][1]);
                decisonVariables[RowIndex - 1] = stod(xvalue);
            }
        }
    }
}

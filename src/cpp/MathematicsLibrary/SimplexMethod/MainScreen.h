#pragma once


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <math.h>
#include <tuple>
#include "../MatrixOperations.h"
#include "./Services/ProblemsService2.h"
#include "./Model/Function2.h"
#include "./Services/Simplex2.h"
#include "./Model/SimplexSnap2.h"
#include "./Model/Data.h"

using namespace std;

class MainScreen
{
private:
    MatrixOperations matrixOperations;
    int extrComboBoxSelectedIndex;

public:
    int constraintsCount = 0;
    int variablesCount = 0;
    vector<double> decisonVariables;
    double optimalSolution = 0;
    string optimalSolutionMessage = "";
    vector<vector<string>> constraintsGridView;
    vector<double> functionGridView;
    vector<vector<string>> resultsGridView;
    string resultsLblText;
   void okBtn_Click();
   void fillConstraintsGrid();
   void fillFunctionGrid();
   void defaultBtn_Click();
   void fillDefaultsConstraints(vector<vector<double>>& consMatrx, vector<string>& signs, vector<double>& freeVars);
   void fillDefaultsFunction(vector<double>& funcVars, const double& c, const bool& isExtrMax);
   void Proceed();
   void ShowResultsGrid(vector<SimplexSnap2>& snaps);
   double Round(double a);
   void Solve(Problem2 p);
};

void MainScreen::okBtn_Click()
{
 
    //constraintsCount = Convert.ToInt32(nOfContraintsTextBox.Text);
    //variablesCount = Convert.ToInt32(nOfVariablesTextBox.Text);
    fillConstraintsGrid();
    fillFunctionGrid();
    
}

void MainScreen::fillConstraintsGrid()
{
    constraintsGridView = matrixOperations.createMatrixString(constraintsCount, variablesCount + 2);
}

void MainScreen::fillFunctionGrid()
{

   functionGridView = matrixOperations.createVector(variablesCount + 2);
    
}

void MainScreen::fillDefaultsFunction(vector<double>& funcVars, const double& c, const bool& isExtrMax)
{
    fillFunctionGrid();
    for (int i = 0; i < variablesCount + 1; i++)
    {
        if (i < variablesCount)
        {
            functionGridView[i] = funcVars[i];
        }
        else
        {
            functionGridView[i] = c;
        }
    }

    extrComboBoxSelectedIndex = isExtrMax ? 0 : 1;
}

void MainScreen::fillDefaultsConstraints(vector<vector<double>>& consMatrx, vector<string>& signs, vector<double>& freeVars)
{

    constraintsCount = signs.size();
    variablesCount = consMatrx[0].size();
    fillConstraintsGrid();

    for (int i = 0; i < constraintsCount; i++)
    {
        for (int j = 0; j < variablesCount + 2; j++)
        {
            if (j < variablesCount)
            {
                constraintsGridView[i][j] = to_string(consMatrx[i][j]);
            }
            else if (j < variablesCount + 1)
            {
                constraintsGridView[i][j] = signs[i];
            }
            else if (j < variablesCount + 2)
            {
                constraintsGridView[i][j] = to_string(freeVars[i]);
            }

        }
    }
}

void MainScreen::Proceed()
{
    vector<Constraint2> constraints;

    for (int i = 0; i < constraintsCount; i++)
    {
        vector<double> variables = matrixOperations.createVector(variablesCount);
        double b = stod(constraintsGridView[i][variablesCount + 1]);
        string sign = constraintsGridView[i][variablesCount];
        for (int j = 0; j < variablesCount; j++)
        {
            variables[j] = stod(constraintsGridView[i][j]);
        }
        constraints.push_back(Constraint2(variables, b, sign));
    }
    vector<double> functionVariables = matrixOperations.createVector(variablesCount);
    for (int i = 0; i < variablesCount; i++)
    {
        functionVariables[i] = functionGridView[i];
    }
    double c = functionGridView[variablesCount];

    bool isExtrMax = extrComboBoxSelectedIndex == 0;

    Function2 function = Function2(functionVariables, c, isExtrMax);

    Simplex2 simplex = Simplex2(function, constraints);

    tuple<vector<SimplexSnap2>, int> result = simplex.GetResult();
    int tupleItem2 = get<1>(result);

    optimalSolution = 0;

    if(tupleItem2 == Found2){
        string extrStr = isExtrMax ? "max" : "min";
        vector<SimplexSnap2> finalResult = get<0>(result);
        int finalResultCount = finalResult.size();
        double fValue = finalResult[finalResultCount-1].fValue;
        optimalSolution = fValue;
        resultsLblText = "The optimal solution is found: F" + extrStr + " =  " + to_string(fValue);
    }

    if(tupleItem2 == Unbounded2){
        resultsLblText = "The domain of admissible solutions is unbounded";
    }

    if(tupleItem2 == NotYetFound2){
        resultsLblText = "Algorithm has made 100 cycles and hasn't found any optimal solution.";
    }

    optimalSolutionMessage = resultsLblText;

    ShowResultsGrid(get<0>(result));
    
}

void MainScreen::ShowResultsGrid(vector<SimplexSnap2>& snaps)
{
    resultsGridView.clear();
    //vector<LinearProgrammingResult> linearProgrammingResults;
    //LinearProgrammingResult linearProgrammingResult;
    vector<int> CCs;
    int snapsSize = snaps.size();
    for (int k = 0; k <  snapsSize; k++)
    {
        for(int j = 0; j < snaps[k].C.size(); j++){
             CCs.push_back(snaps[k].C[j]);
        }
    } 

    int maxCC = 0;
    maxCC = matrixOperations.VectorMaximumInt(CCs);
        
    int variablesCountPlusSlacks = snaps[0].b.size();
    vector<double> decisonVariablesAndSlacks = matrixOperations.createVector(maxCC + 1);
    

    for (int k = 0; k <  snapsSize; k++)
    {
        if(k == snapsSize - 1){
            decisonVariablesAndSlacks = matrixOperations.ZeroVector(decisonVariablesAndSlacks);
        }
        
        SimplexSnap2 snap = snaps[k];
        vector<string> firstRow = matrixOperations.createVectorString(snap.matrix.size() + 4);

        firstRow[0] = "i";
        firstRow[1] = "Basis";
        firstRow[2] = "C";
        firstRow[3] = "B";

        //linearProgrammingResult.refined = matrixOperations.createVector(variablesCount);
        for (int i = 4; i < snap.matrix.size() + 4; i++)
        {
            firstRow[i] = "A" + to_string(i - 3);
        }

        resultsGridView.push_back(firstRow);

        /* linearProgrammingResult.raw = matrixOperations.CopyVector(snap.b);
        linearProgrammingResult.refined = matrixOperations.createVector(variablesCount); */
        
        
        for (int i = 0; i < snap.C.size(); i++)
        {
            vector<string> row = matrixOperations.createVectorString(snap.matrix.size() + 4);
            for (int j = 0; j < snap.matrix.size() + 4; j++)
            {
                if (j == 0)
                {
                    row[j] = to_string(i + 1);
                }
                else if (j == 1)
                {
                    row[j] = "A" + to_string(snap.C[i] + 1);
                    //linearProgrammingResult.indices.push_back(snap.C[i]);
                    //linearProgrammingResult.variables.push_back(row[j]);
                    if(k == snapsSize - 1){
                        decisonVariablesAndSlacks[snap.C[i]] = snap.b[i];
                    } 
                }
                else if (j == 2)
                {
                    row[j] = snap.m[snap.C[i]] ? "-M" : to_string(snap.fVars[snap.C[i]]);
                }
                else if (j == 3)
                {
                    row[j] = to_string(Round(snap.b[i]));
                }
                else
                {
                    row[j] = to_string(Round(snap.matrix[j - 4][i]));
                }
            }
            resultsGridView.push_back(row);
        }
        vector<string> fRow = matrixOperations.createVectorString(snap.matrix.size() + 4);
        fRow[0] = "m+1";
        fRow[1] = "F";
        fRow[2] = "Δj";
        fRow[3] = to_string(Round(snap.fValue));
        for (int i = 4; i < snap.matrix.size() + 4; i++)
        {
            fRow[i] = to_string(Round(snap.F[i - 4]));
        }
        resultsGridView.push_back(fRow);

        if (!snap.isMDone)
        {
            vector<string> mRow = matrixOperations.createVectorString(snap.matrix.size() + 4);
            mRow[0] = "m+2";
            mRow[1] = "M";
            mRow[2] = "Δj";
            mRow[3] = "";
            for (int i = 4; i < snap.matrix.size() + 4; i++)
            {
                mRow[i] = to_string(Round(snap.M[i - 4]));
            }
            resultsGridView.push_back(mRow);
        }
        vector<string> emptyRow = matrixOperations.createVectorString(snap.matrix.size() + 4);
        resultsGridView.push_back(emptyRow);
    }
    //decisonVariables

    //decisonVariables = linearProgrammingResult.refined;
    decisonVariables = matrixOperations.createVector(variablesCount);
    for(int k = 0; k < variablesCount; k++){
        decisonVariables[k] = decisonVariablesAndSlacks[k];
    }
}

double MainScreen::Round(double a)
{
    return a; // round(a, 2);
}

void MainScreen::defaultBtn_Click(){
    ProblemsService2 problemsService;
    int currentProblemIndex = 4;
    Problem2 p = problemsService.GetNext(currentProblemIndex);
    fillDefaultsConstraints(p.consMatrx, p.signs, p.freeVars);
    fillDefaultsFunction(p.funcVars, p.c, p.isExtrMax);
    Proceed();
}

void MainScreen::Solve(Problem2 p){
    fillDefaultsConstraints(p.consMatrx, p.signs, p.freeVars);
    fillDefaultsFunction(p.funcVars, p.c, p.isExtrMax);
    Proceed();
}
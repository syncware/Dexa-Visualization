#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <tuple>
#include <math.h>
#include <functional>
#include "Simplex.h"
#include "MatrixOperations.h"
#include "Optimization.h"

using namespace std;

class Optimization
{
private:
    Simplex simplex;
    MatrixOperations matrixOperations;

public:
    Optimization();
    ~Optimization();
    bool Functionfound(double &gNorm, double &error1);
    vector<double> ProjectionFunction(vector<double> &MinVal, vector<double> &MaxVal,
                                      vector<double> &regparam);
    vector<vector<double>> JacMthd(function<vector<double>(vector<double>)> f, vector<double> &x);
    LMOptData LM_Method(function<vector<double>(vector<double>)> f, LMOptData &LMOptData3);
};

Optimization::Optimization()
{
}

Optimization::~Optimization()
{
}

bool Optimization::Functionfound(double &gNorm, double &error1)
{
    if (gNorm <= error1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

vector<double> Optimization::ProjectionFunction(vector<double> &MinVal, vector<double> &MaxVal,
                                                vector<double> &regparam)
{

    int i, nrow = regparam.size();
    vector<double> pvec = matrixOperations.createVector(nrow);
    for (i = 0; i < nrow; i++)
    {
        if (regparam[i] < MinVal[i])
        {
            pvec[i] = MinVal[i];
        }
        else if (regparam[i] >= MinVal[i] && regparam[i] <= MaxVal[i])
        {
            pvec[i] = regparam[i];
        }
        else
        {
            pvec[i] = MaxVal[i];
        }
    }

    return pvec;
}

vector<vector<double>> Optimization::JacMthd(function<vector<double>(vector<double>)> f, vector<double> &x)
{
    int j, i;
    double decrement = pow(10, 6), scalar = 0;
    int nCols = x.size();
    vector<double> xnew = matrixOperations.createVector(nCols);
    for (j = 0; j < nCols; j++)
    {
        if (x[j] == 0)
        {
            x[j] = pow(10, -8);
        }
    }

    vector<double> diff2 = f(x);
    int nRows = diff2.size();
    vector<vector<double>> ForwardFunc = matrixOperations.createMatrix(nRows, nCols);

    for (j = 0; j < nCols; j++)
    {
        for (i = 0; i < nCols; i++)
        {
            xnew[i] = x[i];
            if (i == j)
            {
                xnew[i] = x[i] + x[i] / decrement;
            }
        }

        diff2 = f(xnew);
        vector<vector<double>> objFunc1 = matrixOperations.Vector2Matrix(diff2);

        for (i = 0; i < nCols; i++)
        {
            xnew[i] = x[i];
            if (i == j)
            {
                xnew[i] = x[i] - x[i] / decrement;
            }
        }

        diff2 = f(xnew);
        vector<vector<double>> objFunc2 = matrixOperations.Vector2Matrix(diff2);
        vector<vector<double>> DerivativeNumerator = matrixOperations.MatSubstract(objFunc1, objFunc2);
        scalar = 1 / (2 * (x[j] / decrement));
        vector<vector<double>> ObjFunc = matrixOperations.ScalarMatrixMultiplication(scalar, DerivativeNumerator);

        for (i = 0; i < nRows; i++)
        {
            ForwardFunc[i][j] = ObjFunc[i][0];
        }
    }

    return ForwardFunc;
}

LMOptData Optimization::LM_Method(function<vector<double>(vector<double>)> f, LMOptData &LMOptData3)
{
    LMOptData LMOptData2 = LMOptData3;
    double Tolerance1 = LMOptData2.Tolerance;
    double Tolerance2 = Tolerance1 * pow(10, -12);
    int MaxIter = LMOptData2.MaxIter;
    double Gamma = LMOptData2.LM_Gamma;
    vector<double> regparamsMax = LMOptData2.regparamsMax;
    vector<double> regparamsMin = LMOptData2.regparamsMin;
    bool IsConstrained = LMOptData2.IsConstrained;
    vector<double> x = LMOptData2.InitialGuess;
    int iteration = 0;

    vector<double> xx = matrixOperations.createVector(2);
    double v = 2;
    vector<vector<double>> Jac = JacMthd(f, x);
    vector<vector<double>> JacT = matrixOperations.MatTranspose(Jac);
    vector<vector<double>> a = matrixOperations.MatMult(JacT, Jac);
    vector<double> diff2 = f(x);
    vector<vector<double>> diff = matrixOperations.Vector2Matrix(diff2);
    vector<vector<double>> G = matrixOperations.MatMult(JacT, diff);
    G = matrixOperations.ScalarMatrixMultiplication(-1, G);
    double gNorm = matrixOperations.norm(G);
    vector<vector<double>> diagA = matrixOperations.DiagonalMatrix(a);
    vector<double> aii = matrixOperations.ConvertDiaMatrixtoVector(diagA);
    double aiiMax = matrixOperations.VectorMaximum(aii);
    double Lamda = Gamma * aiiMax;
    bool found = Functionfound(gNorm, Tolerance1);

    vector<vector<double>> IdentityMatrix, LamdaIDMatrix, sum, hlm, Lamdahlm, hlmT;
    vector<vector<double>> Lamdahlmg, hlTLamdahlmg, diffnew;
    double Normhlm, xNorm, Denomenator, Fx, Fxnew, Numerator, GainRatio, xxmax;
    vector<double> xnew, diff2new;
    do
    {

        iteration = iteration + 1;

        IdentityMatrix = matrixOperations.unitmatrix(a);
        LamdaIDMatrix = matrixOperations.ScalarMatrixMultiplication(Lamda, IdentityMatrix);
        sum = matrixOperations.MatAdd(a, LamdaIDMatrix);
        // invsum = MatrixOperations.LUDecompositionInverse(sum)
        hlm = matrixOperations.LU_Decomposition(sum, G);
        Normhlm = matrixOperations.norm(hlm);
        xNorm = matrixOperations.Vectornorm(x);
        if (Normhlm <= (Tolerance2 * (xNorm + Tolerance2)))
        {
            found = true;
            break;
        }
        else
        {

            xnew = matrixOperations.Mat2Vec(matrixOperations.VecMatAdd(hlm, x));
            if (IsConstrained == true)
            {
                xnew = ProjectionFunction(regparamsMin, regparamsMax, xnew);
            }
            Lamdahlm = matrixOperations.ScalarMatrixMultiplication(Lamda, hlm);
            hlmT = matrixOperations.MatTranspose(hlm);
            Lamdahlmg = matrixOperations.MatAdd(Lamdahlm, G);
            hlTLamdahlmg = matrixOperations.MatMult(hlmT, Lamdahlmg);
            Denomenator = 0.5 * hlTLamdahlmg[0][0];
            diff2 = f(x);
            diff = matrixOperations.Vector2Matrix(diff2);
            diff2new = f(xnew);
            diffnew = matrixOperations.Vector2Matrix(diff2new);
            Fx = 0.5 * (pow(matrixOperations.SumofSquares(diff), 0.5));
            Fxnew = 0.5 * (pow(matrixOperations.SumofSquares(diffnew), 0.5));
            Numerator = Fx - Fxnew;
            GainRatio = Numerator / Denomenator;
            if (GainRatio > 0)
            {
                x = matrixOperations.CopyVector(xnew);
                Jac = JacMthd(f, x);
                JacT = matrixOperations.MatTranspose(Jac);
                a = matrixOperations.MatMult(JacT, Jac);
                diff2 = f(x);
                diff = matrixOperations.Vector2Matrix(diff2);
                G = matrixOperations.MatMult(JacT, diff);
                G = matrixOperations.ScalarMatrixMultiplication(-1, G);
                gNorm = matrixOperations.norm(G);
                found = Functionfound(gNorm, Tolerance1);
                xx[0] = 1.0 / 3.0;
                xx[1] = 1 - pow((2 * GainRatio - 1), 3);
                xxmax = matrixOperations.VectorMaximum(xx);
                Lamda = Lamda * xxmax;
                v = 2.0;
            }
            else
            {
                Lamda = Lamda * v;
                v = 2 * v;
            }
        }

        if (iteration >= MaxIter)
        {
            break;
        }

    } while (found == false);

    LMOptData2.iterations = iteration;
    LMOptData2.BestFitCoefficients = x;
    LMOptData2.errorTolerance = Normhlm;
    return LMOptData2;
}
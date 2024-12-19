#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <tuple>
#include <math.h>
#include "Enums.h"
#include "Func.h"
#include "Constraint.h"
#include "SimplexIndexResult.h"
#include "SimplexSnap.h"

using namespace std;

class Simplex
{
private:
    Funct function;

    vector<double> functionVariables;
    vector<vector<double>> matrix;
    vector<double> b;
    vector<bool> m;
    vector<double> M;
    vector<double> F;
    vector<int> CC;
    bool isMDone = false;
    SimplexResult _Unbounded = Unbounded;
    SimplexResult _Found = Found;
    SimplexResult _NotYetFound = NotYetFound;

public:
    Simplex();

    Simplex(Funct &_function, vector<Constraint> &_constraints);

    int getIndexOfNegativeElementWithMaxAbsoluteValue(vector<double> &arrayData);

    int getIndexOfMinimalRatio(vector<double> &column, vector<double> &b);

    void getFunctionArray();

    Funct Canonize(Funct function);

    vector<vector<double>> appendColumn(vector<vector<double>> &matrix, vector<double> &column);

    vector<double> append(vector<double> &arrayData, double &element);

    vector<bool> appendBool(vector<bool> &arrayData, bool &element);

    vector<double> getColumn(double &value, int &place, int &length);

    vector<vector<double>> createMatrix(const int &rows, const int &cols);

    vector<double> createVector(const int &rows);

    void getMatrix(vector<Constraint> &constraints);

    void calculateSimplexTableau(tuple<int, int> &Xij);

    void getMandF();

    SimplexIndexResult nextStep();

    tuple<vector<SimplexSnap>, SimplexResult> GetResult();
};

Simplex::Simplex()
{
}

Simplex::Simplex(Funct &_function, vector<Constraint> &_constraints)
{
    if (_function.isExtrMax)
    {
        function = _function;
    }
    else
    {
        function = Canonize(_function);
    }

    getMatrix(_constraints);
    getFunctionArray();
    getMandF();

    int FSize = F.size();
    for (int i = 0; i < FSize; i++)
    {
        F[i] = -functionVariables[i];
    }
}

int Simplex::getIndexOfNegativeElementWithMaxAbsoluteValue(vector<double> &arrayData)
{
    int index = -1;
    int arrayDataSize = arrayData.size();
    for (int i = 0; i < arrayDataSize; i++)
    {
        if (arrayData[i] < 0)
        {
            // if (!isMDone || isMDone && !m[i])
            if (!isMDone || (isMDone && !m[i]))
            {
                if (index == -1)
                {
                    index = i;
                }
                else if (abs(arrayData[i]) > abs(arrayData[index]))
                {
                    index = i;
                }
            }
        }
    }
    return index;
}

int Simplex::getIndexOfMinimalRatio(vector<double> &column, vector<double> &b)
{
    int index = -1;
    int columnsize = column.size();
    for (int i = 0; i < columnsize; i++)
    {
        if (column[i] > 0 && b[i] > 0)
        {
            if (index == -1)
            {
                index = i;
            }
            else if (b[i] / column[i] < b[index] / column[index])
            {
                index = i;
            }
        }
    }

    return index;
}

void Simplex::getFunctionArray()
{

    int matrixsize = matrix.size();
    vector<double> funcVars = createVector(matrixsize);
    int functionvariablessize = function.variables.size();
    for (int i = 0; i < matrixsize; i++)
    {
        funcVars[i] = i < functionvariablessize ? function.variables[i] : 0;
    }

    functionVariables = funcVars;
}

Funct Simplex::Canonize(Funct _function)
{
    vector<double> newFuncVars;
    int _functionvariablessize = _function.variables.size();
    for (int i = 0; i < _functionvariablessize; i++)
    {
        newFuncVars.push_back(-_function.variables[i]);
    }

    bool tru = true;
    double Minus_functioncc = -_function.cc;
    Funct ans(newFuncVars, Minus_functioncc, tru);

    return ans;
}

vector<vector<double>> Simplex::appendColumn(vector<vector<double>> &matrix, vector<double> &column)
{
    vector<vector<double>> newMatrix;
    const int cols = matrix.size();
    for (int i = 0; i < cols; i++)
    {
        vector<double> Row = matrix[i];
        newMatrix.push_back(Row);
    }
    newMatrix.push_back(column);

    return newMatrix;
}

vector<double> Simplex::append(vector<double> &arrayData, double &element)
{
    vector<double> newArray;
    int arrayDatasize = arrayData.size();
    for (int i = 0; i < arrayDatasize; i++)
    {
        newArray.push_back(arrayData[i]);
    }
    newArray.push_back(element);

    return newArray;
}

vector<bool> Simplex::appendBool(vector<bool> &arrayData, bool &element)
{
    vector<bool> newArray;
    int arrayDatasize = arrayData.size();
    for (int i = 0; i < arrayDatasize; i++)
    {
        newArray.push_back(arrayData[i]);
    }
    newArray.push_back(element);

    return newArray;
}

vector<double> Simplex::getColumn(double &value, int &place, int &length)
{
    vector<double> newColumn;

    for (int k = 0; k < length; k++)
    {
        double ans = k == place ? value : 0;

        newColumn.push_back(ans);
    }

    return newColumn;
}

vector<vector<double>> Simplex::createMatrix(const int &rows, const int &cols)
{
    vector<vector<double>> ans;
    for (int j = 0; j < cols; j++)
    {
        vector<double> Row;
        for (int i = 0; i < rows; i++)
        {
            Row.push_back(0);
        }

        ans.push_back(Row);
    }

    return ans;
}

vector<double> Simplex::createVector(const int &rows)
{
    vector<double> ans;

    for (int i = 0; i < rows; i++)
    {
        ans.push_back(0);
    }

    return ans;
}

void Simplex::getMatrix(vector<Constraint> &constraints)
{
    int constraintssize = constraints.size();
    int constraintsvariablessize = 0;
    for (int i = 0; i < constraintssize; i++)
    {
        if (constraints[i].b < 0)
        {
            vector<double> cVars;
            int constraintsvariablessize = constraints[i].variables.size();
            for (int j = 0; j < constraintsvariablessize; j++)
            {
                cVars.push_back(-constraints[i].variables[j]);
            }

            string sign = constraints[i].sign;

            if (sign == ">=")
            {
                sign = "<=";
            }
            else if (sign == "<=")
            {
                sign = ">=";
            }

            double minusconstraints_i_b = -constraints[i].b;
            Constraint cNew(cVars, minusconstraints_i_b, sign);
            constraints[i] = cNew;
        }
    }

    constraintsvariablessize = constraints[0].variables.size();
    constraintssize = constraints.size();
    vector<vector<double>> matrix = createMatrix(constraintssize, constraintsvariablessize);

    for (int i = 0; i < constraintsvariablessize; i++)
    {
        for (int j = 0; j < constraintssize; j++)
        {
            matrix[i][j] = constraints[j].variables[i];
        }
    }

    vector<vector<double>> appendixMatrix; // = createMatrix(constraints.size(), 1);
    vector<double> Bs = createVector(constraintssize);
    for (int i = 0; i < constraintssize; i++)
    {
        Constraint current = constraints[i];

        Bs[i] = current.b;

        if (current.sign == ">=")
        {
            double minusOne = -1;
            vector<double> vecT = getColumn(minusOne, i, constraintssize);
            appendixMatrix = appendColumn(appendixMatrix, vecT);
        }
        else if (current.sign == "<=")
        {
            double plusOne = 1;
            vector<double> vecT = getColumn(plusOne, i, constraintssize);
            appendixMatrix = appendColumn(appendixMatrix, vecT);
        }
    }

    vector<vector<double>> newMatrix;
    constraintsvariablessize = constraints[0].variables.size();
    for (int i = 0; i < constraintsvariablessize; i++)
    {
        newMatrix.push_back(matrix[i]);
    }

    int appendixMatrixsize = appendixMatrix.size();
    for (int i = constraintsvariablessize; i < constraintsvariablessize + appendixMatrixsize; i++)
    {
        newMatrix.push_back(appendixMatrix[i - constraintsvariablessize]);
    }

    vector<bool> hasBasicVar;

    constraintssize = constraints.size();
    for (int i = 0; i < constraintssize; i++)
    {
        hasBasicVar.push_back(false);
    }

    CC.clear();

    int newMatrixsize = newMatrix.size();
    for (int i = 0; i < newMatrixsize; i++)
    {

        bool hasOnlyNulls = true;
        bool hasOne = false;
        tuple<int, int> onePosition = make_tuple(0, 0);
        for (int j = 0; j < constraintssize; j++)
        {

            if (newMatrix[i][j] == 1)
            {
                if (hasOne)
                {
                    hasOnlyNulls = false;
                    break;
                }
                else
                {
                    hasOne = true;
                    onePosition = make_tuple(i, j);
                }
            }
            else if (newMatrix[i][j] != 0)
            {
                hasOnlyNulls = false;
                break;
            }
        }

        if (hasOnlyNulls && hasOne)
        {
            hasBasicVar[get<1>(onePosition)] = true;
            CC.push_back(get<0>(onePosition));
            // ci++;
        }
    }

    m.clear();

    for (int i = 0; i < newMatrixsize; i++)
    {
        m.push_back(false);
    }

    for (int i = 0; i < constraintssize; i++)
    {

        if (!hasBasicVar[i])
        {

            vector<double> basicColumn = createVector(constraintssize);

            for (int j = 0; j < constraintssize; j++)
            {
                basicColumn[j] = j == i ? 1 : 0;
            }

            newMatrix = appendColumn(newMatrix, basicColumn);
            bool tru = true;
            m = appendBool(m, tru);
            CC.push_back(newMatrix.size() - 1);
            // ci++;
        }
    }

    this->b = Bs;
    this->matrix = newMatrix;
}

void Simplex::calculateSimplexTableau(tuple<int, int> &Xij)
{

    const int J = get<1>(Xij);
    const int I = get<0>(Xij);
    int matrixsize = matrix.size();
    int bsize = b.size();

    CC[J] = I;

    vector<double> newJRow = createVector(matrixsize);

    for (int i = 0; i < matrixsize; i++)
    {
        newJRow[i] = matrix[i][J] / matrix[I][J];
    }

    vector<double> newB = createVector(bsize);

    for (int i = 0; i < bsize; i++)
    {
        if (i == J)
        {
            newB[i] = b[i] / matrix[I][J];
        }
        else
        {
            newB[i] = b[i] - b[J] / matrix[I][J] * matrix[I][i];
        }
    }

    b = newB;
    int CCsize = CC.size();
    vector<vector<double>> newMatrix = createMatrix(CCsize, matrixsize);

    for (int i = 0; i < matrixsize; i++)
    {
        for (int j = 0; j < CCsize; j++)
        {
            if (j == J)
            {
                newMatrix[i][j] = newJRow[i];
            }
            else
            {
                newMatrix[i][j] = matrix[i][j] - newJRow[i] * matrix[I][j];
            }
        }
    }

    matrix = newMatrix;
    getMandF();
}

void Simplex::getMandF()
{
    int matrixsize = matrix.size();
    M = createVector(matrixsize);
    F = createVector(matrixsize);

    for (int i = 0; i < matrixsize; i++)
    {
        double sumF = 0;
        double sumM = 0;
        int matrix_i_size = matrix[0].size();
        for (int j = 0; j < matrix_i_size; j++)
        {
            if (m[CC[j]])
            {
                sumM -= matrix[i][j];
            }
            else
            {
                sumF += functionVariables[CC[j]] * matrix[i][j];
            }
        }
        M[i] = m[i] ? sumM + 1 : sumM;
        F[i] = sumF - functionVariables[i];
    }
}

SimplexIndexResult Simplex::nextStep()
{

    int columnM = getIndexOfNegativeElementWithMaxAbsoluteValue(M);
    tuple<int, int> tupleObject;

    if (isMDone || columnM == -1)
    {
        // M doesn't have negative values
        isMDone = true;
        int columnF = getIndexOfNegativeElementWithMaxAbsoluteValue(F);

        if (columnF != -1) // Has at least 1 negative value
        {
            int row = getIndexOfMinimalRatio(matrix[columnF], b);

            if (row != -1)
            {
                tupleObject = make_tuple(columnF, row);
                SimplexIndexResult simplexIndexResult(tupleObject, _NotYetFound);

                return simplexIndexResult;
            }
            else
            {
                tupleObject = make_tuple(0, 0);
                SimplexIndexResult simplexIndexResult(tupleObject, _Unbounded);
                return simplexIndexResult;
            }
        }
        else
        {
            tupleObject = make_tuple(0, 0);
            SimplexIndexResult simplexIndexResult(tupleObject, _Found);
            return simplexIndexResult;
        }
    }
    else
    {
        int row = getIndexOfMinimalRatio(matrix[columnM], b);

        if (row != -1)
        {
            tupleObject = make_tuple(columnM, row);
            SimplexIndexResult simplexIndexResult(tupleObject, _NotYetFound);
            return simplexIndexResult;
        }
        else
        {
            tupleObject = make_tuple(0, 0);
            SimplexIndexResult simplexIndexResult(tupleObject, _Unbounded);
            return simplexIndexResult;
        }
    }
}

tuple<vector<SimplexSnap>, SimplexResult> Simplex::GetResult()
{
    vector<SimplexSnap> snaps;
    SimplexSnap simplexSnap(b, matrix, M, F, CC, functionVariables, isMDone, m);
    snaps.push_back(simplexSnap);

    SimplexIndexResult result = nextStep();
    int i = 0;
    while (result.result == _NotYetFound && i < 100)
    {
        calculateSimplexTableau(result.index);
        SimplexSnap simplexSnap2(b, matrix, M, F, CC, functionVariables, isMDone, m);
        snaps.push_back(simplexSnap2);
        result = nextStep();
        i++;
    }

    tuple<vector<SimplexSnap>, SimplexResult> tupleObject;
    tupleObject = make_tuple(snaps, result.result);

    return tupleObject;
}

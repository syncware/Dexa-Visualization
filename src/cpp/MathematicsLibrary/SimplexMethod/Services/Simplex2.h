#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <tuple>
#include <math.h>
#include "../Model/Problem2.h"
#include "../Model/Function2.h"
#include "../Model/Constraint2.h"
#include "../../MatrixOperations.h"
#include "../Model/SimplexIndexResult2.h"
#include "../Model/SimplexSnap2.h"

using namespace std;

const int Unbounded2 = 0;
const int Found2 = 1;
const int NotYetFound2 = 2;

class Simplex2
{
    public: 
        Function2 function;
        MatrixOperations matrixOperations;

       vector<double> functionVariables;
        vector<vector<double>> _matrix;
        vector<double> b;
        vector<bool> m;
        vector<double> M;
        vector<double> F;
        vector<int> C;
        bool isMDone = false;
        Simplex2(Function2 function, vector<Constraint2> constraints);
        tuple<vector<SimplexSnap2>, int> GetResult();
        void calculateSimplexTableau(tuple<int,int>& Xij);
        void getMandF();
        SimplexIndexResult2 nextStep();
        int getIndexOfNegativeElementWithMaxAbsoluteValue(vector<double>& array);
        int getIndexOfMinimalRatio(vector<double>& column, vector<double>& b);
        void getFunctionArray();
        Function2 Canonize(Function2& function);
        vector<vector<double>> appendColumn(vector<vector<double>> matrix, vector<double> column);
        vector<double> getColumn(const double& value, int place, int length);
        void getMatrix(vector<Constraint2>& constraints);
        vector<bool> append(vector<bool>& array, const bool& element);
};

Simplex2::Simplex2(Function2 _function, vector<Constraint2> constraints)
{

    if (_function.isExtrMax)
    {
        function = _function;
    } else
    {
        function = Canonize(_function);
    }

    getMatrix(constraints);
    getFunctionArray();
    getMandF();

    for(int i = 0; i < F.size(); i++)
    {
        F[i] = -functionVariables[i];
    }
}

tuple<vector<SimplexSnap2>, int> Simplex2::GetResult()
{
    vector<SimplexSnap2> snaps;
    snaps.push_back(SimplexSnap2(b, _matrix, M, F, C, functionVariables, isMDone,m));

    SimplexIndexResult2 result = nextStep();
    int i = 0;
    while (result.result == NotYetFound2 && i < 100)
    {
        calculateSimplexTableau(result.index);
        snaps.push_back(SimplexSnap2(b, _matrix, M, F, C, functionVariables, isMDone, m));
        result = nextStep();
        i++;
    }

    return make_tuple(snaps, result.result);
}

void Simplex2::calculateSimplexTableau(tuple<int,int>& Xij)
{
    vector<vector<double>> newMatrix;

    C[get<1>(Xij)] = get<0>(Xij);

    vector<double> newJRow = matrixOperations.createVector(_matrix.size());

    for (int i = 0; i < _matrix.size(); i++)
    {
        newJRow[i] = _matrix[i][get<1>(Xij)] / _matrix[get<0>(Xij)][get<1>(Xij)];
    }

    vector<double> newB = matrixOperations.createVector(b.size());

    for (int i = 0; i < b.size(); i++)
    {
        if (i == get<1>(Xij))
        {
            newB[i] = b[i] / _matrix[get<0>(Xij)][get<1>(Xij)];
        }
        else
        {
            newB[i] = b[i] - b[get<1>(Xij)] / _matrix[get<0>(Xij)][get<1>(Xij)] * _matrix[get<0>(Xij)][i];
        }
    }

    b = newB;

    newMatrix = matrixOperations.createMatrix(_matrix.size(), C.size());
    for (int i = 0; i < _matrix.size(); i++)
    {
        //newMatrix[i] = matrixOperations.createVector(C.size());
        for (int j = 0; j < C.size(); j++)
        {
            if(j == get<1>(Xij))
            {
                newMatrix[i][j] = newJRow[i];
            } else
            {
                newMatrix[i][j] = _matrix[i][j] - newJRow[i] * _matrix[get<0>(Xij)][j];
            }
        }
    }

    _matrix = matrixOperations.CopyMatrix(newMatrix);
    getMandF();
}

void Simplex2::getMandF()
{
    M = matrixOperations.createVector(_matrix.size());
    F = matrixOperations.createVector(_matrix.size());

    for (int i = 0; i < _matrix.size(); i++)
    {
        double sumF = 0;
        double sumM = 0;
        for (int j = 0; j < _matrix[0].size(); j++)
        {
            if (m[C[j]])
            {
                sumM -= _matrix[i][j];
            }
            else
            {
                sumF += functionVariables[C[j]] * _matrix[i][j];
            }
        }
        M[i] = m[i] ? sumM +1 : sumM;
        F[i] = sumF - functionVariables[i];
    }
}

SimplexIndexResult2 Simplex2::nextStep()
{

    int columnM = getIndexOfNegativeElementWithMaxAbsoluteValue(M);

    if (isMDone || columnM == -1)
    {
        //M doesn't have negative values
        isMDone = true;
        int columnF = getIndexOfNegativeElementWithMaxAbsoluteValue(F);

        if (columnF != -1) //Has at least 1 negative value
        {
            int row = getIndexOfMinimalRatio(_matrix[columnF], b);

            if (row != -1)
            {
                return SimplexIndexResult2(make_tuple(columnF, row), NotYetFound2);
            }
            else
            {
                return SimplexIndexResult2(make_tuple(NULL, NULL), Unbounded2);
            }
        }
        else
        {
            return SimplexIndexResult2(make_tuple(NULL, NULL), Found2);
        }
        
    } else
    {
        int row = getIndexOfMinimalRatio(_matrix[columnM], b);

        if (row != -1)
        {
            return SimplexIndexResult2(make_tuple(columnM, row), NotYetFound2);
        }
        else
        {
            return SimplexIndexResult2(make_tuple(NULL, NULL), Unbounded2);
        }
    }
}


int Simplex2::getIndexOfNegativeElementWithMaxAbsoluteValue(vector<double>& array)
{
    int index = -1;

    for(int i = 0; i < array.size(); i++)
    {
        if (array[i] < 0)
        {
            if (!isMDone || isMDone && !m[i])
            {
                if (index == -1)
                {
                    index = i;
                }
                else if (abs(array[i]) > abs(array[index]))
                {
                    index = i;
                }
            }

        }
    }
    return index;
}



int Simplex2::getIndexOfMinimalRatio(vector<double>& column, vector<double>& b)
{
    int index = -1;

    for (int i = 0; i < column.size(); i++)
    {
        if(column[i] > 0 && b[i] > 0)
        {
            if (index == -1)
            {
                index = i;
            }
            else if(b[i] / column[i] < b[index] / column[index])
            {
                index = i;
            }
        }
    }

    return index;
}

void Simplex2::getFunctionArray() {
    vector<double> funcVars = matrixOperations.createVector(_matrix.size());
    for(int i = 0; i < _matrix.size(); i++) {
        funcVars[i] = i < function.variables.size() ? function.variables[i] : 0;
    }
    functionVariables = matrixOperations.CopyVector(funcVars);
}

Function2 Simplex2::Canonize(Function2& function)
{
    vector<double> newFuncVars = matrixOperations.createVector(function.variables.size());

    for (int i = 0; i < function.variables.size(); i++)
    {
        newFuncVars[i] = -function.variables[i];
    }
    return Function2(newFuncVars, -function.c, true);
}

vector<vector<double>> Simplex2::appendColumn(vector<vector<double>> matrix, vector<double> column)
{
    vector<vector<double>> newMatrix = matrixOperations.createMatrix(matrix.size() + 1, column.size());
    for (int i = 0; i < matrix.size(); i++)
    {
        newMatrix[i] = matrix[i];
    }
    newMatrix[matrix.size()] = column;
    return newMatrix;
}

 vector<bool> Simplex2::append(vector<bool>& array, const bool& element)
{
   vector<bool> newArray = matrixOperations.createVectorBool(array.size() + 1);
    for(int i = 0; i <array.size(); i++)
    {
        newArray[i] = array[i];
    }
    newArray[array.size()] = element;
    return newArray;
}

        /* T[] append<T>(T[] array, T element)
        {
            T[] newArray = new T[array.Length + 1];
            for(int i = 0; i<array.Length; i++)
            {
                newArray[i] = array[i];
            }
            newArray[array.Length] = element;
            return newArray;
        } */

vector<double> Simplex2::getColumn(const double& value, int place, int length)
{
    vector<double> newColumn = matrixOperations.createVector(length);

    for (int k = 0; k < length; k++)
    {
        newColumn[k] = k == place ? value : 0;
    }

    return newColumn;
}

void Simplex2::getMatrix(vector<Constraint2>& constraints)
{
    for (int i = 0; i < constraints.size(); i++)
    {
        if (constraints[i].b < 0)
        {
            vector<double> cVars = matrixOperations.createVector(constraints[i].variables.size());

            for (int j = 0; j < constraints[i].variables.size(); j++)
            {
                cVars[j] = -constraints[i].variables[j];
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

            Constraint2 cNew = Constraint2(cVars, -constraints[i].b, sign);
            constraints[i] = cNew;
        }
    }

    vector<vector<double>> matrix = matrixOperations.createMatrix(constraints[0].variables.size(), constraints.size());

    for(int i = 0; i < constraints[0].variables.size(); i++)
    {
        matrix[i] = matrixOperations.createVector(constraints.size());
        for(int j = 0; j < constraints.size(); j++)
        {
            matrix[i][j] = constraints[j].variables[i];
        }
    }

    vector<vector<double>> appendixMatrix;
    vector<double> Bs = matrixOperations.createVector(constraints.size());

    for (int i = 0; i < constraints.size(); i++)
    {
        Constraint2 current = constraints[i];

        Bs[i] = current.b;

        if (current.sign == ">=")
        {
            appendixMatrix = appendColumn(appendixMatrix, getColumn(-1.0, i, constraints.size()));
        } else if (current.sign == "<=")
        {
            appendixMatrix = appendColumn(appendixMatrix, getColumn(1.0, i, constraints.size()));
        }
    }

    vector<vector<double>> newMatrix = matrixOperations.createMatrix(matrix.size(), matrix[0].size());
    if( appendixMatrix.size() > 0){
         newMatrix = matrixOperations.createMatrix(constraints[0].variables.size() + appendixMatrix.size(), constraints.size());
    }

   

    for(int i = 0; i < constraints[0].variables.size(); i++)
    {
        newMatrix[i] = matrix[i];
    }

    for (int i = constraints[0].variables.size(); i < constraints[0].variables.size() + appendixMatrix.size(); i++)
    {
        newMatrix[i] = appendixMatrix[i - constraints[0].variables.size()];
    }

    vector<bool> hasBasicVar = matrixOperations.createVectorBool(constraints.size());

    for(int i = 0; i < constraints.size(); i++) {
        hasBasicVar[i] = false;
    }

    C = matrixOperations.createVectorInt(constraints.size());

    int ci = 0;
    for(int i = 0; i < newMatrix.size(); i++) {


        bool hasOnlyNulls = true;
        bool hasOne = false;
        tuple<int,int> onePosition =make_tuple(0,0);
        for(int j = 0; j < constraints.size(); j++) {


            if (newMatrix[i][j] == 1)
            {
                if (hasOne) {
                    hasOnlyNulls = false;
                    break;
                } else {
                    hasOne = true;
                    onePosition = make_tuple(i,j);
                }
            }
            else if (newMatrix[i][j] != 0)
            {
                hasOnlyNulls = false;
                break;
            }


        }

        if (hasOnlyNulls && hasOne) {
            hasBasicVar[get<1>(onePosition)] = true;
            C[ci] = get<0>(onePosition);
            ci++;
        }
        
    }

    m = matrixOperations.createVectorBool(newMatrix.size());

    for(int i = 0; i < newMatrix.size(); i++)
    {
        m[i] = false;
    }

    for(int i = 0; i < constraints.size(); i++) {
        
        if(!hasBasicVar[i]) {

            vector<double> basicColumn = matrixOperations.createVector(constraints.size());    

            for(int j = 0; j < constraints.size(); j++) {
                basicColumn[j] = j == i ? 1 : 0;
            }    

            newMatrix = appendColumn(newMatrix,basicColumn);
            m = append(m, true);
            C[ci] = newMatrix.size() - 1;
            ci++;
        }
        
    }

    b = matrixOperations.CopyVector(Bs);
    _matrix = matrixOperations.CopyMatrix(newMatrix);
} 
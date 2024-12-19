#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include <math.h>
#include <tuple>
#include "Simplex.h"
#include "Models.h"

using namespace std;

typedef struct _IndexValuePair
{
    double value;
    int index;
} IndexValuePair;

class MatrixOperations
{
private:
    Simplex simplex;
    LinSysResult linSysResult;

public:
    MatrixOperations();
    ~MatrixOperations();
    vector<double> VecCum(vector<double> &vec);
    vector<vector<double>> MatTranspose(const vector<vector<double>> &Matrix);
    vector<vector<double>> unitmatrix(vector<vector<double>> &Matrix);
    vector<vector<double>> ScalarMatrixMultiplication(const double &scalar, vector<vector<double>> &Matrix);
    vector<double> ScalarVectorMultiplication(const double &scalar, const vector<double> &vec);
    vector<double> ConvertDiaMatrixtoVector(vector<vector<double>> &a);
    vector<vector<double>> SubMatrix(vector<vector<double>> &MatrixA,
                                     const int &StartRow, const int &StartCol, const int &EndRow, const int &EndCol);
    vector<vector<double>> MatSubstract(vector<vector<double>> &MatrixA,
                                        vector<vector<double>> &MatrixB);
    vector<vector<double>> MatAdd(vector<vector<double>> &MatrixA,
                                  vector<vector<double>> &MatrixB);
    vector<vector<double>> MatMult(vector<vector<double>> &MatrixA,
                                   vector<vector<double>> &MatrixB);
    vector<vector<double>> Vector2Matrix(const vector<double> &vec);
    vector<double> Mat2Vec(const vector<vector<double>> &Matrix);
    vector<double> CopyVector(vector<double> &vec);
    vector<int> CopyVector(vector<int> &vec);
    vector<bool> CopyVector(vector<bool> &vec);
    vector<string> CopyVector(vector<string> &vec);
    vector<vector<double>> CopyMatrix(vector<vector<double>> &XX1);
    vector<double> CalcualatePolynomial(vector<double> &PolyCoeffs, vector<double> &x,
                                        int &PolynomialOrder);
    vector<vector<double>> horzcat(vector<vector<double>> &xx,
                                   vector<vector<double>> &XX1);
    vector<vector<double>> CreatMatrixFromPolyCoeffs(vector<double> &PolyCoeffs,
                                                     int &PolynomialOrder);
    vector<vector<double>> ZeroMatrix(vector<vector<double>> &MatrixA);
    vector<double> ZeroVector(vector<double> &vec);
    vector<vector<double>> OveWriteMatrix(vector<vector<double>> &MatrixA,
                                          const int &StartRow, const int &StartCol, const int &EndRow, const int &EndCol,
                                          vector<vector<double>> &ReplaceWith);
    double norm(vector<vector<double>> &Matrix);
    double Vectornorm(const vector<double> &vec);
    vector<vector<double>> DiagonalMatrix(vector<vector<double>> &MatrixA);
    double VectorMinimun(vector<double> &a);
    int VectorMinIndex(vector<double> &a);
    double VectorMaximum(vector<double> &a);
    int VectorMaximumInt(vector<int> &a);
    double MatrixMaximum(vector<vector<double>> a);
    double MatrixMinimum(vector<vector<double>> a);
    vector<vector<double>> VecMatAdd(vector<vector<double>> &Matrix,
                                     vector<double> &vec);
    vector<double> VecSubstract(const vector<double> &vecA,
                                const vector<double> &vecB);
    vector<double> VecAdd(const vector<double> &vecA,
                          const vector<double> &vecB);
    vector<vector<double>> VecMatSubtract(vector<vector<double>> &Matrix,
                                          vector<double> &vec);
    vector<vector<double>> MatVecSubtract(vector<vector<double>> &Matrix,
                                          vector<double> &vec);
    double SumofSquares(vector<vector<double>> &Matrix);
    vector<vector<double>> BubbleSortMatrix(vector<vector<double>> &Matrix, int &sortcolumn);
    vector<double> BubbleSortVector(vector<double> &vec);
    tuple<vector<double>, vector<int>> BubbleSortVector2(vector<double> &vec);
    vector<vector<double>> LU_Decomposition(vector<vector<double>> &LHS3, vector<vector<double>> &RHS3);
    vector<double> Get_s(vector<vector<double>> &a);
    LinSysResult LowerUpperTriangularMatrix(vector<vector<double>> &A);
    vector<vector<double>> ForwardSubstitution(vector<vector<double>> &LT, vector<vector<double>> &ColMat);
    vector<vector<double>> BackSubstitution(vector<vector<double>> &HCat);
    vector<double> createVector(const int &rows);
    vector<int> createVectorInt(const int &rows);
    vector<bool> createVectorBool(const int &rows);
    vector<string> createVectorString(const int &rows);
    vector<vector<double>> createMatrix(const int &rows, const int &cols);
    vector<vector<string>> createMatrixString(const int &rows, const int &cols);
    vector<vector<double>> Eye(int N);
};

MatrixOperations::MatrixOperations()
{
}

MatrixOperations::~MatrixOperations()
{
}

vector<vector<double>> MatrixOperations::Eye(int N)
{

    int nrow = N;
    int ncol = N;
    vector<vector<double>> IMatrix = createMatrix(nrow, ncol);
    for (int j = 0; j < ncol; j++)
    {
        for (int i = 0; i < nrow; i++)
        {
            if (i == j)
            {
                IMatrix[i][j] = 1;
            }
            else
            {
                IMatrix[i][j] = 0;
            }
        }
    }

    return IMatrix;
}

vector<vector<double>> MatrixOperations::createMatrix(const int &rows, const int &cols)
{
    vector<vector<double>> ans;

    for (int i = 0; i < rows; i++)
    {

        vector<double> Row;
        for (int j = 0; j < cols; j++)
        {
            Row.push_back(0);
        }

        ans.push_back(Row);
    }

    return ans;
}

vector<vector<string>> MatrixOperations::createMatrixString(const int &rows, const int &cols)
{
    vector<vector<string>> ans;

    for (int i = 0; i < rows; i++)
    {

        vector<string> Row;
        for (int j = 0; j < cols; j++)
        {
            Row.push_back("");
        }

        ans.push_back(Row);
    }

    return ans;
}

vector<double> MatrixOperations::createVector(const int &rows)
{
    vector<double> ans;

    for (int i = 0; i < rows; i++)
    {
        ans.push_back(0);
    }

    return ans;
}

vector<string> MatrixOperations::createVectorString(const int &rows)
{
    vector<string> ans;

    for (int i = 0; i < rows; i++)
    {
        ans.push_back("");
    }

    return ans;
}

vector<bool> MatrixOperations::createVectorBool(const int &rows)
{
    vector<bool> ans;

    for (int i = 0; i < rows; i++)
    {
        ans.push_back(false);
    }

    return ans;
}

vector<int> MatrixOperations::createVectorInt(const int &rows)
{
    vector<int> ans;

    for (int i = 0; i < rows; i++)
    {
        ans.push_back(0);
    }

    return ans;
}
vector<double> MatrixOperations::VecCum(vector<double> &vec)
{

    vector<double> SumVector;
    int i;
    int nrow = vec.size();
    SumVector = createVector(nrow);
    SumVector[0] = vec[0];
    for (i = 1; i < nrow; i++)
    {
        SumVector[i] = SumVector[i - 1] + vec[i];
    }

    return SumVector;
}

vector<vector<double>> MatrixOperations::MatTranspose(const vector<vector<double>> &Matrix)
{

    vector<vector<double>> MatrixT;
    int ncol, nrow, i, j;
    nrow = Matrix.size();
    ncol = Matrix[0].size();

    MatrixT = createMatrix(ncol, nrow);

    for (j = 0; j < ncol; j++)
    {
        for (i = 0; i < nrow; i++)
        {
            MatrixT[j][i] = Matrix[i][j];
        }
    }

    return MatrixT;
}

vector<vector<double>> MatrixOperations::unitmatrix(vector<vector<double>> &Matrix)
{

    int ncol, nrow, i, j;
    nrow = Matrix.size();
    ncol = Matrix[0].size();
    vector<vector<double>> IMatrix = createMatrix(nrow, ncol);
    for (j = 0; j < ncol; j++)
    {
        for (i = 0; i < nrow; i++)
        {
            if (i == j)
            {
                IMatrix[i][j] = 1;
            }
            else
            {
                IMatrix[i][j] = 0;
            }
        }
    }

    return IMatrix;
}

vector<vector<double>> MatrixOperations::ScalarMatrixMultiplication(const double &scalar,
                                                                    vector<vector<double>> &Matrix)
{

    int ncol, nrow, i, j;
    nrow = Matrix.size();
    ncol = Matrix[0].size();
    vector<vector<double>> result = createMatrix(nrow, ncol);
    for (j = 0; j < ncol; j++)
    {
        for (i = 0; i < nrow; i++)
        {
            result[i][j] = scalar * Matrix[i][j];
        }
    }

    return result;
}

vector<double> MatrixOperations::ScalarVectorMultiplication(const double &scalar,
                                                            const vector<double> &vec)
{

    int ncol, nrow, i;
    nrow = vec.size();
    vector<double> result = createVector(nrow);
    for (i = 0; i < nrow; i++)
    {
        result[i] = scalar * vec[i];
    }

    return result;
}

vector<double> MatrixOperations::ConvertDiaMatrixtoVector(vector<vector<double>> &a)
{
    int i = 0, nrow = a.size();
    vector<double> x = createVector(nrow);
    for (i = 0; i < nrow; i++)
    {
        x[i] = a[i][i];
    }

    return x;
}

vector<vector<double>> MatrixOperations::SubMatrix(vector<vector<double>> &MatrixA,
                                                   const int &StartRow, const int &StartCol, const int &EndRow, const int &EndCol)
{

    int i, j, ncolB, nrowA;
    nrowA = EndRow - StartRow + 1;
    ncolB = EndCol - StartCol + 1;
    vector<vector<double>> CloneMatrix = createMatrix(nrowA, ncolB);
    for (j = StartCol; j <= EndCol; j++)
    {
        for (i = StartRow; i <= EndRow; i++)
        {
            // CloneMatrix[i - StartRow][j - StartCol] = MatrixA[i-1][j-1];
            CloneMatrix[i - StartRow][j - StartCol] = MatrixA[i][j];
        }
    }

    return CloneMatrix;
}

vector<vector<double>> MatrixOperations::MatSubstract(vector<vector<double>> &MatrixA,
                                                      vector<vector<double>> &MatrixB)
{

    int ncol, nrow, i, j;
    nrow = MatrixA.size();
    ncol = MatrixA[0].size();
    vector<vector<double>> SubstractionMat = createMatrix(nrow, ncol);
    for (j = 0; j < ncol; j++)
    {
        for (i = 0; i < nrow; i++)
        {
            SubstractionMat[i][j] = MatrixA[i][j] - MatrixB[i][j];
        }
    }

    return SubstractionMat;
}

vector<vector<double>> MatrixOperations::MatAdd(vector<vector<double>> &MatrixA,
                                                vector<vector<double>> &MatrixB)
{

    int ncol, nrow, i, j;
    nrow = MatrixA.size();
    ncol = MatrixA[0].size();
    vector<vector<double>> AddMat = createMatrix(nrow, ncol);
    for (j = 0; j < ncol; j++)
    {
        for (i = 0; i < nrow; i++)
        {
            AddMat[i][j] = MatrixA[i][j] + MatrixB[i][j];
        }
    }

    return AddMat;
}

vector<vector<double>> MatrixOperations::MatMult(vector<vector<double>> &MatrixA,
                                                 vector<vector<double>> &MatrixB)
{

    int i, j, k, ncolB, nrowA, nrowB;
    double sum = 0;
    nrowA = MatrixA.size();
    ncolB = MatrixB[0].size();
    nrowB = MatrixB.size();
    vector<vector<double>> MultMat = createMatrix(nrowA, ncolB);
    for (j = 0; j < nrowA; j++)
    {
        for (i = 0; i < ncolB; i++)
        {
            sum = 0;
            for (k = 0; k < nrowB; k++)
            {
                sum = sum + MatrixA[j][k] * MatrixB[k][i];
            }
            MultMat[j][i] = sum;
        }
    }
    return MultMat;
}

vector<vector<double>> MatrixOperations::Vector2Matrix(const vector<double> &vec)
{
    int nrow = vec.size(), ncol = 1, i = 0;
    vector<vector<double>> Matrix = createMatrix(nrow, ncol);
    for (i = 0; i < nrow; i++)
    {
        Matrix[i][0] = vec[i];
    }

    return Matrix;
}

vector<double> MatrixOperations::Mat2Vec(const vector<vector<double>> &Matrix)
{
    int i, nrow = Matrix.size();
    vector<double> vec = createVector(nrow);
    for (i = 0; i < nrow; i++)
    {
        vec[i] = Matrix[i][0];
    }

    return vec;
}

vector<double> MatrixOperations::CopyVector(vector<double> &vec)
{
    int i, nrow = vec.size();
    vector<double> vec2 = createVector(nrow);
    for (i = 0; i < nrow; i++)
    {
        vec2[i] = vec[i];
    }

    return vec2;
}

vector<int> MatrixOperations::CopyVector(vector<int> &vec)
{
    int i, nrow = vec.size();
    vector<int> vec2 = createVectorInt(nrow);
    for (i = 0; i < nrow; i++)
    {
        vec2[i] = vec[i];
    }

    return vec2;
}

vector<bool> MatrixOperations::CopyVector(vector<bool> &vec)
{
    int i, nrow = vec.size();
    vector<bool> vec2 = createVectorBool(nrow);
    for (i = 0; i < nrow; i++)
    {
        vec2[i] = vec[i];
    }

    return vec2;
}

vector<string> MatrixOperations::CopyVector(vector<string> &vec)
{
    int i, nrow = vec.size();
    vector<string> vec2 = createVectorString(nrow);
    for (i = 0; i < nrow; i++)
    {
        vec2[i] = vec[i];
    }

    return vec2;
}

vector<vector<double>> MatrixOperations::CopyMatrix(vector<vector<double>> &XX1)
{
    int i, j, nrow, ncol;
    nrow = XX1.size();
    ncol = XX1[0].size();
    vector<vector<double>> xx = createMatrix(nrow, ncol);
    for (j = 0; j < ncol; j++)
    {
        for (i = 0; i < nrow; i++)
        {
            xx[i][j] = XX1[i][j];
        }
    }

    return xx;
}

vector<double> MatrixOperations::CalcualatePolynomial(vector<double> &PolyCoeffs, vector<double> &x,
                                                      int &PolynomialOrder)
{

    int i, j, nrow, ncol;
    nrow = x.size();
    double sum1 = 0;
    ncol = PolynomialOrder;
    vector<double> vec = createVector(nrow);
    for (i = 0; i < nrow; i++)
    {
        sum1 = 0;
        for (j = 0; j < ncol; j++)
        {
            sum1 = sum1 + PolyCoeffs[j] * pow(x[i], (ncol - j));
        }
        vec[i] = sum1;
    }

    return vec;
}

vector<vector<double>> MatrixOperations::horzcat(vector<vector<double>> &xx,
                                                 vector<vector<double>> &XX1)
{

    int i, j, nrow, ncol1, ncol2;
    nrow = xx.size();
    ncol1 = xx[0].size();
    ncol2 = XX1[0].size();
    int ncol = ncol1 + ncol2;
    vector<vector<double>> XX2 = createMatrix(nrow, ncol);
    for (j = 0; j < ncol1; j++)
    {
        for (i = 0; i < nrow; i++)
        {
            XX2[i][j] = xx[i][j];
        }
    }

    for (j = 0; j < ncol2; j++)
    {
        for (i = 0; i < nrow; i++)
        {
            XX2[i][j + ncol - 1] = XX1[i][j];
        }
    }

    return XX2;
}

vector<vector<double>> MatrixOperations::CreatMatrixFromPolyCoeffs(vector<double> &PolyCoeffs,
                                                                   int &PolynomialOrder)
{

    int i, j, nrow, ncol;
    nrow = PolyCoeffs.size();
    ncol = PolynomialOrder;
    vector<vector<double>> Matrix = createMatrix(nrow, ncol);
    for (i = 0; i < nrow; i++)
    {
        for (j = 0; j < ncol; j++)
        {
            Matrix[i][j] = pow(PolyCoeffs[i], (ncol - j));
        }
    }

    return Matrix;
}

vector<vector<double>> MatrixOperations::ZeroMatrix(vector<vector<double>> &MatrixA)
{
    int nrow;
    nrow = MatrixA.size();
    vector<vector<double>> ZeroMat = createMatrix(nrow, nrow);
    return ZeroMat;
}

vector<double> MatrixOperations::ZeroVector(vector<double> &vec)
{
    int nrow = vec.size();
    return createVector(nrow);
}

vector<vector<double>> MatrixOperations::OveWriteMatrix(vector<vector<double>> &MatrixA,
                                                        const int &StartRow, const int &StartCol, const int &EndRow, const int &EndCol,
                                                        vector<vector<double>> &ReplaceWith)
{

    int i, j;
    vector<vector<double>> MatrixA1 = CopyMatrix(MatrixA);
    for (j = StartCol; j <= EndCol; j++)
    {
        for (i = StartRow; i <= EndRow; i++)
        {
            MatrixA1[i - 1][j - 1] = ReplaceWith[i - StartRow][j - StartCol];
        }
    }
    return MatrixA1;
}

double MatrixOperations::norm(vector<vector<double>> &Matrix)
{
    int i = 0, j = 0;
    double num = 0, sum = 0;
    int nRows = Matrix.size();
    int nCols = Matrix[0].size();
    for (i = 0; i < nRows; i++)
    {
        for (j = 0; j < nCols; j++)
        {
            sum = sum + pow(Matrix[i][j], 2);
        }
    }

    num = pow(sum, 0.5);
    return num;
}

double MatrixOperations::Vectornorm(const vector<double> &vec)
{
    int i = 0;
    double num = 0, sum = 0;
    int nRows = vec.size();
    for (i = 0; i < nRows; i++)
    {
        sum = sum + pow(vec[i], 2);
    }

    num = pow(sum, 0.5);
    return num;
}

vector<vector<double>> MatrixOperations::DiagonalMatrix(vector<vector<double>> &MatrixA)
{
    int i;
    int nRows = MatrixA.size(), nCols = MatrixA[0].size();
    vector<vector<double>> DiagMatrixA = createMatrix(nRows, nCols);
    for (i = 0; i < nRows; i++)
    {
        DiagMatrixA[i][i] = MatrixA[i][i];
    }
    return DiagMatrixA;
}

double MatrixOperations::VectorMinimun(vector<double> &a)
{
    int i = 0, nRows = a.size();
    double xmin = a[0];
    for (i = 0; i < nRows; i++)
    {
        if (a[i] < xmin)
        {
            xmin = a[i];
        }
    }

    return xmin;
}

int MatrixOperations::VectorMinIndex(vector<double> &a)
{
    int i = 0, nRows = a.size();
    int ii = 0;
    double xmin = a[0];
    for (i = 0; i < nRows; i++)
    {
        if (a[i] < xmin)
        {
            xmin = a[i];
            ii = i;
        }
    }

    return ii;
}

double MatrixOperations::VectorMaximum(vector<double> &a)
{
    int i = 0, nRows = a.size();
    double xmax = a[0];
    for (i = 0; i < nRows; i++)
    {
        if (a[i] > xmax)
        {
            xmax = a[i];
        }
    }

    return xmax;
}

int MatrixOperations::VectorMaximumInt(vector<int> &a)
{
    int i = 0, nRows = a.size();
    int xmax = a[0];
    for (i = 0; i < nRows; i++)
    {
        if (a[i] > xmax)
        {
            xmax = a[i];
        }
    }

    return xmax;
}

double MatrixOperations::MatrixMaximum(vector<vector<double>> a)
{
    int i = 0, j = 0;
    double xmax = a[0][0];
    int nRows = a.size();
    int nCols = a[0].size();
    for (j = 0; j < nCols; j++)
    {
        for (i = 0; i < nRows; i++)
        {
            if (a[i][j] > xmax)
            {
                xmax = a[i][j];
            }
        }
    }

    return xmax;
}

double MatrixOperations::MatrixMinimum(vector<vector<double>> a)
{
    int i = 0, j = 0;
    double xmin = a[0][0];
    int nRows = a.size();
    int nCols = a[0].size();
    for (j = 0; j < nCols; j++)
    {
        for (i = 0; i < nRows; i++)
        {
            if (a[i][j] < xmin)
            {
                xmin = a[i][j];
            }
        }
    }

    return xmin;
}

vector<vector<double>> MatrixOperations::VecMatAdd(vector<vector<double>> &Matrix,
                                                   vector<double> &vec)
{
    int i, j, ncol, nrow;
    nrow = Matrix.size();
    ncol = Matrix[0].size();
    vector<vector<double>> AddMat = createMatrix(nrow, ncol);
    for (j = 0; j < ncol; j++)
    {
        for (i = 0; i < nrow; i++)
        {
            AddMat[i][j] = Matrix[i][j] + vec[i];
        }
    }
    return AddMat;
}

vector<double> MatrixOperations::VecSubstract(const vector<double> &vecA,
                                              const vector<double> &vecB)
{
    int i, nrow;
    nrow = vecA.size();
    vector<double> vec = createVector(nrow);
    for (i = 0; i < nrow; i++)
    {
        vec[i] = vecA[i] - vecB[i];
    }
    return vec;
}

vector<double> MatrixOperations::VecAdd(const vector<double> &vecA,
                                        const vector<double> &vecB)
{
    int i, nrow;
    nrow = vecA.size();
    vector<double> vec = createVector(nrow);
    for (i = 0; i < nrow; i++)
    {
        vec[i] = vecA[i] + vecB[i];
    }
    return vec;
}

vector<vector<double>> MatrixOperations::VecMatSubtract(vector<vector<double>> &Matrix,
                                                        vector<double> &vec)
{
    int i, j, ncol, nrow;
    nrow = Matrix.size();
    ncol = Matrix[0].size();
    vector<vector<double>> AddMat = createMatrix(nrow, ncol);
    for (j = 0; j < ncol; j++)
    {
        for (i = 0; i < nrow; i++)
        {
            AddMat[i][j] = vec[i] - Matrix[i][j];
        }
    }
    return AddMat;
}

vector<vector<double>> MatrixOperations::MatVecSubtract(vector<vector<double>> &Matrix,
                                                        vector<double> &vec)
{
    int i, j, ncol, nrow;
    nrow = Matrix.size();
    ncol = Matrix[0].size();
    vector<vector<double>> AddMat = createMatrix(nrow, ncol);
    for (j = 0; j < ncol; j++)
    {
        for (i = 0; i < nrow; i++)
        {
            AddMat[i][j] = Matrix[i][j] - vec[i];
        }
    }
    return AddMat;
}

double MatrixOperations::SumofSquares(vector<vector<double>> &Matrix)
{
    int i = 0;
    double sum = 0;
    int nRows = Matrix.size();
    for (i = 0; i < nRows; i++)
    {
        sum = sum + pow(Matrix[i][0], 2);
    }

    return sum;
}

vector<vector<double>> MatrixOperations::BubbleSortMatrix(vector<vector<double>> &Matrix, int &sortcolumn)
{
    int icol, inner, outer, ncol;
    double Temp;
    ncol = Matrix[0].size();
    vector<vector<double>> Matrix2 = CopyMatrix(Matrix);
    for (outer = ncol; outer >= 0; outer--)
    {
        for (inner = 0; inner < outer - 1; inner++)
        {
            if (Matrix2[inner][sortcolumn] > Matrix2[inner + 1][sortcolumn])
            {
                for (icol = 0; icol < ncol; icol++)
                {
                    Temp = Matrix2[inner][icol];
                    Matrix2[inner][icol] = Matrix2[inner + 1][icol];
                    Matrix2[inner + 1][icol] = Temp;
                }
            }
        }
    }
    return Matrix2;
}

vector<double> MatrixOperations::BubbleSortVector(vector<double> &vec)
{
    int inner = 0, outer = 0;
    vector<double> vec2 = CopyVector(vec);
    int nRows = vec2.size();
    double Temp = 0;
    for (outer = nRows; outer >= 0; outer--)
    {
        for (inner = 0; inner < outer - 1; inner++)
        {
            if (vec2[inner] > vec2[inner + 1])
            {
                Temp = vec2[inner];
                vec2[inner] = vec2[inner + 1];
                vec2[inner + 1] = Temp;
            }
        }
    }

    return vec2;
}

tuple<vector<double>, vector<int>> MatrixOperations::BubbleSortVector2(vector<double> &vec)
{
    vector<IndexValuePair> vecList;
    vector<IndexValuePair> vec2List;
    int inner = 0, outer = 0;
    IndexValuePair Temp;
    int i = 0, nRows = vec.size();
    for (i = 0; i < nRows; i++)
    {
        IndexValuePair vec_i;
        vec_i.index = i;
        vec_i.value = vec[i];
        vecList.push_back(vec_i);
        vec2List.push_back(vec_i);
    }

    for (outer = nRows; outer >= 0; outer--)
    {
        for (inner = 0; inner < outer - 1; inner++)
        {
            if (vec2List[inner].value > vec2List[inner + 1].value)
            {
                Temp = vec2List[inner];
                vec2List[inner] = vec2List[inner + 1];
                vec2List[inner + 1] = Temp;
            }
        }
    }

    vector<double> vec2;
    vector<int> vec2Indices;

    for (i = 0; i < nRows; i++)
    {
        vec2.push_back(vec2List[i].value);
        vec2Indices.push_back(vec2List[i].index);
    }

    return make_tuple(vec2, vec2Indices);
}

vector<double> MatrixOperations::Get_s(vector<vector<double>> &a)
{
    int i = 0, j = 0;
    int n = a.size();
    vector<double> s = createVector(n);
    for (i = 0; i < n; i++)
    {
        s[i] = abs(a[i][1]);
        for (j = 0; j < n; j++)
        {
            if (abs(a[i][j]) > s[i])
            {
                s[i] = abs(a[i][j]);
            }
        }
    }

    return s;
}

LinSysResult MatrixOperations::LowerUpperTriangularMatrix(vector<vector<double>> &A)
{
    vector<vector<double>> UT = CopyMatrix(A);
    vector<vector<double>> TempRow1;
    vector<vector<double>> TempRow2;
    vector<vector<double>> Row1, Row2;
    int N = UT.size(), nCols = UT[0].size(), k, i;
    double multiplier = 0;
    vector<vector<double>> LT = unitmatrix(UT);

    for (k = 0; k < N - 1; k++)
    {

        Row1 = SubMatrix(UT, k + 1, 1, k + 1, nCols); // UT[k + 1, ":"];
        for (i = k + 1; i < N; i++)
        {
            Row2 = SubMatrix(UT, i + 1, 1, i + 1, nCols); // UT[i + 1, ":"];
            multiplier = Row2[0][k] / Row1[0][k];
            TempRow1 = ScalarMatrixMultiplication(multiplier, Row1);
            TempRow2 = MatSubstract(Row2, TempRow1);
            // vector<vector<double>> BB;
            UT = OveWriteMatrix(UT, i + 1, 1, i + 1, nCols, TempRow2); // UT[i + 1, ":"] = TempRow2;
            LT[i][k] = multiplier;
        }
    }
    LinSysResult linSysResult;
    linSysResult.LowerTriangularMatrix = LT;
    linSysResult.UpperTriangularMatrix = UT;
    return linSysResult;
}

vector<vector<double>> MatrixOperations::ForwardSubstitution(vector<vector<double>> &LT, vector<vector<double>> &ColMat)
{
    int i, j, N;
    N = LT.size();
    vector<vector<double>> Z = createMatrix(N, 1);
    double sum = 0;
    Z[0][0] = ColMat[0][0] / LT[0][0];
    for (i = 1; i < N; i++)
    {
        sum = 0;
        for (j = 0; j <= (i - 1); j++)
        {
            sum = sum + LT[i][j] * Z[j][0];
        }
        Z[i][0] = (ColMat[i][0] - sum) / LT[i][i];
    }

    return Z;
}

vector<vector<double>> MatrixOperations::BackSubstitution(vector<vector<double>> &HCat)
{
    int nrows = HCat.size();
    int ncols = HCat[0].size();
    vector<vector<double>> A = SubMatrix(HCat, 1, 1, nrows, ncols - 1);
    vector<vector<double>> B = SubMatrix(HCat, 1, ncols, nrows, ncols);
    int N = A.size(), NN = N - 1;
    vector<vector<double>> x = createMatrix(N, 1);
    double summ = 0;

    if (A[NN][NN] == 0)
    {
        x[NN][0] = 0;
    }
    else
    {
        x[NN][0] = B[NN][0] / A[NN][NN];
    }

    for (int i = NN - 1; i >= 0; i--)
    {
        summ = 0;
        for (int j = i + 1; j <= NN; j++)
        {
            summ = summ + A[i][j] * x[j][0];
        }
        x[i][0] = (B[i][0] - summ) / A[i][i];
    }

    return x;
}

vector<vector<double>> MatrixOperations::LU_Decomposition(vector<vector<double>> &LHS3, vector<vector<double>> &RHS3)
{

    LinSysResult LU = LowerUpperTriangularMatrix(LHS3);
    vector<vector<double>> LT = LU.LowerTriangularMatrix;
    vector<vector<double>> UT = LU.UpperTriangularMatrix;
    vector<vector<double>> Z = ForwardSubstitution(LT, RHS3);
    vector<vector<double>> HC = horzcat(UT, Z);
    vector<vector<double>> X = BackSubstitution(HC);
    return X;
}

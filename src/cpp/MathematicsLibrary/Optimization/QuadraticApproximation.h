#pragma once

#include <math.h>
#include <tuple>
#include "../MatrixOperations.h"

class QuadraticApproximation
{
    private:
        MatrixOperations matrixOperations;
    public:
        QuadraticApproximation();
        ~QuadraticApproximation();
        vector<double> Opt_Quad0(function<double(vector<double>)> f, vector<double> x012,
        vector<double> f012, double TolX, double TolFun,int  k);
       vector<double> Opt_Quad(function<double(vector<double>)> f, vector<double> x0);
};

QuadraticApproximation::QuadraticApproximation(){

}

QuadraticApproximation::~QuadraticApproximation(){

}

vector<double> QuadraticApproximation::Opt_Quad(function<double(vector<double>)> f, vector<double> x0) 
{

	double TolX = pow(10, -4);
	double TolFun = pow(10, -9);
	int MaxIter = 100;

	double a = x0[0] - 0.2*x0[0];
	double b = x0[0] + 2.0*x0[0];
	vector<double> x012 = matrixOperations.createVector(3);
	x012[0] = a;
	x012[1] = (a + b) / 2.0;
	x012[2] = b;

	vector<double> f012 = matrixOperations.createVector(3);
	for (int i = 0; i < x012.size(); i++) 
    {
		f012[i] = f(vector<double>{x012[i]});
	}

	vector<double> ans = Opt_Quad0(f, x012, f012, TolX, TolFun, MaxIter);
	return ans; //xo, fo
}

 vector<double> QuadraticApproximation::Opt_Quad0(function<double(vector<double>)> f, vector<double> x012,
    vector<double> f012, double TolX, double TolFun,int  k){

    vector<double> ans;
	double x0 = x012[0];
	double x1 = x012[1];
	double x2 = x012[2];
	double f0 = f012[0];
	double f1 = f012[1];
	double f2 = f012[2];

	vector<vector<double>> f_RowMatrix = matrixOperations.createMatrix(1, 3);
	f_RowMatrix[0][0] = f0 - f2;
	f_RowMatrix[0][1] = f1 - f0;
	f_RowMatrix[0][2] = f2 - f1;

	vector<vector<double>> f_ColumnMatrix = matrixOperations.createMatrix(2, 3);
	f_ColumnMatrix[0][0] = x1 * x1;
	f_ColumnMatrix[0][1] = x2 * x2;
	f_ColumnMatrix[0][2] = x0 * x0;
	f_ColumnMatrix[1][0] = x1;
	f_ColumnMatrix[1][1] = x2;
	f_ColumnMatrix[1][2] = x0;
	vector<vector<double>> f_ColumnMatrix_T = matrixOperations.MatTranspose(f_ColumnMatrix);
	vector<vector<double>> nd = matrixOperations.MatMult(f_RowMatrix, f_ColumnMatrix_T);
	double x3 = nd[0][0] / 2.0 / nd[0][1];
	double f3 = f(vector<double>{x3});
	double xo = 0;
	double fo = 0;
	if (k <= 0 || abs(x3-x1) < TolX || abs(f3-f1) < TolFun)
    {
		xo = x3;
		fo = f3;
		if (k == 0) 
        {
			std::cout << "Just the best in given # of iterations";
		}
	} 
    else 
    {
		if (x3 < x1) 
        {
			if (f3 < f1) 
            {
				x012 = matrixOperations.createVector(3);
				x012[0] = x0;
				x012[1] = x3;
				x012[2] = x1;
				f012 = matrixOperations.createVector(3);
				f012[0] = f0;
				f012[1] = f3;
				f012[2] = f1;
			} 
            else 
            {
				x012 = matrixOperations.createVector(3);
				x012[0] = x3;
				x012[1] = x1;
				x012[2] = x2;
				f012 = matrixOperations.createVector(3);
				f012[0] = f3;
				f012[1] = f1;
				f012[2] = f2;
			}
		} 
        else {
			if (f3 <= f1) 
            {
				x012 = matrixOperations.createVector(3);
				x012[0] = x1;
				x012[1] = x3;
				x012[2] = x2;
				f012 = matrixOperations.createVector(3);
				f012[0] = f1;
				f012[1] = f3;
				f012[2] = f2;
			} 
            else 
            {
				x012 = matrixOperations.createVector(3);
				x012[0] = x0;
				x012[1] = x1;
				x012[2] = x3;
				f012 = matrixOperations.createVector(3);
				f012[0] = f0;
				f012[1] = f1;
				f012[2] = f3;
			}
		}
		ans = Opt_Quad0(f, x012,
			f012, TolX, TolFun, k-1);
        //Set Tuple -->  tupleObject = make_tuple(snaps, result.result);
        //Get Tuple --> vector<SimplexSnap> snaps = get<0>(result);
	}
	return ans; //xo, fo
        
}
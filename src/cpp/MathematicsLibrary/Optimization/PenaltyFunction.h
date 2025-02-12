#pragma once

#include <math.h>
#include <tuple>
#include <functional>
#include "../MatrixOperations.h"

class PenaltyFunction
{
    private:
        MatrixOperations matrixOperations;
    public:
        PenaltyFunction();
        ~PenaltyFunction();

        tuple<double, double, vector<double>> ArgumentedFunction(
	    function<double(vector<double>)> f, vector<double> x,
		vector<double> weights,
	    vector<double> lb, vector<double> ub);
		tuple<double, double, vector<double>> ArgumentedFunction2(
	    function<double(vector<double>)> f, vector<double> x,
		vector<double> weights,
	    function<vector<double>(vector<double>)> constraints);
};

PenaltyFunction::PenaltyFunction(){

}

PenaltyFunction::~PenaltyFunction(){

}

tuple<double, double, vector<double>> PenaltyFunction::ArgumentedFunction(
	    function<double(vector<double>)> f, vector<double> x,
		vector<double> weights,
	    vector<double> lb, vector<double> ub) 
{

	//vector<double> v=[1 1 1 1 1]; e = [1 1 1 1 1]’
	double e = 1;

	vector<double> c;
	vector<double> v;
	for (int i = 0; i < x.size(); i++) 
    {
		double c_lb = lb[i] - x[i];
		double c_ub = x[i] - ub[i];

		if (c_lb <= 0) 
        {
			c_lb = 0;
		} 
        else 
        {
			c_lb = exp(e * c_lb);
		}
		c.push_back(c_lb);
		v.push_back(1);

		if (c_ub <= 0) 
        {
			c_ub = 0;
		} 
        else 
        {
			c_ub = exp(e * c_ub);
		}
		c.push_back(c_ub);
		v.push_back(weights[i]);
	}

	vector<vector<double>> v_mat_T = matrixOperations.MatTranspose(matrixOperations.Vector2Matrix(v));
	vector<vector<double>> c_mat = matrixOperations.Vector2Matrix(c);
	vector<vector<double>> inEqC = matrixOperations.MatMult(v_mat_T, c_mat);
	double f_unC = f(x);
	double fc = f_unC + inEqC[0][0];
	return make_tuple(fc, f_unC, c);
}


tuple<double, double, vector<double>> PenaltyFunction::ArgumentedFunction2(
	    function<double(vector<double>)> f, vector<double> x,
		vector<double> weights,
	    function<vector<double>(vector<double>)> constraints) 
{

	
	double e = 1;

	vector<double> c;
	vector<double> v;
	vector<double> fcc = constraints(x);

	for (int i = 0; i < weights.size(); i++) 
    {
		if (fcc[i] <= 0) 
        {
			c.push_back(0);
		} 
        else 
        {
			c.push_back(e * fcc[i]);
		}
		v.push_back(weights[i]);
	}

	vector<vector<double>> v_mat_T = matrixOperations.MatTranspose(matrixOperations.Vector2Matrix(v));
	vector<vector<double>> c_mat = matrixOperations.Vector2Matrix(c);
	vector<vector<double>> inEqC = matrixOperations.MatMult(v_mat_T, c_mat);
	double f_unC = f(x);
	double fc = f_unC + inEqC[0][0];
	return make_tuple(fc, f_unC, c);
}
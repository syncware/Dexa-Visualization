#pragma once

#include <math.h>
#include <tuple>
#include <functional>
#include "../MatrixOperations.h"
#include "./QuadraticApproximation.h"
#include "./PenaltyFunction.h"
;
class Nelder_Mead
{
private:
	MatrixOperations matrixOperations;
	QuadraticApproximation quadraticApproximation;
	PenaltyFunction penaltyFunction;

	function<double(vector<double>)> f_copy;
	vector<double> lb_copy;
	vector<double> ub_copy;
	vector<double> xo;
	vector<double> weights_copy;
	function<vector<double>(vector<double>)> constraints_copy;
	double fo;

public:
	Nelder_Mead();
	~Nelder_Mead();

	tuple<double, double, vector<double>> ArgumentedFunction(
		function<double(vector<double>)> f, vector<double> x,
		vector<double> lb, vector<double> ub);

	void Nelder0(function<double(vector<double>)> f,
				 vector<vector<double>> abc, vector<double> _fabc, double TolX, double TolFun,
				 int k);
	tuple<vector<double>, double> Opt_Nelder(function<double(vector<double>)> f, vector<double> x0);

	tuple<vector<double>, double, vector<double>> Opt_Nelder_Constrained(function<double(vector<double>)> f, vector<double> x0,
																		 vector<double> weights, vector<double> lb, vector<double> ub);

	tuple<vector<double>, double, vector<double>> Opt_Nelder_Constrained2(function<double(vector<double>)> f, vector<double> x0,
																		  vector<double> weights, function<vector<double>(vector<double>)> constraints);

	double objectiveFunction(vector<double> x);
	double objectiveFunction2(vector<double> x);
};

Nelder_Mead::Nelder_Mead()
{
}

Nelder_Mead::~Nelder_Mead()
{
}

double Nelder_Mead::objectiveFunction(vector<double> x)
{
	tuple<double, double, vector<double>> ans = penaltyFunction.ArgumentedFunction(f_copy, x, weights_copy, lb_copy, ub_copy);
	// ff, _, _
	double ff = get<0>(ans);
	return ff;
}

double Nelder_Mead::objectiveFunction2(vector<double> x)
{
	tuple<double, double, vector<double>> ans = penaltyFunction.ArgumentedFunction2(f_copy, x, weights_copy, constraints_copy);
	// ff, _, _
	double ff = get<0>(ans);
	return ff;
}

tuple<vector<double>, double, vector<double>> Nelder_Mead::Opt_Nelder_Constrained(function<double(vector<double>)> f, vector<double> x0,
																				  vector<double> weights, vector<double> lb, vector<double> ub)
{
	f_copy = f;
	lb_copy = lb;
	ub_copy = ub;
	weights_copy = weights;

	Nelder_Mead obj;
	auto funcP = bind(&Nelder_Mead::objectiveFunction, obj, std::placeholders::_1);
	tuple<vector<double>, double> ans = Opt_Nelder(funcP, x0);
	vector<double> xo_Nelder = get<0>(ans);																			// Nelder method
	tuple<double, double, vector<double>> ans2 = penaltyFunction.ArgumentedFunction(f, xo_Nelder, weights, lb, ub); // its results
	double fo_Nelder = get<1>(ans2);
	vector<double> co_Nelder = get<2>(ans2);
	return make_tuple(xo_Nelder, fo_Nelder, co_Nelder); // xo_Nelder, fo_Nelder, co_Nelder
}

tuple<vector<double>, double, vector<double>> Nelder_Mead::Opt_Nelder_Constrained2(function<double(vector<double>)> f, vector<double> x0,
																				   vector<double> weights, function<vector<double>(vector<double>)> constraints)
{

	f_copy = f;
	weights_copy = weights;
	constraints_copy = constraints;

	Nelder_Mead obj;
	obj.f_copy = f;
	obj.weights_copy = weights;
	obj.constraints_copy = constraints;
	auto funcP = bind(&Nelder_Mead::objectiveFunction2, obj, std::placeholders::_1);
	tuple<vector<double>, double> ans = Opt_Nelder(funcP, x0);
	vector<double> xo_Nelder = get<0>(ans);																				  // Nelder method
	tuple<double, double, vector<double>> ans2 = penaltyFunction.ArgumentedFunction2(f, xo_Nelder, weights, constraints); // its results
	double fo_Nelder = get<1>(ans2);
	vector<double> co_Nelder = get<2>(ans2);
	return make_tuple(xo_Nelder, fo_Nelder, co_Nelder); // xo_Nelder, fo_Nelder, co_Nelder
}

tuple<vector<double>, double> Nelder_Mead::Opt_Nelder(function<double(vector<double>)> f, vector<double> x0)
{
	double TolX = 1e-4;
	double TolFun = 1e-9;
	int MaxIter = 100;

	int N = x0.size();
	if (N == 1)
	{
		// for 1-dimensional case
		vector<double> xo1_fo1 = quadraticApproximation.Opt_Quad(f, x0);
		double xo1 = xo1_fo1[0];
		double fo1 = xo1_fo1[1];
		vector<double> xo = vector<double>{xo1};
		fo = fo1;
		return make_tuple(xo, fo); // xo, fo
	}

	vector<vector<double>> S = matrixOperations.Eye(N);
	for (int i = 0; i < N; i++)
	{
		// repeat the procedure for each subplane
		int i1 = i + 1;
		if (i1 > N - 1)
		{
			i1 = 1;
		}

		vector<double> Si = matrixOperations.Mat2Vec(matrixOperations.MatTranspose(matrixOperations.SubMatrix(S, i, 0, i, N - 1)));
		vector<double> x0Si = matrixOperations.VecAdd(x0, Si);

		vector<double> Si1 = matrixOperations.Mat2Vec(matrixOperations.MatTranspose(matrixOperations.SubMatrix(S, i1, 0, i1, N - 1)));
		vector<double> x0Si1 = matrixOperations.VecAdd(x0, Si1);
		vector<vector<double>> abc = vector<vector<double>>{x0, x0Si, x0Si1};
		vector<double> _a = matrixOperations.Mat2Vec(matrixOperations.MatTranspose(matrixOperations.SubMatrix(abc, 0, 0, 0, N - 1)));
		vector<double> _b = matrixOperations.Mat2Vec(matrixOperations.MatTranspose(matrixOperations.SubMatrix(abc, 1, 0, 1, N - 1)));
		vector<double> _c = matrixOperations.Mat2Vec(matrixOperations.MatTranspose(matrixOperations.SubMatrix(abc, 2, 0, 2, N - 1)));
		vector<double> fabc = vector<double>{
			f(_a),
			f(_b),
			f(_c),
		};
		Nelder0(f, abc, fabc, TolX, TolFun, MaxIter);

		if (N < 3)
		{
			// No repetition needed for a 2-dimensional case
			break;
		}
	}

	// xo = matrixOperations.CopyVector(x0);
	return make_tuple(xo, fo); // xo, fo
}

void Nelder_Mead::Nelder0(function<double(vector<double>)> f,
						  vector<vector<double>> abc, vector<double> _fabc, double TolX, double TolFun,
						  int k)
{
	tuple<vector<double>, vector<int>> fabc_I = matrixOperations.BubbleSortVector2(_fabc);
	vector<double> fabc = get<0>(fabc_I);
	vector<int> I = get<1>(fabc_I);
	int nCols = abc[0].size();
	int zero = 0;
	vector<double> a = matrixOperations.Mat2Vec(matrixOperations.MatTranspose(matrixOperations.SubMatrix(abc, I[0], 0, I[0], nCols - 1)));
	vector<double> b = matrixOperations.Mat2Vec(matrixOperations.MatTranspose(matrixOperations.SubMatrix(abc, I[1], 0, I[1], nCols - 1)));
	vector<double> c = matrixOperations.Mat2Vec(matrixOperations.MatTranspose(matrixOperations.SubMatrix(abc, I[2], 0, I[2], nCols - 1)));
	double fa = fabc[0];
	double fb = fabc[1];
	double fc = fabc[2];
	double fba = fb - fa;
	double fcb = fc - fb;

	double ba_Norm = matrixOperations.Vectornorm(matrixOperations.VecSubstract(b, a));
	double ca_Norm = matrixOperations.Vectornorm(matrixOperations.VecSubstract(c, a));
	if (k <= 0 || abs(fba) + abs(fcb) < TolFun ||
		ba_Norm + ca_Norm < TolX)
	{
		xo = matrixOperations.CopyVector(a);
		fo = fa;
		if (k == 0)
		{
			std::cout << "Just best in given # of iterations";
		}
	}
	else
	{
		vector<double> m = matrixOperations.ScalarVectorMultiplication(1 / 2.0, matrixOperations.VecAdd(a, b));
		vector<double> e = matrixOperations.VecSubstract(matrixOperations.ScalarVectorMultiplication(3, m),
														 matrixOperations.ScalarVectorMultiplication(2, c));
		double fe = f(e);
		if (fe < fb)
		{
			c = matrixOperations.CopyVector(e);
			fc = fe;
		}
		else
		{
			vector<double> r = matrixOperations.ScalarVectorMultiplication(1 / 2.0, matrixOperations.VecAdd(m, e));
			double fr = f(r);
			if (fr < fc)
			{
				c = matrixOperations.CopyVector(r);
				fc = fr;
			}
			if (fr >= fb)
			{
				vector<double> s = matrixOperations.ScalarVectorMultiplication(1 / 2.0, matrixOperations.VecAdd(c, m));
				double fs = f(s);
				if (fs < fc)
				{
					c = matrixOperations.CopyVector(s);
					fc = fs;
				}
				else
				{
					b = matrixOperations.CopyVector(m);
					c = matrixOperations.ScalarVectorMultiplication(1 / 2.0, matrixOperations.VecAdd(a, c));
					fb = f(b);
					fc = f(c);
				}
			}
		}

		vector<vector<double>> _abc = vector<vector<double>>{a, b, c};
		vector<double> _fabc = vector<double>{fa, fb, fc};
		Nelder0(f, _abc, _fabc, TolX, TolFun, k - 1);
	}
}

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <tuple>
#include "../Model/Problem2.h"

using namespace std;
class ProblemsService2
{
   
    public: 
        //public static ProblemsService shared = new ProblemsService();
        vector<Problem2> problems;
        ProblemsService2();
        Problem2 GetNext(int currentProblemIndex);
        void initDefaults();
};

 

ProblemsService2::ProblemsService2()
{
    initDefaults();
}

Problem2 ProblemsService2::GetNext(int currentProblemIndex)
{
    if (currentProblemIndex == problems.size())
    {
        currentProblemIndex = 0;
    }
    return problems[currentProblemIndex];
}

void ProblemsService2::initDefaults()
{

    vector<double> c91Vars = vector<double>{ 4, 5, 1, 2, 3, 1, 0 };
    vector<double> c92Vars = vector<double>{ 2, -10, 3, 1, 7,0,1 };
    vector<double> c93Vars = vector<double>{ 2, -2, 15, 2, -1,0,0 };

    vector<vector<double>> consMatrx9 = vector<vector<double>>{
        c91Vars,
        c92Vars,
        c93Vars
    };

    vector<string> signs9 = vector<string>{ "=", "=", "=" };
    vector<double> freeVars9 = vector<double>{ 35, 12, 28 };

    vector<double> funcVars9 = vector<double>{ 15, -4, 1, -3, 2,0,0 };

    problems.push_back(Problem2(consMatrx9, signs9, freeVars9, funcVars9, 0, true)); // 0


    vector<double> c51Vars = vector<double>{ 4, 5, 1, 2, 3 };
    vector<double> c52Vars = vector<double>{ 2, 15, -2, 1, -4 };
    vector<double> c53Vars = vector<double>{ 2, -2, 15, 2, -1 };

    vector<vector<double>> consMatrx5 = vector<vector<double>>{
        c51Vars,
        c52Vars,
        c53Vars
    };

    vector<string> signs5 = vector<string>{ "<=", ">=", "=" };
    vector<double> freeVars5 = vector<double>{ 35, 23, 28 };

    vector<double> funcVars5 = vector<double>{ 15, -4, 1, -3, 2 };

    problems.push_back(Problem2(consMatrx5, signs5, freeVars5, funcVars5, 0, true)); // 1

    vector<double> c1Vars = vector<double>{ 2, 3, 1, 2, 3 };
    vector<double> c2Vars = vector<double>{ 2, 15, 2, 1, -1 };
    vector<double> c3Vars = vector<double>{ 3, -2, 4, 2, -1 };

    vector<vector<double>> consMatrx =vector<vector<double>>{
        c1Vars,
        c2Vars,
        c3Vars
    };

    vector<string> signs = vector<string>{ "<=", "=", ">=" };
    vector<double> freeVars = vector<double>{ 35, 25, 16 };
    vector<double> funcVars = vector<double>{ 14, -22, 1, -3, 2 };

    problems.push_back(Problem2(consMatrx, signs, freeVars, funcVars, 0, true)); // 2

    vector<double> c11Vars = vector<double>{ 2, 0, 5, 1, 8 };

    vector<double> c12Vars = vector<double>{ -3, 6, 2, -2, 0 };

    vector<vector<double>> consMatrx1 = vector<vector<double>>{
        c11Vars,
        c12Vars
    };

    vector<string> signs1 =  vector<string>{ "=", "<=" };
    vector<double> freeVars1 = vector<double>{ 12, 5 };

    vector<double> funcVars1 = vector<double>{ 2, -1, 7, 11, 5 };

    problems.push_back(Problem2(consMatrx1, signs1, freeVars1, funcVars1, 0, false)); // 3

    vector<double> c21Vars = vector<double>{ 1, 1 };
    vector<double> c22Vars = vector<double>{ 2, 3 };
    vector<double> c23Vars = vector<double>{ 14, 30 };

    vector<vector<double>> consMatrx2 = vector<vector<double>>{
        c21Vars,
        c22Vars,
        c23Vars
    };

    vector<string> signs2 = vector<string>{ "<=", "<=", "<=" };
    vector<double> freeVars2 = { 550, 1200, 9600 };

    vector<double> funcVars2 = vector<double>{ 3, 4 };

    problems.push_back(Problem2(consMatrx2, signs2, freeVars2, funcVars2, 0, true)); // 4

    vector<double> c31Vars = vector<double>{ 1,1,-1 };
    vector<double> c32Vars = vector<double>{ 1,-1,2 };
    vector<double> c33Vars = vector<double>{ -2,-8,3 };

    vector<vector<double>> consMatrx3 = vector<vector<double>>{
        c31Vars,
        c32Vars,
        c33Vars
    };

    vector<string> signs3 = vector<string>{ ">=", ">=", ">=" };
    vector<double> freeVars3 = vector<double>{ 8, 2, 1 };

    vector<double> funcVars3 = vector<double>{ 2, 1, -2 };

    problems.push_back(Problem2(consMatrx3, signs3, freeVars3, funcVars3, 0, false)); // 5

    vector<double> c41Vars = vector<double>{ 0,-1,1,1,0 };
    vector<double> c42Vars = vector<double>{-5,1,1,0, 0 };
    vector<double> c43Vars = vector<double>{ -8,1,2,0,-1 };

    vector<vector<double>> consMatrx4 = vector<vector<double>>{
        c41Vars,
        c42Vars,
        c43Vars
    };

    vector<string> signs4 = vector<string>{ "=", "=", "=" };
    vector<double> freeVars4 = { 1,2,3 };

    vector<double> funcVars4 = { -3,1,4,0,0 };

    problems.push_back(Problem2(consMatrx4, signs4, freeVars4, funcVars4, 0, true)); // 66

    vector<double> c61Vars = vector<double>{ 1,1,-3,1,-1 };
    vector<double> c62Vars = vector<double>{ 6,-3,-1,-2,2 };
    vector<double> c63Vars = vector<double>{ 3,-2,1,2,3 };

    vector<vector<double>> consMatrx6 = vector<vector<double>>{
        c61Vars,
        c62Vars,
        c63Vars
    };

    vector<string> signs6 = vector<string>{ "=", ">=", "<=" };
    vector<double> freeVars6 = vector<double>{ 4,2,8 };

    vector<double> funcVars6 = vector<double>{2,3,-3,1,0 };

    problems.push_back(Problem2(consMatrx6, signs6, freeVars6, funcVars6, 0, true)); // 7

}

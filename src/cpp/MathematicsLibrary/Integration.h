#pragma once

#ifndef INTEGRATION_H
#define INTEGRATION_H




#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include <math.h>

using namespace std;


class  Integration
{
private:

public:

    double trapzd(function<double(double)> func, double& a, double& b, int& n);

    double qtrap(function<double(double)> func, double& a, double& b);

    double qsimp(function<double(double)> func, double& a, double& b);

    //double qromb(function<double(double)> func, double a, double b);

    double midpnt(function<double(double)> func, double& a, double& b, int& n);


};
#endif // !INTEGRATION_H

double Integration::trapzd(function<double(double)> func, double& a, double& b, int& n)
{
    float x, tnm, sum, del;
    static float s;
    int it, j;
    if (n == 1) {
        return (s = 0.5 * (b - a) * (func(a) + func(b)));
    }
    else {
        for (it = 1, j = 1; j < n - 1; j++) it <<= 1;
        tnm = it;
        del = (b - a) / tnm; 
            x = a + 0.5 * del;
        for (sum = 0.0, j = 1; j <= it; j++, x += del) sum += func(x);
        s = 0.5 * (s + (b - a) * sum / tnm); 
            return s;
    }
}

double Integration::qtrap(function<double(double)> func, double& a, double& b)
{
  
    int j;
    int JMAX = 20;
    double EPS = 1.0e-6;
    double s, olds = 0.0; 
        for (j = 1; j <= JMAX; j++) {
            s = trapzd(func, a, b, j);
            if (j > 5) 
                if (fabs(s - olds) < EPS * fabs(olds) ||
                    (s == 0.0 && olds == 0.0)) return s;
            olds = s;
        }
    return 0.0;
}


double Integration::qsimp(function<double(double)> func, double& a, double& b)
{

    int j;
    int JMAX = 20;
    double EPS = 1.0e-6;
    double s, st, ost = 0.0, os = 0.0;
    for (j = 1; j <= JMAX; j++) {
        st = trapzd(func, a, b, j);
        s = (4.0 * st - ost) / 3.0; 
            if (j > 5) 
                if (fabs(s - os) < EPS * fabs(os) ||
                    (s == 0.0 && os == 0.0)) return s;
        os = s;
        ost = st;
    }
    return 0.0;
}

/* double Integration::qromb(function<double(double)> func, double a, double b)
{
    double ss, dss;
    int JMAX = 20;
    int JMAXP = JMAX+1;
    int K =  5;
    double EPS = 1.0e-6;
    double s[JMAXP], h[JMAXP + 1]; 
    int j; 
        h[1] = 1.0;
    for (j = 1; j <= JMAX; j++) {
        s[j] = trapzd(func, a, b, j);
        if (j >= K) {
            polint(&h[j - K], &s[j - K], K, 0.0, &ss, &dss);
            if (fabs(dss) <= EPS * fabs(ss)) return ss;
        }
        h[j + 1] = 0.25 * h[j];
        
    }
    return 0.0;
} */


double Integration::midpnt(function<double(double)> func, double& a, double& b, int& n)
{
    float x, tnm, sum, del, ddel;
    static float s;
    int it, j;
    if (n == 1) {
        return (s = (b - a) * func(0.5 * (a + b)));
    }
    else {
        for (it = 1, j = 1; j < n - 1; j++) it *= 3;
        tnm = it;
        del = (b - a) / (3.0 * tnm);
        ddel = del + del; 
            x = a + 0.5 * del; 
            sum = 0.0;
        for (j = 1; j <= it; j++) {
            sum += func(x);
            x += ddel;
            sum += func(x);
            x += del;
        }
        s = (s + (b - a) * sum / tnm) / 3.0;
            return s; 
    }
}

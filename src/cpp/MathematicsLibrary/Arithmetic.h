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

using namespace std;

class  Arithmetic
{
private:

public:
	Arithmetic();
    double min(vector<double>& values);
    double max(vector<double>& values);
	~Arithmetic();

};

Arithmetic::Arithmetic()
{

}

Arithmetic::~Arithmetic()
{

}

double Arithmetic::min(vector<double>& values)
{
    double x = 0;
    int i = 0, length = values.size();
    x = values[0];
    for(i = 0; i < length; i++){
        if(values[i] < x){
            x = values[i];
        }
    }
   
    return x;
}

double Arithmetic::max(vector<double>& values)
{
    double x = 0;
    int i = 0, length = values.size();
    x = values[0];
    for(i = 0; i < length; i++){
        if(values[i] > x){
            x = values[i];
        }
    }
   
    return x;
}
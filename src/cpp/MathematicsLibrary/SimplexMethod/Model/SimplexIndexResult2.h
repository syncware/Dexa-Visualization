#pragma once


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <tuple>

using namespace std;

class SimplexIndexResult2
{
    public:
        tuple<int, int> index;
        int result;
        SimplexIndexResult2(tuple<int, int> index, const int& result);

    
};

SimplexIndexResult2::SimplexIndexResult2(tuple<int, int> _index, const int& _result)
{
    index = _index;
    result = _result;
}
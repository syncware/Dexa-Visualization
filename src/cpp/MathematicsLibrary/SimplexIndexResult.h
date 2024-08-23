#pragma once


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <tuple>
#include "Enums.h"

using namespace std;


class SimplexIndexResult
{
private:

public:
    tuple<int, int> index;
    SimplexResult result;

    SimplexIndexResult(tuple<int, int> _index, SimplexResult _result);

};

SimplexIndexResult::SimplexIndexResult(tuple<int, int> _index, SimplexResult _result)
{
    index = _index;
    result = _result;
}

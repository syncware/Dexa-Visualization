#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include "./Forecast.h"
#include "./Inputdeck.h"

using namespace std;
using namespace std::placeholders;

class ImportMBALForecastResults
{
private:
    Inputdeck inputdeck;
    const char delimeter = '\t';

public:
    ImportMBALForecastResults();
    ~ImportMBALForecastResults();
    double stod(string &s);
    vector<string> GetHeaders(vector<string> &rows);
    vector<string> GetUnits(vector<string> &rows);
    vector<ForecastResult> GetMBALForecastResult(vector<string> &ColumHeaders,
                                                 vector<string> &rows, string &wellName);
};

ImportMBALForecastResults::ImportMBALForecastResults()
{
}

ImportMBALForecastResults::~ImportMBALForecastResults()
{
}

double ImportMBALForecastResults::stod(string &s)
{
    double ans = 0;
    if (s.empty() == false)
        ans = std::stod(s);
    return ans;
}

vector<string> ImportMBALForecastResults::GetHeaders(vector<string> &rows)
{
    int HeadersStartRow = 7;
    string FirstRow = rows[HeadersStartRow];
    string SecondRow = rows[HeadersStartRow + 1];

    vector<string> FirstRowColumnValues;
    inputdeck.customGetline(FirstRow, delimeter, FirstRowColumnValues);

    vector<string> SecondRowColumnValues;
    inputdeck.customGetline(SecondRow, delimeter, SecondRowColumnValues);

    vector<string> ColumHeaders;
    int i = 0, ni = FirstRowColumnValues.size();
    for (i = 0; i < ni; i++)
    {
        string coulumHeader = FirstRowColumnValues[i] + " " + SecondRowColumnValues[i];
        ColumHeaders.push_back(coulumHeader);
    }

    return ColumHeaders;
}

vector<string> ImportMBALForecastResults::GetUnits(vector<string> &rows)
{
    int UnitsRowIndex = 9;
    string UnitsRow = rows[UnitsRowIndex];
    vector<string> units;
    inputdeck.customGetline(UnitsRow, delimeter, units);

    return units;
}

vector<ForecastResult> ImportMBALForecastResults::GetMBALForecastResult(vector<string> &ColumHeaders,
                                                                        vector<string> &rows, string &wellName)
{

    int i = 0, ni = rows.size();
    int j = 0, nj = ColumHeaders.size();
    int startRowIndex = 11;
    MBALVariableHeaders mBALVariableHeaders;
    mBALVariableHeaders.InitializeData();
    vector<ForecastResult> mBALForecasts;

    for (i = startRowIndex; i < ni - 2; i++)
    {
        vector<string> strings;
        inputdeck.customGetline(rows[i], delimeter, strings);
        ForecastResult mBALForecastModel;
        mBALForecastModel.InitializeData();

        mBALForecastModel.ModuleName = wellName;
        mBALForecastModel.CGR = stod(strings[13]);
        mBALForecastModel.GOR = stod(strings[13]);
        mBALForecastModel.BSW = stod(strings[12]);
        mBALForecastModel.WGR = stod(strings[12]);
        mBALForecastModel.Cum_Gas_Prod = stod(strings[16]);
        mBALForecastModel.Cum_Oil_Prod = stod(strings[15]);
        mBALForecastModel.Oil_rate = stod(strings[8]);
        mBALForecastModel.Gas_Rate = stod(strings[9]);

        mBALForecasts.push_back(mBALForecastModel);
    }

    return mBALForecasts;
}
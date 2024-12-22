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

using namespace std;
using namespace std::placeholders;

class ExternalForecast
{
private:
public:
    ExternalForecast();
    ~ExternalForecast();
    WellActivityResult GetWellActivityResult(vector<WellActivityResult> &WellActivities,
                                             string &SelectedModuleName);
    int GetCumProductionIndex(double &CurrentCumProduction, WellActivityResult &wellActivityResult,
                              string &hyrocarbonStream);
    ForecastResult GetForecastResult(int &cumProductionIndex, WellActivityResult &wellActivityResult,
                                     string &hyrocarbonStream, double &CurrentCumProduction);
    double linerInterp(double &x1, double &x2, double &x, double &y1, double &y2);
    bool IsContainsModuleName(vector<string> &uniqueModuleNames, ForecastResult &forecastResult);
    vector<string> GetUniqueModuleNames(vector<vector<ForecastResult>> &forecastResultsList);
    vector<WellActivityResult> GetWellActivities(vector<vector<ForecastResult>> &forecastProfilesList,
                                                 vector<InputDeckStruct> &decks, vector<string> &uniqueModuleNames);
    vector<string> GetHyrocarbonStreams(vector<string> &uniqueModuleNames,
                                        vector<InputDeckStruct> &decks);
    bool MatchForecastProfilesAndDecks(vector<string> &uniqueModuleNames,
                                       vector<InputDeckStruct> &decks);
    vector<vector<ForecastResult>> GetUniqueForecastProfiles(vector<ForecastResult> &forecastResults,
                                                             vector<InputDeckStruct> &decks);
};

ExternalForecast::ExternalForecast()
{
}

ExternalForecast::~ExternalForecast()
{
}

bool ExternalForecast::IsContainsModuleName(vector<string> &uniqueModuleNames, ForecastResult &forecastResult)
{
    bool check = false;
    int datesSize = uniqueModuleNames.size();
    for (int i = 0; i < datesSize; i++)
    {
        if (uniqueModuleNames[i] == forecastResult.ModuleName)
        {
            check = true;
            break;
        }
    }

    return check;
}

bool ExternalForecast::MatchForecastProfilesAndDecks(vector<string> &uniqueModuleNames,
                                                     vector<InputDeckStruct> &decks)
{

    bool totalCheck = true;
    vector<bool> initialChecks;
    int i = 0, j = 0;
    int lent1 = uniqueModuleNames.size();
    int lent2 = decks.size();

    for (i = 0; i < lent1; i++)
    {
        initialChecks.push_back(false);
    }

    for (i = 0; i < lent1; i++)
    {
        for (j = 0; j < lent2; j++)
        {
            if (uniqueModuleNames[i] == decks[j].Module)
            {
                initialChecks[i] = true;
                break;
            }
        }
    }

    for (i = 0; i < lent1; i++)
    {
        if (initialChecks[i] == false)
        {
            totalCheck = false;
            break;
        }
    }

    return totalCheck;
}

vector<vector<ForecastResult>> ExternalForecast::GetUniqueForecastProfiles(vector<ForecastResult> &forecastResults,
                                                                           vector<InputDeckStruct> &decks)
{
    vector<string> uniqueModuleNames;
    int i = 0, j = 0;
    int lent = forecastResults.size();
    int lent2 = decks.size();
    vector<vector<ForecastResult>> forecastResultsList;

    for (i = 0; i < lent2; i++)
    {
        vector<ForecastResult> temp;
        for (j = 0; j < lent; j++)
        {
            if (forecastResults[j].ModuleName == decks[i].Module)
            {
                temp.push_back(forecastResults[j]);
            }
        }
        forecastResultsList.push_back(temp);
    }
    return forecastResultsList;
}

vector<string> ExternalForecast::GetUniqueModuleNames(vector<vector<ForecastResult>> &forecastResultsList)
{
    vector<string> uniqueModuleNames;
    int i = 0;
    int lent = forecastResultsList.size();

    bool check = true;
    for (i = 0; i < lent; i++)
    {
        uniqueModuleNames.push_back(forecastResultsList[i][0].ModuleName);
    }

    return uniqueModuleNames;
}

vector<string> ExternalForecast::GetHyrocarbonStreams(vector<string> &uniqueModuleNames,
                                                      vector<InputDeckStruct> &decks)
{
    vector<string> hydrocarbonStreams;
    int i = 0, j = 0;
    int lent = uniqueModuleNames.size();
    int lent2 = decks.size();
    bool check = true;
    for (i = 0; i < lent; i++)
    {
        for (j = 0; j < lent2; j++)
        {
            if (uniqueModuleNames[i] == decks[j].Module)
            {
                hydrocarbonStreams.push_back(decks[j].Hydrocarbon_Stream);
                break;
            }
        }
    }

    return hydrocarbonStreams;
}

vector<WellActivityResult> ExternalForecast::GetWellActivities(vector<vector<ForecastResult>> &forecastProfilesList,
                                                               vector<InputDeckStruct> &decks, vector<string> &uniqueModuleNames)
{
    double MM = 1000000.0;
    vector<string> wellsHydrocarbonStream = GetHyrocarbonStreams(uniqueModuleNames,
                                                                 decks);
    int i = 0, j = 0;
    int lent = forecastProfilesList.size();
    vector<WellActivityResult> wellActivities;
    for (j = 0; j < lent; j++)
    {
        WellActivityResult wellActivityResult;
        int lent2 = forecastProfilesList[j].size();
        int counter = 0;
        for (i = 0; i < lent2; i++)
        {
            ForecastResult temp;
            temp.InitializeData();
            if (wellsHydrocarbonStream[j] == "oil")
            {
                if (forecastProfilesList[j][i].Oil_rate > 0)
                {
                    if (counter < 1)
                    {
                        counter++;
                        wellActivityResult.startRowIndex = i;
                    }
                }
            }
            else
            {
                if (forecastProfilesList[j][i].Gas_Rate > 0)
                {
                    if (counter < 1)
                    {
                        counter++;
                        wellActivityResult.startRowIndex = i;
                    }
                }
            }

            temp.Cum_Gas_Prod = forecastProfilesList[j][i].Cum_Gas_Prod * MM;
            temp.Cum_Oil_Prod = forecastProfilesList[j][i].Cum_Oil_Prod * MM;
            temp.CGR = forecastProfilesList[j][i].CGR / MM;
            temp.WGR = forecastProfilesList[j][i].WGR / MM;
            temp.Gas_Rate = forecastProfilesList[j][i].Gas_Rate * MM;
            temp.Oil_rate = forecastProfilesList[j][i].Oil_rate;
            temp.GOR = forecastProfilesList[j][i].GOR;
            temp.Water_Rate = forecastProfilesList[j][i].BSW / 100.0;
            wellActivityResult.externalForecastProfile.push_back(temp);
            wellActivityResult.ModuleName = forecastProfilesList[j][i].ModuleName;
        }

        wellActivities.push_back(wellActivityResult);
    }
    return wellActivities;
}

WellActivityResult ExternalForecast::GetWellActivityResult(vector<WellActivityResult> &WellActivities,
                                                           string &SelectedModuleName)
{
    WellActivityResult wellActivityResult;
    wellActivityResult.InitializeData();
    int i = 0, nSize = WellActivities.size();
    for (i = 0; i < nSize; i++)
    {
        if (WellActivities[i].ModuleName == SelectedModuleName)
        {
            wellActivityResult = WellActivities[i];
            return wellActivityResult;
        }
    }

    return wellActivityResult;
}

int ExternalForecast::GetCumProductionIndex(double &CurrentCumProduction2, WellActivityResult &wellActivityResult,
                                            string &hyrocarbonStream)
{
    double CurrentCumProduction = CurrentCumProduction2 * 1000000.0;
    int cumProductionIndex = -1, i = 0;
    int nSize = wellActivityResult.externalForecastProfile.size();
    if (hyrocarbonStream == "oil")
    {
        for (i = wellActivityResult.startRowIndex + 1; i < nSize; i++)
        {
            if (CurrentCumProduction >= wellActivityResult.externalForecastProfile[i - 1].Cum_Oil_Prod && CurrentCumProduction <= wellActivityResult.externalForecastProfile[i].Cum_Oil_Prod)
            {
                cumProductionIndex = i - 1;
                return cumProductionIndex;
            }
        }
    }
    else
    {
        for (i = wellActivityResult.startRowIndex + 1; i < nSize; i++)
        {
            if (CurrentCumProduction >= wellActivityResult.externalForecastProfile[i - 1].Cum_Gas_Prod && CurrentCumProduction <= wellActivityResult.externalForecastProfile[i].Cum_Gas_Prod)
            {
                cumProductionIndex = i - 1;
                return cumProductionIndex;
            }
        }
    }

    return cumProductionIndex;
}

ForecastResult ExternalForecast::GetForecastResult(int &cumProductionIndex, WellActivityResult &wellActivityResult,
                                                   string &hyrocarbonStream, double &CurrentCumProduction2)
{

    double CurrentCumProduction = CurrentCumProduction2 * 1000000.0;
    ForecastResult forecastResult;
    int startRowIndex = wellActivityResult.startRowIndex;

    if (CurrentCumProduction == 0)
    {
        if (hyrocarbonStream == "oil")
        {
            forecastResult.Cum_Oil_Prod = CurrentCumProduction;
            forecastResult.Oil_rate = wellActivityResult.externalForecastProfile[startRowIndex].Oil_rate;
            forecastResult.GOR = wellActivityResult.externalForecastProfile[startRowIndex].GOR;
            forecastResult.BSW = wellActivityResult.externalForecastProfile[startRowIndex].BSW;
            forecastResult.CGR = 0;
            forecastResult.WGR = 0;
            return forecastResult;
        }
        else
        {
            forecastResult.Cum_Gas_Prod = CurrentCumProduction;
            forecastResult.Gas_Rate = wellActivityResult.externalForecastProfile[startRowIndex].Gas_Rate;
            forecastResult.CGR = wellActivityResult.externalForecastProfile[startRowIndex].CGR;
            forecastResult.WGR = wellActivityResult.externalForecastProfile[startRowIndex].WGR;
            forecastResult.BSW = 0;
            forecastResult.GOR = 0;
            return forecastResult;
        }
    }

    if (cumProductionIndex == -1)
    {
        if (hyrocarbonStream == "oil")
        {
            forecastResult.Cum_Oil_Prod = CurrentCumProduction;
            forecastResult.Oil_rate = wellActivityResult.externalForecastProfile[startRowIndex].Oil_rate;
            forecastResult.GOR = wellActivityResult.externalForecastProfile[startRowIndex].GOR;
            forecastResult.BSW = wellActivityResult.externalForecastProfile[startRowIndex].BSW;
            forecastResult.CGR = 0;
            forecastResult.WGR = 0;
            return forecastResult;
        }
        else
        {
            forecastResult.Cum_Gas_Prod = CurrentCumProduction;
            forecastResult.Gas_Rate = wellActivityResult.externalForecastProfile[startRowIndex].Gas_Rate;
            forecastResult.CGR = wellActivityResult.externalForecastProfile[startRowIndex].CGR;
            forecastResult.WGR = wellActivityResult.externalForecastProfile[startRowIndex].WGR;
            forecastResult.BSW = 0;
            forecastResult.GOR = 0;
            return forecastResult;
        }
    }

    int i_1 = cumProductionIndex;
    int i = cumProductionIndex + 1;
    double x1 = 0, x2 = 0;
    double y1 = 0, y2 = 0;
    if (hyrocarbonStream == "oil")
    {
        forecastResult.Cum_Oil_Prod = CurrentCumProduction;
        x1 = wellActivityResult.externalForecastProfile[i_1].Cum_Oil_Prod;
        x2 = wellActivityResult.externalForecastProfile[i].Cum_Oil_Prod;
        y1 = wellActivityResult.externalForecastProfile[i_1].Oil_rate;
        y2 = wellActivityResult.externalForecastProfile[i].Oil_rate;
        forecastResult.Oil_rate = linerInterp(x1, x2, CurrentCumProduction, y1, y2);
        y1 = wellActivityResult.externalForecastProfile[i_1].BSW;
        y2 = wellActivityResult.externalForecastProfile[i].BSW;
        forecastResult.BSW = linerInterp(x1, x2, CurrentCumProduction, y1, y2);
        y1 = wellActivityResult.externalForecastProfile[i_1].GOR;
        y2 = wellActivityResult.externalForecastProfile[i].GOR;
        forecastResult.GOR = linerInterp(x1, x2, CurrentCumProduction, y1, y2);
    }
    else
    {
        forecastResult.Cum_Gas_Prod = CurrentCumProduction;
        x1 = wellActivityResult.externalForecastProfile[i_1].Cum_Gas_Prod;
        x2 = wellActivityResult.externalForecastProfile[i].Cum_Gas_Prod;
        y1 = wellActivityResult.externalForecastProfile[i_1].Gas_Rate;
        y2 = wellActivityResult.externalForecastProfile[i].Gas_Rate;
        forecastResult.Gas_Rate = linerInterp(x1, x2, CurrentCumProduction, y1, y2);
        y1 = wellActivityResult.externalForecastProfile[i_1].WGR;
        y2 = wellActivityResult.externalForecastProfile[i].WGR;
        forecastResult.WGR = linerInterp(x1, x2, CurrentCumProduction, y1, y2);
        y1 = wellActivityResult.externalForecastProfile[i_1].CGR;
        y2 = wellActivityResult.externalForecastProfile[i].CGR;
        forecastResult.CGR = linerInterp(x1, x2, CurrentCumProduction, y1, y2);
    }

    return forecastResult;
}

double ExternalForecast::linerInterp(double &x1, double &x2, double &x, double &y1, double &y2)
{
    double y = 0;
    double term1 = 0;
    if ((x2 - x1) != 0)
    {
        term1 = (x - x1) / (x2 - x1);
    }
    double term2 = (y2 - y1);
    y = y1 + term2 * term1;
    if (y < 0)
    {
        y = 0;
    }
    return y;
}
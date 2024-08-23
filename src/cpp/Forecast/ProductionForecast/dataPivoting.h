#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include "Forecast.h"
#include "Decline_Curve_Analysis.h"
#include "../../MathematicsLibrary/Integration.h"
#include "FractionalFlow.h"
#include "DateCreation.h"
#include "../../MathematicsLibrary/MainSimplex.h"
#include "Inputdeck.h"

using namespace std;
using namespace std::placeholders;

class dataPivoting
{
private:
    double M = 1000.0;
    double MM = 1000000.0;
    DateCreation dateCreation;

public:
    dataPivoting();
    ~dataPivoting();
    bool isContain(vector<Date>&  dates, int& year);
    bool isContain(vector<Date>&  dates, int& year, int& month);
    vector<Date> GetListOfYears(vector<ForecastResult>& forecastResults, bool& isByYear);
    vector<Date> GetListOfYears(vector<vector<ForecastResult>>& allWellForecastResults,
    bool& isByYear);
    vector<Date> GetListOfYears(vector<vector<ForecastResultForChart>>& allWellForecastResults,
    bool& isByYear);
    vector<Date> GetListOfYears(vector<vector<vector<ForecastResult>>>& allWellForecastResults,
    bool& isByYear);
    vector<ForecastResult> GetYearlyForcastResultModuleLevel(vector<ForecastResult>& forecastResults,
                                        vector<Date>& dates, bool& isForChart);
    vector<ForecastResult>GetYearlyForcastResultModuleLevelMonthly(vector<ForecastResult>& forecastResults,
                                 vector<Date>& dates);

    vector<vector<ForecastResult>> GetYearlyForcastResultModulesLevel(vector<vector<ForecastResult>>& forecastResults,
    vector<Date>& dates, bool& isByYear, bool& isForChart);

    vector<ForecastResult> GetYearlyForcastResultFacilityLevel(vector<vector<ForecastResult>>& forecastResults,
    vector<Date>& dates, bool& isByYear, bool& isForChart);

    vector<vector<ForecastResult>> GetYearlyForcastResultFacilitiesLevel(vector<vector<vector<ForecastResult>>>& forecastResults,
    vector<Date>& dates, bool& isByYear, bool& isForChart);

    vector<vector<ForecastResultForChart>> GetYearlyForcastResultModulesLevelForChart(vector<vector<ForecastResultForChart>>& forecastResults,
    vector<Date>& dates, string& selectedVariable);

    vector<ForecastResultForChart> GetYearlyForcastResultModuleLevelForChart(vector<ForecastResultForChart>& forecastResults,
                                 vector<Date>& dates, string& selectedVariable);

};

dataPivoting::dataPivoting()
{

}

dataPivoting::~dataPivoting()
{

}

bool dataPivoting::isContain(vector<Date>&  dates, int& year)
{
    bool check = false;
    //forecastResults[i].Day == day && forecastResults[i].Month == month && 
    int i = 0, lent = dates.size();
    for(i = 0; i < lent; i++){
         if(year < 1900 || year >= 2900){
            check  = true;
            break;
        }
        if(dates[i].year == year){
            check  = true;
            break;
        }
    }

    return check;
}

bool dataPivoting::isContain(vector<Date>&  dates, int& year, int& month)
{
    bool check = false;
    //forecastResults[i].Day == day && forecastResults[i].Month == month && 
    int i = 0, lent = dates.size();
    for(i = 0; i < lent; i++){
        if(month <= 0 || month > 12 || year < 1900 || year >= 2900){
            check  = true;
            break;
        }
        if(dates[i].year == year && dates[i].month == month){
            check  = true;
            break;
        }

    }

    return check;
}

vector<Date> dataPivoting::GetListOfYears(vector<ForecastResult>& forecastResults, bool& isByYear)
{
   vector<Date> dates;
   int i = 0;
   bool check = false;

   Date date;
   /* date.day = 31;
   date.month = 12;
   date.year = forecastResults[i].Year;
   dates.push_back(date); */

    int noOfTimes = forecastResults.size();
    for(i = 0; i < noOfTimes; i++){
        if(isByYear == true){
            check = isContain(dates, forecastResults[i].Year);
            if(check == false){

                date.day = 31;
                date.month = 12;
                date.year = forecastResults[i].Year;
                dates.push_back(date);
            }
        }else{
            if(i == 695){
                double  aa1 = 0;
            }
          check = isContain(dates, forecastResults[i].Year, forecastResults[i].Month);
            if(check == false){
                if(forecastResults[i].Year == 0 && forecastResults[i].Month == 0){
                    double  aa = 0;
                }

                date.day = 28;
                date.month = forecastResults[i].Month;
                date.year = forecastResults[i].Year;
                dates.push_back(date);
            }  
        }
        
    }

    dateCreation.SortDate(dates);
    return dates;
}

vector<Date> dataPivoting::GetListOfYears(vector<vector<ForecastResult>>& allWellForecastResults,
bool& isByYear)
{
   vector<Date> dates;
   int i = 0, j = 0, noOfWells = allWellForecastResults.size();
   bool check = false;

   Date date;
   /* date.day = 31;
   date.month = 12;
   date.year = forecastResults[i].Year;
   dates.push_back(date); */


    for(j = 0; j < noOfWells; j++){
        vector<ForecastResult> forecastResults = allWellForecastResults[j];
        int noOfTimes = forecastResults.size();
        for(i = 0; i < noOfTimes; i++){
            if(isByYear == true){
                check = isContain(dates, forecastResults[i].Year);
                if(check == false){

                    date.day = 31;
                    date.month = 12;
                    date.year = forecastResults[i].Year;
                    //std::cout << date.day << "/" << date.month << "/" << date.year << std::endl;
                    dates.push_back(date);
                }
            }else{
            check = isContain(dates, forecastResults[i].Year, forecastResults[i].Month);
                if(check == false){

                    date.day = 28;
                    date.month = forecastResults[i].Month;
                    date.year = forecastResults[i].Year;
                    //std::cout << date.day << "/" << date.month << "/" << date.year << std::endl;
                    dates.push_back(date);
                }  
            }
            
        }
    }

    dateCreation.SortDate(dates);

   return dates;
}

vector<Date> dataPivoting::GetListOfYears(vector<vector<ForecastResultForChart>>& allWellForecastResults,
bool& isByYear)
{
   vector<Date> dates;
   int i = 0, j = 0, noOfWells = allWellForecastResults.size();
   bool check = false;

   Date date;
   /* date.day = 31;
   date.month = 12;
   date.year = forecastResults[i].Year;
   dates.push_back(date); */


    for(j = 0; j < noOfWells; j++){
        vector<ForecastResultForChart> forecastResults = allWellForecastResults[j];
        int noOfTimes = forecastResults.size();
        for(i = 0; i < noOfTimes; i++){
            if(isByYear == true){
                check = isContain(dates, forecastResults[i].Year);
                if(check == false){

                    date.day = 31;
                    date.month = 12;
                    date.year = forecastResults[i].Year;
                    //std::cout << date.day << "/" << date.month << "/" << date.year << std::endl;
                    dates.push_back(date);
                }
            }else{
            check = isContain(dates, forecastResults[i].Year, forecastResults[i].Month);
                if(check == false){

                    date.day = 28;
                    date.month = forecastResults[i].Month;
                    date.year = forecastResults[i].Year;
                    //std::cout << date.day << "/" << date.month << "/" << date.year << std::endl;
                    dates.push_back(date);
                }  
            }
            
        }
    }

    dateCreation.SortDate(dates);

   return dates;
}


vector<Date> dataPivoting::GetListOfYears(vector<vector<vector<ForecastResult>>>& allWellForecastResults,
bool& isByYear)
{
   vector<Date> dates;
   int i = 0, j = 0, k = 0, noOfFacilities = allWellForecastResults.size();
   bool check = false;

   Date date;
   /* date.day = 31;
   date.month = 12;
   date.year = forecastResults[i].Year;
   dates.push_back(date); */

    for(k = 0; k < noOfFacilities; k++){
        int noOfWells = allWellForecastResults[k].size();
        for(j = 0; j < noOfWells; j++){
        vector<ForecastResult> forecastResults = allWellForecastResults[k][j];
        int noOfTimes = forecastResults.size();
        for(i = 0; i < noOfTimes; i++){
                if(isByYear == true){
                check = isContain(dates, forecastResults[i].Year);
                if(check == false){

                    date.day = 31;
                    date.month = 12;
                    date.year = forecastResults[i].Year;
                    dates.push_back(date);
                }
            }else{
            check = isContain(dates, forecastResults[i].Year, forecastResults[i].Month);
                if(check == false){

                    date.day = 28;
                    date.month = forecastResults[i].Month;
                    date.year = forecastResults[i].Year;
                    dates.push_back(date);
                }  
            }
            
        }
    }

}
    
    dateCreation.SortDate(dates);

   return dates;
}


vector<ForecastResult> dataPivoting::GetYearlyForcastResultModuleLevel(vector<ForecastResult>& forecastResults,
                                 vector<Date>& dates, bool& isForChart)
{

    int i = 0, j = 0, lent = dates.size();
    int lent2 = forecastResults.size();

    int startFlowIndex = 0;

    for(i = 0; i < lent2; i++){
        if(forecastResults[i].Flow_station != ""){
            startFlowIndex = i;
            break;
        }
    }

    vector<ForecastResult> results;
    for(i = 0; i < lent; i++){
        ForecastResult forecastResult;// = forecastResults[startFlowIndex];
        forecastResult.InitailizeData();
        forecastResult.Day = dates[i].day;
        forecastResult.Month = dates[i].month;
        forecastResult.Year = dates[i].year;
        forecastResult.HyrocarbonStream = forecastResults[startFlowIndex].HyrocarbonStream;
        forecastResult.hydrocarbonType = forecastResults[startFlowIndex].hydrocarbonType;
        forecastResult.terminal = forecastResults[startFlowIndex].terminal;

        forecastResult.ModuleName = forecastResults[startFlowIndex].ModuleName;
        forecastResult.Version_Name = forecastResults[startFlowIndex].Version_Name;
        forecastResult.Field = forecastResults[startFlowIndex].Field;
        forecastResult.Reservoir = forecastResults[startFlowIndex].Reservoir;
        forecastResult.Drainage_Point = forecastResults[startFlowIndex].Drainage_Point;
        forecastResult.Production_String = forecastResults[startFlowIndex].Production_String;
        forecastResult.TRANCHE = forecastResults[startFlowIndex].TRANCHE;
        forecastResult.Asset_Team = forecastResults[startFlowIndex].Asset_Team;
        forecastResult.Flow_station = forecastResults[startFlowIndex].Flow_station;
        forecastResult.projectCode = forecastResults[startFlowIndex].projectCode;
        forecastResult.projectName = forecastResults[startFlowIndex].projectName;
        forecastResult.resourceClass = forecastResults[startFlowIndex].resourceClass;
        forecastResult.Oil_rate = 0;
        forecastResult.Gas_Rate =   0;
        forecastResult.Water_Rate =  0;
        forecastResult.Liquid_Rate =  0;
        forecastResult.Gas_Own_Use =  0;
        forecastResult.Gas_Demand =  0;
        forecastResult.Gas_Flared =  0;
        forecastResult.Crude_Oil_Lossess =  0;
        forecastResult.Condensate_Rate = 0;


        results.push_back(forecastResult);
    }

    double Np = 0, Gp = 0, Wp = 0, Npc = 0;
    for(i = 0; i < lent; i++){
        double dNp = 0, dGp = 0, dWp = 0, dNpc = 0;
        double ProdaysPerYear = 0;
        double dGpOwnUse = 0, dGpDemand = 0, dGpFlared = 0;
        double dCrudeOilLoss = 0;
        double dt30 = 30;
        double dt365 = 365;
        for(j = 0; j < lent2; j++){
            if(isForChart == false){
                if(results[i].Year == forecastResults[j].Year){
                    if(forecastResults[j].HyrocarbonStream == "oil"){
                        if(forecastResults[j].Oil_rate > 0){
                            ProdaysPerYear = ProdaysPerYear + dt30;
                        }
                    }else{
                        if(forecastResults[j].Gas_Rate > 0){
                            ProdaysPerYear = ProdaysPerYear + dt30;
                        }
                    }
                    dNp = dNp + (forecastResults[j].Oil_rate * dt30);
                    dNpc = dNpc + (forecastResults[j].Condensate_Rate * dt30);
                    dGp = dGp + (forecastResults[j].Gas_Rate * dt30);
                    dWp = dWp + (forecastResults[j].Water_Rate * dt30);
                    dGpOwnUse = dGpOwnUse + (forecastResults[j].Gas_Own_Use * dt30);
                    dGpDemand = dGpDemand + (forecastResults[j].Gas_Demand * dt30);
                    dGpFlared = dGpFlared + (forecastResults[j].Gas_Flared * dt30);
                    dCrudeOilLoss = dCrudeOilLoss + (forecastResults[j].Crude_Oil_Lossess * dt30);
                    results[i].CutBack = forecastResults[j].CutBack;
                    results[i].DeclineRate = forecastResults[j].DeclineRate;
                    results[i].URo = forecastResults[j].URo;
                    results[i].URg = forecastResults[j].URg;
                    if(forecastResults[j].reasonForTermination != ""){
                        results[i].reasonForTermination = forecastResults[j].reasonForTermination;
                    }
                } 
            }else {
                if(results[i].Year == forecastResults[j].Year){
                    ProdaysPerYear = dt365;
                    dNp = dNp + (forecastResults[j].Oil_rate * dt365);
                    dNpc = dNpc + (forecastResults[j].Condensate_Rate * dt365);
                    dGp = dGp + (forecastResults[j].Gas_Rate * dt365);
                    dWp = dWp + (forecastResults[j].Water_Rate * dt365);
                    dGpOwnUse = dGpOwnUse + (forecastResults[j].Gas_Own_Use * dt365);
                    dGpDemand = dGpDemand + (forecastResults[j].Gas_Demand * dt365);
                    dGpFlared = dGpFlared + (forecastResults[j].Gas_Flared * dt365);
                    dCrudeOilLoss = dCrudeOilLoss + (forecastResults[j].Crude_Oil_Lossess * dt365);
                    results[i].CutBack = forecastResults[j].CutBack;
                    results[i].DeclineRate = forecastResults[j].DeclineRate;
                    results[i].URo = forecastResults[j].URo;
                    results[i].URg = forecastResults[j].URg;
                } 
            }  
        }

        results[i].Oil_rate =  dNp/ProdaysPerYear;
        results[i].Condensate_Rate =  dNpc/ProdaysPerYear;
        results[i].Gas_Rate =   dGp/ProdaysPerYear;
        results[i].Water_Rate =  dWp/ProdaysPerYear;
        results[i].Liquid_Rate =  results[i].Oil_rate +  results[i].Water_Rate;
        results[i].Gas_Own_Use =  dGpOwnUse/ProdaysPerYear;
        results[i].Gas_Demand =  dGpDemand/ProdaysPerYear;
        results[i].Gas_Flared =  dGpFlared/ProdaysPerYear;
        results[i].Crude_Oil_Lossess =  dCrudeOilLoss/ProdaysPerYear;
        if(results[i].Gas_Rate < 0.000000000){
            results[i].Gas_Own_Use = 0;
            results[i].Gas_Demand = 0;
            results[i].Gas_Flared = 0;
        }

        /* if(results[i].Oil_rate < 0.000000000){
            results[i].Crude_Oil_Lossess = 0;
        } */

        //std::cout << "dNp: " << dNp  << std::endl;
        //std::cout << "oil rate: " << results[i].Oil_rate  << std::endl;

        Np = Np + dNp;
        Gp = Gp + dGp;
        Wp = Wp + dWp;
        Npc = Npc + dNpc;

        results[i].Cum_Oil_Prod = Np;
        results[i].Cum_Condensate_Prod = Npc;
        results[i].Cum_Gas_Prod = Gp;
        results[i].Cum_Water_Prod = Wp;
        results[i].prodDays = ProdaysPerYear;

        if( results[i].HyrocarbonStream  == "oil")
        {
            results[i].BSW = 0;
            if((dNp + dWp) > 0){
                results[i].BSW = (dWp * 100)/(dNp + dWp);
            }
            results[i].GOR = 0;
            if(dNp > 0){
                 results[i].GOR = dGp/dNp;
            }
        }
        else
        {
            results[i].CGR = 0;
            results[i].WGR = 0;
            if(dGp > 0){
                results[i].CGR = dNpc/dGp;
                results[i].WGR = dWp/dGp;
            } 
        }
        

    }

    return results;
}


vector<ForecastResultForChart> dataPivoting::GetYearlyForcastResultModuleLevelForChart(vector<ForecastResultForChart>& forecastResults,
                                 vector<Date>& dates, string& selectedVariable)
{

    int i = 0, j = 0, lent = dates.size();
    vector<ForecastResultForChart> results;
    for(i = 0; i < lent; i++){
        ForecastResultForChart forecastResult;
        forecastResult.InitailizeData();
        forecastResult.Day = dates[i].day;
        forecastResult.Month = dates[i].month;
        forecastResult.Year = dates[i].year;
        forecastResult.data = forecastResults[0].data;
        

        results.push_back(forecastResult);
    }

    int lent2 = forecastResults.size();
    double CumValue = 0;
    for(i = 0; i < lent; i++){
        double dCumValue  = 0;
        double dt365 = 365;
        for(j = 0; j < lent2; j++){
            if(results[i].Year == forecastResults[j].Year){
                dCumValue = dCumValue + (forecastResults[j].data * dt365);
                break;
            }      
        }
        
        results[i].data =  dCumValue/dt365;

        CumValue = CumValue + dCumValue;

        results[i].data = CumValue;

    }

    return results;
}


vector<ForecastResult> dataPivoting::GetYearlyForcastResultModuleLevelMonthly(vector<ForecastResult>& forecastResults,
                                 vector<Date>& dates)
{

    int i = 0, j = 0, lent = dates.size();
    int lent2 = forecastResults.size();
    vector<ForecastResult> results;
    int startFlowIndex = 0;

    for(i = 0; i < lent2; i++){
        if(forecastResults[i].Flow_station != ""){
            startFlowIndex = i;
            break;
        }
    }

    for(i = 0; i < lent; i++){
        ForecastResult forecastResult;// = forecastResults[0];
        forecastResult.InitailizeData();
        forecastResult.Day = dates[i].day;
        forecastResult.Month = dates[i].month;
        forecastResult.Year = dates[i].year;
        forecastResult.HyrocarbonStream = forecastResults[startFlowIndex].HyrocarbonStream;
        forecastResult.hydrocarbonType = forecastResults[startFlowIndex].hydrocarbonType;
        forecastResult.terminal = forecastResults[startFlowIndex].terminal;

        forecastResult.ModuleName = forecastResults[startFlowIndex].ModuleName;
        forecastResult.Version_Name = forecastResults[startFlowIndex].Version_Name;
        forecastResult.Field = forecastResults[startFlowIndex].Field;
        forecastResult.Reservoir = forecastResults[startFlowIndex].Reservoir;
        forecastResult.Drainage_Point = forecastResults[startFlowIndex].Drainage_Point;
        forecastResult.Production_String = forecastResults[startFlowIndex].Production_String;
        forecastResult.TRANCHE = forecastResults[startFlowIndex].TRANCHE;
        forecastResult.Asset_Team = forecastResults[startFlowIndex].Asset_Team;
        forecastResult.Flow_station = forecastResults[startFlowIndex].Flow_station;
        forecastResult.projectCode = forecastResults[startFlowIndex].projectCode;
        forecastResult.projectName = forecastResults[startFlowIndex].projectName;
        forecastResult.resourceClass = forecastResults[startFlowIndex].resourceClass;
        forecastResult.Oil_rate = 0;
        forecastResult.Gas_Rate =   0;
        forecastResult.Water_Rate =  0;
        forecastResult.Liquid_Rate =  0;
        forecastResult.Gas_Own_Use =  0;
        forecastResult.Gas_Demand =  0;
        forecastResult.Gas_Flared =  0;
        forecastResult.Crude_Oil_Lossess =  0;
        forecastResult.Condensate_Rate = 0;

        results.push_back(forecastResult);
    }

    double Np = 0, Gp = 0, Wp = 0, Npc = 0;
    for(i = 0; i < lent; i++){
        double dNp = 0, dGp = 0, dWp = 0, dNpc = 0;
        double dGpOwnUse = 0, dGpDemand = 0, dGpFlared = 0;
        double dCrudeOilLoss = 0;
        double dt30 = 30;
        double ProdaysPerYear = 0;
       // std::cout << "ModuleName: " << forecastResults[0].ModuleName << std::endl;
        for(j = 0; j < lent2; j++){
            if(results[i].Year == forecastResults[j].Year && results[i].Month == forecastResults[j].Month){
                //std::cout << "Oil Rate: " << forecastResults[j].Oil_rate << std::endl;
                dNp = dNp + (forecastResults[j].Oil_rate * dt30);
                dNpc = dNpc + (forecastResults[j].Oil_rate * dt30);
                dGp = dGp + (forecastResults[j].Gas_Rate * dt30);
                dWp = dWp + (forecastResults[j].Water_Rate * dt30);
                dGpOwnUse = dGpOwnUse + (forecastResults[j].Gas_Own_Use * dt30);
                dGpDemand = dGpDemand + (forecastResults[j].Gas_Demand * dt30);
                dGpFlared = dGpFlared + (forecastResults[j].Gas_Flared * dt30);
                dCrudeOilLoss = dCrudeOilLoss + (forecastResults[j].Crude_Oil_Lossess * dt30);
                results[i].CutBack = forecastResults[j].CutBack;
                results[i].DeclineRate = forecastResults[j].DeclineRate;
                results[i].URo = forecastResults[j].URo;
                results[i].URg = forecastResults[j].URg;
                    if(forecastResults[j].reasonForTermination != ""){
                        results[i].reasonForTermination = forecastResults[j].reasonForTermination;
                    }
                break;
            }      
        }

         results[i].prodDays = dt30;
        results[i].Oil_rate =  dNp/dt30;
        results[i].Condensate_Rate =  dNpc/dt30;
        results[i].Gas_Rate =   dGp/dt30;
        results[i].Water_Rate =  dWp/dt30;
        results[i].Liquid_Rate =  results[i].Oil_rate +  results[i].Water_Rate;
        results[i].Gas_Own_Use =  dGpOwnUse/dt30;
        results[i].Gas_Demand =  dGpDemand/dt30;
        results[i].Gas_Flared =  dGpFlared/dt30;
        results[i].Crude_Oil_Lossess =  dCrudeOilLoss/dt30;

        if(results[i].Gas_Rate < 0.000000000){
            results[i].Gas_Own_Use = 0;
            results[i].Gas_Demand = 0;
            results[i].Gas_Flared = 0;
        }

        /* if(results[i].Oil_rate < 0.000000000){
            results[i].Crude_Oil_Lossess = 0;
        } */

        Np = Np + dNp;
        Gp = Gp + dGp;
        Wp = Wp + dWp;
        Npc = Npc + dNpc;

        results[i].Cum_Oil_Prod = Np;
        results[i].Cum_Gas_Prod = Gp;
        results[i].Cum_Water_Prod = Wp;
        results[i].Cum_Condensate_Prod = Npc;

        if( results[i].HyrocarbonStream  == "oil")
        {
            results[i].BSW = 0;
            if((dNp + dWp) > 0){
                results[i].BSW = (dWp * 100)/(dNp + dWp);
            }
            results[i].GOR = 0;
            if(dNp > 0){
                 results[i].GOR = dGp/dNp;
            }
        }
        else
        {
            results[i].CGR = 0;
            results[i].WGR = 0;
            if(dGp > 0){
                results[i].CGR = dNpc/dGp;
                results[i].WGR = dWp/dGp;
            } 
        }
        

    }

    return results;
}

vector<vector<ForecastResult>> dataPivoting::GetYearlyForcastResultModulesLevel(vector<vector<ForecastResult>>& forecastResults,
    vector<Date>& dates, bool& isByYear, bool& isForChart)
{
    vector<vector<ForecastResult>> results;
    int i = 0, lent = forecastResults.size();
    for(i = 0; i < lent; i++){
        if(isByYear == true){
            results.push_back(GetYearlyForcastResultModuleLevel(forecastResults[i], dates, isForChart));
        }else{
            results.push_back(GetYearlyForcastResultModuleLevelMonthly(forecastResults[i],dates));
        }
    }

    return results;

}

vector<vector<ForecastResultForChart>> dataPivoting::GetYearlyForcastResultModulesLevelForChart(vector<vector<ForecastResultForChart>>& forecastResults,
    vector<Date>& dates, string& selectedVariable)
{
    vector<vector<ForecastResultForChart>> results;
    int i = 0, lent = forecastResults.size();
    for(i = 0; i < lent; i++){
        results.push_back(GetYearlyForcastResultModuleLevelForChart(forecastResults[i],dates, selectedVariable));
    }

    return results;

}

vector<ForecastResult> dataPivoting::GetYearlyForcastResultFacilityLevel(vector<vector<ForecastResult>>& forecastResults,
    vector<Date>& dates, bool& isByYear, bool& isForChart)
{
    vector<vector<ForecastResult>> AllModules = GetYearlyForcastResultModulesLevel(forecastResults,
     dates, isByYear, isForChart);

    int i = 0, k = 0, lent = dates.size(), nModules = AllModules.size();
    vector<ForecastResult> results;
    for(i = 0; i < lent; i++){
        ForecastResult forecastResult;// = forecastResults[0][0];
        forecastResult.InitailizeData();
        forecastResult.Day = dates[i].day;
        forecastResult.Month = dates[i].month;
        forecastResult.Year = dates[i].year;
        forecastResult.hydrocarbonType = forecastResults[0][0].hydrocarbonType;
        forecastResult.terminal = forecastResults[0][0].terminal;

        forecastResult.ModuleName = forecastResults[0][0].ModuleName;
        forecastResult.Version_Name = forecastResults[0][0].Version_Name;
        forecastResult.Field = forecastResults[0][0].Field;
        forecastResult.Reservoir = forecastResults[0][0].Reservoir;
        forecastResult.Drainage_Point = forecastResults[0][0].Drainage_Point;
        forecastResult.Production_String = forecastResults[0][0].Production_String;
        forecastResult.TRANCHE = forecastResults[0][0].TRANCHE;
        forecastResult.Asset_Team = forecastResults[0][0].Asset_Team;
        forecastResult.Flow_station = forecastResults[0][0].Flow_station;
        forecastResult.projectCode = forecastResults[0][0].projectCode;
        forecastResult.projectName = forecastResults[0][0].projectName;
        forecastResult.resourceClass = forecastResults[0][0].resourceClass;

        results.push_back(forecastResult);
        //std::cout << "Year: " << dates[i].year << std::endl;
    }


    vector<ForecastResult> forecastResultsNew;
    for(k = 0; k < nModules; k++){

        if(isByYear == true){
           forecastResultsNew 
                =  GetYearlyForcastResultModuleLevel(forecastResults[k], dates, isForChart);
        }else{
            forecastResultsNew 
                =  GetYearlyForcastResultModuleLevelMonthly(forecastResults[k], dates);
        }

        for(i = 0; i < lent; i++){

            results[i].Cum_Oil_Prod = results[i].Cum_Oil_Prod + forecastResultsNew[i].Cum_Oil_Prod;
            results[i].Cum_Condensate_Prod = results[i].Cum_Condensate_Prod + forecastResultsNew[i].Cum_Condensate_Prod;
            results[i].Cum_Gas_Prod = results[i].Cum_Gas_Prod + forecastResultsNew[i].Cum_Gas_Prod;
            results[i].Cum_Water_Prod = results[i].Cum_Water_Prod + forecastResultsNew[i].Cum_Water_Prod;
            results[i].Oil_rate = results[i].Oil_rate + forecastResultsNew[i].Oil_rate;
            results[i].Condensate_Rate = results[i].Condensate_Rate + forecastResultsNew[i].Condensate_Rate;
            results[i].Gas_Rate = results[i].Gas_Rate + forecastResultsNew[i].Gas_Rate;
            results[i].Water_Rate = results[i].Water_Rate + forecastResultsNew[i].Water_Rate;
            results[i].Liquid_Rate = results[i].Liquid_Rate + (forecastResultsNew[i].Oil_rate 
            + forecastResultsNew[i].Water_Rate);
        
        }
             
    }
    
//}

    return results;

}

vector<vector<ForecastResult>> dataPivoting::GetYearlyForcastResultFacilitiesLevel(
                            vector<vector<vector<ForecastResult>>>& forecastResults,
                            vector<Date>& dates, bool& isByYear, bool& isForChart)
{
    vector<vector<ForecastResult>> results;
    int i = 0, lent = forecastResults.size();
    for(i = 0; i < lent; i++){
        results.push_back(GetYearlyForcastResultFacilityLevel(forecastResults[i], 
        dates, isByYear, isForChart));
    }

    return results;

}
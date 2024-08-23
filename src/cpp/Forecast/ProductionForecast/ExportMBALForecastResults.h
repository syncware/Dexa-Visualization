#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <tuple>
#include <time.h>
#include <functional>
#include "./Forecast.h"

using namespace std;
using namespace std::placeholders;

class ExportMBALForecastResults
{
private:

public:
    ExportMBALForecastResults();
    ~ExportMBALForecastResults();
    string GetRow(MBALForecastModel& r, int& ii, bool& isLastRow,
    string& ModuleName);
    WellActivityResult GetForecastWellOutput(vector<MBALForecastModel>& results,
    string& moduleName);
    tuple<vector<string>, vector<string>> ExportFiles(vector<WellActivityResult>& wellActivities,
    string& FolderName);


    vector<vector<vector<ForecastResult>>> results;

};

ExportMBALForecastResults::ExportMBALForecastResults()
{

}

ExportMBALForecastResults::~ExportMBALForecastResults()
{

}


string ExportMBALForecastResults::GetRow(MBALForecastModel& r, int& ii, bool& isLastRow,
string& ModuleName){

string row = "";
string columnDelimeter = "@#$%";
string rowDelimeter = "@#*$%";

std::string uniqueId = ModuleName +  to_string(ii);

string lastrow = std::to_string(r.wGR) +  rowDelimeter;
if(isLastRow == true){
	lastrow = std::to_string(r.wGR); // no new line
}

//isLastRow
row = to_string(r.cGR) +  columnDelimeter
		+ to_string(r.cumGasProduced) +  columnDelimeter
		+ to_string(r.cumOilProduced) +  columnDelimeter
        + to_string(r.cumWaterProduced) +  columnDelimeter
        + to_string(r.deltaPPressure) +  columnDelimeter
        + to_string(r.deltaPTubing) +  columnDelimeter
        + to_string(r.dPChoke) +  columnDelimeter
        + to_string(r.fBHP) +  columnDelimeter
        + to_string(r.gasRate) +  columnDelimeter
        + to_string(r.gLR) +  columnDelimeter
        + to_string(r.gOR) +  columnDelimeter
        + to_string(r.liquidRate) +  columnDelimeter
        + to_string(r.manPress) +  columnDelimeter
        + to_string(r.numberOfWells) +  columnDelimeter
        + to_string(r.oilRate) +  columnDelimeter
        + r.status +  columnDelimeter
        + to_string(r.tankPressure) +  columnDelimeter
        + r.time +  columnDelimeter
        + r.uniqueId +  columnDelimeter
        + to_string(r.waterCut) +  columnDelimeter
        + to_string(r.waterRate) +  columnDelimeter
		+ lastrow;

		return row;

}

WellActivityResult ExportMBALForecastResults::GetForecastWellOutput(vector<MBALForecastModel>& results,
string& moduleName)
{
    string table = "";
	int lastRow = results.size();

	int ij = -1;

	
	for (int ii = 0; ii < lastRow; ii++) {

		bool isLastRow = false;
		if(ii == lastRow-1){
			isLastRow = true;
		}
        table = table + GetRow(results[ii], ii, isLastRow, moduleName);

	}

    WellActivityResult wellActivity;
    wellActivity.table = table;
    wellActivity.ForecastProfile = MBAL;
    wellActivity.ModuleName = moduleName;

    return wellActivity;
}

tuple<vector<string>, vector<string>> ExportMBALForecastResults::ExportFiles(vector<WellActivityResult>& wellActivities,
 string& FolderName)
{
    vector<string> filePaths;
    vector<string> tables;
    int k = 0, nk = wellActivities.size();
    tuple<vector<string>, vector<string>> tupleObject;

    for(k = 0; k < nk; k++)
    {
        string filePath = FolderName + "/" + wellActivities[k].ModuleName + ".txt";
        string table = wellActivities[k].table;
        filePaths.push_back(filePath);
        tables.push_back(table);
    }

    tupleObject = make_tuple(filePaths, tables);
    return tupleObject;
}

#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <tuple>
#include <time.h>
#include <dirent.h>
#include <functional>
#include "./Forecast.h"
#include "./Inputdeck.h"

using namespace std;
using namespace std::placeholders;

class ImportForecastResults
{
private:
	Inputdeck inputdeck;
	const string columnDelimeter = "@#$%";
	const string rowDelimeter = "@#*$%";

public:
	ImportForecastResults();
	~ImportForecastResults();
	vector<ForecastResult> GetForecastResults(vector<string> &forecastResultRows);
	ForecastResult SetRow(vector<string> &forecastColumnsValues);
	vector<ForecastResult> ImportForecastResultFiles(vector<string> &ModuleNames,
													 vector<vector<string>> &files);
	vector<string> GetSubDirectories(const std::string &parentDirectory);
	vector<string> GetDirectoryFiles(const string &parentDirectory);
	vector<ForecastResult> GetForecastResults(string &forecastResulttable, vector<Date> &dates);
};

ImportForecastResults::ImportForecastResults()
{
}

ImportForecastResults::~ImportForecastResults()
{
}

/* vector<string> ImportForecastResults::GetSubDirectories(const string& parentDirectory) {
	vector<string> r;
	for(auto& p : std::filesystem::recursive_directory_iterator(parentDirectory))
		if (p.is_directory())
			r.push_back(p.path().string());
	return r;
}
 */
vector<string> ImportForecastResults::GetSubDirectories(const std::string &parentDirectory)
{
	std::vector<std::string> subdirs;
	DIR *dir = opendir(parentDirectory.c_str());
	if (dir)
	{
		struct dirent *entry;
		while ((entry = readdir(dir)) != NULL)
		{
			if (entry->d_type == DT_DIR && std::string(entry->d_name) != "." && std::string(entry->d_name) != "..")
			{
				subdirs.push_back(entry->d_name);
			}
		}
		closedir(dir);
	}
	return subdirs;
}

/* vector<string> ImportForecastResults::GetDirectoryFiles(const string& parentDirectory)
{
	vector<string> r;
	for (const auto & entry : std::filesystem::directory_iterator(parentDirectory)){
		r.push_back(entry.path().filename().string());
	}
	return r;
} */

vector<string> ImportForecastResults::GetDirectoryFiles(const std::string &parentDirectory)
{
	std::vector<std::string> files;
	DIR *dir = opendir(parentDirectory.c_str());
	if (dir)
	{
		struct dirent *entry;
		while ((entry = readdir(dir)) != NULL)
		{
			if (entry->d_type == DT_REG)
			{ // Check if it's a regular file
				files.push_back(entry->d_name);
			}
		}
		closedir(dir);
	}
	return files;
}

ForecastResult ImportForecastResults::SetRow(vector<string> &forecastColumnsValues)
{

	ForecastResult forecastResult;
	int i = -1;
	i++;
	forecastResult.uniqueId = forecastColumnsValues[i];
	i++;
	forecastResult.Version_Name = forecastColumnsValues[i];
	i++;
	forecastResult.Field = forecastColumnsValues[i];
	i++;
	forecastResult.Reservoir = forecastColumnsValues[i];
	i++;
	forecastResult.Drainage_Point = forecastColumnsValues[i];
	i++;
	forecastResult.Production_String = forecastColumnsValues[i];
	i++;
	forecastResult.TRANCHE = forecastColumnsValues[i];
	i++;
	forecastResult.Asset_Team = forecastColumnsValues[i];
	i++;
	forecastResult.Flow_station = forecastColumnsValues[i];
	i++;
	forecastResult.ModuleName = forecastColumnsValues[i];
	i++;
	forecastResult.Day = stoi(forecastColumnsValues[i]);
	i++;
	forecastResult.Month = stoi(forecastColumnsValues[i]);
	i++;
	forecastResult.Year = stoi(forecastColumnsValues[i]);
	i++;
	forecastResult.Oil_rate = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.Gas_Rate = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.Water_Rate = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.Liquid_Rate = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.Cum_Oil_Prod = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.Cum_Gas_Prod = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.Cum_Water_Prod = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.GOR = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.BSW = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.CGR = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.WGR = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.CutBack = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.HyrocarbonStream = forecastColumnsValues[i];
	i++;
	forecastResult.hydrocarbonType = forecastColumnsValues[i];
	i++;
	forecastResult.terminal = forecastColumnsValues[i];
	i++;
	forecastResult.URo = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.URg = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.Gas_Own_Use = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.Gas_Demand = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.Gas_Flared = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.Crude_Oil_Lossess = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.CutBack = stod(forecastColumnsValues[i]);
	i++;
	forecastResult.projectCode = forecastColumnsValues[i];
	i++;
	forecastResult.projectName = forecastColumnsValues[i];
	i++;
	i++;
	i++;
	i++;
	i++;
	forecastResult.resourceClass = forecastColumnsValues[i];
	i++;
	forecastResult.DeclineRate = stod(forecastColumnsValues[i]);
	i++;

	return forecastResult;
}

vector<ForecastResult> ImportForecastResults::GetForecastResults(string &forecastResulttable,
																 vector<Date> &dates)
{
	vector<ForecastResult> results;
	vector<string> stringRows;
	ForecastResult forecastResult2;
	forecastResult2.InitailizeData();
	inputdeck.tokenize(forecastResulttable, rowDelimeter, stringRows);
	int j = 0, nj = stringRows.size();

	vector<double> gasOwnUse;
	vector<double> gasFlared;
	vector<double> salesGas;

	for (j = 0; j < nj; j++)
	{
		if (j > 300)
		{
			double a = 0;
		}
		vector<string> stringColumns;
		inputdeck.tokenize(stringRows[j], columnDelimeter, stringColumns);
		if (stringColumns.size() == 43)
		{
			ForecastResult forecastResult = SetRow(stringColumns);
			forecastResult2 = SetRow(stringColumns);
			results.push_back(forecastResult);

			gasOwnUse.push_back(forecastResult2.Gas_Own_Use);
			gasFlared.push_back(forecastResult2.Gas_Flared);
			salesGas.push_back(forecastResult2.Gas_Demand);
		}
		else
		{
			ForecastResult forecastResult;
			forecastResult.InitailizeData();
			forecastResult.Day = dates[j].day;
			forecastResult.Month = dates[j].month;
			forecastResult.Year = dates[j].year;
			results.push_back(forecastResult);

			gasOwnUse.push_back(forecastResult2.Gas_Own_Use);
			gasFlared.push_back(forecastResult2.Gas_Flared);
			salesGas.push_back(forecastResult2.Gas_Demand);
		}
	}

	for (j = 0; j < nj; j++)
	{
		results[j].HyrocarbonStream = forecastResult2.HyrocarbonStream;
		results[j].hydrocarbonType = forecastResult2.hydrocarbonType;
		results[j].terminal = forecastResult2.terminal;
		results[j].ModuleName = forecastResult2.ModuleName;
		results[j].Version_Name = forecastResult2.Version_Name;
		results[j].Field = forecastResult2.Field;
		results[j].Reservoir = forecastResult2.Reservoir;
		results[j].Drainage_Point = forecastResult2.Drainage_Point;
		results[j].Production_String = forecastResult2.Production_String;
		results[j].TRANCHE = forecastResult2.TRANCHE;
		results[j].Asset_Team = forecastResult2.Asset_Team;
		results[j].Flow_station = forecastResult2.Flow_station;
		results[j].projectCode = forecastResult2.projectCode;
		results[j].projectName = forecastResult2.projectName;
		results[j].resourceClass = forecastResult2.resourceClass;
	}

	return results;
}

vector<ForecastResult> ImportForecastResults::GetForecastResults(vector<string> &forecastResultRows)
{
	vector<ForecastResult> results;
	int k = 0, nk = forecastResultRows.size();

	for (k = 0; k < nk; k++)
	{
		string row = forecastResultRows[k];
		vector<string> strings;
		inputdeck.tokenize(row, columnDelimeter, strings);
		ForecastResult forecastResult = SetRow(strings);
		results.push_back(forecastResult);
	}

	return results;
}

vector<ForecastResult> ImportForecastResults::ImportForecastResultFiles(vector<string> &ModuleNames,
																		vector<vector<string>> &files)
{
	vector<ForecastResult> results;
	int k = 0, nk = ModuleNames.size();

	for (k = 0; k < nk; k++)
	{
		vector<string> table = files[k];
		vector<string> strings;
		inputdeck.tokenize(table[0], rowDelimeter, strings);

		/* WellActivityResult wellActivityResult;
		wellActivityResult.ModuleName = ModuleNames[k];
		wellActivityResult.externalForecastProfile =  */
		vector<ForecastResult> result2 = GetForecastResults(strings);
		int i = 0;
		int ni = result2.size();
		for (i = 0; i < ni; i++)
		{
			results.push_back(result2[i]);
		}
	}

	return results;
}
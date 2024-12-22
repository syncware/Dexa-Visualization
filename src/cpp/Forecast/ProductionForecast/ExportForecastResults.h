#pragma once

#include <iostream>
#include <fstream>
#include <future>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <tuple>
#include <time.h>
#include <functional>
#include <sys/stat.h>
#include <errno.h> // errno, ENOENT, EEXIST
// #include <filesystem>
#include "./Forecast.h"
#include "./Inputdeck.h"
#include "./dataPivoting.h"

using namespace std;
using namespace std::placeholders;

class ExportForecastResults
{
private:
	Inputdeck inputdeck;
	DateCreation dateCreation;
	dataPivoting _dataPivoting;

public:
	ExportForecastResults();
	~ExportForecastResults();
	void GetForecastOutputAllFacilities(int &scenario,
										vector<vector<FacilityWellsIndicies>> &facilityWellsIndicies, vector<Date> &dateTimes);
	/* void GetForecastOutputAllFacilitiesAsync(int& scenario,
	vector<vector<FacilityWellsIndicies>>& facilityWellsIndicies, vector<Date>& dateTimes); */
	string GetRow(ForecastResult &r, int &scenario, int &ii, bool &isLastRow);
	string GetRow(ForecastResult &r, int &scenario, int &ii, vector<Date> &dateTimes);
	void GetForecastWellMonthOutput(int &k, int &j, int &scenario,
									string &table);
	vector<WellActivityResult> GetForecastFacilityOutput(int &k, int &scenario);
	vector<FacilityActivityResult> GetForecastOutput(int &scenario, vector<string> Facilities);
	void GetForecastOutput(int &scenario,
						   vector<vector<FacilityWellsIndicies>> &facilityWellsIndicies,
						   vector<Date> &dateTimes, int &facilityIndex, int &wellIndex,
						   string &wellName, string &facilityName);
	tuple<vector<string>, vector<string>> ExportFiles(vector<WellActivityResult> &wellActivities,
													  string &FolderName);
	vector<ScenarioModel> UpdateScenarios();
	// int mkpath(std::string s);
	int mkpath(std::string s);
	void WriteToAFile(const string &FilePath, string &table);
	/* void WriteToAFileAsync(const string& FilePath, string& table); */
	void exportConstraintMatrix(vector<vector<double>> &consMatrx);
	void exportFreeVariables(vector<double> &freeVars);
	void exportFunctionVariables(vector<double> &funcVars);
	void exportSolution(vector<double> &sols);
	void GetTable(string &table, string &row);
	void GetListofTables(string &listOfTables, string &table);

	vector<vector<vector<ForecastResult>>> results;
	vector<ScenarioModel> Scenarios;
};

ExportForecastResults::ExportForecastResults()
{
}

ExportForecastResults::~ExportForecastResults()
{
}

void ExportForecastResults::exportConstraintMatrix(vector<vector<double>> &consMatrx)
{
	string tab = "\t", newline = "\n";
	int nrows = consMatrx.size();
	int ncols = consMatrx[0].size();
	string table = "";
	string FolderName = "./Demo Data";
	string filePath = FolderName + "/Validate Apex Solver/ConstraintMatrix.txt";
	int i = 0, j = 0;
	for (i = 0; i < nrows; i++)
	{
		string row = "";
		for (j = 0; j < ncols; j++)
		{
			row = row + to_string(consMatrx[i][j]) + tab;
		}
		table = table + row + newline;
	}
	WriteToAFile(filePath, table);
}
void ExportForecastResults::exportFreeVariables(vector<double> &freeVars)
{
	string tab = "\t", newline = "\n";
	int nrows = freeVars.size();
	string table = "";
	string FolderName = "./Demo Data";
	string filePath = FolderName + "/Validate Apex Solver/FreeVariables.txt";
	int i = 0, j = 0;
	for (i = 0; i < nrows; i++)
	{
		string row = "";
		row = row + to_string(freeVars[i]) + tab;
		table = table + row + newline;
	}
	WriteToAFile(filePath, table);
}
void ExportForecastResults::exportFunctionVariables(vector<double> &funcVars)
{
	string tab = "\t", newline = "\n";
	int nrows = funcVars.size();
	string table = "";
	string FolderName = "./Demo Data";
	string filePath = FolderName + "/Validate Apex Solver/FunctionVariables.txt";
	int i = 0, j = 0;
	for (i = 0; i < nrows; i++)
	{
		string row = "";
		row = row + to_string(funcVars[i]) + tab;
		table = table + row + newline;
	}
	WriteToAFile(filePath, table);
}

void ExportForecastResults::exportSolution(vector<double> &sols)
{
	string tab = "\t", newline = "\n";
	int nrows = sols.size();
	string table = "";
	string FolderName = "./Demo Data";
	string filePath = FolderName + "/Validate Apex Solver/Solution.txt";
	int i = 0, j = 0;
	for (i = 0; i < nrows; i++)
	{
		string row = "";
		row = row + to_string(sols[i]) + tab;
		table = table + row + newline;
	}
	WriteToAFile(filePath, table);
}

void ExportForecastResults::GetTable(string &table, string &row)
{
	string columnDelimeter = "@#$%";
	string rowDelimeter = "@#*$%";
	table = table + row;
}

void ExportForecastResults::GetListofTables(string &listOfTables, string &table)
{
}

string ExportForecastResults::GetRow(ForecastResult &r, int &scenario, int &ii, bool &isLastRow)
{

	string row = "";
	string columnDelimeter = "@#$%";
	string rowDelimeter = "@#*$%";

	std::string uniqueId = r.ModuleName + r.Flow_station + to_string(scenario) + "P" + to_string(scenario) + "C" + to_string(ii);
	double oilRate = 0, condensateRate = 0;
	if (r.HyrocarbonStream == "oil")
	{
		oilRate = r.Oil_rate;
		condensateRate = 0;
	}
	else
	{
		condensateRate = r.Oil_rate;
		oilRate = 0;
	}

	double liquid = 0;
	if (r.HyrocarbonStream == "oil")
	{
		liquid = oilRate + r.Water_Rate;
	}
	else
	{
		liquid = condensateRate + r.Water_Rate;
	}
	string lastrow = std::to_string(r.DeclineRate) + rowDelimeter;
	if (isLastRow == true)
	{
		lastrow = std::to_string(r.DeclineRate); // no new line
	}

	// isLastRow
	row = uniqueId + columnDelimeter + r.Version_Name + columnDelimeter + r.Field + columnDelimeter + r.Reservoir + columnDelimeter + r.Drainage_Point + columnDelimeter + r.Production_String + columnDelimeter + r.TRANCHE + columnDelimeter + r.Asset_Team + columnDelimeter + r.Flow_station + columnDelimeter + r.ModuleName + columnDelimeter + std::to_string(r.Day) + columnDelimeter + std::to_string(r.Month) + columnDelimeter + std::to_string(r.Year) + columnDelimeter + std::to_string(oilRate) + columnDelimeter + std::to_string(r.Gas_Rate) + columnDelimeter + std::to_string(r.Water_Rate) + columnDelimeter + std::to_string(liquid) + columnDelimeter + std::to_string(r.Cum_Oil_Prod) + columnDelimeter + std::to_string(r.Cum_Gas_Prod) + columnDelimeter + std::to_string(r.Cum_Water_Prod) + columnDelimeter + std::to_string(r.GOR) + columnDelimeter + std::to_string(r.BSW) + columnDelimeter + std::to_string(r.CGR) + columnDelimeter + std::to_string(r.WGR) + columnDelimeter + std::to_string(r.CutBack) + columnDelimeter + r.HyrocarbonStream + columnDelimeter + r.hydrocarbonType + columnDelimeter + r.terminal + columnDelimeter + std::to_string(r.URo) + columnDelimeter + std::to_string(r.URg) + columnDelimeter + std::to_string(r.Gas_Own_Use) + columnDelimeter + std::to_string(r.Gas_Demand) + columnDelimeter + std::to_string(r.Gas_Flared) + columnDelimeter + std::to_string(r.Crude_Oil_Lossess) + columnDelimeter + std::to_string(r.CutBack) + columnDelimeter + r.projectCode + columnDelimeter + r.projectName + columnDelimeter + r.resourceClass + columnDelimeter + std::to_string(condensateRate) + columnDelimeter + lastrow;

	return row;
}

string ExportForecastResults::GetRow(ForecastResult &r, int &scenario, int &ii, vector<Date> &dateTimes)
{

	string row = "";
	string columnDelimeter = "@#$%";
	string rowDelimeter = "@#*$%";
	int days = dateCreation.DateDiff_TotalDays(dateTimes[ii], dateTimes[0]);

	std::string uniqueId = r.ModuleName + r.Flow_station + to_string(scenario) + "P" + to_string(scenario) + "C" + to_string(ii);

	double oilRate = 0, condensateRate = 0;
	if (r.HyrocarbonStream == "oil")
	{
		oilRate = r.Oil_rate;
		condensateRate = 0;
	}
	else
	{
		condensateRate = r.Oil_rate;
		oilRate = 0;
	}

	if (r.isOilTerminated == true)
	{
		oilRate = 0;
		condensateRate = 0;
	}

	if (r.isGasTerminated == true)
	{
		r.Gas_Rate = 0;
	}

	if (r.isWaterTerminated == true)
	{
		r.Water_Rate = 0;
	}

	double liquid = 0;
	if (r.HyrocarbonStream == "oil")
	{
		liquid = oilRate + r.Water_Rate;
	}
	else
	{
		liquid = condensateRate + r.Water_Rate;
	}
	string lastrow = std::to_string(r.DeclineRate) + rowDelimeter;

	// isLastRow
	row = uniqueId + columnDelimeter + r.Version_Name + columnDelimeter + r.Field + columnDelimeter + r.Reservoir + columnDelimeter + r.Drainage_Point + columnDelimeter + r.Production_String + columnDelimeter + r.TRANCHE + columnDelimeter + r.Asset_Team + columnDelimeter + r.Flow_station + columnDelimeter + r.ModuleName + columnDelimeter + std::to_string(r.Day) + columnDelimeter + std::to_string(r.Month) + columnDelimeter + std::to_string(r.Year) + columnDelimeter + std::to_string(oilRate) + columnDelimeter + std::to_string(r.Gas_Rate) + columnDelimeter + std::to_string(r.Water_Rate) + columnDelimeter + std::to_string(liquid) + columnDelimeter + std::to_string(r.Cum_Oil_Prod) + columnDelimeter + std::to_string(r.Cum_Gas_Prod) + columnDelimeter + std::to_string(r.Cum_Water_Prod) + columnDelimeter + std::to_string(r.GOR) + columnDelimeter + std::to_string(r.BSW) + columnDelimeter + std::to_string(r.CGR) + columnDelimeter + std::to_string(r.WGR) + columnDelimeter + std::to_string(r.CutBack) + columnDelimeter + r.HyrocarbonStream + columnDelimeter + r.hydrocarbonType + columnDelimeter + r.terminal + columnDelimeter + std::to_string(r.URo) + columnDelimeter + std::to_string(r.URg) + columnDelimeter + std::to_string(r.Gas_Own_Use) + columnDelimeter + std::to_string(r.Gas_Demand) + columnDelimeter + std::to_string(r.Gas_Flared) + columnDelimeter + std::to_string(r.Crude_Oil_Lossess) + columnDelimeter + std::to_string(r.CutBack) + columnDelimeter + r.projectCode + columnDelimeter + r.projectName + columnDelimeter + std::to_string(days) + columnDelimeter + std::to_string(r.OptimalSolution) + columnDelimeter + std::to_string(r.AllWellsLiquidCapacity) + columnDelimeter + std::to_string(r.AllWellsGasCapacity) + columnDelimeter + r.resourceClass + columnDelimeter + std::to_string(condensateRate) + columnDelimeter + lastrow;

	return row;
}

void ExportForecastResults::GetForecastWellMonthOutput(int &k, int &j, int &scenario,
													   string &table)
{

	int lastRow = results[k][j].size();

	int ij = -1;

	for (int ii = 0; ii < lastRow; ii++)
	{

		Date startDate;
		startDate.day = results[k][j][ii].startDay;
		startDate.month = results[k][j][ii].startMonth;
		startDate.year = results[k][j][ii].StartYear;

		bool isLastRow = false;
		if (ii == lastRow - 1)
		{
			isLastRow = true;
		}

		if (startDate.year != 2900)
		{
			ij++;
			table = table + GetRow(results[k][j][ii], scenario, ij, isLastRow);
		}
	}
}

vector<WellActivityResult> ExportForecastResults::GetForecastFacilityOutput(int &k,
																			int &scenario)
{

	int j = -1;
	int noOfWells = results[k].size();
	string FacilityName = "";
	vector<WellActivityResult> wellActivities;

	for (j = 0; j < noOfWells; j++)
	{
		string table = "";
		GetForecastWellMonthOutput(k, j, scenario, table);

		if (table != "")
		{
			WellActivityResult wellActivity;
			wellActivity.table = table;
			wellActivity.ForecastProfile = Default;
			wellActivity.ModuleName = results[k][j][0].ModuleName;
			wellActivities.push_back(wellActivity);
		}
	}

	return wellActivities;
}

vector<FacilityActivityResult> ExportForecastResults::GetForecastOutput(int &scenario,
																		vector<string> Facilities)
{

	int k = -1;
	vector<FacilityActivityResult> wellActivities;

	int FacilitiesSize = results.size();

	for (k = 0; k < FacilitiesSize; k++)
	{
		vector<WellActivityResult> wellActivitiesByFacility =
			GetForecastFacilityOutput(k, scenario);

		FacilityActivityResult facility;
		facility.FacilityName = Facilities[k];
		facility.WellActivityResults = wellActivitiesByFacility;

		int j = 0, nSize = wellActivitiesByFacility.size();
		for (j = 0; j < nSize; j++)
		{
			facility.WellActivityResults.push_back(wellActivitiesByFacility[j]);
		}

		wellActivities.push_back(facility);
	}

	return wellActivities;
}

/* void ExportForecastResults::GetForecastOutputAllFacilitiesAsync(const int scenario,
vector<vector<FacilityWellsIndicies>>& facilityWellsIndicies, vector<Date>& dateTimes)
{
	std::async(std::launch::async, [=](){
		 GetForecastOutputAllFacilities(scenario,facilityWellsIndicies, dateTimes);
	});
} */

void ExportForecastResults::GetForecastOutputAllFacilities(int &scenario,
														   vector<vector<FacilityWellsIndicies>> &facilityWellsIndicies, vector<Date> &dateTimes)
{
	int mkdirretval = 0;
	int nDates = dateTimes.size();
	string FolderName = "./Demo Data";
	string filePath = FolderName + "/Reroute Wells Result/Scenarios";
	// Create scenario folder path
	string filePath1 = filePath + "/" + "Scenario" + std::to_string(scenario);
	//========================================================================//
	// Create scenario folder
	mkdirretval = mkpath(filePath1);
	//==========================================================================//
	int j = nDates - 1, facilityIndex = 0;
	int wellIndex = 0;
	int nFacilities = facilityWellsIndicies[j].size();
	for (facilityIndex = 0; facilityIndex < nFacilities; facilityIndex++)
	{

		// Create facility folder path
		string filePath2 = filePath1 + "/" +
						   facilityWellsIndicies[j][facilityIndex].Facility;
		// Create facility folder
		mkdirretval = mkpath(filePath2);

		// if(facilityWellsIndicies[j][facilityIndex].Facility == "ABU_FS1"){
		int nWells = facilityWellsIndicies[j][facilityIndex].WellNames.size();
		for (wellIndex = 0; wellIndex < nWells; wellIndex++)
		{
			GetForecastOutput(scenario, facilityWellsIndicies, dateTimes, facilityIndex, wellIndex,
							  facilityWellsIndicies[j][facilityIndex].WellNames[wellIndex],
							  facilityWellsIndicies[j][facilityIndex].Facility);
		}
		//}
	}
}

void ExportForecastResults::GetForecastOutput(int &scenario,
											  vector<vector<FacilityWellsIndicies>> &facilityWellsIndicies,
											  vector<Date> &dateTimes, int &facilityIndex, int &wellIndex,
											  string &wellName, string &facilityName)
{

	/* std::cout << "Started Streaming Facility " <<
	facilityWellsIndicies[0][facilityIndex].Facility <<
	" of Well " <<
	facilityWellsIndicies[0][facilityIndex].WellNames[wellIndex]
	<<  std::endl; */

	int j = 0, mkdirretval = 0;

	int nDates = dateTimes.size();
	vector<ForecastResult> wellResultsForAggregation;
	// vector<ForecastResult> aggregatedWellResults;

	for (j = 0; j < nDates; j++)
	{

		if (j > 0)
		{

			if (facilityWellsIndicies[j - 1][facilityIndex].tables.size() <
				facilityWellsIndicies[j][facilityIndex].tables.size())
			{
				facilityWellsIndicies[j][facilityIndex].tables = facilityWellsIndicies[j - 1][facilityIndex].tables;
				facilityWellsIndicies[j][facilityIndex].tables.push_back("");
			}
			else
			{
				facilityWellsIndicies[j][facilityIndex].tables = facilityWellsIndicies[j - 1][facilityIndex].tables;
			}
		}

		if (results[j][facilityIndex][wellIndex].IsFlowing == false)
		{
			// Clean up unwanted data
			results[j][facilityIndex][wellIndex].InitializeData();
		}

		wellResultsForAggregation.push_back(results[j][facilityIndex][wellIndex]);
	}

	// bool isByYear = false;
	// vector<Date> aggregatedDates = _dataPivoting.GetListOfYears(wellResultsForAggregation, isByYear);

	// aggregatedWellResults = _dataPivoting.GetYearlyForcastResultModuleLevelMonthly(
	//	wellResultsForAggregation, aggregatedDates);

	string table = "";
	nDates = wellResultsForAggregation.size();
	for (j = 0; j < nDates; j++)
	{
		if (j > 300)
		{
			double aa = 0;
		}
		table = table + GetRow(wellResultsForAggregation[j], scenario, j, dateTimes);
	}

	if (nDates > 0)
	{
		j = nDates - 1;
		string FolderName = "./Demo Data";
		string filePath = FolderName + "/Reroute Wells Result/Scenarios";
		string filePath1 = filePath + "/" + "Scenario" + std::to_string(scenario);
		string filePath2 = filePath1 + "/" + facilityName;
		string filePath3 = filePath2 + "/" + wellName + ".txt";
		WriteToAFile(filePath3, table);
	}
}

tuple<vector<string>, vector<string>> ExportForecastResults::ExportFiles(vector<WellActivityResult> &wellActivities,
																		 string &FolderName)
{
	vector<string> filePaths;
	vector<string> tables;
	int k = 0, nk = wellActivities.size();
	tuple<vector<string>, vector<string>> tupleObject;

	for (k = 0; k < nk; k++)
	{
		string filePath = FolderName + "/" + wellActivities[k].ModuleName + ".txt";
		string table = wellActivities[k].table;
		filePaths.push_back(filePath);
		tables.push_back(table);
	}

	tupleObject = make_tuple(filePaths, tables);
	return tupleObject;
}

vector<ScenarioModel> ExportForecastResults::UpdateScenarios()
{

	int i = 0;
	int j = 0;
	int k = 0;
	int nScenarios = Scenarios.size();
	string columnDelimeter = "@#$%";
	string rowDelimeter = "@#*$%";

	for (k = 0; k < nScenarios; k++)
	{
		int nFacilities = Scenarios[k].result.size();
		for (j = 0; j < nFacilities; j++)
		{
			int nWells = Scenarios[k].result[j].WellActivityResults.size();
			for (i = 0; i < nWells; i++)
			{
				vector<string> rows;
				inputdeck.tokenize(Scenarios[k].result[j].WellActivityResults[i].table,
								   rowDelimeter,
								   rows);
				for (int jj = 0; jj < rows.size(); jj++)
				{
					vector<string> columns;
					inputdeck.tokenize(rows[jj],
									   columnDelimeter,
									   columns);
					ForecastResult customForecastResult;
					int ii = -1;
					ii++;
					customForecastResult.uniqueId = columns[ii];
					ii++;
					customForecastResult.Version_Name = columns[ii];
					ii++;
					customForecastResult.Field = columns[ii];
					ii++;
					customForecastResult.Reservoir = columns[ii];
					ii++;
					customForecastResult.Drainage_Point = columns[ii];
					ii++;
					customForecastResult.TRANCHE = columns[ii];
					ii++;
					customForecastResult.Asset_Team = columns[ii];
					ii++;
					customForecastResult.Flow_station = columns[ii];
					ii++;
					customForecastResult.ModuleName = columns[ii];
					ii++;
					customForecastResult.Day = stoi(columns[ii]);
					ii++;
					customForecastResult.Month = stoi(columns[ii]);
					ii++;
					customForecastResult.Year = stoi(columns[ii]);
					ii++;
					customForecastResult.Oil_rate = stod(columns[ii]);
					ii++;
					customForecastResult.Gas_Rate = stod(columns[ii]);
					ii++;
					customForecastResult.Water_Rate = stod(columns[ii]);
					ii++;
					customForecastResult.Liquid_Rate = stod(columns[ii]);
					ii++;
					customForecastResult.Cum_Oil_Prod = stod(columns[ii]);
					ii++;
					customForecastResult.Cum_Gas_Prod = stod(columns[ii]);
					ii++;
					customForecastResult.Cum_Water_Prod = stod(columns[ii]);
					ii++;
					customForecastResult.GOR = stod(columns[ii]);
					ii++;
					customForecastResult.BSW = stod(columns[ii]);
					ii++;
					customForecastResult.CGR = stod(columns[ii]);
					ii++;
					customForecastResult.WGR = stod(columns[ii]);
					ii++;
					customForecastResult.CutBack = stod(columns[ii]);
					ii++;
					customForecastResult.HyrocarbonStream = columns[ii];
					ii++;
					customForecastResult.hydrocarbonType = columns[ii];
					ii++;
					customForecastResult.terminal = columns[ii];
					ii++;
					customForecastResult.URo = stod(columns[ii]);
					ii++;
					customForecastResult.URg = stod(columns[ii]);
					ii++;
					customForecastResult.Gas_Own_Use = stod(columns[ii]);
					ii++;
					customForecastResult.Gas_Demand = stod(columns[ii]);
					ii++;
					customForecastResult.Gas_Flared = stod(columns[ii]);
					ii++;
					customForecastResult.Crude_Oil_Lossess = stod(columns[ii]);
					ii++;
					customForecastResult.CutBack = stod(columns[ii]);
					ii++;
					customForecastResult.projectCode = columns[ii];
					ii++;
					customForecastResult.projectName = columns[ii];
					ii++;
					customForecastResult.resourceClass = columns[ii];

					Scenarios[k].result[j].WellActivityResults[i].externalForecastProfile.push_back(customForecastResult);
				}
			}
		}
	}

	return Scenarios;
}

int ExportForecastResults::mkpath(std::string s)
{
	/* mode_t mode = 0755;
	size_t pos=0;
	std::string dir;
	int mdret;

	if(s[s.size()-1]!='/'){
		// force trailing / so we can handle everything in loop
		s+='/';
	}

	while((pos=s.find_first_of('/',pos))!=std::string::npos){
		dir=s.substr(0,pos++);
		if(dir.size()==0) continue; // if leading / first time is 0 length
		if((mdret=mkdir(dir.c_str(),mode)) && errno!=EEXIST){
			return mdret;
		}
	}
	return mdret; */
	return 0;
}

/* int ExportForecastResults::mkpath(std::string s)
{
	bool created_new_directory = false;
	bool there_was_an_exception = false;

	try {
	created_new_directory
		= std::filesystem::create_directory(s);
	} catch(std::exception & e){
	there_was_an_exception = true;
	// creation failed
	}

	return 0;
} */

void ExportForecastResults::WriteToAFile(const string &FilePath, string &table)
{
	ofstream myFile_Handler;

	// File Open
	myFile_Handler.open(FilePath);

	// Write to the file
	myFile_Handler << table << endl;

	// File Close
	myFile_Handler.close();
}

/* void ExportForecastResults::WriteToAFileAsync(const string& FilePath, string& table)
{
	std::async(std::launch::async, [=](){
		ofstream myFile_Handler;
		myFile_Handler.open(FilePath);
		myFile_Handler << table << endl;
		myFile_Handler.close();
	});
} */

#pragma once

#ifndef CALCULATEDECKVARIABLES_H
#define CALCULATEDECKVARIABLES_H
#endif

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <thread>
#include <vector>
#include <iomanip>
#include <tuple>
#include <time.h>
#include <functional>
#include "Forecast.h"
#include "Decline_Curve_Analysis.h"
#include "../../MathematicsLibrary/Integration.h"
#include "../../MathematicsLibrary/MatrixOperations.h"
#include "FractionalFlow.h"
#include "DateCreation.h"
#include "../../MathematicsLibrary/MainSimplex.h"
#include "Inputdeck.h"
#include "./ExternalForecast.h"
#include "./ExportForecastResults.h"
#include "../../MathematicsLibrary/SimplexMethod/MainScreen.h"
#include "../../MathematicsLibrary/SimplexMethod/Model/Problem2.h"
//#include "../utilities/ToJSON.h"

using namespace std;
using namespace std::placeholders;

class CalculateDeckVariables
{
private:
	MatrixOperations matrixOperations;
	Decline_Curve_Analysis DCA;
	FractionalFlow fractionalFlow;
	Integration integration;
	DateCreation dateCreation;
	Inputdeck deckobj;
	ExternalForecast externalForecast;
	ExportForecastResults exportForecastResults;
	double Gas_Capacity;
	double Liquid_Capacity;
	double AG_Capacity;
	double NAG_Capacity;
	vector<ForecastResult> OnStreamWells;
	vector<ForecastResult> OptimizedWells;
	vector<int> OptimizedWellsIndicies;
	double optimalSolution;
	double allWellsLiquidCapacity;
	double allWellsGasCapacity = 0;
	bool isGasFlow = false;
	vector<double> wellsOilRates;
	vector<double> cumProdDays;
	double avgOilWellsRate;
	

public:
	//typedef double func(double x);

	CalculateDeckVariables();

	void GetDeckVariables(vector<vector<vector<InputDeckStruct>>> &Faclities, vector<int> &daysList,
						  int &scenario, vector<FacilityStruct> &FacilityTable,
						  vector<string> &FacilitiesNames, DateCreation &dateCreationX,
						  vector<WellReroute> &routedWells, string &forecastCase,
						  vector<vector<Priotization>> &priotizationsFacilities,
						  vector<Node> &updatesNodes, bool isMonthly);
	void GetDeckVariables(vector<InputDeckStruct> &facility, vector<int> &daysList,
						  int &scenario, int &facilityCounter, FacilityStruct &facilityStruct,
						  int &dateIndex, int &numberOfFacilities,
						  vector<vector<vector<InputDeckStruct>>> &Faclities,
						  string &forecastCase, Priotization &priotizationFacility);

	void GetDeckVariables2(vector<InputDeckStruct> &facility,
						   vector<int> &daysList, int &scenario, int &facilityCounter,
						   FacilityStruct &facilityStruct, int &dateIndex, int &numberOfFacilities,
						   vector<vector<vector<InputDeckStruct>>> &Faclities,
						   string &forecastCase, Priotization &priotizationFacility,
						   double &gasCutBack, double &liquidCutBack,
						   string &liquidCutBackText, string &gasCutBackText, 
						   string &nodeConnections);

	void GetActiveRate(int &scenario, InputDeckStruct &deck, ForecastResult &forecastResult, ForecastResult &forecastResult_old);

	void GetVariables(int &scenario, InputDeckStruct &deck, ForecastResult &forecastResult, ForecastResult &forecastResult_old,
					  double &externalCurrentCumProd, bool &isAfetrOptimization);

	void GetActiveCumProd(int &scenario, InputDeckStruct &deck, ForecastResult &forecastResult, ForecastResult &forecastResult_old);

	~CalculateDeckVariables();

	void GetGasFractionalFlow(int &scenario, InputDeckStruct &deck, ForecastResult &forecastResult,
	ForecastResult &forecastResult_old);

	void GetWaterFractionalFlow(int &scenario, InputDeckStruct &deck, ForecastResult &forecastResult,
	ForecastResult &forecastResult_old);

	void GetCumProds(int &scenario, InputDeckStruct &deck, ForecastResult &forecastResult, ForecastResult &forecastResult_old);

	void GetRates(int &scenario, InputDeckStruct &deck, ForecastResult &forecastResult);

	void PrintResults(string &BasePath, vector<string> &FaclitiesNames, vector<vector<InputDeckStruct>> &Faclities);

	void CreateFiles(string &BasePath, vector<vector<InputDeckStruct>> &Faclities, vector<string> &FaclitiesNames,
					 vector<Date> &dates, vector<int> &daysList, int &scenario);

	bool IsDirectory(const char *dirName);

	double fun(double a);

	double fun2(double a);

	using pFUNC = double (CalculateDeckVariables::*)(double);

	double TraplRule(pFUNC fun, double lowerBound, double upperBound, int intervals);

	double DeltaT;

	double initial_rate;

	double rate_of_change;

	int Method;

	vector<InputDeckStruct> InputDecks;

	vector<vector<vector<ForecastResult>>> results;

	void optimize_constraint_by_well(vector<ForecastResult> &onStreamWells,
		vector<double> &cutbacks, Priotization &priotizationFacility);

	void optimize_constraint_no_prioritization(vector<ForecastResult> &onStreamWells,
	vector<double> &cutbacks2, Priotization &priotizationFacility);

	void optimize_by_stream_prioritization(vector<ForecastResult> &onStreamWells,
		vector<double> &cutbacks2, Priotization &priotizationFacility);

	void optimize_olderNode_children(vector<Node> &nodes, int &nodeIndex,
									 vector<int> &actualChildrenNodesIndicies,
									 Priotization &priotizationNode);

	void GetOnstreamWells(int &facilityCounter, int &timeStepCounter, int &nWells, 
	FacilityStruct &facilityStruct, string& forecastCase, Priotization &priotizationFacility);

	void GetOnstreamWells2(int &facilityCounter, int &timeStepCounter, int &nWells, FacilityStruct &facilityStruct,
						   string &liquidCutBackText, string &gasCutBackText, string &nodeConnections);

	void SetCutRatesBackValues(int &facilityCounter, int &timeStepCounter, double &onStreamWellCutBack,
							   int &scenario, InputDeckStruct &deck, int &actualWellIndex);

	void SetCutRatesBackValues(int &facilityCounter, int &timeStepCounter,
							   int &scenario, InputDeckStruct &deck, int &actualWellIndex,
							   double &gasCutBack, double &liquidCutBack);

	bool isDefered;
	bool isFacilityDefered;

	void GetDeferedParameters(double &InitialRate, double &cumProdData, double &URf, double &AbandRate,
							  double &InitialCumProd, string &HCStream, InputDeckStruct &deck, int &scenario);
	void GetStartCumProdDefered(Date &FacilityDate, string &HCStream,
								InputDeckStruct &deck, int &scenario);
	void GetCurrentFacilityData();
	void GetActiveRate(int &scenario, InputDeckStruct &deck,
					   ForecastResult &forecastResult, ForecastResult &forecastResult_old,
					   ForecastResult &externalResult);
	bool CheckWellFacility(vector<WellFacilityData> WellFacilityDataList, string ModuleName, string FacilityName);
	tuple<bool, int> CheckWellFacilityAndGetIndex(vector<WellFacilityData> WellFacilityDataList, string ModuleName);
	bool GetIsWellFlowing(bool &isOilTerminated, bool &isGasTerminated, bool &isWaterterminated);
	void GetFacilityFlowRates(vector<Node> &updatesNodes);
	void GetDownStreamNodesFlux(vector<Node> &updatesNodes, int &activeNodeIndex);
	void AdjustWellsFlowRates(vector<Node> &updatesNodes,
							  vector<int> &daysList, int &scenario, vector<FacilityStruct> &FacilityTable,
							  string &forecastCase, vector<vector<Priotization>> &priotizationsFacilities,
							  vector<vector<vector<InputDeckStruct>>> &Faclities,
							  vector<Date>& dateTimes);
	int isContainText(vector<string>& texts, string& text);
	void WellAbandonmentConditions(int &scenario, InputDeckStruct &deck, ForecastResult &forecastResult, ForecastResult &forecastResult_old);
	vector<ForecastResult> SortOnstreamWells(vector<ForecastResult> &onstreamWells);
	vector<ForecastResult> SortOnstreamWellsByMean(vector<ForecastResult> &onstreamWells);
	double Percentile(vector<ForecastResult> &onstreamWells, double& p);
	vector<ForecastResult> SortOnstreamWellsByProbabilityDistribution(vector<ForecastResult> &onstreamWells);
	int isContainFluidFractionIndicator(vector<double> &uniqueFluidFractionIndicators, double& fluidFraction);
	vector<double> GetUniqueFluidFractionIndicators(vector<ForecastResult> &onstreamWells);

	double InitialRate_Defered;
	double Rate_of_Change_Defered;
	double startCumProdDefered;
	vector<FacilityStruct> FacilityList;
	vector<vector<FacilityStruct>> FacilityTables_Actual;

	Date CurrentDate;
	vector<Date> dates;
	int datePosition;
	int facilityCounter;
	int WellIndex;
	FacilityStruct CurrentFacilityData;
	vector<double> cutbacks;
	vector<double> optimized_cutbacks;

	/* ReportJSON reportJSON; */
	double LastRate;
	double SalesGasPlusOwnUse = 0;
	int startFrom = 0;
	double FacilityOiProduced = 0;
	double FacilityCondensateProduced = 0;
	double FacilityWaterProduced = 0;
	double FacilityGasProduced = 0;
	double FacilityAGProduced = 0;
	double FacilityNAGProduced = 0;
	double FacilityLiquidProduced = 0;
	string UseExternalForecastprofile = "internal";
	vector<WellActivityResult> WellActivities;
	vector<WellFacilityData> WellFacilityDataList;
	DateCreation dateCreationX;
	string facilitiesPerTimeStepReport = "";
	string facilitiesTimeStepsReport = "";
	string checker = "";
	bool dURConstrained = false;
	bool isMonthly = true;
	bool isRateCum = false;
	//ReportJSON reportJSON;
};

CalculateDeckVariables::CalculateDeckVariables()
{
}

CalculateDeckVariables::~CalculateDeckVariables()
{
}

double CalculateDeckVariables::Percentile(vector<ForecastResult> &onstreamWells, double& p) {
    
	// Ensure the data is sorted
	vector<ForecastResult> onstreamWells2 = SortOnstreamWells(onstreamWells);
    
    // Calculate the index for the percentile
    double n = onstreamWells2.size();
    double pos = p * (n + 1) / 100.0;
    int k = static_cast<int>(std::floor(pos));
    double d = pos - k;

    if (k == 0) {
        return onstreamWells2[0].fluidFraction;
    } else if (k >= n) {
        return onstreamWells2[n - 1].fluidFraction;
    } else {
        return onstreamWells2[k - 1].fluidFraction + d * (onstreamWells2[k].fluidFraction - onstreamWells2[k - 1].fluidFraction);
    }
}

vector<ForecastResult> CalculateDeckVariables::SortOnstreamWellsByProbabilityDistribution(vector<ForecastResult> &onstreamWells)
{


	// Calculate 10th, 50th, and 90th percentiles
	int n  = onstreamWells.size();
	double ten = 10.0;
	double fifty = 50.0;
	double ninety = 90.0;
    double p10 = Percentile(onstreamWells, ten);
    double p50 = Percentile(onstreamWells, fifty);
    double p90 = Percentile(onstreamWells, ninety);
	vector<double> percentiles = {p10, p50, p90};
	double minValue = matrixOperations.VectorMinimun(percentiles);
	double maxValue = matrixOperations.VectorMaximum(percentiles);
	double meadian = minValue;
	for(int j = 0; j < percentiles.size(); j++){
		if(percentiles[j] != minValue && percentiles[j] != maxValue){
			meadian = percentiles[j];
			break;
		}
	}

	for (int j = 0; j < n; j++)
	{
		if(onstreamWells[j].fluidFraction <= minValue){
			onstreamWells[j].fluidFraction = minValue;
		}else if(onstreamWells[j].fluidFraction > minValue && onstreamWells[j].fluidFraction <= meadian){
			onstreamWells[j].fluidFraction = meadian;
		}else{
			onstreamWells[j].fluidFraction = maxValue;
		}
	}

	onstreamWells = SortOnstreamWells(onstreamWells);

	return onstreamWells;
}

vector<ForecastResult> CalculateDeckVariables::SortOnstreamWellsByMean(vector<ForecastResult> &onstreamWells)
{

	DateCreation dateCreation;
	ForecastResult temp;
	int n = onstreamWells.size();
	double mean = 0;
	for (int j = 0; j < n ; j++)
	{
		mean = mean + onstreamWells[j].fluidFraction;
	}

	if(n > 0){
		mean = mean / n;
	}

	for (int j = 0; j < n ; j++)
	{
		if(onstreamWells[j].fluidFraction <= mean){
			onstreamWells[j].fluidFraction = 1.0;
		}else{
			onstreamWells[j].fluidFraction = 2.0;
		}
	}

	return onstreamWells;
}

vector<ForecastResult> CalculateDeckVariables::SortOnstreamWells(vector<ForecastResult> &onstreamWells)
{

	DateCreation dateCreation;
	ForecastResult temp;
	int n = onstreamWells.size();

	for (int j = 0; j <= n - 2; j++)
	{
		for (int i = 0; i <= n - 2; i++)
		{
			if (onstreamWells[i].fluidFraction > onstreamWells[i+1].fluidFraction)
			{
				temp = onstreamWells[i + 1];
				onstreamWells[i + 1] = onstreamWells[i];
				onstreamWells[i] = temp;
			}
		}
	}

	return onstreamWells;
}

int CalculateDeckVariables::isContainFluidFractionIndicator(vector<double> &uniqueFluidFractionIndicators, double& fluidFraction){
	int check = -1;
	int  i = 0, n = uniqueFluidFractionIndicators.size();
	for(i = 0; i < n; i++){
		if(uniqueFluidFractionIndicators[i] == fluidFraction){
			check = i;
			break;
		}
	}

	return check;
}

vector<double> CalculateDeckVariables::GetUniqueFluidFractionIndicators(vector<ForecastResult> &onstreamWells){
	vector<double> uniqueFluidFractionIndicators;
	int check = 0;
	for(int i = 0; i < onstreamWells.size(); i++){
		check = isContainFluidFractionIndicator(uniqueFluidFractionIndicators, onstreamWells[i].fluidFraction);
		if(check == -1){
			uniqueFluidFractionIndicators.push_back(onstreamWells[i].fluidFraction);
		}
	}

	return uniqueFluidFractionIndicators;
}



int CalculateDeckVariables::isContainText(vector<string>& texts, string& text){
	int check = -1;
	int  i = 0, n= texts.size();
	for(i = 0; i < n; i++){
		if(texts[i] == text){
			check = i;
			break;
		}
	}

	return check;
}

bool CalculateDeckVariables::GetIsWellFlowing(bool &isOilTerminated, bool &isGasTerminated, bool &isWaterterminated)
{
	bool isWellFlowing = true;
	if (isOilTerminated == true && isGasTerminated == true && isWaterterminated == true)
	{
		isWellFlowing = false;
	}
	return isWellFlowing;
}

bool CalculateDeckVariables::CheckWellFacility(vector<WellFacilityData> WellFacilityDataList, string ModuleName, string FacilityName)
{
	bool check = false;
	int i = 0;
	int n = WellFacilityDataList.size();
	for (i = 0; i < n; i++)
	{
		if (WellFacilityDataList[i].Flow_station == FacilityName &&
			WellFacilityDataList[i].ModuleName == ModuleName)
		{
			check = true;
			break;
		}
	}
	return check;
}

tuple<bool, int> CalculateDeckVariables::CheckWellFacilityAndGetIndex(vector<WellFacilityData> WellFacilityDataList, string ModuleName)
{
	bool check = false;
	int i = 0;
	int n = WellFacilityDataList.size();
	int index = -1;
	for (i = 0; i < n; i++)
	{
		if (WellFacilityDataList[i].ModuleName == ModuleName)
		{
			index = i;
			check = true;
			break;
		}
	}
	return make_tuple(check, index);
}

void CalculateDeckVariables::GetFacilityFlowRates(vector<Node> &updatesNodes)
{
	Date minimumNodeOnstreamDate;
	int ik = 0;

	if (datePosition == 0)
	{
		//Get the minimum OSD from all the wells flowing to a facility
		//only at the first time step

		minimumNodeOnstreamDate.day = results[datePosition][facilityCounter][0].startDay;
		minimumNodeOnstreamDate.month = results[datePosition][facilityCounter][0].startMonth;
		minimumNodeOnstreamDate.year = results[datePosition][facilityCounter][0].StartYear;
		int nw = results[datePosition][facilityCounter].size();

		for (ik = 1; ik < nw; ik++)
		{
			Date nextWellOSDDate;
			nextWellOSDDate.day = results[datePosition][facilityCounter][ik].startDay;
			nextWellOSDDate.month = results[datePosition][facilityCounter][ik].startMonth;
			nextWellOSDDate.year = results[datePosition][facilityCounter][ik].StartYear;
			minimumNodeOnstreamDate = dateCreation.GetMinimumDate(nextWellOSDDate, minimumNodeOnstreamDate);
		}
	}

	int nequipmentDataInEquipementConnections =
		updatesNodes[0].equipmentDataInEquipementConnections.size();
	vector<FacilityStructExternal> singleNodeDataList;
	vector<int> singleNodeDataIndicies;

	for (ik = 0; ik < nequipmentDataInEquipementConnections; ik++)
	{
		if (updatesNodes[0].equipmentDataInEquipementConnections[ik].Primary_Facility ==
			results[datePosition][facilityCounter][0].Flow_station)
		{
			//Get facilities nodes of all the wells flowing into them and the index positions of the nodes

			if (dateCreation.IsMinimumDate(updatesNodes[0].equipmentDataInEquipementConnections[ik].FacilityDate1P,
										   minimumNodeOnstreamDate))
			{
				//Adjust the facility OSD to be the minimum well OSD
				updatesNodes[0].equipmentDataInEquipementConnections[ik].FacilityDate1P = minimumNodeOnstreamDate;
				updatesNodes[0].equipmentDataInEquipementConnections[ik].FacilityDate2P = minimumNodeOnstreamDate;
				updatesNodes[0].equipmentDataInEquipementConnections[ik].FacilityDate3P = minimumNodeOnstreamDate;
			}

			singleNodeDataIndicies.push_back(ik);
			singleNodeDataList.push_back(updatesNodes[0].equipmentDataInEquipementConnections[ik]);
		}
	}

	int nSingleNodeDataList = singleNodeDataList.size();
	for (int ikk = 0; ikk < nSingleNodeDataList; ikk++)
	{
		int idx = singleNodeDataIndicies[ikk];
		//CurrentDate.day == updatesNodes[0].equipmentDataInEquipementConnections[idx].FacilityDate1P.day &&
		if (dateCreation.IsMaximumDate(CurrentDate, updatesNodes[0].equipmentDataInEquipementConnections[idx].FacilityDate1P) ||
		dateCreation.EqualTo2(CurrentDate, updatesNodes[0].equipmentDataInEquipementConnections[idx].FacilityDate1P, isMonthly))
		{
			//Set the sum of fluxes from wells to its corresponding facility provided
			//the current time step date is greater or equal to the facility OSD
			if(updatesNodes[0].equipmentDataInEquipementConnections[idx].Primary_Facility == "REO_GP3"){
				double cg = 0;
			}
			updatesNodes[0].equipmentDataInEquipementConnections[idx].FacilityOiProduced = FacilityOiProduced;
			updatesNodes[0].equipmentDataInEquipementConnections[idx].FacilityGasProduced = FacilityGasProduced;
			updatesNodes[0].equipmentDataInEquipementConnections[idx].FacilityAGProduced = FacilityAGProduced;
			updatesNodes[0].equipmentDataInEquipementConnections[idx].FacilityNAGProduced = FacilityNAGProduced;
			updatesNodes[0].equipmentDataInEquipementConnections[idx].FacilityWaterProduced = FacilityWaterProduced;
			updatesNodes[0].equipmentDataInEquipementConnections[idx].FacilityLiquidProduced = FacilityLiquidProduced;
			break;
		}
	}
}

void CalculateDeckVariables::GetDownStreamNodesFlux(vector<Node> &updatesNodes, int &activeNodeIndex)
{

	//Get the fluxes of nodes = 2, ... n

	int kk = activeNodeIndex;
	int Faclitiessize =
		updatesNodes[kk].equipmentDataInEquipementConnections.size();
	for (int ij = 0; ij < Faclitiessize; ij++)
	{
		int u = 0;
		vector<int> actualChildrenNodesIndicies;
		vector<string> actualChildrenNodesKeys;
		//Get previous node children count
		int nAllChildrenNodes = updatesNodes[kk - 1].equipmentDataInEquipementConnections.size();
		for (u = 0; u < nAllChildrenNodes; u++)
		{
			//Get current nodes name from the previous node. If a previous node is a separator
			//it can have multpile outlet (eg. oil, gas, water) flowing to the next current node
			//That is why we split the concatenated text to get the next current nodes names
			string parentNodes_Text = updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].ParentNodes;
			vector<string> parentNodes;
			string delimeter = "===";
			deckobj.tokenize(parentNodes_Text, delimeter, parentNodes);
			int v = 0;
			int nParentNodes = parentNodes.size();
			for (v = 0; v < nParentNodes; v++)
			{
				//Get current node name from the the current node
				string nodeName = updatesNodes[kk].equipmentDataInEquipementConnections[ij].Primary_Facility;
				//Check if current node name from previous node is the same as current node name from the current node
				if (nodeName == parentNodes[v])
				{
					//CurrentDate.day == updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityDate1P.day &&
					//check if the previous node that is connected to the current node has a flow at the current time step date
					if (dateCreation.IsMaximumDate(CurrentDate, updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityDate1P) ||
					dateCreation.EqualTo2(CurrentDate, updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityDate1P, isMonthly))
					{

						Date minimumNodeOnstreamDate, minimumNodeOnstreamDate2;
						int ik = 0;
						if (datePosition == 0)
						{
							//Adjust the current node OSD to be equal to the minimum OSD of the previous node
							minimumNodeOnstreamDate.day = updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityDate1P.day;
							minimumNodeOnstreamDate.month = updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityDate1P.month;
							minimumNodeOnstreamDate.year = updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityDate1P.year;

							//find minimumIndex
							int vv = 0;
							int minimumIndex = ij;
							minimumNodeOnstreamDate2.day = updatesNodes[kk].equipmentDataInEquipementConnections[ij].FacilityDate1P.day;
							minimumNodeOnstreamDate2.month = updatesNodes[kk].equipmentDataInEquipementConnections[ij].FacilityDate1P.month;
							minimumNodeOnstreamDate2.year = updatesNodes[kk].equipmentDataInEquipementConnections[ij].FacilityDate1P.year;
							//This for loop is used to get the minimum schedule date of the current node
							for (vv = 0; vv < Faclitiessize; vv++)
							{
								if (updatesNodes[kk].equipmentDataInEquipementConnections[ij].Primary_Facility ==
										updatesNodes[kk].equipmentDataInEquipementConnections[vv].Primary_Facility &&
									dateCreation.IsMinimumDate(updatesNodes[kk].equipmentDataInEquipementConnections[vv].FacilityDate1P,
															   minimumNodeOnstreamDate2))
								{
									minimumIndex = vv;
								}
							}

							//minimumIndex is used to ensure that other date schedules dates of the current node is not altered.
							//minimumIndexis also used to only adjust the OSD of the current node if the
							minimumNodeOnstreamDate = dateCreation.GetMinimumDate(
								updatesNodes[kk].equipmentDataInEquipementConnections[minimumIndex].FacilityDate1P, minimumNodeOnstreamDate);

							updatesNodes[kk].equipmentDataInEquipementConnections[minimumIndex].FacilityDate1P = minimumNodeOnstreamDate;
						}

						if (kk == 1)
						{
							int idx_u = isContainText(actualChildrenNodesKeys,
							updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].nodesConnectionKey);
							if(idx_u == -1){
								if(updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityOiProduced > 0 ||
								updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityGasProduced > 0){
									actualChildrenNodesIndicies.push_back(u); // get facilities nodes indicies
									actualChildrenNodesKeys.push_back(updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].nodesConnectionKey);
								}
							}else{
								int l_u = actualChildrenNodesIndicies[idx_u];
								bool isMaximum = dateCreation.IsMaximumDate(
									updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityDate1P,
									updatesNodes[kk - 1].equipmentDataInEquipementConnections[l_u].FacilityDate1P
								);
								
								if(isMaximum == true){
									if(updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityOiProduced > 0 ||
									updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityGasProduced > 0){
										actualChildrenNodesIndicies[idx_u] = u;
									}
								}
							}
						}
						else
						{
							if (updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].isGasFlow == false)
							{
								if (updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityOiProduced > 0.0000001)
								{
									//get the previous nodes indicies flowing oil to the current node
									int idx_u = isContainText(actualChildrenNodesKeys,
									updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].nodesConnectionKey);
									if(idx_u == -1){
										actualChildrenNodesIndicies.push_back(u); // get facilities nodes indicies
										actualChildrenNodesKeys.push_back(updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].nodesConnectionKey);
									}else{
										int l_u = actualChildrenNodesIndicies[idx_u];
										bool isMaximum = dateCreation.IsMaximumDate(
											updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityDate1P,
											updatesNodes[kk - 1].equipmentDataInEquipementConnections[l_u].FacilityDate1P
										);
										
										if(isMaximum == true &&
										updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityOiProduced > 0){
											actualChildrenNodesIndicies[idx_u] = u;
										}
									}
								}
							}
							else
							{
								if (updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityGasProduced > 0.0000001)
								{
									//get the previous nodes indicies flowing gas to the current node
									int idx_u = isContainText(actualChildrenNodesKeys,
									updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].nodesConnectionKey);
									if(idx_u == -1){
										actualChildrenNodesIndicies.push_back(u); // get facilities nodes indicies
										actualChildrenNodesKeys.push_back(updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].nodesConnectionKey);
									}else{
										int l_u = actualChildrenNodesIndicies[idx_u];
										bool isMaximum = dateCreation.IsMaximumDate(
											updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityDate1P,
											updatesNodes[kk - 1].equipmentDataInEquipementConnections[l_u].FacilityDate1P
										);
										
										if(isMaximum &&
										updatesNodes[kk - 1].equipmentDataInEquipementConnections[u].FacilityGasProduced > 0){
											actualChildrenNodesIndicies[idx_u] = u;
										}
									}
								}
							}
						}
						break;
					}
				}
			}
		}
		if (actualChildrenNodesIndicies.size() > 0)
		{
			if(actualChildrenNodesIndicies.size() > 7){
				double jhu = 0;
			}
			int previousNodeIndex = kk - 1;
			Liquid_Capacity = 0;
			Gas_Capacity = 0;
			int idx2 = -1;
			int currentNodesCount = updatesNodes[kk].equipmentDataInEquipementConnections.size();
			for (u = ij; u < currentNodesCount; u++)
			{
				//Gets the capacities of the current node provided it is currently onstream
				if (updatesNodes[kk].equipmentDataInEquipementConnections[ij].Primary_Facility ==
					updatesNodes[kk].equipmentDataInEquipementConnections[u].Primary_Facility)
				{
					//CurrentDate.day == updatesNodes[kk].equipmentDataInEquipementConnections[u].FacilityDate1P.day &&
					if (dateCreation.IsMaximumDate(CurrentDate, updatesNodes[kk].equipmentDataInEquipementConnections[u].FacilityDate1P) ||
					dateCreation.EqualTo2(CurrentDate, updatesNodes[kk].equipmentDataInEquipementConnections[u].FacilityDate1P, isMonthly))
					{
						Liquid_Capacity = updatesNodes[kk].equipmentDataInEquipementConnections[u].Liquid_Capacity1P * 1000;
						AG_Capacity = updatesNodes[kk].equipmentDataInEquipementConnections[u].AG_Capacity1P * 1000000;
						NAG_Capacity = updatesNodes[kk].equipmentDataInEquipementConnections[u].NAG_Capacity1P * 1000000;
						Gas_Capacity = updatesNodes[kk].equipmentDataInEquipementConnections[u].Gas_Capacity1P * 1000000;
						if (Gas_Capacity <= 0)
						{
							Gas_Capacity = AG_Capacity + NAG_Capacity;
						}
						idx2 = u;
						break;
					}
				}
			}
			if (idx2 > -1)
			{
				if(Liquid_Capacity > 0 || Gas_Capacity > 0){
					optimize_olderNode_children(updatesNodes, previousNodeIndex, actualChildrenNodesIndicies,
												updatesNodes[kk].priotizations[idx2]);

					updatesNodes[kk].equipmentDataInEquipementConnections[idx2].isGasFlow = isGasFlow;

					updatesNodes[kk].equipmentDataInEquipementConnections[idx2].FacilityOiProduced = FacilityOiProduced;
					updatesNodes[kk].equipmentDataInEquipementConnections[idx2].FacilityGasProduced = FacilityGasProduced;
					updatesNodes[kk].equipmentDataInEquipementConnections[idx2].FacilityAGProduced = FacilityAGProduced;
					updatesNodes[kk].equipmentDataInEquipementConnections[idx2].FacilityNAGProduced = FacilityNAGProduced;
					updatesNodes[kk].equipmentDataInEquipementConnections[idx2].FacilityWaterProduced = FacilityWaterProduced;
					updatesNodes[kk].equipmentDataInEquipementConnections[idx2].FacilityLiquidProduced = FacilityLiquidProduced;

				}
			}
		}
	}
}

void CalculateDeckVariables::AdjustWellsFlowRates(vector<Node> &updatesNodes,
												  vector<int> &daysList, int &scenario, vector<FacilityStruct> &FacilityTable,
												  string &forecastCase, vector<vector<Priotization>> &priotizationsFacilities,
												  vector<vector<vector<InputDeckStruct>>> &Faclities,
												  vector<Date>& dateTimes)
{

	int nUpdatesNodes = updatesNodes.size();
	//Start from node zero which is the facilities node
	int nFacilitiesNodes = updatesNodes[0].equipmentInEquipementConnections.size();
	string logger = "";
	int j = 0;
	for (j = 0; j < nFacilitiesNodes; j++)
	{
		int idx2 = -1;
		int idx = -1;
		int u = 0;
		int currentNodesCount = updatesNodes[0].equipmentDataInEquipementConnections.size();
		double liquidCutBack = 1;
		double gasCutBack = 1;
		string liquidCutBackText = "";
		string gasCutBackText = "";
		string nodeConnections = "";
		logger = "Facility Node ==> ";

		for (u = 0; u < currentNodesCount; u++)
		{
			if (updatesNodes[0].equipmentInEquipementConnections[j].facilityName ==
				updatesNodes[0].equipmentDataInEquipementConnections[u].Primary_Facility)
			{
				//If facility name in equipmentInEquipementConnections is the same as
				// equipmentDataInEquipementConnections do something
				//CurrentDate.day == updatesNodes[0].equipmentDataInEquipementConnections[u].FacilityDate1P.day &&
				if (dateCreation.IsMaximumDate(CurrentDate, updatesNodes[0].equipmentDataInEquipementConnections[u].FacilityDate1P) ||
				dateCreation.EqualTo2(CurrentDate, updatesNodes[0].equipmentDataInEquipementConnections[u].FacilityDate1P, isMonthly))
				{
					liquidCutBack = liquidCutBack * updatesNodes[0].equipmentDataInEquipementConnections[u].cutBack;
					gasCutBack = gasCutBack * updatesNodes[0].equipmentDataInEquipementConnections[u].cutBack;
					if (liquidCutBack < 0.0000000000001)
					{
						liquidCutBack = 1;
					}
					if (gasCutBack < 0.0000000000001)
					{
						gasCutBack = 1;
					}
					liquidCutBackText = liquidCutBackText + to_string(liquidCutBack) + "===";
					gasCutBackText = gasCutBackText + to_string(gasCutBack) + "===";
					nodeConnections = nodeConnections + updatesNodes[0].equipmentDataInEquipementConnections[u].Primary_Facility + "===";
					idx = u;

					logger = logger + 
					"liquidCutBack = " + to_string(liquidCutBack) + " * "
					"gasCutBack = " + to_string(gasCutBack) + " * ";

					break;
				}
			}
		}
		
		if (idx > -1)
		{
			string parentNodes_Text = updatesNodes[0].equipmentDataInEquipementConnections[idx].ParentNodes;
			vector<string> parentNodes;
			string delimeter = "===";
			deckobj.tokenize(parentNodes_Text, delimeter, parentNodes);
			int v = 0;
			int nParentNodes = parentNodes.size();
			int kk = 0;
			/* if(updatesNodes[0].equipmentDataInEquipementConnections[u].Primary_Facility == "ABU_FS1"){
				std::cout << logger << "\n";
			} */

			logger = " other nodes ==>";

			for (kk = 1; kk < nUpdatesNodes; kk++)
			{
				int currentNodesCount =
					updatesNodes[kk].equipmentDataInEquipementConnections.size();
				bool check = false;
				for (int ij = 0; ij < currentNodesCount; ij++)
				{
					for (v = 0; v < nParentNodes; v++)
					{
						string nodeName = updatesNodes[kk].equipmentDataInEquipementConnections[ij].Primary_Facility;
						if (nodeName == parentNodes[v])
						{
							//CurrentDate.day == updatesNodes[kk].equipmentDataInEquipementConnections[ij].FacilityDate1P.day &&
							if (dateCreation.IsMaximumDate(CurrentDate, updatesNodes[kk].equipmentDataInEquipementConnections[ij].FacilityDate1P) ||
								dateCreation.EqualTo2(CurrentDate, updatesNodes[kk].equipmentDataInEquipementConnections[ij].FacilityDate1P, isMonthly))
							{
								if (updatesNodes[kk].equipmentDataInEquipementConnections[ij].isGasFlow == false)
								{
									if (updatesNodes[kk].equipmentDataInEquipementConnections[ij].cutBack < 0.0000000000001)
									{
										updatesNodes[kk].equipmentDataInEquipementConnections[ij].cutBack = 1;
									}
									liquidCutBack = liquidCutBack * updatesNodes[kk].equipmentDataInEquipementConnections[ij].cutBack;
								}
								else
								{
									if (updatesNodes[kk].equipmentDataInEquipementConnections[ij].cutBack < 0.0000000000001)
									{
										updatesNodes[kk].equipmentDataInEquipementConnections[ij].cutBack = 1;
									}
									gasCutBack = gasCutBack * updatesNodes[kk].equipmentDataInEquipementConnections[ij].cutBack;
								}
								if (liquidCutBack < 0.0000000000001)
								{
									liquidCutBack = 1;
								}
								if (gasCutBack < 0.0000000000001)
								{
									gasCutBack = 1;
								}
								liquidCutBackText = liquidCutBackText + to_string(liquidCutBack) + "===";
								gasCutBackText = gasCutBackText + to_string(gasCutBack) + "===";
								nodeConnections = nodeConnections + updatesNodes[kk].equipmentDataInEquipementConnections[u].Primary_Facility + "===";
								check = true; 

								logger = logger + 
								"liquidCutBack = " + to_string(liquidCutBack) + " * "
								"gasCutBack = " + to_string(gasCutBack) + " * ";
								
								break;
							}
						}
					}
					if (check == true)
					{
						idx2 = ij;
						break;
					}
				}

				parentNodes_Text = updatesNodes[kk].equipmentDataInEquipementConnections[idx2].ParentNodes;
				parentNodes.clear();
				parentNodes.shrink_to_fit();
				deckobj.tokenize(parentNodes_Text, delimeter, parentNodes);
			}

			int Faclitiessize = Faclities[0].size();
			for (int kk = 0; kk < Faclitiessize; kk++)
			{
				vector<InputDeckStruct> Facility = Faclities[datePosition][kk];
				if (Facility[0].Flow_station == updatesNodes[0].equipmentDataInEquipementConnections[idx].Primary_Facility)
				{
					facilityCounter = kk;
					/* if(updatesNodes[0].equipmentDataInEquipementConnections[u].Primary_Facility == "ABU_FS1"){
						std::cout << logger << "\n";
					} */

					FacilityOiProduced = updatesNodes[0].equipmentDataInEquipementConnections[idx].FacilityOiProduced;
					FacilityWaterProduced = updatesNodes[0].equipmentDataInEquipementConnections[idx].FacilityWaterProduced;
					FacilityGasProduced = updatesNodes[0].equipmentDataInEquipementConnections[idx].FacilityGasProduced;
					FacilityLiquidProduced = updatesNodes[0].equipmentDataInEquipementConnections[idx].FacilityLiquidProduced;
					//std::cout << "GetDeckVariables2 Started" << "\n";
					GetDeckVariables2(Facility,
									  daysList, scenario, facilityCounter,
									  FacilityTable[facilityCounter], datePosition, Faclitiessize, Faclities,
									  forecastCase, priotizationsFacilities[datePosition][j],
									  gasCutBack, liquidCutBack, liquidCutBackText, gasCutBackText, nodeConnections);
					//std::cout << "GetDeckVariables2 Cpmpleted" << "\n";
					break;
				}
			}
		}

	}
}

void CalculateDeckVariables::GetDeckVariables(vector<vector<vector<InputDeckStruct>>> &Faclities,
											  vector<int> &daysList, int &scenario, vector<FacilityStruct> &FacilityTable,
											  vector<string> &FaclitiesNames, DateCreation &dateCreationX,
											  vector<WellReroute> &routedWells, string &forecastCase,
											  vector<vector<Priotization>> &priotizationsFacilities,
											  vector<Node> &updatesNodes, bool isMonthly)
{

	double MM = 1000000.0;

	int j = -1, k = -1, i = 0;
	int nFaclities2 = Faclities.size();
	int datessize = dates.size();

	for (i = 0; i < datessize; i++)
	{
		int nFacilities = Faclities[i].size();

		vector<vector<ForecastResult>> facilitiesResultsPerDate;

		for (j = 0; j < nFacilities; j++)
		{
			vector<InputDeckStruct> Facility = Faclities[i][j];

			vector<ForecastResult> wellsResultsPerFacilityPerDate;

			int allWellsPerFacility = Facility.size();
			for (k = 0; k < allWellsPerFacility; k++)
			{

				_InputDeckStruct deck = Faclities[i][j][k];
				CurrentDate = dates[i];
				ForecastResult result;
				result.InitailizeData();
				result.Day = CurrentDate.day;
				result.Month = CurrentDate.month;
				result.Year = CurrentDate.year;
				result.HyrocarbonStream = deck.Hydrocarbon_Stream;
				result.hydrocarbonType = deck.hydrocarbonType;
				result.terminal = deck.terminal;
				result.ModuleName = deck.Module;
				result.Version_Name = deck.Version_Name;
				result.Field = deck.Field;
				result.Reservoir = deck.Reservoir;
				result.Drainage_Point = deck.Drainage_Point;
				result.Production_String = deck.Production_String;
				result.TRANCHE = deck.TRANCHE;
				result.Asset_Team = deck.Asset_Team;
				result.Flow_station = deck.Flow_station;
				result.projectCode = deck.PEEP_Project;
				result.projectName = deck.Activity_Entity;
				result.resourceClass = deck.Resource_Class;
				result.index = i;
				result.wellIndex = k;
				result.optimizationWeight2 = deck.optimizationWeight2;
				result.startupRate = deck.startupRate;
				result.declineRate = deck.declineRate;
				result.declineType = deck.declineType;
				result.declineType2 = deck.declineType2;
				result.hyperbolicExponent = deck.hyperbolicExponent;
				result.startupRatePlateau = deck.startupRatePlateau;
				result.percentOfMaximumPotential = deck.percentOfMaximumPotential;
				result.scheduleKey = deck.scheduleKey;
				result.dcaStrategy = deck.dcaStrategy;
				result.FromDate = deck.FromDate;
				result.ToDate = deck.ToDate;
				result.PlateauDate = deck.PlateauDate;
				result.resourceClass = deck.Resource_Class;
				result.isTerminated = deck.isTerminated;
				result.isOilTerminated = deck.isOilTerminated;
				result.isGasTerminated = deck.isGasTerminated;
				result.isWaterTerminated = deck.isWaterTerminated;
				result.startDay = deck.Date_1P_1C.day;
				result.startMonth = deck.Date_1P_1C.month;
				result.StartYear = deck.Date_1P_1C.year;

				switch (scenario)
				{
				case 1:
					if (dateCreation.EqualTo2(dates[i], deck.Date_1P_1C, isMonthly)) // Assign Initial Values
					{
						if (deck.Hydrocarbon_Stream == oil)
						{
							//deck.Rate_of_Change_Rate_1P_1C = deck.Rate_of_Change_Rate_1P_1C * 0.00001;
							//Faclities[i][j][k].Rate_of_Change_Rate_1P_1C = Faclities[i][j][k].Rate_of_Change_Rate_1P_1C * 0.00001;
							result.HyrocarbonStream = deck.Hydrocarbon_Stream;
							result.hydrocarbonType = deck.hydrocarbonType;
							result.terminal = deck.terminal;
							result.ModuleName = deck.Module;
							result.Version_Name = deck.Version_Name;
							result.Field = deck.Field;
							result.Reservoir = deck.Reservoir;
							result.Drainage_Point = deck.Drainage_Point;
							result.Production_String = deck.Production_String;
							result.TRANCHE = deck.TRANCHE;
							result.Asset_Team = deck.Asset_Team;
							result.Flow_station = deck.Flow_station;
							result.Liquid_Rate = deck.Init_Liquid_Gas_Rate_1P_1C;
							result.Liquid_rate_NotTerminated = deck.Init_Liquid_Gas_Rate_1P_1C;
							result.Oil_rate = deck.Init_Liquid_Gas_Rate_1P_1C * (1 - deck.Init_BSW_WGR);
							result.Oil_rate_NotTerminated = deck.Init_Liquid_Gas_Rate_1P_1C * (1 - deck.Init_BSW_WGR);
							result.Water_Rate = deck.Init_Liquid_Gas_Rate_1P_1C * deck.Init_BSW_WGR;
							result.Gas_Rate = result.Oil_rate * deck.Init_GOR_CGR;
							result.Cum_Oil_Prod = deck.Np;
							result.Cum_Gas_Prod = result.Cum_Oil_Prod * deck.Init_GOR_CGR;
							result.Cum_Water_Prod = result.Cum_Oil_Prod * deck.Init_BSW_WGR / (1 - deck.Init_BSW_WGR);
							result.Cum_Liquid_Prod = result.Cum_Oil_Prod + result.Cum_Water_Prod;
							result.URo = deck.URo_1P_1C;
							result.URg = deck.URg_1P_1C;
							result.startDay = deck.Date_1P_1C.day;
							result.startMonth = deck.Date_1P_1C.month;
							result.StartYear = deck.Date_1P_1C.year;
							result.projectCode = deck.PEEP_Project;
							result.projectName = deck.Activity_Entity;
							result.resourceClass = deck.Resource_Class;
							result.isTerminated = deck.isTerminated;
							result.oilRateAbandonment = deck.Aband_Liquid_Gas_Rate_1P_1C * (1 - deck.Init_BSW_WGR);
							result.liquidRateAbandonmemt = deck.Aband_Liquid_Gas_Rate_1P_1C;

							if(i > 0){
								results[i-1][j][k].Oil_rate = result.Oil_rate;
								results[i-1][j][k].Oil_rate_NotTerminated = result.Oil_rate_NotTerminated;
								results[i-1][j][k].Water_Rate = result.Water_Rate;
								results[i-1][j][k].Liquid_Rate = result.Liquid_Rate;
								results[i-1][j][k].Liquid_rate_NotTerminated = result.Liquid_rate_NotTerminated;
								results[i-1][j][k].Gas_Rate = result.Gas_Rate;
								results[i-1][j][k].Cum_Oil_Prod = result.Cum_Oil_Prod;
								results[i-1][j][k].Cum_Gas_Prod = result.Cum_Gas_Prod;
								results[i-1][j][k].Cum_Water_Prod = result.Cum_Water_Prod;
								results[i-1][j][k].Cum_Liquid_Prod = result.Cum_Liquid_Prod;
								results[i-1][j][k].URo = result.URo;
								results[i-1][j][k].URg = result.URg;
							}
						}
						else
						{
							result.HyrocarbonStream = deck.Hydrocarbon_Stream;
							result.hydrocarbonType = deck.hydrocarbonType;
							result.terminal = deck.terminal;
							result.ModuleName = deck.Module;
							result.Version_Name = deck.Version_Name;
							result.Field = deck.Field;
							result.Reservoir = deck.Reservoir;
							result.Drainage_Point = deck.Drainage_Point;
							result.Production_String = deck.Production_String;
							result.TRANCHE = deck.TRANCHE;
							result.Asset_Team = deck.Asset_Team;
							result.Flow_station = deck.Flow_station;
							result.Gas_Rate = deck.Init_Liquid_Gas_Rate_1P_1C;
							result.Gas_Rate_NotTerminated = deck.Init_Liquid_Gas_Rate_1P_1C;
							result.Oil_rate = result.Gas_Rate * deck.Init_GOR_CGR;
							result.Water_Rate = result.Gas_Rate * deck.Init_BSW_WGR;
							result.Liquid_Rate = result.Water_Rate + result.Oil_rate;
							result.Liquid_rate_NotTerminated = result.Liquid_Rate;
							result.Cum_Gas_Prod = deck.Gp;
							result.Cum_Oil_Prod = result.Cum_Gas_Prod * deck.Init_GOR_CGR;
							result.Cum_Water_Prod = result.Cum_Gas_Prod * deck.Init_BSW_WGR;
							result.Cum_Liquid_Prod = result.Cum_Oil_Prod + result.Cum_Water_Prod;
							result.URo = deck.URo_1P_1C;
							result.URg = deck.URg_1P_1C;
							result.startDay = deck.Date_1P_1C.day;
							result.startMonth = deck.Date_1P_1C.month;
							result.StartYear = deck.Date_1P_1C.year;
							result.projectCode = deck.PEEP_Project;
							result.projectName = deck.Activity_Entity;
							result.resourceClass = deck.Resource_Class;
							result.isTerminated = deck.isTerminated;
							result.gasRateAbandonment = deck.Aband_Liquid_Gas_Rate_1P_1C;

							if(i > 0){
								results[i-1][j][k].Oil_rate = result.Oil_rate;
								results[i-1][j][k].Oil_rate_NotTerminated = result.Oil_rate_NotTerminated;
								results[i-1][j][k].Water_Rate = result.Water_Rate;
								results[i-1][j][k].Liquid_Rate = result.Liquid_Rate;
								results[i-1][j][k].Liquid_rate_NotTerminated = result.Liquid_rate_NotTerminated;
								results[i-1][j][k].Gas_Rate = result.Gas_Rate;
								results[i-1][j][k].Cum_Oil_Prod = result.Cum_Oil_Prod;
								results[i-1][j][k].Cum_Gas_Prod = result.Cum_Gas_Prod;
								results[i-1][j][k].Cum_Water_Prod = result.Cum_Water_Prod;
								results[i-1][j][k].Cum_Liquid_Prod = result.Cum_Liquid_Prod;
								results[i-1][j][k].URo = result.URo;
								results[i-1][j][k].URg = result.URg;
							}
						}
					}

					break;

				case 2:
					if (dateCreation.EqualTo2(dates[i], deck.Date_2P_2C, isMonthly)) // Assign Initial Values
					{

						if (deck.Hydrocarbon_Stream == oil)
						{
							result.HyrocarbonStream = deck.Hydrocarbon_Stream;
							result.hydrocarbonType = deck.hydrocarbonType;
							result.terminal = deck.terminal;
							result.ModuleName = deck.Module;
							result.Version_Name = deck.Version_Name;
							result.Field = deck.Field;
							result.Reservoir = deck.Reservoir;
							result.Drainage_Point = deck.Drainage_Point;
							result.Production_String = deck.Production_String;
							result.TRANCHE = deck.TRANCHE;
							result.Asset_Team = deck.Asset_Team;
							result.Flow_station = deck.Flow_station;
							result.Liquid_Rate = deck.Init_Liquid_Gas_Rate_2P_2C;
							result.Liquid_rate_NotTerminated = deck.Init_Liquid_Gas_Rate_2P_2C;
							result.Oil_rate = deck.Init_Liquid_Gas_Rate_2P_2C * (1 - deck.Init_BSW_WGR);
							result.Oil_rate_NotTerminated = deck.Init_Liquid_Gas_Rate_2P_2C * (1 - deck.Init_BSW_WGR);
							result.Water_Rate = deck.Init_Liquid_Gas_Rate_2P_2C * deck.Init_BSW_WGR;
							result.Gas_Rate = result.Oil_rate * deck.Init_GOR_CGR;
							result.Cum_Oil_Prod = deck.Np;
							result.Cum_Gas_Prod = result.Cum_Oil_Prod * deck.Init_GOR_CGR;
							result.Cum_Water_Prod = result.Cum_Oil_Prod * deck.Init_BSW_WGR / (1 - deck.Init_BSW_WGR);
							result.Cum_Liquid_Prod = result.Cum_Oil_Prod + result.Cum_Water_Prod;
							result.URo = deck.URo_2P_2C;
							result.URg = deck.URg_2P_2C;
							result.startDay = deck.Date_2P_2C.day;
							result.startMonth = deck.Date_2P_2C.month;
							result.StartYear = deck.Date_2P_2C.year;
							result.projectCode = deck.PEEP_Project;
							result.projectName = deck.Activity_Entity;
							result.resourceClass = deck.Resource_Class;
							result.isTerminated = deck.isTerminated;
							result.oilRateAbandonment = deck.Aband_Liquid_Gas_Rate_2P_2C * (1 - deck.Init_BSW_WGR);
							result.liquidRateAbandonmemt = deck.Aband_Liquid_Gas_Rate_2P_2C;

							if(i > 0){
								results[i-1][j][k].Oil_rate = result.Oil_rate;
								results[i-1][j][k].Oil_rate_NotTerminated = result.Oil_rate_NotTerminated;
								results[i-1][j][k].Water_Rate = result.Water_Rate;
								results[i-1][j][k].Liquid_Rate = result.Liquid_Rate;
								results[i-1][j][k].Liquid_rate_NotTerminated = result.Liquid_rate_NotTerminated;
								results[i-1][j][k].Gas_Rate = result.Gas_Rate;
								results[i-1][j][k].Cum_Oil_Prod = result.Cum_Oil_Prod;
								results[i-1][j][k].Cum_Gas_Prod = result.Cum_Gas_Prod;
								results[i-1][j][k].Cum_Water_Prod = result.Cum_Water_Prod;
								results[i-1][j][k].Cum_Liquid_Prod = result.Cum_Liquid_Prod;
								results[i-1][j][k].URo = result.URo;
								results[i-1][j][k].URg = result.URg;
							}

						}
						else
						{
							result.HyrocarbonStream = deck.Hydrocarbon_Stream;
							result.hydrocarbonType = deck.hydrocarbonType;
							result.terminal = deck.terminal;
							result.ModuleName = deck.Module;
							result.Version_Name = deck.Version_Name;
							result.Field = deck.Field;
							result.Reservoir = deck.Reservoir;
							result.Drainage_Point = deck.Drainage_Point;
							result.Production_String = deck.Production_String;
							result.TRANCHE = deck.TRANCHE;
							result.Asset_Team = deck.Asset_Team;
							result.Flow_station = deck.Flow_station;
							result.Gas_Rate = deck.Init_Liquid_Gas_Rate_2P_2C;
							result.Gas_Rate_NotTerminated = deck.Init_Liquid_Gas_Rate_2P_2C;
							result.Oil_rate = result.Gas_Rate * deck.Init_GOR_CGR;
							result.Water_Rate = result.Gas_Rate * deck.Init_BSW_WGR;
							result.Liquid_Rate = result.Water_Rate + result.Oil_rate;
							result.Liquid_rate_NotTerminated = result.Liquid_Rate;
							result.Cum_Gas_Prod = deck.Gp;
							result.Cum_Oil_Prod = result.Cum_Gas_Prod * deck.Init_GOR_CGR;
							result.Cum_Water_Prod = result.Cum_Gas_Prod * deck.Init_BSW_WGR;
							result.Cum_Liquid_Prod = result.Cum_Oil_Prod + result.Cum_Water_Prod;
							result.URo = deck.URo_2P_2C;
							result.URg = deck.URg_2P_2C;
							result.startDay = deck.Date_2P_2C.day;
							result.startMonth = deck.Date_2P_2C.month;
							result.StartYear = deck.Date_2P_2C.year;
							result.projectCode = deck.PEEP_Project;
							result.projectName = deck.Activity_Entity;
							result.resourceClass = deck.Resource_Class;
							result.isTerminated = deck.isTerminated;
							result.gasRateAbandonment = deck.Aband_Liquid_Gas_Rate_2P_2C;

							if(i > 0){
								results[i-1][j][k].Oil_rate = result.Oil_rate;
								results[i-1][j][k].Oil_rate_NotTerminated = result.Oil_rate_NotTerminated;
								results[i-1][j][k].Water_Rate = result.Water_Rate;
								results[i-1][j][k].Liquid_Rate = result.Liquid_Rate;
								results[i-1][j][k].Liquid_rate_NotTerminated = result.Liquid_rate_NotTerminated;
								results[i-1][j][k].Gas_Rate = result.Gas_Rate;
								results[i-1][j][k].Cum_Oil_Prod = result.Cum_Oil_Prod;
								results[i-1][j][k].Cum_Gas_Prod = result.Cum_Gas_Prod;
								results[i-1][j][k].Cum_Water_Prod = result.Cum_Water_Prod;
								results[i-1][j][k].Cum_Liquid_Prod = result.Cum_Liquid_Prod;
								results[i-1][j][k].URo = result.URo;
								results[i-1][j][k].URg = result.URg;
							}
						}
					}

					break;

				case 3:
					if (dateCreation.EqualTo2(dates[i], deck.Date_3P_3C, isMonthly))// Assign Initial Values
					{
						if (deck.Hydrocarbon_Stream == oil)
						{
							result.HyrocarbonStream = deck.Hydrocarbon_Stream;
							result.hydrocarbonType = deck.hydrocarbonType;
							result.terminal = deck.terminal;
							result.ModuleName = deck.Module;
							result.Version_Name = deck.Version_Name;
							result.Field = deck.Field;
							result.Reservoir = deck.Reservoir;
							result.Drainage_Point = deck.Drainage_Point;
							result.Production_String = deck.Production_String;
							result.TRANCHE = deck.TRANCHE;
							result.Asset_Team = deck.Asset_Team;
							result.Flow_station = deck.Flow_station;
							result.Liquid_Rate = deck.Init_Liquid_Gas_Rate_3P_3C;
							result.Liquid_rate_NotTerminated = deck.Init_Liquid_Gas_Rate_3P_3C;
							result.Oil_rate = deck.Init_Liquid_Gas_Rate_1P_1C * (1 - deck.Init_BSW_WGR);
							result.Oil_rate_NotTerminated = deck.Init_Liquid_Gas_Rate_3P_3C * (1 - deck.Init_BSW_WGR);
							result.Water_Rate = deck.Init_Liquid_Gas_Rate_3P_3C * deck.Init_BSW_WGR;
							result.Gas_Rate = result.Oil_rate * deck.Init_GOR_CGR;
							result.Cum_Oil_Prod = deck.Np;
							result.Cum_Gas_Prod = result.Cum_Oil_Prod * deck.Init_GOR_CGR;
							result.Cum_Water_Prod = result.Cum_Oil_Prod * deck.Init_BSW_WGR / (1 - deck.Init_BSW_WGR);
							result.Cum_Liquid_Prod = result.Cum_Oil_Prod + result.Cum_Water_Prod;
							result.URo = deck.URo_3P_3C;
							result.URg = deck.URg_3P_3C;
							result.startDay = deck.Date_3P_3C.day;
							result.startMonth = deck.Date_3P_3C.month;
							result.StartYear = deck.Date_3P_3C.year;
							result.projectCode = deck.PEEP_Project;
							result.projectName = deck.Activity_Entity;
							result.resourceClass = deck.Resource_Class;
							result.isTerminated = deck.isTerminated;
							result.oilRateAbandonment = deck.Aband_Liquid_Gas_Rate_3P_3C * (1 -  deck.Init_BSW_WGR);
							result.liquidRateAbandonmemt = deck.Aband_Liquid_Gas_Rate_3P_3C;

							if(i > 0){
								results[i-1][j][k].Oil_rate = result.Oil_rate;
								results[i-1][j][k].Oil_rate_NotTerminated = result.Oil_rate_NotTerminated;
								results[i-1][j][k].Water_Rate = result.Water_Rate;
								results[i-1][j][k].Liquid_Rate = result.Liquid_Rate;
								results[i-1][j][k].Liquid_rate_NotTerminated = result.Liquid_rate_NotTerminated;
								results[i-1][j][k].Gas_Rate = result.Gas_Rate;
								results[i-1][j][k].Cum_Oil_Prod = result.Cum_Oil_Prod;
								results[i-1][j][k].Cum_Gas_Prod = result.Cum_Gas_Prod;
								results[i-1][j][k].Cum_Water_Prod = result.Cum_Water_Prod;
								results[i-1][j][k].Cum_Liquid_Prod = result.Cum_Liquid_Prod;
								results[i-1][j][k].URo = result.URo;
								results[i-1][j][k].URg = result.URg;
							}

							//std::cout << "Module Name: " << result.ModuleName << std::endl;
							//std::cout << "Start Date: " << result.startDay << "/"  << result.startMonth << "/"  << result.StartYear  << std::endl;
						}
						else
						{
							result.HyrocarbonStream = deck.Hydrocarbon_Stream;
							result.hydrocarbonType = deck.hydrocarbonType;
							result.terminal = deck.terminal;
							result.ModuleName = deck.Module;
							result.Version_Name = deck.Version_Name;
							result.Field = deck.Field;
							result.Reservoir = deck.Reservoir;
							result.Drainage_Point = deck.Drainage_Point;
							result.Production_String = deck.Production_String;
							result.TRANCHE = deck.TRANCHE;
							result.Asset_Team = deck.Asset_Team;
							result.Flow_station = deck.Flow_station;
							result.Gas_Rate = deck.Init_Liquid_Gas_Rate_3P_3C;
							result.Gas_Rate_NotTerminated = deck.Init_Liquid_Gas_Rate_3P_3C;
							result.Oil_rate = result.Gas_Rate * deck.Init_GOR_CGR;
							result.Water_Rate = result.Gas_Rate * deck.Init_BSW_WGR;
							result.Liquid_Rate = result.Water_Rate + result.Oil_rate;
							result.Liquid_rate_NotTerminated = result.Liquid_Rate;
							result.Cum_Gas_Prod = deck.Gp;
							result.Cum_Oil_Prod = result.Cum_Gas_Prod * deck.Init_GOR_CGR;
							result.Cum_Water_Prod = result.Cum_Gas_Prod * deck.Init_BSW_WGR;
							result.Cum_Liquid_Prod = result.Cum_Oil_Prod + result.Cum_Water_Prod;
							result.URo = deck.URo_3P_3C;
							result.URg = deck.URg_3P_3C;
							result.startDay = deck.Date_3P_3C.day;
							result.startMonth = deck.Date_3P_3C.month;
							result.StartYear = deck.Date_3P_3C.year;
							result.projectCode = deck.PEEP_Project;
							result.projectName = deck.Activity_Entity;
							result.resourceClass = deck.Resource_Class;
							result.isTerminated = deck.isTerminated;
							result.gasRateAbandonment = deck.Aband_Liquid_Gas_Rate_3P_3C;

							if(i > 0){
								results[i-1][j][k].Oil_rate = result.Oil_rate;
								results[i-1][j][k].Oil_rate_NotTerminated = result.Oil_rate_NotTerminated;
								results[i-1][j][k].Water_Rate = result.Water_Rate;
								results[i-1][j][k].Liquid_Rate = result.Liquid_Rate;
								results[i-1][j][k].Liquid_rate_NotTerminated = result.Liquid_rate_NotTerminated;
								results[i-1][j][k].Gas_Rate = result.Gas_Rate;
								results[i-1][j][k].Cum_Oil_Prod = result.Cum_Oil_Prod;
								results[i-1][j][k].Cum_Gas_Prod = result.Cum_Gas_Prod;
								results[i-1][j][k].Cum_Water_Prod = result.Cum_Water_Prod;
								results[i-1][j][k].Cum_Liquid_Prod = result.Cum_Liquid_Prod;
								results[i-1][j][k].URo = result.URo;
								results[i-1][j][k].URg = result.URg;
							}

							//std::cout << "Module Name: " << result.ModuleName << std::endl;
							//std::cout << "Start Date: " << result.startDay << "/"  << result.startMonth << "/"  << result.StartYear  << std::endl;
						}

						/* if (i > 0)
									wellsResultsPerFacilityPerDate[i - 1] = result; */
					}

					break;
				}

				wellsResultsPerFacilityPerDate.push_back(result);
			}

			facilitiesResultsPerDate.push_back(wellsResultsPerFacilityPerDate);
		}
		results.push_back(facilitiesResultsPerDate);
	}

	//int nTimes = 3 * dates.size();
	//vector<ForecastResult> resultsN = results[0][0];
	//std::cout << "No. of resultsN: " << resultsN.size() << std::endl;
	datessize = dates.size();
	std::cout << "datessize: " << datessize << std::endl;
	int Faclitiessize = Faclities[0].size();

	/* try
	{ */
		Date minimumNodeOnstreamDate;
		for (i = 0; i < datessize; i++)
		{
			facilitiesPerTimeStepReport = "";
			datePosition = i;
			facilityCounter = -1;
			CurrentDate = dates[i];
			//WellFacilityDataList.clear();
			int kk = 0;
			int nUpdatesNodes = 1; //updatesNodes.size(); //nUpdatesNodes = 1; To be removed
			if (forecastCase == potential)
			{
				nUpdatesNodes = 1;
			}

			for (kk = 0; kk < nUpdatesNodes; kk++)
			{
				if (kk == 0)
				{
					for (int ij = 0; ij < Faclitiessize; ij++)
					{
						facilityCounter = ij;
						FacilityList = FacilityTables_Actual[ij];
						vector<InputDeckStruct> Facility = Faclities[i][ij];
						FacilityOiProduced = 0;
						FacilityWaterProduced = 0;
						FacilityGasProduced = 0;
						FacilityLiquidProduced = 0;

						int facilityCounter2 = 0;
						for (int ik = 0; ik < priotizationsFacilities[i].size(); ik++)
						{
							if (Facility[0].Flow_station == priotizationsFacilities[i][ik].FacilityName)
							{
								facilityCounter2 = ik;
								break;
							}
						}

						//std::cout << "GetDeckVariables started" << std::endl;
						GetDeckVariables(Facility, daysList, scenario, facilityCounter, FacilityTable[facilityCounter], i,
										 Faclitiessize, Faclities, forecastCase, priotizationsFacilities[i][facilityCounter2]);
						//std::cout << "GetDeckVariables completed" << std::endl;
						//std::cout << "GetFacilityFlowRates started" << std::endl;
						GetFacilityFlowRates(updatesNodes);
						//std::cout << "GetFacilityFlowRates completed" << std::endl;
					}
				}
				else
				{
					//std::cout << "GetDownStreamNodesFlux started" << std::endl;
					GetDownStreamNodesFlux(updatesNodes, kk);
					//std::cout << "GetDownStreamNodesFlux completed" << std::endl;
				}
			}

			if (nUpdatesNodes > 1)
			{
				//std::cout << "AdjustWellsFlowRates started" << std::endl;
				AdjustWellsFlowRates(updatesNodes, daysList, scenario, FacilityTable,
									 forecastCase, priotizationsFacilities, Faclities,
									 dateCreationX.dateTimes);
				//std::cout << "AdjustWellsFlowRates completed" << std::endl;
			}

			std::cout << CurrentDate.day << "/" << CurrentDate.month << "/" << CurrentDate.year << std::endl;

			// if(i > 0 && i % 10 == 0)
			// {
			// 	reportJSON.GetForecastOutput(Faclities, FaclitiesNames, env,
			// 	dateCreationX.dateTimes, dateCreationX.daysList, scenario, results);

			// 	Napi::Object emmittedObject = Napi::Object::New(env);

			// 	double percentageCompletion = ((1.0 * (i + startFrom))/(1.0 * nTimes))* 100.0;

			// 	emmittedObject.Set(Napi::String::New(env, "FaclitiesObject"), reportJSON.FaclitiesObject);
			// 	emmittedObject.Set(Napi::String::New(env, "percentageCompletion"), percentageCompletion);

			// 	emit.Call( { Napi::String::New(env, "publishForecastResult"), emmittedObject } );
			// }
		}
	//}
	/* catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	} */

	avgOilWellsRate = 0;
	double n = 365.0;
	for(i = 0; i < wellsOilRates.size(); i++){
		avgOilWellsRate = avgOilWellsRate + wellsOilRates[i];;
	}
	
	avgOilWellsRate = avgOilWellsRate / n;
	

	InputDecks.clear();
	InputDecks.shrink_to_fit();
	FacilityList.clear();
	FacilityList.shrink_to_fit();
	FacilityTables_Actual.clear();
	FacilityTables_Actual.shrink_to_fit();
	cutbacks.clear();
	cutbacks.shrink_to_fit();
	optimized_cutbacks.clear();
	optimized_cutbacks.shrink_to_fit();
	WellActivities.clear();
	WellActivities.shrink_to_fit();
	WellFacilityDataList.clear();
	WellFacilityDataList.shrink_to_fit();
}

void CalculateDeckVariables::GetDeckVariables(vector<InputDeckStruct> &facility,
											  vector<int> &daysList, int &scenario, int &facilityCounter,
											  FacilityStruct &facilityStruct, int &dateIndex, int &numberOfFacilities,
											  vector<vector<vector<InputDeckStruct>>> &Faclities,
											  string &forecastCase, Priotization &priotizationFacility)
{
	bool isAfetrOptimization = false;
	try
	{
		//double MM = 1000000.0;
		if (dateIndex == 0)
		{

			DeltaT = 0;
		}
		else
		{
			DeltaT = static_cast<double>(daysList[dateIndex] - daysList[dateIndex - 1]);
		}

		int j = -1;
		int i = 0;
		int facilityDecks = facility.size();
		for (j = 0; j < facilityDecks; j++)
		{
			//j++;
			InputDeckStruct deck = facility[j];
			WellIndex = j;
			ForecastResult forecastResult;
			ForecastResult forecastResult_old;

			if (dateIndex == 0)
			{
				forecastResult = results[dateIndex][facilityCounter][j];
				forecastResult_old = results[dateIndex][facilityCounter][j];
			}
			else
			{

				if (results[dateIndex][facilityCounter].size() > results[dateIndex - 1][facilityCounter].size() &&
					j >= results[dateIndex - 1][facilityCounter].size())
				{
					tuple<bool, int> checkIndex = CheckWellFacilityAndGetIndex(WellFacilityDataList, deck.Module);
					int Idx = get<1>(checkIndex);
					if (get<0>(checkIndex) == true)
					{

						forecastResult_old = results[dateIndex][facilityCounter][j];
						forecastResult = results[dateIndex][facilityCounter][j];
						if (deck.Hydrocarbon_Stream == oil)
						{
							forecastResult_old.Liquid_Rate = WellFacilityDataList[Idx].Rate;
							forecastResult.Liquid_Rate = WellFacilityDataList[Idx].Rate;
							forecastResult.URo = WellFacilityDataList[Idx].UR;
							forecastResult.Cum_Liquid_Prod = WellFacilityDataList[Idx].CumProd;
						}
						else
						{
							forecastResult_old.Gas_Rate = WellFacilityDataList[Idx].Rate;
							forecastResult.Gas_Rate = WellFacilityDataList[Idx].Rate;
							forecastResult.URg = WellFacilityDataList[Idx].UR;
							forecastResult.Cum_Gas_Prod = WellFacilityDataList[Idx].CumProd;
						}
					}
				}
				else
				{
					forecastResult_old = results[dateIndex - 1][facilityCounter][j];
					forecastResult = results[dateIndex][facilityCounter][j];
				}
			}

			forecastResult.Day = CurrentDate.day;
			forecastResult.Month = CurrentDate.month;
			forecastResult.Year = CurrentDate.year;

			double externalCurrentCumProd = 0;
			if (deck.Hydrocarbon_Stream == oil)
			{
				externalCurrentCumProd = (forecastResult_old.Cum_Oil_Prod - deck.Np);
			}
			else
			{
				externalCurrentCumProd = (forecastResult_old.Cum_Gas_Prod - deck.Gp);
			}

			switch (scenario)
			{
			case 1:
				/* if(dates[dateIndex].month == 7 && dates[dateIndex].year == 2024 &&
				deck.Module == "FO26016T_FO26 F40X_P09"){
					double hgs = 0;
				} */
				if (dateCreation.IsMaximumDate(dates[dateIndex], deck.Date_1P_1C) || dateCreation.EqualTo2(dates[dateIndex], deck.Date_1P_1C, isMonthly)) // Start Forecast for the well
				{
					forecastResult.deltaDay = 30;
					forecastResult.cumDays = forecastResult_old.cumDays + forecastResult.deltaDay;

					/* if(deck.Module == "FO10D40T_FO10 D40X_P12"){
						cumProdDays.push_back(forecastResult.cumDays);
					} */

					forecastResult.ModuleName = deck.Module;
					forecastResult.HyrocarbonStream = deck.Hydrocarbon_Stream;
					forecastResult.hydrocarbonType = deck.hydrocarbonType;
					forecastResult.terminal = deck.terminal;
					forecastResult.CutBack = 1.0;
					forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
						forecastResult.isGasTerminated, forecastResult.isWaterTerminated);

					if (UseExternalForecastprofile == external)
					{

						GetVariables(scenario, deck, forecastResult, forecastResult_old,
									 externalCurrentCumProd, isAfetrOptimization);
						if (deck.Hydrocarbon_Stream == oil)
						{
							if (forecastResult.Oil_rate <= 0)
							{
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								forecastResult.Oil_rate = 0;
							}
						}
						else
						{
							if (forecastResult.Gas_Rate <= 0)
							{
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								forecastResult.Gas_Rate = 0;
							}
						}

						if (forecastResult.Oil_rate == 0 &&
							forecastResult.Gas_Rate == 0)
						{
							forecastResult.IsFlowing = false;
						}

						results[dateIndex][facilityCounter][j] = forecastResult;
					}
					else
					{

						GetActiveRate(scenario, deck, forecastResult, forecastResult_old);
						if (deck.Hydrocarbon_Stream == oil)
						{
							if (forecastResult.Liquid_Rate <= 0)
							{
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								forecastResult.Liquid_Rate = 0;
							}

							if (deck.isTerminated == true ||
								deck.isOilTerminated == true ||
								deck.isGasTerminated == true ||
								deck.isWaterTerminated == true)
							{
								bool chk = CheckWellFacility(WellFacilityDataList, forecastResult.ModuleName, forecastResult.Flow_station);
								if (chk == false)
								{
									WellFacilityData wellFacilityData;
									wellFacilityData.Flow_station = forecastResult.Flow_station;
									wellFacilityData.ModuleName = forecastResult.ModuleName;
									wellFacilityData.Rate = forecastResult.Liquid_Rate;
									wellFacilityData.UR = forecastResult_old.URo;
									wellFacilityData.CumProd = forecastResult_old.Cum_Liquid_Prod;
									wellFacilityData.LastDate = dates[dateIndex];
									WellFacilityDataList.push_back(wellFacilityData);

									for (i = 0; i < numberOfFacilities; i++)
									{
										if (facilityCounter != i)
										{
											vector<InputDeckStruct> decks_i = Faclities[dateIndex][i];
											int nWells = results[dateIndex][i].size();
											int ij = 0, ik = 0;
											for (ij = 0; ij < nWells; ij++)
											{
												if (results[dateIndex][i][ij].ModuleName == forecastResult.ModuleName)
												{
													if (dateCreation.IsMaximumDate(dates[dateIndex], decks_i[ij].Date_1P_1C) ||
														dateCreation.EqualTo2(dates[dateIndex], decks_i[ij].Date_1P_1C, isMonthly))
													{
														if (results[dateIndex][i][ij].Liquid_Rate > 0)
														{
															if (dateIndex > 0)
															{
																results[dateIndex - 1][i][ij].Liquid_Rate = forecastResult.Liquid_rate_NotTerminated;
															}
															results[dateIndex][i][ij].Liquid_Rate = forecastResult.Liquid_rate_NotTerminated;
															results[dateIndex][i][ij].URo = forecastResult_old.URo;
															results[dateIndex][i][ij].Cum_Liquid_Prod = forecastResult_old.Cum_Liquid_Prod;

															int nSize = Faclities.size();
															for (ik = dateIndex; ik < nSize; ik++)
															{
																Faclities[ik][i][ij].Init_Liquid_Gas_Rate_1P_1C = forecastResult.Liquid_rate_NotTerminated;
																//Faclities[ik][i][ij].URo_1P_1C = forecastResult.URo;
																//Faclities[ik][i][ij].URo_1P_1C = forecastResult.URo;
															}
														}
													}
												}
											}
										}
									}
								}
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								if (deck.isOilTerminated == true)
								{
									forecastResult.Oil_rate = 0;
								}
								if (deck.isGasTerminated == true)
								{
									forecastResult.Gas_Rate = 0;
								}
								if (deck.isWaterTerminated == true)
								{
									forecastResult.Water_Rate = 0;
								}
							}
						}
						else
						{
							if (forecastResult.Gas_Rate <= 0)
							{
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								forecastResult.Gas_Rate = 0;
							}

							if (deck.isTerminated == true ||
								deck.isOilTerminated == true ||
								deck.isGasTerminated == true ||
								deck.isWaterTerminated == true)
							{
								bool chk = CheckWellFacility(WellFacilityDataList, forecastResult.ModuleName, forecastResult.Flow_station);
								if (chk == false)
								{
									WellFacilityData wellFacilityData;
									wellFacilityData.Flow_station = forecastResult.Flow_station;
									wellFacilityData.ModuleName = forecastResult.ModuleName;
									wellFacilityData.Rate = forecastResult.Gas_Rate;
									wellFacilityData.UR = forecastResult_old.URg;
									wellFacilityData.CumProd = forecastResult_old.Cum_Gas_Prod;
									wellFacilityData.LastDate = dates[dateIndex];
									WellFacilityDataList.push_back(wellFacilityData);

									for (i = 0; i < numberOfFacilities; i++)
									{
										if (facilityCounter != i)
										{
											vector<InputDeckStruct> decks_i = Faclities[dateIndex][i];
											int nWells = results[dateIndex][i].size();
											int ij = 0, ik = 0;
											for (ij = 0; ij < nWells; ij++)
											{
												if (results[dateIndex][i][ij].ModuleName == forecastResult.ModuleName)
												{
													if (dateCreation.IsMaximumDate(dates[dateIndex], decks_i[ij].Date_1P_1C) ||
														dateCreation.EqualTo2(dates[dateIndex], decks_i[ij].Date_1P_1C, isMonthly))
													{
														if (results[dateIndex][i][ij].Gas_Rate > 0)
														{
															if (dateIndex > 0)
															{
																results[dateIndex - 1][i][ij].Gas_Rate = forecastResult.Gas_Rate_NotTerminated;
															}
															results[dateIndex][i][ij].Gas_Rate = forecastResult.Gas_Rate_NotTerminated;
															results[dateIndex][i][ij].URg = forecastResult_old.URg;
															results[dateIndex][i][ij].Cum_Gas_Prod = forecastResult_old.Cum_Gas_Prod;
															int nSize = Faclities.size();
															for (ik = dateIndex; ik < nSize; ik++)
															{
																Faclities[ik][i][ij].Init_Liquid_Gas_Rate_1P_1C = forecastResult.Gas_Rate_NotTerminated;
															}
														}
													}
												}
											}
										}
									}
								}
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								if (deck.isOilTerminated == true)
								{
									forecastResult.Oil_rate = 0;
								}
								if (deck.isGasTerminated == true)
								{
									forecastResult.Gas_Rate = 0;
								}
								if (deck.isWaterTerminated == true)
								{
									forecastResult.Water_Rate = 0;
								}
							}
						}

						GetVariables(scenario, deck, forecastResult, forecastResult_old,
									 externalCurrentCumProd, isAfetrOptimization);
						if (forecastResult.Oil_rate == 0 &&
							forecastResult.Gas_Rate == 0)
						{
							forecastResult.IsFlowing = false;
						}
						results[dateIndex][facilityCounter][j] = forecastResult;
					}
				}
				break;
			case 2:
				if (dateCreation.IsMaximumDate(dates[dateIndex], deck.Date_2P_2C) || dateCreation.EqualTo2(dates[dateIndex], deck.Date_2P_2C, isMonthly)) // Start Forecast for the well
				{
					forecastResult.deltaDay = 30;
					forecastResult.cumDays = forecastResult_old.cumDays + forecastResult.deltaDay;
					/* if(deck.Module == "FO10D40T_FO10 D40X_P12"){
						cumProdDays.push_back(forecastResult.cumDays);
					} */

					forecastResult.ModuleName = deck.Module;
					forecastResult.HyrocarbonStream = deck.Hydrocarbon_Stream;
					forecastResult.hydrocarbonType = deck.hydrocarbonType;
					forecastResult.terminal = deck.terminal;
					forecastResult.CutBack = 1.0;
					forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																forecastResult.isGasTerminated, forecastResult.isWaterTerminated);

					if (UseExternalForecastprofile == external)
					{

						GetVariables(scenario, deck, forecastResult, forecastResult_old,
									 externalCurrentCumProd, isAfetrOptimization);
						if (deck.Hydrocarbon_Stream == oil)
						{
							if (forecastResult.Liquid_Rate <= 0)
							{
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								forecastResult.Liquid_Rate = 0;
							}
						}
						else
						{
							if (forecastResult.Gas_Rate <= 0)
							{
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								forecastResult.Gas_Rate = 0;
							}
						}
						if (forecastResult.Oil_rate == 0 &&
							forecastResult.Gas_Rate == 0)
						{
							forecastResult.IsFlowing = false;
						}
						results[dateIndex][facilityCounter][j] = forecastResult;
					}
					else
					{
						GetActiveRate(scenario, deck, forecastResult, forecastResult_old);
						if (deck.Hydrocarbon_Stream == oil)
						{
							if (forecastResult.Liquid_Rate <= 0)
							{
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								forecastResult.Liquid_Rate = 0;
							}

							if (deck.isTerminated == true ||
								deck.isOilTerminated == true ||
								deck.isGasTerminated == true ||
								deck.isWaterTerminated == true)
							{
								bool chk = CheckWellFacility(WellFacilityDataList, forecastResult.ModuleName, forecastResult.Flow_station);
								if (chk == false)
								{
									WellFacilityData wellFacilityData;
									wellFacilityData.Flow_station = forecastResult.Flow_station;
									wellFacilityData.ModuleName = forecastResult.ModuleName;
									wellFacilityData.Rate = forecastResult.Liquid_Rate;
									wellFacilityData.UR = forecastResult_old.URo;
									wellFacilityData.CumProd = forecastResult_old.Cum_Liquid_Prod;
									wellFacilityData.LastDate = dates[dateIndex];
									WellFacilityDataList.push_back(wellFacilityData);

									for (i = 0; i < numberOfFacilities; i++)
									{
										if (facilityCounter != i)
										{
											vector<InputDeckStruct> decks_i = Faclities[dateIndex][i];
											int nWells = results[dateIndex][i].size();
											int ij = 0, ik = 0;
											for (ij = 0; ij < nWells; ij++)
											{
												if (results[dateIndex][i][ij].ModuleName == forecastResult.ModuleName)
												{
													if (dateCreation.IsMaximumDate(dates[dateIndex], decks_i[ij].Date_2P_2C) ||
														dateCreation.EqualTo2(dates[dateIndex], decks_i[ij].Date_2P_2C, isMonthly))
													{
														if (results[dateIndex][i][ij].Liquid_Rate > 0)
														{
															if (dateIndex > 0)
															{
																results[dateIndex - 1][i][ij].Liquid_Rate = forecastResult.Liquid_rate_NotTerminated;
															}
															results[dateIndex][i][ij].Liquid_Rate = forecastResult.Liquid_rate_NotTerminated;
															results[dateIndex][i][ij].URo = forecastResult_old.URo;
															results[dateIndex][i][ij].Cum_Liquid_Prod = forecastResult_old.Cum_Liquid_Prod;
															int nSize = Faclities.size();
															for (ik = dateIndex; ik < nSize; ik++)
															{
																Faclities[ik][i][ij].Init_Liquid_Gas_Rate_2P_2C = forecastResult.Liquid_rate_NotTerminated;
															}
														}
													}
												}
											}
										}
									}
								}
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								if (deck.isOilTerminated == true)
								{
									forecastResult.Oil_rate = 0;
								}
								if (deck.isGasTerminated == true)
								{
									forecastResult.Gas_Rate = 0;
								}
								if (deck.isWaterTerminated == true)
								{
									forecastResult.Water_Rate = 0;
								}
							}
						}
						else
						{
							if (forecastResult.Gas_Rate <= 0)
							{
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								forecastResult.Gas_Rate = 0;
							}

							if (deck.isTerminated == true ||
								deck.isOilTerminated == true ||
								deck.isGasTerminated == true ||
								deck.isWaterTerminated == true)
							{
								bool chk = CheckWellFacility(WellFacilityDataList, forecastResult.ModuleName, forecastResult.Flow_station);
								if (chk == false)
								{
									WellFacilityData wellFacilityData;
									wellFacilityData.Flow_station = forecastResult.Flow_station;
									wellFacilityData.ModuleName = forecastResult.ModuleName;
									wellFacilityData.Rate = forecastResult.Gas_Rate;
									wellFacilityData.UR = forecastResult_old.URg;
									wellFacilityData.CumProd = forecastResult_old.Cum_Gas_Prod;
									wellFacilityData.LastDate = dates[dateIndex];
									WellFacilityDataList.push_back(wellFacilityData);

									for (i = 0; i < numberOfFacilities; i++)
									{
										if (facilityCounter != i)
										{
											vector<InputDeckStruct> decks_i = Faclities[dateIndex][i];
											int nWells = results[dateIndex][i].size();
											int ij = 0, ik = 0;
											for (ij = 0; ij < nWells; ij++)
											{
												if (results[dateIndex][i][ij].ModuleName == forecastResult.ModuleName)
												{
													if (dateCreation.IsMaximumDate(dates[dateIndex], decks_i[ij].Date_2P_2C) ||
														dateCreation.EqualTo2(dates[dateIndex], decks_i[ij].Date_2P_2C, isMonthly))
													{
														if (results[dateIndex][i][ij].Gas_Rate > 0)
														{
															if (dateIndex > 0)
															{
																results[dateIndex - 1][i][ij].Gas_Rate = forecastResult.Gas_Rate_NotTerminated;
															}
															results[dateIndex][i][ij].Gas_Rate = forecastResult.Gas_Rate_NotTerminated;
															results[dateIndex][i][ij].URg = forecastResult_old.URg;
															results[dateIndex][i][ij].Cum_Gas_Prod = forecastResult_old.Cum_Gas_Prod;
															int nSize = Faclities.size();
															for (ik = dateIndex; ik < nSize; ik++)
															{
																Faclities[ik][i][ij].Init_Liquid_Gas_Rate_2P_2C = forecastResult.Gas_Rate_NotTerminated;
															}
														}
													}
												}
											}
										}
									}
								}
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								if (deck.isOilTerminated == true)
								{
									forecastResult.Oil_rate = 0;
								}
								if (deck.isGasTerminated == true)
								{
									forecastResult.Gas_Rate = 0;
								}
								if (deck.isWaterTerminated == true)
								{
									forecastResult.Water_Rate = 0;
								}
							}
						}
						GetVariables(scenario, deck, forecastResult, forecastResult_old,
									 externalCurrentCumProd, isAfetrOptimization);
						if (forecastResult.Oil_rate == 0 &&
							forecastResult.Gas_Rate == 0)
						{
							forecastResult.IsFlowing = false;
						}
						results[dateIndex][facilityCounter][j] = forecastResult;
					}
				}
				break;
			case 3:
				if (dateCreation.IsMaximumDate(dates[dateIndex], deck.Date_3P_3C) || dateCreation.EqualTo2(dates[dateIndex], deck.Date_3P_3C, isMonthly)) // Start Forecast for the well
				{
					forecastResult.deltaDay = 30;
					forecastResult.cumDays = forecastResult_old.cumDays + forecastResult.deltaDay;
					if(deck.Module == "FO10D40T_FO10 D40X_P12"){
						cumProdDays.push_back(forecastResult.cumDays);
					}

					forecastResult.ModuleName = deck.Module;
					forecastResult.HyrocarbonStream = deck.Hydrocarbon_Stream;
					forecastResult.hydrocarbonType = deck.hydrocarbonType;
					forecastResult.terminal = deck.terminal;
					forecastResult.CutBack = 1.0;
					forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																forecastResult.isGasTerminated, forecastResult.isWaterTerminated);

					if (UseExternalForecastprofile == external)
					{

						GetVariables(scenario, deck, forecastResult, forecastResult_old,
									 externalCurrentCumProd, isAfetrOptimization);
						if (deck.Hydrocarbon_Stream == oil)
						{
							if (forecastResult.Liquid_Rate <= 0)
							{
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								forecastResult.Liquid_Rate = 0;
							}
						}
						else
						{
							if (forecastResult.Gas_Rate <= 0)
							{
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								forecastResult.Gas_Rate = 0;
							}
						}
						results[dateIndex][facilityCounter][j] = forecastResult;
					}
					else
					{
						GetActiveRate(scenario, deck, forecastResult, forecastResult_old);
						if (deck.Hydrocarbon_Stream == oil)
						{
							if (forecastResult.Liquid_Rate <= 0)
							{
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								forecastResult.Liquid_Rate = 0;
							}

							if (deck.isTerminated == true ||
								deck.isOilTerminated == true ||
								deck.isGasTerminated == true ||
								deck.isWaterTerminated == true)
							{
								bool chk = CheckWellFacility(WellFacilityDataList, forecastResult.ModuleName, forecastResult.Flow_station);
								if (chk == false)
								{
									WellFacilityData wellFacilityData;
									wellFacilityData.Flow_station = forecastResult.Flow_station;
									wellFacilityData.ModuleName = forecastResult.ModuleName;
									wellFacilityData.Rate = forecastResult.Liquid_Rate;
									wellFacilityData.UR = forecastResult_old.URo;
									wellFacilityData.CumProd = forecastResult_old.Cum_Liquid_Prod;
									wellFacilityData.LastDate = dates[dateIndex];
									WellFacilityDataList.push_back(wellFacilityData);

									for (i = 0; i < numberOfFacilities; i++)
									{
										if (facilityCounter != i)
										{
											vector<InputDeckStruct> decks_i = Faclities[dateIndex][i];
											int nWells = results[dateIndex][i].size();
											int ij = 0, ik = 0;
											for (ij = 0; ij < nWells; ij++)
											{
												if (results[dateIndex][i][ij].ModuleName == forecastResult.ModuleName)
												{
													if (dateCreation.IsMaximumDate(dates[dateIndex], decks_i[ij].Date_3P_3C) ||
														dateCreation.EqualTo2(dates[dateIndex], decks_i[ij].Date_3P_3C, isMonthly))
													{
														if (results[dateIndex][i][ij].Liquid_Rate > 0)
														{
															if (dateIndex > 0)
															{
																results[dateIndex - 1][i][ij].Liquid_Rate = forecastResult.Liquid_rate_NotTerminated;
															}
															results[dateIndex][i][ij].Liquid_Rate = forecastResult.Liquid_rate_NotTerminated;
															results[dateIndex][i][ij].URo = forecastResult_old.URo;
															results[dateIndex][i][ij].Cum_Liquid_Prod = forecastResult_old.Cum_Liquid_Prod;
															int nSize = Faclities.size();
															for (ik = dateIndex; ik < nSize; ik++)
															{
																Faclities[ik][i][ij].Init_Liquid_Gas_Rate_3P_3C = forecastResult.Liquid_rate_NotTerminated;
															}
														}
													}
												}
											}
										}
									}
								}
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								if (deck.isOilTerminated == true)
								{
									forecastResult.Oil_rate = 0;
								}
								if (deck.isGasTerminated == true)
								{
									forecastResult.Gas_Rate = 0;
								}
								if (deck.isWaterTerminated == true)
								{
									forecastResult.Water_Rate = 0;
								}
							}
						}
						else
						{
							if (forecastResult.Gas_Rate <= 0)
							{
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								forecastResult.Gas_Rate = 0;
							}

							if (deck.isTerminated == true ||
								deck.isOilTerminated == true ||
								deck.isGasTerminated == true ||
								deck.isWaterTerminated == true)
							{
								bool chk = CheckWellFacility(WellFacilityDataList, forecastResult.ModuleName, forecastResult.Flow_station);
								if (chk == false)
								{
									WellFacilityData wellFacilityData;
									wellFacilityData.Flow_station = forecastResult.Flow_station;
									wellFacilityData.ModuleName = forecastResult.ModuleName;
									wellFacilityData.Rate = forecastResult.Gas_Rate;
									wellFacilityData.UR = forecastResult_old.URg;
									wellFacilityData.CumProd = forecastResult_old.Cum_Gas_Prod;
									wellFacilityData.LastDate = dates[dateIndex];
									WellFacilityDataList.push_back(wellFacilityData);

									for (i = 0; i < numberOfFacilities; i++)
									{
										if (facilityCounter != i)
										{
											vector<InputDeckStruct> decks_i = Faclities[dateIndex][i];
											int nWells = results[dateIndex][i].size();
											int ij = 0, ik = 0;
											for (ij = 0; ij < nWells; ij++)
											{
												if (results[dateIndex][i][ij].ModuleName == forecastResult.ModuleName)
												{
													if (dateCreation.IsMaximumDate(dates[dateIndex], decks_i[ij].Date_3P_3C) ||
														dateCreation.EqualTo2(dates[dateIndex], decks_i[ij].Date_3P_3C, isMonthly))
													{
														if (results[dateIndex][i][ij].Gas_Rate > 0)
														{
															if (dateIndex > 0)
															{
																results[dateIndex - 1][i][ij].Gas_Rate = forecastResult.Gas_Rate_NotTerminated;
															}
															results[dateIndex][i][ij].Gas_Rate = forecastResult.Gas_Rate_NotTerminated;
															results[dateIndex][i][ij].URg = forecastResult_old.URg;
															results[dateIndex][i][ij].Cum_Gas_Prod = forecastResult_old.Cum_Gas_Prod;
															int nSize = Faclities.size();
															for (ik = dateIndex; ik < nSize; ik++)
															{
																Faclities[ik][i][ij].Init_Liquid_Gas_Rate_3P_3C = forecastResult.Gas_Rate_NotTerminated;
															}
														}
													}
												}
											}
										}
									}
								}
								forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
																			forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
								if (deck.isOilTerminated == true)
								{
									forecastResult.Oil_rate = 0;
								}
								if (deck.isGasTerminated == true)
								{
									forecastResult.Gas_Rate = 0;
								}
								if (deck.isWaterTerminated == true)
								{
									forecastResult.Water_Rate = 0;
								}
							}
						}

						GetVariables(scenario, deck, forecastResult, forecastResult_old,
									 externalCurrentCumProd, isAfetrOptimization);
						if (forecastResult.Oil_rate == 0 &&
							forecastResult.Gas_Rate == 0)
						{
							forecastResult.IsFlowing = false;
						}
						results[dateIndex][facilityCounter][j] = forecastResult;
					}
				}
				break;
			}
		}

		int nWells = facility.size();
		//std::cout << "NO OF WELLS " << nWells << std::endl;

		GetOnstreamWells(facilityCounter, dateIndex, nWells, facilityStruct, forecastCase, priotizationFacility);
		optimalSolution = 0;

		int nth = OptimizedWells.size();

		/* if(priotizationFacility.FacilityName == "REO_GP2"){
			double cg = 0;
		} */

		if (forecastCase != potential)
		{
			if (nth > 0)
			{

				if (priotizationFacility.typeOfPrioritization == streamPrioritization)
				{
					
					optimize_by_stream_prioritization(OptimizedWells, optimized_cutbacks, priotizationFacility);

				}else if (priotizationFacility.typeOfPrioritization == wellPrioritization ||
					priotizationFacility.typeOfPrioritization == resourceClassPrioritization)
				{
					
					optimize_constraint_by_well(OptimizedWells, optimized_cutbacks, priotizationFacility);
				}else{
					optimize_constraint_no_prioritization(OptimizedWells, optimized_cutbacks, priotizationFacility);
				}
			}
		}

		j = -1;

		GetCurrentFacilityData();
		Liquid_Capacity = CurrentFacilityData.Liquid_Capacity;
		Gas_Capacity = CurrentFacilityData.Gas_Capacity;
		AG_Capacity = CurrentFacilityData.AG_Capacity;
		NAG_Capacity = CurrentFacilityData.NAG_Capacity;
		if (Gas_Capacity == 0)
		{
			Gas_Capacity = AG_Capacity + NAG_Capacity;
		}
		SalesGasPlusOwnUse = CurrentFacilityData.GasDemand + CurrentFacilityData.GasOwnUse;
		double plateauGasVolume = 0;
		double plateauLiquidVolume = 0;
		double defermentFactor = 1 - (CurrentFacilityData.Scheduled_Deferment / 100) -
								(CurrentFacilityData.Unscheduled_Deferment / 100) -
								(CurrentFacilityData.Thirdparty_Deferment / 100);
		if (forecastCase == delivered)
		{
			Gas_Capacity = Gas_Capacity * defermentFactor;
			Liquid_Capacity = CurrentFacilityData.Liquid_Capacity * defermentFactor;
		}

		if (forecastCase == offtake)
		{
			Gas_Capacity = CurrentFacilityData.GasDemand * defermentFactor;
			Liquid_Capacity = CurrentFacilityData.Liquid_Capacity * defermentFactor;
		}

		FacilityOiProduced = 0;
		FacilityWaterProduced = 0;
		FacilityGasProduced = 0;
		FacilityAGProduced = 0;
		FacilityNAGProduced = 0;
		FacilityLiquidProduced = 0;

		double FQg = 0;
		double FQL = 0;
		double Liquid_Capacity_Artificial = 0;
		double Gas_Capacity_Artificial = 0;
		int OnstreamDecksCount = OptimizedWellsIndicies.size();
		for (i = 0; i < OnstreamDecksCount; i++)
		{
			j = OptimizedWellsIndicies[i];

			Liquid_Capacity_Artificial = Liquid_Capacity_Artificial + 
			(results[dateIndex][facilityCounter][j].Water_Rate + results[dateIndex][facilityCounter][j].Oil_rate);
			Gas_Capacity_Artificial = Gas_Capacity_Artificial + results[dateIndex][facilityCounter][j].Gas_Rate;

		}

		if(Gas_Capacity < 0.00001){
			Gas_Capacity = Gas_Capacity_Artificial * 1.5;
		}

		if(Liquid_Capacity < 0.00001){
			Liquid_Capacity = Liquid_Capacity_Artificial * 1.5;
		}

		for (i = 0; i < OnstreamDecksCount; i++)
		{
			j = OptimizedWellsIndicies[i];
			InputDeckStruct deck = facility[j];
			

			switch (scenario)
			{
			case 1:
				SetCutRatesBackValues(facilityCounter, dateIndex, optimized_cutbacks[i],
									  scenario, deck, j);

					/* if(deck.Module == "FO10D40T_FO10 D40X_P12"){
						wellsOilRates.push_back(results[dateIndex][facilityCounter][j].Oil_rate);
					} */
				break;

			case 2:
				SetCutRatesBackValues(facilityCounter, dateIndex, optimized_cutbacks[i],
									  scenario, deck, j);
				/* if(deck.Module == "FO10D40T_FO10 D40X_P12"){
						wellsOilRates.push_back(results[dateIndex][facilityCounter][j].Oil_rate);
				} */
				break;

			case 3:
				SetCutRatesBackValues(facilityCounter, dateIndex, optimized_cutbacks[i],
									  scenario, deck, j);
				if(deck.Module == "FO10D40T_FO10 D40X_P12"){
						wellsOilRates.push_back(results[dateIndex][facilityCounter][j].Oil_rate);
				}
				break;
			}

			

			if (results[dateIndex][facilityCounter][j].IsFlowing == false &&
				results[dateIndex][facilityCounter][j].Gas_Rate > 0)
			{
				double aa = 0;
			}

			if (results[dateIndex][facilityCounter][j].IsFlowing == false &&
				results[dateIndex][facilityCounter][j].Oil_rate > 0)
			{
				double aa = 0;
			}

			FQg = FQg + results[dateIndex][facilityCounter][j].Gas_Rate;
			FQL = FQL +
				  (results[dateIndex][facilityCounter][j].Oil_rate + results[dateIndex][facilityCounter][j].Water_Rate);

			if (FQg > Gas_Capacity)
			{
				double aa = 0;
			}

			if (FQL > Liquid_Capacity)
			{
				double aa = 0;
			}
		}

		if(priotizationFacility.FacilityName == "REO_GP2"){
			double cg = 0;
		}
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CalculateDeckVariables::GetDeckVariables2(vector<InputDeckStruct> &facility,
											   vector<int> &daysList, int &scenario, int &facilityCounter,
											   FacilityStruct &facilityStruct, int &dateIndex, int &numberOfFacilities,
											   vector<vector<vector<InputDeckStruct>>> &Faclities,
											   string &forecastCase, Priotization &priotizationFacility,
											   double &gasCutBack, double &liquidCutBack,
											   string &liquidCutBackText, string &gasCutBackText, 
											   string &nodeConnections)
{
	bool isAfetrOptimization = false;
	try
	{
		//double MM = 1000000.0;
		if (dateIndex == 0)
		{
			DeltaT = 0;
		}
		else
		{
			DeltaT = static_cast<double>(daysList[dateIndex] - daysList[dateIndex - 1]);
		}

		int j = -1;
		int i = 0;
		int nWells = facility.size();
		int facilityDecks = nWells;
		//std::cout << "GetOnstreamWells2 started" << "\n";
		GetOnstreamWells2(facilityCounter, dateIndex, nWells, facilityStruct,
						  liquidCutBackText, gasCutBackText, nodeConnections);
		optimalSolution = 0;
		//std::cout << "GetOnstreamWells2 completed" << "\n";

		int nth = OptimizedWells.size();

		j = -1;

		GetCurrentFacilityData();
		Liquid_Capacity = CurrentFacilityData.Liquid_Capacity;
		Gas_Capacity = CurrentFacilityData.Gas_Capacity;
		AG_Capacity = CurrentFacilityData.AG_Capacity;
		NAG_Capacity = CurrentFacilityData.NAG_Capacity;
		if (Gas_Capacity == 0)
		{
			Gas_Capacity = AG_Capacity + NAG_Capacity;
		}
		SalesGasPlusOwnUse = CurrentFacilityData.GasDemand + CurrentFacilityData.GasOwnUse;
		double plateauGasVolume = 0;
		double plateauLiquidVolume = 0;
		double defermentFactor = 1 - (CurrentFacilityData.Scheduled_Deferment / 100) -
								(CurrentFacilityData.Unscheduled_Deferment / 100) -
								(CurrentFacilityData.Thirdparty_Deferment / 100);
		if (forecastCase == delivered)
		{
			Gas_Capacity = Gas_Capacity * defermentFactor;
			Liquid_Capacity = CurrentFacilityData.Liquid_Capacity * defermentFactor;
		}

		if (forecastCase == offtake)
		{
			Gas_Capacity = CurrentFacilityData.GasDemand * defermentFactor;
			Liquid_Capacity = CurrentFacilityData.Liquid_Capacity * defermentFactor;
		}

		int onStreamWellsCount = OptimizedWellsIndicies.size();
		double Liquid_Capacity_Artificial = 0;
		double Gas_Capacity_Artificial = 0;

		for (i = 0; i < onStreamWellsCount; i++)
		{
			j = OptimizedWellsIndicies[i];
			Liquid_Capacity_Artificial = Liquid_Capacity_Artificial + 
			(results[dateIndex][facilityCounter][j].Water_Rate + results[dateIndex][facilityCounter][j].Oil_rate);
			Gas_Capacity_Artificial = Gas_Capacity_Artificial + results[dateIndex][facilityCounter][j].Gas_Rate;
		}

		if(Gas_Capacity < 0.00001){
			Gas_Capacity = Gas_Capacity_Artificial * 1.5;
		}

		if(Liquid_Capacity < 0.00001){
			Liquid_Capacity = Liquid_Capacity_Artificial * 1.5;
		}

		for (i = 0; i < onStreamWellsCount; i++)
		{
			j = OptimizedWellsIndicies[i];
			InputDeckStruct deck = facility[j];
			switch (scenario)
			{
			case 1:
				SetCutRatesBackValues(facilityCounter, dateIndex, scenario, deck, j, gasCutBack, liquidCutBack);

				break;

			case 2:
				SetCutRatesBackValues(facilityCounter, dateIndex, scenario, deck, j, gasCutBack, liquidCutBack);
				break;

			case 3:
				SetCutRatesBackValues(facilityCounter, dateIndex, scenario, deck, j, gasCutBack, liquidCutBack);
				break;
			}
		}

	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CalculateDeckVariables::GetOnstreamWells(int &facilityCounter, int &timeStepCounter, int &nWells,
											  FacilityStruct &facilityStruct, string& forecastCase, Priotization& priotizationFacility)
{
	checker= " GetOnstreamWells ";

	OnStreamWells.clear();
	OptimizedWells.clear();
	OptimizedWellsIndicies.clear();
	cutbacks.clear();
	optimized_cutbacks.clear();
	GetCurrentFacilityData();
	Liquid_Capacity = CurrentFacilityData.Liquid_Capacity;
	Gas_Capacity = CurrentFacilityData.Gas_Capacity;
	AG_Capacity = CurrentFacilityData.AG_Capacity;
	NAG_Capacity = CurrentFacilityData.NAG_Capacity;
	if (Gas_Capacity == 0)
	{
		Gas_Capacity = AG_Capacity + NAG_Capacity;
	}
	SalesGasPlusOwnUse = CurrentFacilityData.GasDemand + CurrentFacilityData.GasOwnUse;
	double plateauGasVolume = 0;
	double plateauLiquidVolume = 0;
	double defermentFactor = 1 - (CurrentFacilityData.Scheduled_Deferment / 100) -
							 (CurrentFacilityData.Unscheduled_Deferment / 100) -
							 (CurrentFacilityData.Thirdparty_Deferment / 100);
	if (forecastCase == delivered)
	{
		Gas_Capacity = Gas_Capacity * defermentFactor;
		Liquid_Capacity = CurrentFacilityData.Liquid_Capacity * defermentFactor;
	}

	if (forecastCase == offtake)
	{
		Gas_Capacity = CurrentFacilityData.GasDemand * defermentFactor;
		Liquid_Capacity = CurrentFacilityData.Liquid_Capacity * defermentFactor;
	}

	//int FlowingWellIndex = -1;

	double Liquid_Capacity_Artificial = 0;
	double Gas_Capacity_Artificial = 0;

	for (int i = 0; i < nWells; i++)
	{
		ForecastResult forecastResult = results[timeStepCounter][facilityCounter][i];

		forecastResult.fluidFraction = 0;


		if (forecastResult.IsFlowing == true)
		{

			if(priotizationFacility.ochestrationVariable == "gOR"){
				if(forecastResult.Oil_rate > 0){
					forecastResult.fluidFraction = forecastResult.Gas_Rate/forecastResult.Oil_rate;
				}
			}

			if(priotizationFacility.ochestrationVariable == "cGR"){
				if(forecastResult.Gas_Rate > 0){
					forecastResult.fluidFraction = forecastResult.Oil_rate/forecastResult.Gas_Rate;
				}
			}

			if(priotizationFacility.ochestrationVariable == "bSW"){
				if(forecastResult.Liquid_Rate > 0){
					forecastResult.fluidFraction = forecastResult.Water_Rate/forecastResult.Liquid_Rate;
				}
			}

			if(priotizationFacility.ochestrationVariable == "wGR"){
				if(forecastResult.Gas_Rate > 0){
					forecastResult.fluidFraction = forecastResult.Water_Rate/forecastResult.Gas_Rate;
				}
			}

			OnStreamWells.push_back(forecastResult);
			cutbacks.push_back(1.0);

			OptimizedWells.push_back(forecastResult);
			OptimizedWellsIndicies.push_back(i);
			optimized_cutbacks.push_back(1.0);

			Liquid_Capacity_Artificial = Liquid_Capacity_Artificial + 
			(forecastResult.Water_Rate + forecastResult.Oil_rate);
			Gas_Capacity_Artificial = Gas_Capacity_Artificial + forecastResult.Gas_Rate;

		}
	}

	//assestPriotization.ochestrationVariable = priotization.ochestrationVariable

	if(OnStreamWells.size() > 0){
		if(priotizationFacility.ochestrationMethod == "ranking"){
			OnStreamWells = SortOnstreamWells(OnStreamWells);
		}

		if(priotizationFacility.ochestrationMethod == "mean"){
			OnStreamWells = SortOnstreamWellsByMean(OnStreamWells);
		}

		if(priotizationFacility.ochestrationMethod == "probabilityDensityFunction"){
			OnStreamWells = SortOnstreamWellsByProbabilityDistribution(OnStreamWells);
		}

		OptimizedWells = OnStreamWells;
	}


	if(Gas_Capacity < 0.00001){
		Gas_Capacity = Gas_Capacity_Artificial * 1.5;
	}

	if(Liquid_Capacity < 0.00001){
		Liquid_Capacity = Liquid_Capacity_Artificial * 1.5;
	}
}

void CalculateDeckVariables::GetOnstreamWells2(int &facilityCounter, int &timeStepCounter, int &nWells,
											   FacilityStruct &facilityStruct,
											   string &liquidCutBackText, string &gasCutBackText, string &nodeConnections)
{

	OnStreamWells.clear();
	OptimizedWells.clear();
	OptimizedWellsIndicies.clear();
	cutbacks.clear();
	optimized_cutbacks.clear();

	double plateauGasVolume = 0;
	double plateauLiquidVolume = 0;

	for (int i = 0; i < nWells; i++)
	{
		ForecastResult forecastResult = results[timeStepCounter][facilityCounter][i];
		if (forecastResult.IsFlowing == true)
		{
			forecastResult.liquidCutBackText = liquidCutBackText;
			forecastResult.gasCutBackText = liquidCutBackText;
			forecastResult.nodeConnections = liquidCutBackText;

			OnStreamWells.push_back(forecastResult);
			cutbacks.push_back(1.0);

			OptimizedWells.push_back(forecastResult);
			OptimizedWellsIndicies.push_back(i);
			optimized_cutbacks.push_back(1.0);
		}
	}
}

void CalculateDeckVariables::GetCurrentFacilityData()
{
	//double frac0 = 0, frac1 = 0, frac2 = 0;
	//double MM = 1000000.0;
	int i = 0, nSIze = FacilityList.size();

	if (dateCreation.EqualTo2(CurrentDate, FacilityList[0].FacilityDate, isMonthly))
	{

		CurrentFacilityData = FacilityList[0];
		//std::cout << "GAS CAPACITY: " << CurrentFacilityData.Gas_Capacity << std::endl;
		//std::cout << "LIQUID CAPACITY: " << CurrentFacilityData.Liquid_Capacity << std::endl;

		return;
	}

	if (dateCreation.IsMinimumDate(CurrentDate, FacilityList[0].FacilityDate))
	{
		CurrentFacilityData = FacilityList[0];
		//std::cout << "GAS CAPACITY: " << CurrentFacilityData.Gas_Capacity << std::endl;
		//std::cout << "LIQUID CAPACITY: " << CurrentFacilityData.Liquid_Capacity << std::endl;
		return;
	}

	if (nSIze > 1)
	{
		for (i = 1; i < nSIze; i++)
		{

			if (dateCreation.EqualTo2(CurrentDate, FacilityList[i - 1].FacilityDate, isMonthly))
			{
				CurrentFacilityData = FacilityList[i - 1];
				//std::cout << "GAS CAPACITY: " << CurrentFacilityData.Gas_Capacity << std::endl;
				//std::cout << "LIQUID CAPACITY: " << CurrentFacilityData.Liquid_Capacity << std::endl;

				return;
			}

			if (dateCreation.EqualTo2(CurrentDate, FacilityList[i].FacilityDate, isMonthly))
			{
				CurrentFacilityData = FacilityList[i];
				//std::cout << "GAS CAPACITY: " << CurrentFacilityData.Gas_Capacity << std::endl;
				//std::cout << "LIQUID CAPACITY: " << CurrentFacilityData.Liquid_Capacity << std::endl;
				return;
			}

			if (dateCreation.IsMaximumDate(CurrentDate, FacilityList[i - 1].FacilityDate) && dateCreation.IsMinimumDate(CurrentDate, FacilityList[i].FacilityDate))
			{
				CurrentFacilityData = FacilityList[i - 1];
				//std::cout << "GAS CAPACITY: " << CurrentFacilityData.Gas_Capacity << std::endl;
				//std::cout << "LIQUID CAPACITY: " << CurrentFacilityData.Liquid_Capacity << std::endl;
				return;
			}
		}
	}

	if (dateCreation.IsMaximumDate(CurrentDate, FacilityList[nSIze - 1].FacilityDate))
	{
		CurrentFacilityData = FacilityList[nSIze - 1];
		//std::cout << "GAS CAPACITY: " << CurrentFacilityData.Gas_Capacity << std::endl;
		//std::cout << "LIQUID CAPACITY: " << CurrentFacilityData.Liquid_Capacity << std::endl;
		return;
	}
}



void CalculateDeckVariables::optimize_constraint_no_prioritization(vector<ForecastResult> &onStreamWells,
	vector<double> &cutbacks2, Priotization &priotizationFacility)
{

	int k = 0;
	allWellsLiquidCapacity = 0;
	allWellsGasCapacity = 0;
	double allWellsLiquidCapacity3 = 0;
	double allWellsGasCapacity3 = 0;
	int nwells = onStreamWells.size();
	int nFacility = 1;
	int constraints = 2 * nFacility + nwells;
	int variables = nwells;
	string logger;

	cutbacks2.clear();
	for (k = 0; k < nwells; k++)
	{
		onStreamWells[k].wellIndex = k;
		cutbacks2.push_back(0);
	}

	vector<vector<double>> consMatrx;
	vector<double> funcVars;
	vector<string> signs;
	vector<double> freeVars;
	double zero = 0.0001;

	for (int i = 0; i < variables; i++)
	{
		if (priotizationFacility.targetFluid == oil)
		{
			if (onStreamWells[i].isOilTerminated == true)
			{
				funcVars.push_back(onStreamWells[i].Oil_rate_NotTerminated);
			}
			else
			{
				funcVars.push_back(onStreamWells[i].Oil_rate);
			}
		}
		if (priotizationFacility.targetFluid == gas)
		{
			if (onStreamWells[i].isGasTerminated == true)
			{
				funcVars.push_back(onStreamWells[i].Gas_Rate_NotTerminated);
			}
			else
			{
				funcVars.push_back(onStreamWells[i].Gas_Rate);
			}
		}
		if (priotizationFacility.targetFluid == liquid)
		{
			if (onStreamWells[i].isOilTerminated == true)
			{
				funcVars.push_back(onStreamWells[i].Oil_rate_NotTerminated + onStreamWells[i].Water_Rate);
			}
			else
			{
				funcVars.push_back(onStreamWells[i].Oil_rate + onStreamWells[i].Water_Rate);
			}
		}
		if (priotizationFacility.targetFluid == water)
		{
			funcVars.push_back(onStreamWells[i].Water_Rate);
		}
	}

	//First Row
	vector<double> consMatrxRow1;
	for (int i = 0; i < variables + 2; i++)
	{
		if (i == variables + 1)
		{
			freeVars.push_back(Gas_Capacity);
		}
		else if (i == variables)
		{
			signs.push_back("<=");
		}
		else
		{
			if (onStreamWells[i].isGasTerminated == true)
			{
				consMatrxRow1.push_back(onStreamWells[i].Gas_Rate_NotTerminated);
				//consMatrxRow1.push_back(zero);
			}
			else
			{
				consMatrxRow1.push_back(onStreamWells[i].Gas_Rate);
			}
		}
	}

	consMatrx.push_back(consMatrxRow1);

	//Second Row
	vector<double> consMatrxRow2;
	for (int i = 0; i < variables + 2; i++)
	{
		if (i == variables + 1)
		{
			freeVars.push_back(Liquid_Capacity);
		}
		else if (i == variables)
		{
			signs.push_back("<=");
		}

		else
		{
			if (onStreamWells[i].isOilTerminated == true)
			{
				consMatrxRow2.push_back(onStreamWells[i].Oil_rate_NotTerminated + onStreamWells[i].Water_Rate);
			}
			else
			{
				consMatrxRow2.push_back(onStreamWells[i].Oil_rate + onStreamWells[i].Water_Rate);
			}
		}
	}
	consMatrx.push_back(consMatrxRow2);

	//Third Row to Last Row
	for (int j = 2; j < constraints; j++)
	{
		vector<double> consMatrxRow_j;
		for (int i = 0; i < variables + 2; i++)
		{
			if (i == variables + 1)
			{
				freeVars.push_back(1.0);
			}
			else if (i == variables)
			{
				signs.push_back("<=");
			}
			else if (i == j - 2)
			{
				consMatrxRow_j.push_back(1.0);
			}
			else
			{
				consMatrxRow_j.push_back(0.0);
			}
		}
		consMatrx.push_back(consMatrxRow_j);
	}

	Problem2 p = Problem2(consMatrx, signs, freeVars, funcVars, 0, true);
	MainScreen mainScreen;
	mainScreen.Solve(p);

	//check objective function
	//double Qmax = 0;
	cutbacks2 = mainScreen.decisonVariables;
	for (int i = 0; i < nwells; i++)
	{

		if(cutbacks2[i] < 0){
			cutbacks2[i] = 0;
		}

		if(cutbacks2[i] > 1.09){
			cutbacks2[i] = 1.0;
		}

		if (onStreamWells[i].isOilTerminated == true)
		{
			allWellsLiquidCapacity3 = allWellsLiquidCapacity3 + 
			(onStreamWells[i].Oil_rate_NotTerminated + onStreamWells[i].Water_Rate) * cutbacks2[i];
		}
		else
		{
			allWellsLiquidCapacity3 = allWellsLiquidCapacity3 + (onStreamWells[i].Oil_rate +
			onStreamWells[i].Water_Rate) * cutbacks2[i];
		}

		if (onStreamWells[i].isGasTerminated == true)
		{
			allWellsGasCapacity3 = allWellsGasCapacity3 + (onStreamWells[i].Gas_Rate_NotTerminated * cutbacks2[i]);;
		}
		else
		{
			allWellsGasCapacity3 = allWellsGasCapacity3 + (onStreamWells[i].Gas_Rate * cutbacks2[i]);
		}

		if (static_cast<int>(allWellsGasCapacity3) > static_cast<int>(Gas_Capacity) ||
		static_cast<int>(allWellsLiquidCapacity3) > static_cast<int>(Liquid_Capacity))
		{
			cutbacks2[i] = 0;
			//break;
		}

		logger = logger + 
		"Gas_Rate = "  + to_string(onStreamWells[i].Gas_Rate) + " * " +
		"Liquid_Rate = "  + to_string(onStreamWells[i].Liquid_Rate) + " * "
		"cutbacks = "  + to_string(cutbacks2[i]) + " * ";

		
	}

	/* if(onStreamWells[0].Flow_station == "REO_GP5"){
		logger = logger + 
		"Gas_Capacity = "  + to_string(Gas_Capacity) + " * "
		"Liquid_Capacity = "  + to_string(Liquid_Capacity) + " * "
		"CurrentDate = " + to_string(CurrentDate.day) + "/" + to_string(CurrentDate.month) + "/" + to_string(CurrentDate.year) + "/" + "\n";
		std::cout << checker <<  logger;
	} */

	optimalSolution = mainScreen.optimalSolution;

	for (int i = 0; i < nwells; i++)
	{
		if (onStreamWells[i].isOilTerminated == true)
		{
			allWellsLiquidCapacity = allWellsLiquidCapacity + (onStreamWells[i].Oil_rate_NotTerminated + onStreamWells[i].Water_Rate) * cutbacks2[i];
		}
		else
		{
			allWellsLiquidCapacity = allWellsLiquidCapacity + (onStreamWells[i].Oil_rate + onStreamWells[i].Water_Rate) * cutbacks2[i];
		}

		if (onStreamWells[i].isGasTerminated == true)
		{
			allWellsGasCapacity = allWellsGasCapacity + (onStreamWells[i].Gas_Rate_NotTerminated * cutbacks2[i]);
		}
		else
		{
			allWellsGasCapacity = allWellsGasCapacity + (onStreamWells[i].Gas_Rate * cutbacks2[i]);
		}
	}

	if (static_cast<int>(allWellsGasCapacity) > static_cast<int>(Gas_Capacity) ||
		static_cast<int>(allWellsLiquidCapacity) > static_cast<int>(Liquid_Capacity))
	{
		string gasError = "";
		/* exportForecastResults.exportConstraintMatrix(consMatrx);
		exportForecastResults.exportFreeVariables(freeVars);
		exportForecastResults.exportFunctionVariables(funcVars);
		exportForecastResults.exportSolution(mainScreen.decisonVariables); */
	}
}


void CalculateDeckVariables::optimize_constraint_by_well(vector<ForecastResult> &onStreamWells,
														 vector<double> &cutbacks2, Priotization &priotizationFacility)
{

	int k = 0;
	allWellsLiquidCapacity = 0;
	allWellsGasCapacity = 0;
	double allWellsLiquidCapacity2 = 0;
	double allWellsGasCapacity2 = 0;
	double allWellsLiquidCapacity3 = 0;
	double allWellsGasCapacity3 = 0;
	int nwells = onStreamWells.size();
	int nFacility = 1;
	cutbacks2.clear();
	string logger = "";
	for (k = 0; k < nwells; k++)
	{
		onStreamWells[k].wellIndex = k;
		cutbacks2.push_back(0);
	}

	double Qf_gas_Total = Gas_Capacity;
	double Qf_liquid_Total = Liquid_Capacity;

	for (k = 0; k < priotizationFacility.prioritizationModel.ParameterNames.size(); k++)
	{

		vector<ForecastResult> onStreamWells2;
		vector<double> cutbacks3;
		double Qf_gas = 0;
		double Qf_liquid = 0;
		for (int i = 0; i < nwells; i++)
		{
			if (priotizationFacility.typeOfPrioritization == wellPrioritization)
			{
				if (onStreamWells[i].optimizationWeight2 == priotizationFacility.prioritizationModel.ParameterNames[k])
				{
					onStreamWells2.push_back(onStreamWells[i]);
				}
			}

			if (priotizationFacility.typeOfPrioritization == streamPrioritization)
			{
				if (onStreamWells[i].HyrocarbonStream == priotizationFacility.prioritizationModel.ParameterNames[k])
				{
					onStreamWells2.push_back(onStreamWells[i]);
				}
			}

			if (priotizationFacility.typeOfPrioritization == projectPrioritization)
			{
				if (onStreamWells[i].HyrocarbonStream == priotizationFacility.prioritizationModel.ParameterNames[k])
				{
					onStreamWells2.push_back(onStreamWells[i]);
				}
			}

			if (priotizationFacility.typeOfPrioritization == resourceClassPrioritization)
			{
				if (onStreamWells[i].resourceClass == priotizationFacility.prioritizationModel.ParameterNames[k])
				{
					onStreamWells2.push_back(onStreamWells[i]);
				}
			}
		}

		if (onStreamWells2.size() > 0)
		{

			if (priotizationFacility.prioritizationModel.ParameterNames[k].size() > 0)
			{
				int nwells2 = onStreamWells2.size();

				int constraints = 2 * nFacility + nwells2;
				int variables = nwells2;

				if (priotizationFacility.methodOfPrioritization == sequential)
				{
					Qf_gas = Qf_gas_Total;
					Qf_liquid = Qf_liquid_Total;
				}

				if (priotizationFacility.methodOfPrioritization == weighted)
				{
					Qf_gas = Gas_Capacity * priotizationFacility.prioritizationModel.ParameterWeights[k];
					Qf_liquid = Liquid_Capacity * priotizationFacility.prioritizationModel.ParameterWeights[k];
				}

				vector<vector<double>> consMatrx;
				vector<double> funcVars;
				vector<string> signs;
				vector<double> freeVars;
				double zero = 0.0001;
				logger = "";

				logger = logger + 
				"targetFluid = "  + priotizationFacility.targetFluid + " * ";

				for (int i = 0; i < variables; i++)
				{
					if (priotizationFacility.targetFluid == oil)
					{
						if (onStreamWells2[i].isOilTerminated == true)
						{
							funcVars.push_back(onStreamWells2[i].Oil_rate_NotTerminated);
						}
						else
						{
							funcVars.push_back(onStreamWells2[i].Oil_rate);
						}

						logger = logger + 
						"Oil_rate = "  + to_string(onStreamWells2[i].Oil_rate) + " * ";
					}
					if (priotizationFacility.targetFluid == gas)
					{
						if (onStreamWells2[i].isGasTerminated == true)
						{
							funcVars.push_back(onStreamWells2[i].Gas_Rate_NotTerminated);
						}
						else
						{
							funcVars.push_back(onStreamWells2[i].Gas_Rate);
						}
					}
					if (priotizationFacility.targetFluid == liquid)
					{
						if (onStreamWells2[i].isOilTerminated == true)
						{
							funcVars.push_back(onStreamWells2[i].Oil_rate_NotTerminated + onStreamWells2[i].Water_Rate);
						}
						else
						{
							funcVars.push_back(onStreamWells2[i].Oil_rate + onStreamWells2[i].Water_Rate);
						}
					}
					if (priotizationFacility.targetFluid == water)
					{
						funcVars.push_back(onStreamWells2[i].Water_Rate);
					}
				}

				//First Row
				vector<double> consMatrxRow1;
				for (int i = 0; i < variables + 2; i++)
				{
					if (i == variables + 1)
					{
						freeVars.push_back(Qf_gas);
					}
					else if (i == variables)
					{
						signs.push_back("<=");
					}
					else
					{
						if (onStreamWells2[i].isGasTerminated == true)
						{
							consMatrxRow1.push_back(onStreamWells2[i].Gas_Rate_NotTerminated);
							//consMatrxRow1.push_back(zero);
						}
						else
						{
							consMatrxRow1.push_back(onStreamWells2[i].Gas_Rate);
						}

						logger = logger + 
						"Gas_Rate = "  + to_string(onStreamWells2[i].Gas_Rate) + " * ";
					}
				}

				consMatrx.push_back(consMatrxRow1);

				//Second Row
				vector<double> consMatrxRow2;
				for (int i = 0; i < variables + 2; i++)
				{
					if (i == variables + 1)
					{
						freeVars.push_back(Qf_liquid);
					}
					else if (i == variables)
					{
						signs.push_back("<=");
					}

					else
					{
						if (onStreamWells2[i].isOilTerminated == true)
						{
							consMatrxRow2.push_back(onStreamWells2[i].Oil_rate_NotTerminated + onStreamWells2[i].Water_Rate);
						}
						else
						{
							consMatrxRow2.push_back(onStreamWells2[i].Oil_rate + onStreamWells2[i].Water_Rate);
						}

						logger = logger + 
						"Liquid_rate = "  + to_string(onStreamWells2[i].Oil_rate + onStreamWells2[i].Water_Rate) + " * ";
					}
				}
				consMatrx.push_back(consMatrxRow2);

				//Third Row to Last Row
				for (int j = 2; j < constraints; j++)
				{
					vector<double> consMatrxRow_j;
					for (int i = 0; i < variables + 2; i++)
					{
						if (i == variables + 1)
						{
							freeVars.push_back(1.0);
						}
						else if (i == variables)
						{
							signs.push_back("<=");
						}
						else if (i == j - 2)
						{
							consMatrxRow_j.push_back(1.0);
						}
						else
						{
							consMatrxRow_j.push_back(0.0);
						}
					}
					consMatrx.push_back(consMatrxRow_j);
				}

				Problem2 p = Problem2(consMatrx, signs, freeVars, funcVars, 0, true);
				MainScreen mainScreen;
				mainScreen.Solve(p);

				//check objective function
				//double Qmax = 0;
				cutbacks3 = mainScreen.decisonVariables;
				for (int i = 0; i < nwells2; i++)
				{
					logger = logger + 
					"x"  + to_string(i+1) + " = " + to_string(cutbacks3[i]) + " * ";

					if(cutbacks3[i] < 0){
						cutbacks3[i] = 0;
					}

					if(cutbacks3[i] > 1.09){
						cutbacks3[i] = 1.0;
					}

					if (onStreamWells2[i].isOilTerminated == true)
					{
						allWellsLiquidCapacity3 = allWellsLiquidCapacity3 + (onStreamWells2[i].Oil_rate_NotTerminated + onStreamWells2[i].Water_Rate) * cutbacks3[i];
					}
					else
					{
						allWellsLiquidCapacity3 = allWellsLiquidCapacity3 + (onStreamWells2[i].Oil_rate + onStreamWells2[i].Water_Rate) * cutbacks3[i];
					}

					if (onStreamWells2[i].isGasTerminated == true)
					{
						allWellsGasCapacity3 = allWellsGasCapacity3 + (onStreamWells2[i].Gas_Rate_NotTerminated * cutbacks3[i]);;
					}
					else
					{
						allWellsGasCapacity3 = allWellsGasCapacity3 + (onStreamWells2[i].Gas_Rate * cutbacks3[i]);
					}

					if (static_cast<int>(allWellsGasCapacity3) > static_cast<int>(Gas_Capacity) ||
					static_cast<int>(allWellsLiquidCapacity3) > static_cast<int>(Liquid_Capacity))
					{
						cutbacks3[i] = 0;
						break;
					}
					cutbacks2[onStreamWells2[i].wellIndex] = cutbacks3[i];
				}

				logger = logger + 
				"GAS CAPACITY = "  + to_string(Qf_gas) + " * " +
				"LIQUID CAPACITY = "  + to_string(Qf_liquid) + "\n";

				/* if(onStreamWells2[0].Flow_station == "ABU_FS1"){
					std::cout << logger;
				} */

				optimalSolution = mainScreen.optimalSolution;

				allWellsLiquidCapacity2 = 0;
				allWellsGasCapacity2 = 0;
				for (int i = 0; i < nwells2; i++)
				{
					if (onStreamWells2[i].isOilTerminated == true)
					{
						allWellsLiquidCapacity = allWellsLiquidCapacity + (onStreamWells2[i].Oil_rate_NotTerminated + onStreamWells2[i].Water_Rate) * cutbacks3[i];
						allWellsLiquidCapacity2 = allWellsLiquidCapacity2 + (onStreamWells2[i].Oil_rate_NotTerminated + onStreamWells2[i].Water_Rate) * cutbacks3[i];
					}
					else
					{
						allWellsLiquidCapacity2 = allWellsLiquidCapacity2 + (onStreamWells2[i].Oil_rate + onStreamWells2[i].Water_Rate) * cutbacks3[i];
					}

					if (onStreamWells2[i].isGasTerminated == true)
					{
						allWellsGasCapacity = allWellsGasCapacity + (onStreamWells2[i].Gas_Rate_NotTerminated * cutbacks3[i]);
						allWellsGasCapacity2 = allWellsGasCapacity2 + (onStreamWells2[i].Gas_Rate_NotTerminated * cutbacks3[i]);
					}
					else
					{
						allWellsGasCapacity = allWellsGasCapacity + (onStreamWells2[i].Gas_Rate * cutbacks3[i]);
						allWellsGasCapacity2 = allWellsGasCapacity2 + (onStreamWells2[i].Gas_Rate * cutbacks3[i]);
					}
				}

				if (static_cast<int>(allWellsGasCapacity) > static_cast<int>(Gas_Capacity) ||
					static_cast<int>(allWellsLiquidCapacity) > static_cast<int>(Liquid_Capacity))
				{
					string gasError = "";
					/* exportForecastResults.exportConstraintMatrix(consMatrx);
					exportForecastResults.exportFreeVariables(freeVars);
					exportForecastResults.exportFunctionVariables(funcVars);
					exportForecastResults.exportSolution(mainScreen.decisonVariables); */
					break;
				}

				if (priotizationFacility.methodOfPrioritization == sequential)
				{
					Qf_liquid_Total = Qf_liquid_Total - allWellsLiquidCapacity2;
					if (Qf_liquid_Total < 5)
					{
						Qf_liquid_Total = 0;
						break;
					}
					Qf_gas_Total = Qf_gas_Total - allWellsGasCapacity2;
					if (Qf_gas_Total < 5)
					{
						Qf_gas_Total = 0;
						break;
					}
				}
			}
		}
	}
}



void CalculateDeckVariables::optimize_by_stream_prioritization(vector<ForecastResult> &onStreamWells,
														 vector<double> &cutbacks2, Priotization &priotizationFacility)
{

	int k = 0;
	allWellsLiquidCapacity = 0;
	allWellsGasCapacity = 0;
	double allWellsLiquidCapacity2 = 0;
	double allWellsGasCapacity2 = 0;
	double allWellsLiquidCapacity3 = 0;
	double allWellsGasCapacity3 = 0;
	int nwells = onStreamWells.size();
	vector<double> uniqueFluidFractionIndicators = GetUniqueFluidFractionIndicators(onStreamWells);
	int nFacility = 1;
	cutbacks2.clear();
	string logger = "";
	for (k = 0; k < nwells; k++)
	{
		onStreamWells[k].wellIndex = k;
		cutbacks2.push_back(0);
	}

	double Qf_gas_Total = Gas_Capacity;
	double Qf_liquid_Total = Liquid_Capacity;

	for (k = 0; k < uniqueFluidFractionIndicators.size(); k++)
	{

		vector<ForecastResult> onStreamWells2;
		vector<double> cutbacks3;
		double Qf_gas = 0;
		double Qf_liquid = 0;
		for (int i = 0; i < nwells; i++)
		{

			if (priotizationFacility.typeOfPrioritization == streamPrioritization)
			{
				if (abs(onStreamWells[i].fluidFraction - uniqueFluidFractionIndicators[k]) < 0.00001)
				{
					onStreamWells2.push_back(onStreamWells[i]);
				}
			}
		}

		if (onStreamWells2.size() > 0)
		{

			if (uniqueFluidFractionIndicators.size() > 0)
			{
				int nwells2 = onStreamWells2.size();

				int constraints = 2 * nFacility + nwells2;
				int variables = nwells2;

				Qf_gas = Qf_gas_Total;
				Qf_liquid = Qf_liquid_Total;

				vector<vector<double>> consMatrx;
				vector<double> funcVars;
				vector<string> signs;
				vector<double> freeVars;
				double zero = 0.0001;
				logger = "";

				logger = logger + 
				"targetFluid = "  + priotizationFacility.targetFluid + " * ";

				for (int i = 0; i < variables; i++)
				{
					if (priotizationFacility.targetFluid == oil)
					{
						if (onStreamWells2[i].isOilTerminated == true)
						{
							funcVars.push_back(onStreamWells2[i].Oil_rate_NotTerminated);
						}
						else
						{
							funcVars.push_back(onStreamWells2[i].Oil_rate);
						}

						logger = logger + 
						"Oil_rate = "  + to_string(onStreamWells2[i].Oil_rate) + " * ";
					}
					if (priotizationFacility.targetFluid == gas)
					{
						if (onStreamWells2[i].isGasTerminated == true)
						{
							funcVars.push_back(onStreamWells2[i].Gas_Rate_NotTerminated);
						}
						else
						{
							funcVars.push_back(onStreamWells2[i].Gas_Rate);
						}
					}
					if (priotizationFacility.targetFluid == liquid)
					{
						if (onStreamWells2[i].isOilTerminated == true)
						{
							funcVars.push_back(onStreamWells2[i].Oil_rate_NotTerminated + onStreamWells2[i].Water_Rate);
						}
						else
						{
							funcVars.push_back(onStreamWells2[i].Oil_rate + onStreamWells2[i].Water_Rate);
						}
					}
					if (priotizationFacility.targetFluid == water)
					{
						funcVars.push_back(onStreamWells2[i].Water_Rate);
					}
				}

				//First Row
				vector<double> consMatrxRow1;
				for (int i = 0; i < variables + 2; i++)
				{
					if (i == variables + 1)
					{
						freeVars.push_back(Qf_gas);
					}
					else if (i == variables)
					{
						signs.push_back("<=");
					}
					else
					{
						if (onStreamWells2[i].isGasTerminated == true)
						{
							consMatrxRow1.push_back(onStreamWells2[i].Gas_Rate_NotTerminated);
							//consMatrxRow1.push_back(zero);
						}
						else
						{
							consMatrxRow1.push_back(onStreamWells2[i].Gas_Rate);
						}

						logger = logger + 
						"Gas_Rate = "  + to_string(onStreamWells2[i].Gas_Rate) + " * ";
					}
				}

				consMatrx.push_back(consMatrxRow1);

				//Second Row
				vector<double> consMatrxRow2;
				for (int i = 0; i < variables + 2; i++)
				{
					if (i == variables + 1)
					{
						freeVars.push_back(Qf_liquid);
					}
					else if (i == variables)
					{
						signs.push_back("<=");
					}

					else
					{
						if (onStreamWells2[i].isOilTerminated == true)
						{
							consMatrxRow2.push_back(onStreamWells2[i].Oil_rate_NotTerminated + onStreamWells2[i].Water_Rate);
						}
						else
						{
							consMatrxRow2.push_back(onStreamWells2[i].Oil_rate + onStreamWells2[i].Water_Rate);
						}

						logger = logger + 
						"Liquid_rate = "  + to_string(onStreamWells2[i].Oil_rate + onStreamWells2[i].Water_Rate) + " * ";
					}
				}
				consMatrx.push_back(consMatrxRow2);

				//Third Row to Last Row
				for (int j = 2; j < constraints; j++)
				{
					vector<double> consMatrxRow_j;
					for (int i = 0; i < variables + 2; i++)
					{
						if (i == variables + 1)
						{
							freeVars.push_back(1.0);
						}
						else if (i == variables)
						{
							signs.push_back("<=");
						}
						else if (i == j - 2)
						{
							consMatrxRow_j.push_back(1.0);
						}
						else
						{
							consMatrxRow_j.push_back(0.0);
						}
					}
					consMatrx.push_back(consMatrxRow_j);
				}

				Problem2 p = Problem2(consMatrx, signs, freeVars, funcVars, 0, true);
				MainScreen mainScreen;
				mainScreen.Solve(p);

				//check objective function
				//double Qmax = 0;
				cutbacks3 = mainScreen.decisonVariables;
				for (int i = 0; i < nwells2; i++)
				{
					logger = logger + 
					"x"  + to_string(i+1) + " = " + to_string(cutbacks3[i]) + " * ";

					if(cutbacks3[i] < 0){
						cutbacks3[i] = 0;
					}

					if(cutbacks3[i] > 1.09){
						cutbacks3[i] = 1.0;
					}

					if (onStreamWells2[i].isOilTerminated == true)
					{
						allWellsLiquidCapacity3 = allWellsLiquidCapacity3 + (onStreamWells2[i].Oil_rate_NotTerminated + onStreamWells2[i].Water_Rate) * cutbacks3[i];
					}
					else
					{
						allWellsLiquidCapacity3 = allWellsLiquidCapacity3 + (onStreamWells2[i].Oil_rate + onStreamWells2[i].Water_Rate) * cutbacks3[i];
					}

					if (onStreamWells2[i].isGasTerminated == true)
					{
						allWellsGasCapacity3 = allWellsGasCapacity3 + (onStreamWells2[i].Gas_Rate_NotTerminated * cutbacks3[i]);;
					}
					else
					{
						allWellsGasCapacity3 = allWellsGasCapacity3 + (onStreamWells2[i].Gas_Rate * cutbacks3[i]);
					}

					if (static_cast<int>(allWellsGasCapacity3) > static_cast<int>(Gas_Capacity) ||
					static_cast<int>(allWellsLiquidCapacity3) > static_cast<int>(Liquid_Capacity))
					{
						cutbacks3[i] = 0;
						break;
					}
					cutbacks2[onStreamWells2[i].wellIndex] = cutbacks3[i];
				}

				logger = logger + 
				"GAS CAPACITY = "  + to_string(Qf_gas) + " * " +
				"LIQUID CAPACITY = "  + to_string(Qf_liquid) + "\n";

				/* if(onStreamWells2[0].Flow_station == "ABU_FS1"){
					std::cout << logger;
				} */

				optimalSolution = mainScreen.optimalSolution;

				allWellsLiquidCapacity2 = 0;
				allWellsGasCapacity2 = 0;
				for (int i = 0; i < nwells2; i++)
				{
					if (onStreamWells2[i].isOilTerminated == true)
					{
						allWellsLiquidCapacity = allWellsLiquidCapacity + (onStreamWells2[i].Oil_rate_NotTerminated + onStreamWells2[i].Water_Rate) * cutbacks3[i];
						allWellsLiquidCapacity2 = allWellsLiquidCapacity2 + (onStreamWells2[i].Oil_rate_NotTerminated + onStreamWells2[i].Water_Rate) * cutbacks3[i];
					}
					else
					{
						allWellsLiquidCapacity2 = allWellsLiquidCapacity2 + (onStreamWells2[i].Oil_rate + onStreamWells2[i].Water_Rate) * cutbacks3[i];
					}

					if (onStreamWells2[i].isGasTerminated == true)
					{
						allWellsGasCapacity = allWellsGasCapacity + (onStreamWells2[i].Gas_Rate_NotTerminated * cutbacks3[i]);
						allWellsGasCapacity2 = allWellsGasCapacity2 + (onStreamWells2[i].Gas_Rate_NotTerminated * cutbacks3[i]);
					}
					else
					{
						allWellsGasCapacity = allWellsGasCapacity + (onStreamWells2[i].Gas_Rate * cutbacks3[i]);
						allWellsGasCapacity2 = allWellsGasCapacity2 + (onStreamWells2[i].Gas_Rate * cutbacks3[i]);
					}
				}

				if (static_cast<int>(allWellsGasCapacity) > static_cast<int>(Gas_Capacity) ||
					static_cast<int>(allWellsLiquidCapacity) > static_cast<int>(Liquid_Capacity))
				{
					string gasError = "";
					/* exportForecastResults.exportConstraintMatrix(consMatrx);
					exportForecastResults.exportFreeVariables(freeVars);
					exportForecastResults.exportFunctionVariables(funcVars);
					exportForecastResults.exportSolution(mainScreen.decisonVariables); */
					break;
				}

				if (priotizationFacility.methodOfPrioritization == sequential)
				{
					Qf_liquid_Total = Qf_liquid_Total - allWellsLiquidCapacity2;
					if (Qf_liquid_Total < 5)
					{
						Qf_liquid_Total = 0;
						break;
					}
					Qf_gas_Total = Qf_gas_Total - allWellsGasCapacity2;
					if (Qf_gas_Total < 5)
					{
						Qf_gas_Total = 0;
						break;
					}
				}
			}
		}
	}
}


void CalculateDeckVariables::optimize_olderNode_children(vector<Node> &nodes, int &nodeIndex,
														 vector<int> &actualChildrenNodesIndicies, Priotization &priotizationNode)
{
	int k = 0;
	allWellsLiquidCapacity = 0;
	allWellsGasCapacity = 0;
	int nwells = actualChildrenNodesIndicies.size();
	vector<int> actualChildrenNodesIndicies2;
	int nFacility = 1;

	double Qf_gas_Total = Gas_Capacity;
	double Qf_liquid_Total = Liquid_Capacity;
	int constraints = nwells;
	//int constraints = 2*nFacility + nwells;
	int LiquidGasConstraintCount = 0;
	if (Gas_Capacity > 0)
	{
		constraints = constraints + 1;
		LiquidGasConstraintCount = LiquidGasConstraintCount + 1;
		isGasFlow = true;
	}
	else
	{
		constraints = constraints + 1;
		LiquidGasConstraintCount = LiquidGasConstraintCount + 1;
		isGasFlow = false;
	}
	int variables = nwells;
	//Get actual parent cal variables
	FacilityOiProduced = 0;
	FacilityWaterProduced = 0;
	FacilityGasProduced = 0;
	FacilityAGProduced = 0;
	FacilityNAGProduced = 0;
	FacilityCondensateProduced = 0;
	FacilityLiquidProduced = 0;

	for (k = 0; k < priotizationNode.prioritizationModel.ParameterNames.size(); k++)
	{

		vector<FacilityStructExternal> onStreamWells2;
		vector<double> cutbacks3;
		double Qf_gas = 0;
		double Qf_liquid = 0;
		actualChildrenNodesIndicies2.clear();
		for (int i = 0; i < nwells; i++)
		{

			if (priotizationNode.typeOfPrioritization == streamPrioritization)
			{
				if (nodes[nodeIndex].priotizations[actualChildrenNodesIndicies[i]].targetFluid ==
					priotizationNode.prioritizationModel.ParameterNames[k])
				{
					onStreamWells2.push_back(nodes[nodeIndex].equipmentDataInEquipementConnections[actualChildrenNodesIndicies[i]]);
					actualChildrenNodesIndicies2.push_back(actualChildrenNodesIndicies[i]);
				}
			}
		}

		if (onStreamWells2.size() > 0)
		{
			if (priotizationNode.prioritizationModel.ParameterNames[k].size() > 0)
			{
				int nwells2 = onStreamWells2.size();

				int constraints = 1 + nwells2;
				int variables = nwells2;

				if (priotizationNode.methodOfPrioritization == sequential)
				{
					Qf_gas = Qf_gas_Total;
					Qf_liquid = Qf_liquid_Total;
				}

				if (priotizationNode.methodOfPrioritization == weighted)
				{
					Qf_gas = Gas_Capacity * priotizationNode.prioritizationModel.ParameterWeights[k];
					Qf_liquid = Liquid_Capacity * priotizationNode.prioritizationModel.ParameterWeights[k];
				}

				vector<vector<double>> consMatrx;
				vector<double> funcVars;
				vector<string> signs;
				vector<double> freeVars;
				double zero = 0.0001;

				for (int i = 0; i < variables; i++)
				{
					if (priotizationNode.targetFluid == oil)
					{
						funcVars.push_back(onStreamWells2[i].FacilityOiProduced);
					}

					if (priotizationNode.targetFluid == condensate)
					{
						funcVars.push_back(onStreamWells2[i].FacilityComdensateProduced);
					}
					if (priotizationNode.targetFluid == gas)
					{
						funcVars.push_back(onStreamWells2[i].FacilityGasProduced);
					}

					if (priotizationNode.targetFluid == ag)
					{
						funcVars.push_back(onStreamWells2[i].FacilityAGProduced);
					}

					if (priotizationNode.targetFluid == nag)
					{
						funcVars.push_back(onStreamWells2[i].FacilityNAGProduced);
					}
					if (priotizationNode.targetFluid == liquid)
					{
						funcVars.push_back(onStreamWells2[i].FacilityLiquidProduced);
					}
					if (priotizationNode.targetFluid == water)
					{
						funcVars.push_back(onStreamWells2[i].FacilityWaterProduced);
					}
				}

				//First Row
				if (isGasFlow == true)
				{
					vector<double> consMatrxRow1;
					for (int i = 0; i < variables + 2; i++)
					{

						if (i < variables)
						{
							consMatrxRow1.push_back(onStreamWells2[i].FacilityGasProduced);
						}
						else if (i == variables)
						{
							signs.push_back("<=");
						}
						else
						{
							freeVars.push_back(Qf_gas);
						}
					}
					consMatrx.push_back(consMatrxRow1);
				}

				if (isGasFlow == false)
				{
					//Second Row
					vector<double> consMatrxRow2;
					for (int i = 0; i < variables + 2; i++)
					{
						if (i < variables)
						{
							double qL = onStreamWells2[i].FacilityOiProduced; // +
							consMatrxRow2.push_back(qL);
						}
						else if (i == variables)
						{
							signs.push_back("<=");
						}
						else
						{
							freeVars.push_back(Qf_liquid);
						}
					}
					consMatrx.push_back(consMatrxRow2);
				}

				//Third Row to Last Row
				for (int j = LiquidGasConstraintCount; j < constraints; j++)
				{
					vector<double> consMatrxRow_j;
					for (int i = 0; i < variables + 2; i++)
					{
						if (i < variables)
						{
							if (i == j - LiquidGasConstraintCount)
							{
								consMatrxRow_j.push_back(1.0);
							}
							else
							{
								consMatrxRow_j.push_back(0.0);
							}
						}
						else if (i == variables)
						{
							signs.push_back("<=");
						}
						else
						{
							freeVars.push_back(1.0);
						}
					}

					consMatrx.push_back(consMatrxRow_j);
				}

				Problem2 p = Problem2(consMatrx, signs, freeVars, funcVars, 0, true);
				MainScreen mainScreen;
				try
				{
					mainScreen.Solve(p);
				}
				catch (const std::exception &e)
				{
					mainScreen.decisonVariables.clear();
					for (int i = 0; i < variables; i++)
					{
						mainScreen.decisonVariables.push_back(1.0);
					}
					std::cout << e.what() << std::endl;
				}

				for (int i = 0; i < variables; i++)
				{
					
					if(mainScreen.decisonVariables[i] < 0){
						mainScreen.decisonVariables[i] = 0;
					}

					if(mainScreen.decisonVariables[i] > 1.0){
						mainScreen.decisonVariables[i] = 1.0;
					}

					nodes[nodeIndex].equipmentDataInEquipementConnections[actualChildrenNodesIndicies2[i]].cutBack = mainScreen.decisonVariables[i];
				}

				for (int i = 0; i < variables; i++)
				{
					FacilityOiProduced = FacilityOiProduced + (nodes[nodeIndex].equipmentDataInEquipementConnections[actualChildrenNodesIndicies2[i]].FacilityOiProduced *
															   nodes[nodeIndex].equipmentDataInEquipementConnections[actualChildrenNodesIndicies2[i]].cutBack);
					FacilityWaterProduced = 0;
					FacilityLiquidProduced = FacilityOiProduced;
					FacilityGasProduced = FacilityGasProduced + (nodes[nodeIndex].equipmentDataInEquipementConnections[actualChildrenNodesIndicies2[i]].FacilityGasProduced *
																 nodes[nodeIndex].equipmentDataInEquipementConnections[actualChildrenNodesIndicies2[i]].cutBack);
					FacilityAGProduced = FacilityAGProduced + (nodes[nodeIndex].equipmentDataInEquipementConnections[actualChildrenNodesIndicies2[i]].FacilityAGProduced *
															   nodes[nodeIndex].equipmentDataInEquipementConnections[actualChildrenNodesIndicies2[i]].cutBack);
					FacilityNAGProduced = FacilityNAGProduced + (nodes[nodeIndex].equipmentDataInEquipementConnections[actualChildrenNodesIndicies2[i]].FacilityNAGProduced *
																 nodes[nodeIndex].equipmentDataInEquipementConnections[actualChildrenNodesIndicies2[i]].cutBack);
					FacilityCondensateProduced = FacilityCondensateProduced + (nodes[nodeIndex].equipmentDataInEquipementConnections[actualChildrenNodesIndicies2[i]].FacilityComdensateProduced *
																			   nodes[nodeIndex].equipmentDataInEquipementConnections[actualChildrenNodesIndicies2[i]].cutBack);
					if (FacilityOiProduced < 0.0000000000000000000001)
					{
						FacilityOiProduced = 0;
					}
					if (FacilityGasProduced < 0.0000000000000000000001)
					{
						FacilityGasProduced = 0;
					}
					if (FacilityNAGProduced < 0.0000000000000000000001)
					{
						FacilityNAGProduced = 0;
					}
					if (FacilityAGProduced < 0.0000000000000000000001)
					{
						FacilityAGProduced = 0;
					}
				}

				//Adjust optimized result with cutbacks

				if (isGasFlow == true)
				{
					if (static_cast<int>(FacilityGasProduced) > static_cast<int>(Gas_Capacity))
					{
						if (Gas_Capacity > 0)
						{
							string gasError = "";
							/* exportForecastResults.exportConstraintMatrix(consMatrx);
							exportForecastResults.exportFreeVariables(freeVars);
							exportForecastResults.exportFunctionVariables(funcVars);
							exportForecastResults.exportSolution(mainScreen.decisonVariables); */
						}
					}
					if (priotizationNode.methodOfPrioritization == sequential)
					{
						Qf_gas_Total = Qf_gas_Total - FacilityGasProduced;
						if (Qf_gas_Total < 5)
						{
							Qf_gas_Total = 0;
							break;
						}
					}
				}
				else
				{
					if (static_cast<int>(FacilityLiquidProduced) > static_cast<int>(Liquid_Capacity))
					{
						if (Liquid_Capacity > 0)
						{
							string liquidError = "";
							/* exportForecastResults.exportConstraintMatrix(consMatrx);
							exportForecastResults.exportFreeVariables(freeVars);
							exportForecastResults.exportFunctionVariables(funcVars);
							exportForecastResults.exportSolution(mainScreen.decisonVariables); */
						}
					}
					if (priotizationNode.methodOfPrioritization == sequential)
					{
						Qf_liquid_Total = Qf_liquid_Total - FacilityLiquidProduced;
						if (Qf_liquid_Total < 5)
						{
							Qf_liquid_Total = 0;
							break;
						}
					}
				}
			}
		}
	}
}

void CalculateDeckVariables::SetCutRatesBackValues(int &facilityCounter, int &timeStepCounter, double &onStreamWellCutBack,
	int &scenario, InputDeckStruct &deck, int &actualWellIndex)
{
	bool isAfetrOptimization = true;
	int i = actualWellIndex;
	int cutbackSizex = cutbacks.size() - 1;
	double cumXProd = 0;
	string logger = "";

	checker= " SetCutRatesBackValues ";
	

	if (results[timeStepCounter][facilityCounter][i].IsFlowing == true)
	{
		if (deck.Module == results[timeStepCounter][facilityCounter][i].ModuleName)
		{
			results[timeStepCounter][facilityCounter][i].CutBack = onStreamWellCutBack;

			if (deck.Hydrocarbon_Stream == oil)
			{
				results[timeStepCounter][facilityCounter][i].Liquid_Rate =
					results[timeStepCounter][facilityCounter][i].Liquid_Rate * results[timeStepCounter][facilityCounter][i].CutBack;

				results[timeStepCounter][facilityCounter][i].Liquid_rate_NotTerminated =
					results[timeStepCounter][facilityCounter][i].Liquid_rate_NotTerminated * results[timeStepCounter][facilityCounter][i].CutBack;
			}
			else
			{

				/* logger = logger +  
				"Gas_Rate After Optimization = " + to_string(results[timeStepCounter][facilityCounter][i].Gas_Rate) + " * " +
				"onStreamWellCutBack = " + to_string(onStreamWellCutBack) + "\n";

				if(deck.Module == "FO12U60T_FO12 U60X_P03"){
					std::cout << checker << logger;
				} */

				results[timeStepCounter][facilityCounter][i].Gas_Rate =
					results[timeStepCounter][facilityCounter][i].Gas_Rate * results[timeStepCounter][facilityCounter][i].CutBack;

				results[timeStepCounter][facilityCounter][i].Gas_Rate_NotTerminated =
					results[timeStepCounter][facilityCounter][i].Gas_Rate_NotTerminated * results[timeStepCounter][facilityCounter][i].CutBack;
			}

			ForecastResult forecastResult_old;
			ForecastResult forecastResult;

			if (timeStepCounter == 0)
			{
				forecastResult_old = results[timeStepCounter][facilityCounter][i];
				forecastResult = results[timeStepCounter][facilityCounter][i];
			}
			else
			{

				if (results[timeStepCounter][facilityCounter].size() > results[timeStepCounter - 1][facilityCounter].size() &&
					i >= results[timeStepCounter - 1][facilityCounter].size())
				{
					tuple<bool, int> checkIndex = CheckWellFacilityAndGetIndex(WellFacilityDataList, deck.Module);
					int Idx = get<1>(checkIndex);
					if (get<0>(checkIndex) == true)
					{

						forecastResult_old = results[timeStepCounter][facilityCounter][i];
						forecastResult = results[timeStepCounter][facilityCounter][i];
						if (deck.Hydrocarbon_Stream == oil)
						{
							forecastResult_old.Liquid_Rate = WellFacilityDataList[Idx].Rate;
							forecastResult.Liquid_Rate = WellFacilityDataList[Idx].Rate;
							forecastResult.URo = WellFacilityDataList[Idx].UR;
							forecastResult.Cum_Liquid_Prod = WellFacilityDataList[Idx].CumProd;
						}
						else
						{
							forecastResult_old.Gas_Rate = WellFacilityDataList[Idx].Rate;
							forecastResult.Gas_Rate = WellFacilityDataList[Idx].Rate;
							forecastResult.URg = WellFacilityDataList[Idx].UR;
							forecastResult.Cum_Gas_Prod = WellFacilityDataList[Idx].CumProd;
						}
					}
				}
				else
				{
					forecastResult_old = results[timeStepCounter - 1][facilityCounter][i];
					forecastResult = results[timeStepCounter][facilityCounter][i];
				}
			}


			GetVariables(scenario, deck, forecastResult, forecastResult_old, cumXProd, isAfetrOptimization);
			if (deck.Hydrocarbon_Stream == oil)
			{
				cumXProd = results[timeStepCounter][facilityCounter][i].Oil_rate;
			}
			else{
				cumXProd = results[timeStepCounter][facilityCounter][i].Gas_Rate;
			}

			if (forecastResult.hydrocarbonType == ag)
			{
				FacilityAGProduced = FacilityAGProduced + forecastResult.Gas_Rate;
			}
			if (forecastResult.hydrocarbonType == nag)
			{
				FacilityNAGProduced = FacilityNAGProduced + forecastResult.Gas_Rate;
			}

			
			FacilityOiProduced = FacilityOiProduced + forecastResult.Oil_rate;
			FacilityWaterProduced = FacilityWaterProduced + forecastResult.Water_Rate;
			FacilityGasProduced = FacilityGasProduced + forecastResult.Gas_Rate;
			FacilityLiquidProduced = FacilityLiquidProduced + (forecastResult.Oil_rate + forecastResult.Water_Rate);
			results[timeStepCounter][facilityCounter][i] = forecastResult;
		}
	}
}

void CalculateDeckVariables::SetCutRatesBackValues(int &facilityCounter, int &timeStepCounter,
												   int &scenario, InputDeckStruct &deck, int &actualWellIndex,
												   double &gasCutBack, double &liquidCutBack)
{
	bool isAfetrOptimization = true;
	int i = actualWellIndex;
	int cutbackSizex = cutbacks.size() - 1;
	double cumXProd = 0;
	checker= " SetCutRatesBackValues -2 ";
	string logger = "";

	//GetCurrentFacilityData();

	
	
	if (results[timeStepCounter][facilityCounter][i].IsFlowing == true)
	{
		if (deck.Module == results[timeStepCounter][facilityCounter][i].ModuleName)
		{
			results[timeStepCounter][facilityCounter][i].Oil_rate =
				results[timeStepCounter][facilityCounter][i].Oil_rate * liquidCutBack;
			results[timeStepCounter][facilityCounter][i].Water_Rate =
				results[timeStepCounter][facilityCounter][i].Water_Rate * liquidCutBack;
			results[timeStepCounter][facilityCounter][i].Liquid_Rate =
				results[timeStepCounter][facilityCounter][i].Liquid_Rate * liquidCutBack;
			results[timeStepCounter][facilityCounter][i].Oil_rate_NotTerminated =
				results[timeStepCounter][facilityCounter][i].Oil_rate_NotTerminated * liquidCutBack;
			results[timeStepCounter][facilityCounter][i].Gas_Rate =
				results[timeStepCounter][facilityCounter][i].Gas_Rate * gasCutBack;
			results[timeStepCounter][facilityCounter][i].Gas_Rate_NotTerminated =
				results[timeStepCounter][facilityCounter][i].Gas_Rate_NotTerminated * gasCutBack;

			ForecastResult forecastResult_old;
			ForecastResult forecastResult;

			if (timeStepCounter == 0)
			{
				forecastResult_old = results[timeStepCounter][facilityCounter][i];
				forecastResult = results[timeStepCounter][facilityCounter][i];
				GetVariables(scenario, deck, forecastResult, forecastResult_old, cumXProd, isAfetrOptimization);
				results[timeStepCounter][facilityCounter][i] = forecastResult;
			}
			else
			{

				if (results[timeStepCounter][facilityCounter].size() > results[timeStepCounter - 1][facilityCounter].size() &&
					i >= results[timeStepCounter - 1][facilityCounter].size())
				{
					tuple<bool, int> checkIndex = CheckWellFacilityAndGetIndex(WellFacilityDataList, deck.Module);
					int Idx = get<1>(checkIndex);
					if (get<0>(checkIndex) == true)
					{

						forecastResult_old = results[timeStepCounter][facilityCounter][i];
						forecastResult = results[timeStepCounter][facilityCounter][i];
						if (deck.Hydrocarbon_Stream == oil)
						{
							forecastResult_old.Liquid_Rate = WellFacilityDataList[Idx].Rate;
							forecastResult.Liquid_Rate = WellFacilityDataList[Idx].Rate;
							forecastResult.URo = WellFacilityDataList[Idx].UR;
							forecastResult.Cum_Liquid_Prod = WellFacilityDataList[Idx].CumProd;
						}
						else
						{
							forecastResult_old.Gas_Rate = WellFacilityDataList[Idx].Rate;
							forecastResult.Gas_Rate = WellFacilityDataList[Idx].Rate;
							forecastResult.URg = WellFacilityDataList[Idx].UR;
							forecastResult.Cum_Gas_Prod = WellFacilityDataList[Idx].CumProd;
						}
					}
				}
				else
				{
					forecastResult_old = results[timeStepCounter - 1][facilityCounter][i];
					forecastResult = results[timeStepCounter][facilityCounter][i];
				}
			}

			GetVariables(scenario, deck, forecastResult, forecastResult_old, cumXProd, isAfetrOptimization);
			results[timeStepCounter][facilityCounter][i] = forecastResult;

			/* logger = logger +  
				"Gas_Rate  = " + to_string(results[timeStepCounter][facilityCounter][i].Gas_Rate) + "\n";

				if(deck.Module == "FO12U60T_FO12 U60X_P03"){
					std::cout << logger;
				} */
		}
	}
}

void CalculateDeckVariables::GetActiveRate(int &scenario,
										   InputDeckStruct &deck,
										   ForecastResult &forecastResult,
										   ForecastResult &forecastResult_old)
{

	int method = deck.DeclineMethod;
	double cumprod = 0, MM = 1000000.0, plateauCumProd = 0, cumprodNoPlateau = 0;
	forecastResult.isPlateau = false;
	string logger = "";


	if (deck.Hydrocarbon_Stream == oil)
	{
		double initialLiquidRate = 0;
		cumprod = (forecastResult_old.Cum_Liquid_Prod - deck.Cum_Liq_Prod) * MM;

		switch (scenario)
		{
		case 1:
			initialLiquidRate = deck.Init_Liquid_Gas_Rate_1P_1C; // Initial liquid rate
			plateauCumProd = deck.PlateauUR_1P_1C * MM;

			cumprodNoPlateau = (cumprod - plateauCumProd); //Liquid remaining plateau volume
			if (cumprodNoPlateau < 0)
			{
				forecastResult.Liquid_Rate = initialLiquidRate;
				forecastResult.isPlateau = true;
			}
			else
			{
				if (forecastResult.dcaStrategy == "" || forecastResult.dcaStrategy == existingStrategy_String)
				{
					if (forecastResult.scheduleKey == WellShutIn_String)
					{
						forecastResult.Liquid_Rate = 0;
					}
					else if (forecastResult.scheduleKey == WellOpenUp_String)
					{
						forecastResult.Liquid_Rate = DCA.Get_DCA(initialLiquidRate,
							deck.Rate_of_Change_Rate_1P_1C, cumprodNoPlateau, method, 
							deck.DeclineExponent_1P_1C, forecastResult.cumDays, isRateCum);
					}
					else if (forecastResult.scheduleKey == WellRampUp_String)
					{
						forecastResult.Liquid_Rate = 
						(forecastResult.startupRate * forecastResult.percentOfMaximumPotential);
					}
					else
					{
						forecastResult.Liquid_Rate = DCA.Get_DCA(initialLiquidRate,
							deck.Rate_of_Change_Rate_1P_1C, cumprodNoPlateau, method, 
							deck.DeclineExponent_1P_1C, forecastResult.cumDays, isRateCum);
					}
				}
				else
				{
					if (dateCreation.IsMinimumDate(CurrentDate, forecastResult.PlateauDate))
					{
						forecastResult.Liquid_Rate = forecastResult.startupRate;
					}
					else if (forecastResult.scheduleKey == WellShutIn_String)
					{
						forecastResult.Liquid_Rate = 0;
					}
					else if (forecastResult.scheduleKey == WellOpenUp_String)
					{
						double startUpLiquidRate = forecastResult.startupRate;
						forecastResult.Liquid_Rate = DCA.Get_DCA(startUpLiquidRate,
						forecastResult.declineRate, cumprodNoPlateau,
						forecastResult.declineType2, forecastResult.hyperbolicExponent,
						forecastResult.cumDays, isRateCum);
					}
					else if (forecastResult.scheduleKey == WellRampUp_String)
					{
						double startUpLiquidRate = forecastResult.startupRate;
						forecastResult.Liquid_Rate = startUpLiquidRate * forecastResult.percentOfMaximumPotential;
					}
					else if (forecastResult.scheduleKey == WellReroute_String)
					{
						double startUpLiquidRate = forecastResult.startupRate;
						forecastResult.Liquid_Rate = DCA.Get_DCA(startUpLiquidRate,
						forecastResult.declineRate, cumprodNoPlateau,
						forecastResult.declineType2, forecastResult.hyperbolicExponent,
						forecastResult.cumDays, isRateCum);
					}
				}
			}
			if (forecastResult.dcaStrategy == "" || forecastResult.dcaStrategy == existingStrategy_String)
			{
				forecastResult.DeclineRate = deck.Rate_of_Change_Rate_1P_1C;
			}
			else
			{
				forecastResult.DeclineRate = forecastResult.declineRate;
			}

			
			/* logger = logger +  "initialLiquidRate = "  + to_string(initialLiquidRate) + " * " +
			+  "Liquid_Rate Before Optimization = "  + to_string(forecastResult.Liquid_Rate) + " * "
			+  "Decline Rate = " + to_string(deck.Rate_of_Change_Rate_1P_1C) + " * "
			+  "cumprodNoPlateau = " + to_string(cumprodNoPlateau) + " * "
			+  "Decline Method = " + to_string(method) + " * "
			+  "DeclineExponent_1P_1C = " + to_string(deck.DeclineExponent_1P_1C) + "\n";

			if(deck.Module == "FO15003L_FO15 P15X_P13"){
				std::cout << logger;
			} */

			break;

		case 2:

			initialLiquidRate = deck.Init_Liquid_Gas_Rate_2P_2C; // Initial liquid rate
			plateauCumProd = deck.PlateauUR_1P_1C * MM;

			cumprodNoPlateau = (cumprod - plateauCumProd); //Liquid remaining plateau volume
			if (cumprodNoPlateau < 0)
			{
				forecastResult.Liquid_Rate = initialLiquidRate;
				forecastResult.isPlateau = true;
			}
			else
			{
				if (forecastResult.dcaStrategy == "" || forecastResult.dcaStrategy == existingStrategy_String)
				{
					if (forecastResult.scheduleKey == WellShutIn_String)
					{
						forecastResult.Liquid_Rate = 0;
					}
					else if (forecastResult.scheduleKey == WellOpenUp_String)
					{
						forecastResult.Liquid_Rate = DCA.Get_DCA(initialLiquidRate,
							deck.Rate_of_Change_Rate_2P_2C, cumprodNoPlateau, method, 
							deck.DeclineExponent_2P_2C, forecastResult.cumDays, isRateCum);
					}
					else if (forecastResult.scheduleKey == WellRampUp_String)
					{
						forecastResult.Liquid_Rate = 
						(forecastResult.startupRate * forecastResult.percentOfMaximumPotential);
					}
					else
					{
						forecastResult.Liquid_Rate = DCA.Get_DCA(initialLiquidRate,
								deck.Rate_of_Change_Rate_2P_2C, cumprodNoPlateau, method, 
								deck.DeclineExponent_2P_2C, forecastResult.cumDays, isRateCum);
					}
				}
				else
				{
					if (dateCreation.IsMinimumDate(CurrentDate, forecastResult.PlateauDate))
					{
						forecastResult.Liquid_Rate = forecastResult.startupRate;
					}
					else if (forecastResult.scheduleKey == WellShutIn_String)
					{
						forecastResult.Liquid_Rate = 0;
					}
					else if (forecastResult.scheduleKey == WellOpenUp_String)
					{
						double startUpLiquidRate = forecastResult.startupRate;
						forecastResult.Liquid_Rate = DCA.Get_DCA(startUpLiquidRate,
						forecastResult.declineRate, cumprodNoPlateau,
						forecastResult.declineType2, 
						forecastResult.hyperbolicExponent, forecastResult.cumDays, isRateCum);
					}
					else if (forecastResult.scheduleKey == WellRampUp_String)
					{
						double startUpLiquidRate = forecastResult.startupRate;
						forecastResult.Liquid_Rate = startUpLiquidRate * forecastResult.percentOfMaximumPotential;
					}
					else if (forecastResult.scheduleKey == WellReroute_String)
					{
						double startUpLiquidRate = forecastResult.startupRate;
						forecastResult.Liquid_Rate = DCA.Get_DCA(startUpLiquidRate,
						forecastResult.declineRate, cumprodNoPlateau,
						forecastResult.declineType2, 
						forecastResult.hyperbolicExponent, forecastResult.cumDays, isRateCum);
					}
				}
			}

			if (forecastResult.dcaStrategy == "" || forecastResult.dcaStrategy == existingStrategy_String)
			{
				forecastResult.DeclineRate = deck.Rate_of_Change_Rate_2P_2C;
			}
			else
			{
				forecastResult.DeclineRate = forecastResult.declineRate;
			}
			break;

		case 3:
			initialLiquidRate = deck.Init_Liquid_Gas_Rate_3P_3C; // Initial liquid rate
			plateauCumProd = deck.PlateauUR_1P_1C * MM;

			cumprodNoPlateau = (cumprod - plateauCumProd); //Liquid remaining plateau volume
			if (cumprodNoPlateau < 0)
			{
				forecastResult.Liquid_Rate = initialLiquidRate;
				forecastResult.isPlateau = true;
			}
			else
			{
				if (forecastResult.dcaStrategy == "" || forecastResult.dcaStrategy == existingStrategy_String)
				{
					if (forecastResult.scheduleKey == WellShutIn_String)
					{
						forecastResult.Liquid_Rate = 0;
					}
					else if (forecastResult.scheduleKey == WellOpenUp_String)
					{
						forecastResult.Liquid_Rate = DCA.Get_DCA(initialLiquidRate,
							deck.Rate_of_Change_Rate_3P_3C, cumprodNoPlateau, method, 
							deck.DeclineExponent_3P_3C, forecastResult.cumDays, isRateCum);
					}
					else if (forecastResult.scheduleKey == WellRampUp_String)
					{
						forecastResult.Liquid_Rate = 
						(forecastResult.startupRate * forecastResult.percentOfMaximumPotential);
					}
					else
					{
						forecastResult.Liquid_Rate = DCA.Get_DCA(initialLiquidRate,
							deck.Rate_of_Change_Rate_3P_3C, cumprodNoPlateau, method, 
							deck.DeclineExponent_3P_3C, forecastResult.cumDays, isRateCum);
					}
				}
				else
				{
					if (dateCreation.IsMinimumDate(CurrentDate, forecastResult.PlateauDate))
					{
						forecastResult.Liquid_Rate = forecastResult.startupRate;
					}
					else if (forecastResult.scheduleKey == WellShutIn_String)
					{
						forecastResult.Liquid_Rate = 0;
					}
					else if (forecastResult.scheduleKey == WellOpenUp_String)
					{
						double startUpLiquidRate = forecastResult.startupRate;
						forecastResult.Liquid_Rate = DCA.Get_DCA(startUpLiquidRate,
						forecastResult.declineRate, cumprodNoPlateau,
						forecastResult.declineType2, 
						forecastResult.hyperbolicExponent, forecastResult.cumDays, isRateCum);
					}
					else if (forecastResult.scheduleKey == WellRampUp_String)
					{
						double startUpLiquidRate = forecastResult.startupRate;
						forecastResult.Liquid_Rate = startUpLiquidRate * forecastResult.percentOfMaximumPotential;
					}
					else if (forecastResult.scheduleKey == WellReroute_String)
					{
						double startUpLiquidRate = forecastResult.startupRate;
						forecastResult.Liquid_Rate = DCA.Get_DCA(startUpLiquidRate,
						forecastResult.declineRate, cumprodNoPlateau,
						forecastResult.declineType2, 
						forecastResult.hyperbolicExponent, forecastResult.cumDays, isRateCum);
					}
				}
			}

			if (forecastResult.dcaStrategy == "" || forecastResult.dcaStrategy == existingStrategy_String)
			{
				forecastResult.DeclineRate = deck.Rate_of_Change_Rate_3P_3C;
			}
			else
				{
					forecastResult.DeclineRate = forecastResult.declineRate;
				}
			
			break;
		}

		if (forecastResult.Liquid_Rate < forecastResult.liquidRateAbandonmemt)
		{
			forecastResult.Liquid_Rate = 0;
		}
		if (forecastResult.Liquid_Rate < 0)
		{
			forecastResult.Liquid_Rate = 0;
		}
		
		forecastResult.Liquid_rate_NotTerminated = forecastResult.Liquid_Rate; // For well rerouting purpose
		if (forecastResult.isOilTerminated == true)
		{
			forecastResult.Liquid_Rate = 0;
		}
	}
	else
	{
		cumprod = (forecastResult_old.Cum_Gas_Prod - deck.Gp) * MM;

		switch (scenario)
		{
		case 1:
			plateauCumProd = deck.PlateauUR_1P_1C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.Gas_Rate = deck.Init_Liquid_Gas_Rate_1P_1C;
				forecastResult.isPlateau = true;
			}
			else
			{
				if (forecastResult.dcaStrategy == "" || forecastResult.dcaStrategy == existingStrategy_String)
				{
					if (forecastResult.scheduleKey == WellShutIn_String)
					{
						forecastResult.Gas_Rate = 0;
					}
					else if (forecastResult.scheduleKey == WellOpenUp_String)
					{
						forecastResult.Gas_Rate = DCA.Get_DCA(deck.Init_Liquid_Gas_Rate_1P_1C,
						deck.Rate_of_Change_Rate_1P_1C, 
						cumprodNoPlateau, method, deck.DeclineExponent_1P_1C,
						forecastResult.cumDays, isRateCum);
					}
					else if (forecastResult.scheduleKey == WellRampUp_String)
					{
						forecastResult.Gas_Rate = forecastResult.startupRate * forecastResult.percentOfMaximumPotential;
					}
					else
					{
						forecastResult.Gas_Rate = DCA.Get_DCA(deck.Init_Liquid_Gas_Rate_1P_1C,
						deck.Rate_of_Change_Rate_1P_1C, cumprodNoPlateau, method, 
						deck.DeclineExponent_1P_1C,  forecastResult.cumDays, isRateCum);
					}
				}
				else
				{
					if (dateCreation.IsMinimumDate(CurrentDate, forecastResult.PlateauDate))
					{
						forecastResult.Gas_Rate = forecastResult.startupRate;
					}
					else if (forecastResult.scheduleKey == WellShutIn_String)
					{
						forecastResult.Gas_Rate = 0;
					}
					else if (forecastResult.scheduleKey == WellOpenUp_String)
					{
						forecastResult.Gas_Rate = DCA.Get_DCA(forecastResult.startupRate,
						forecastResult.declineRate, cumprodNoPlateau,
						forecastResult.declineType2, 
						forecastResult.hyperbolicExponent, forecastResult.cumDays, isRateCum);
					}
					else if (forecastResult.scheduleKey == WellRampUp_String)
					{
						forecastResult.Gas_Rate = forecastResult.startupRate * forecastResult.percentOfMaximumPotential;
					}
					else if (forecastResult.scheduleKey == WellReroute_String)
					{
						forecastResult.Gas_Rate = DCA.Get_DCA(forecastResult.startupRate,
						forecastResult.declineRate, cumprodNoPlateau,
						forecastResult.declineType2, 
						forecastResult.hyperbolicExponent, forecastResult.cumDays, isRateCum);
					}
				}
			}

			if (forecastResult.dcaStrategy == "" || forecastResult.dcaStrategy == existingStrategy_String)
			{
				forecastResult.DeclineRate = deck.Rate_of_Change_Rate_1P_1C;
			}
			else
			{
				forecastResult.DeclineRate = forecastResult.declineRate;
			}
			break;

		case 2:
			plateauCumProd = deck.PlateauUR_2P_2C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.Gas_Rate = deck.Init_Liquid_Gas_Rate_1P_1C;
				forecastResult.isPlateau = true;
			}
			else
			{
				if (forecastResult.dcaStrategy == "" || forecastResult.dcaStrategy == existingStrategy_String)
				{
					if (forecastResult.scheduleKey == WellShutIn_String)
					{
						forecastResult.Gas_Rate = 0;
					}
					else if (forecastResult.scheduleKey == WellOpenUp_String)
					{
						forecastResult.Gas_Rate = DCA.Get_DCA(deck.Init_Liquid_Gas_Rate_2P_2C,
				deck.Rate_of_Change_Rate_2P_2C, cumprodNoPlateau, method, 
				deck.DeclineExponent_2P_2C, forecastResult.cumDays, isRateCum);
					}
					else if (forecastResult.scheduleKey == WellRampUp_String)
					{
						forecastResult.Gas_Rate = forecastResult.startupRate * forecastResult.percentOfMaximumPotential;
					}
					else
					{
						forecastResult.Gas_Rate = DCA.Get_DCA(deck.Init_Liquid_Gas_Rate_2P_2C,
						deck.Rate_of_Change_Rate_2P_2C, cumprodNoPlateau, method, 
						deck.DeclineExponent_2P_2C, forecastResult.cumDays, isRateCum);
					}
				}
				else
				{
					if (dateCreation.IsMinimumDate(CurrentDate, forecastResult.PlateauDate))
					{
						forecastResult.Gas_Rate = forecastResult.startupRate;
					}
					else if (forecastResult.scheduleKey == WellShutIn_String)
					{
						forecastResult.Gas_Rate = 0;
					}
					else if (forecastResult.scheduleKey == WellOpenUp_String)
					{
						forecastResult.Gas_Rate = DCA.Get_DCA(forecastResult.startupRate,
						forecastResult.declineRate, cumprodNoPlateau,
						forecastResult.declineType2, 
						forecastResult.hyperbolicExponent, forecastResult.cumDays, isRateCum);
					}
					else if (forecastResult.scheduleKey == WellRampUp_String)
					{
						forecastResult.Gas_Rate = forecastResult.startupRate * forecastResult.percentOfMaximumPotential;
					}
					else if (forecastResult.scheduleKey == WellReroute_String)
					{
						forecastResult.Gas_Rate = DCA.Get_DCA(forecastResult.startupRate,
						forecastResult.declineRate, cumprodNoPlateau,
						forecastResult.declineType2, 
						forecastResult.hyperbolicExponent, forecastResult.cumDays, isRateCum);
					}
				}
			}

			if (forecastResult.dcaStrategy == "" || forecastResult.dcaStrategy == existingStrategy_String)
			{
				forecastResult.DeclineRate = deck.Rate_of_Change_Rate_2P_2C;
			}
			else
			{
				forecastResult.DeclineRate = forecastResult.declineRate;
			}
			break;

		case 3:
			plateauCumProd = deck.PlateauUR_3P_3C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.Gas_Rate = deck.Init_Liquid_Gas_Rate_3P_3C;
				forecastResult.isPlateau = true;
			}
			else
			{
				if (forecastResult.dcaStrategy == "" || forecastResult.dcaStrategy == existingStrategy_String)
				{
					if (forecastResult.scheduleKey == WellShutIn_String)
					{
						forecastResult.Gas_Rate = 0;
					}
					else if (forecastResult.scheduleKey == WellOpenUp_String)
					{
						forecastResult.Gas_Rate = DCA.Get_DCA(deck.Init_Liquid_Gas_Rate_3P_3C,
						deck.Rate_of_Change_Rate_3P_3C, cumprodNoPlateau, method, 
						deck.DeclineExponent_3P_3C, forecastResult.cumDays, isRateCum);
					}
					else if (forecastResult.scheduleKey == WellRampUp_String)
					{
						forecastResult.Gas_Rate = forecastResult.startupRate * forecastResult.percentOfMaximumPotential;
					}
					else
					{
						forecastResult.Gas_Rate = DCA.Get_DCA(deck.Init_Liquid_Gas_Rate_3P_3C,
						deck.Rate_of_Change_Rate_3P_3C, cumprodNoPlateau, method, 
						deck.DeclineExponent_3P_3C, forecastResult.cumDays, isRateCum);
					}
				}
				else
				{
					if (dateCreation.IsMinimumDate(CurrentDate, forecastResult.PlateauDate))
					{
						forecastResult.Gas_Rate = forecastResult.startupRate;
					}
					else if (forecastResult.scheduleKey == WellShutIn_String)
					{
						forecastResult.Gas_Rate = 0;
					}
					else if (forecastResult.scheduleKey == WellOpenUp_String)
					{
						forecastResult.Gas_Rate = DCA.Get_DCA(forecastResult.startupRate,
						forecastResult.declineRate, cumprodNoPlateau,
						forecastResult.declineType2, 
						forecastResult.hyperbolicExponent, forecastResult.cumDays, isRateCum);
					}
					else if (forecastResult.scheduleKey == WellRampUp_String)
					{
						forecastResult.Gas_Rate = forecastResult.startupRate * forecastResult.percentOfMaximumPotential;
					}
					else if (forecastResult.scheduleKey == WellReroute_String)
					{
						forecastResult.Gas_Rate = DCA.Get_DCA(forecastResult.startupRate,
						forecastResult.declineRate, cumprodNoPlateau,
						forecastResult.declineType2, 
						forecastResult.hyperbolicExponent, forecastResult.cumDays, isRateCum);
					}
				}
			}

			if (forecastResult.dcaStrategy == "" || forecastResult.dcaStrategy == existingStrategy_String)
			{
				forecastResult.DeclineRate = deck.Rate_of_Change_Rate_3P_3C;
			}
			else
			{
				forecastResult.DeclineRate = forecastResult.declineRate;
			}
			break;
		}

		if (forecastResult.Gas_Rate < forecastResult.gasRateAbandonment)
		{
			forecastResult.Gas_Rate = forecastResult.gasRateAbandonment;
		}

		if (forecastResult.Gas_Rate < 0)
		{
			forecastResult.Gas_Rate = 0;
		}
		forecastResult.Gas_Rate_NotTerminated = forecastResult.Gas_Rate;

		if (forecastResult.isGasTerminated == true)
		{
			forecastResult.Gas_Rate = 0;
		}
	}
}

void CalculateDeckVariables::GetActiveRate(int &scenario,
										   InputDeckStruct &deck,
										   ForecastResult &forecastResult,
										   ForecastResult &forecastResult_old,
										   ForecastResult &externalResult)
{
	int method = deck.DeclineMethod;
	double cumprod = 0, MM = 1000000.0, plateauCumProd = 0, cumprodNoPlateau = 0;
	forecastResult.isPlateau = false;


	if (deck.Hydrocarbon_Stream == "oil")
	{

		cumprod = (forecastResult_old.Cum_Oil_Prod - deck.Np) * MM;

		switch (scenario)
		{
		case 1:
			plateauCumProd = deck.PlateauUR_1P_1C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.Liquid_Rate = deck.Init_Liquid_Gas_Rate_1P_1C;
				forecastResult.isPlateau = true;
			}
			else
			{
				if (UseExternalForecastprofile == "external")
				{
					forecastResult.Liquid_Rate = externalResult.Liquid_Rate;
				}
				else
				{
					if (dateCreation.IsMinimumDate(CurrentDate, forecastResult.PlateauDate))
					{
					}
					else
					{
					}
					forecastResult.Liquid_Rate = DCA.Get_DCA(deck.Init_Liquid_Gas_Rate_1P_1C,
					deck.Rate_of_Change_Rate_1P_1C, cumprodNoPlateau, method,
					deck.DeclineExponent_1P_1C, forecastResult.cumDays, isRateCum);
				}
			}
			forecastResult.DeclineRate = deck.Rate_of_Change_Rate_1P_1C;
			if (forecastResult.Liquid_Rate < deck.Aband_Liquid_Gas_Rate_1P_1C)
			{
				forecastResult.Oil_rate = 0;
			}

			if (forecastResult.isOilTerminated == true)
			{
				forecastResult.Oil_rate = 0;
			}
			break;

		case 2:

			plateauCumProd = deck.PlateauUR_2P_2C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.Liquid_Rate = deck.Init_Liquid_Gas_Rate_2P_2C;
				forecastResult.isPlateau = true;
			}
			else
			{
				if (UseExternalForecastprofile == "external")
				{
					forecastResult.Liquid_Rate = externalResult.Liquid_Rate;
				}
				else
				{
					forecastResult.Liquid_Rate = DCA.Get_DCA(deck.Init_Liquid_Gas_Rate_2P_2C,
					deck.Rate_of_Change_Rate_2P_2C, cumprodNoPlateau, method,
					deck.DeclineExponent_2P_2C, forecastResult.cumDays, isRateCum);
				}
			}
			forecastResult.DeclineRate = deck.Rate_of_Change_Rate_2P_2C;
			if (forecastResult.Liquid_Rate < deck.Aband_Liquid_Gas_Rate_2P_2C)
			{
				forecastResult.Liquid_Rate = deck.Aband_Liquid_Gas_Rate_2P_2C;
			}
			break;

		case 3:
			plateauCumProd = deck.PlateauUR_3P_3C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.Liquid_Rate = deck.Init_Liquid_Gas_Rate_3P_3C;
				forecastResult.isPlateau = true;
			}
			else
			{
				if (UseExternalForecastprofile == "external")
				{
					forecastResult.Liquid_Rate = externalResult.Liquid_Rate;
				}
				else
				{
					forecastResult.Liquid_Rate = DCA.Get_DCA(deck.Init_Liquid_Gas_Rate_3P_3C,
					deck.Rate_of_Change_Rate_3P_3C, cumprodNoPlateau, method,
					deck.DeclineExponent_3P_3C, forecastResult.cumDays, isRateCum);
				}
			}
			forecastResult.DeclineRate = deck.Rate_of_Change_Rate_3P_3C;
			if (forecastResult.Liquid_Rate < deck.Aband_Liquid_Gas_Rate_3P_3C)
			{
				forecastResult.Liquid_Rate = deck.Aband_Liquid_Gas_Rate_3P_3C;
			}
			break;
		}
	}
	else
	{
		cumprod = (forecastResult_old.Cum_Gas_Prod - deck.Gp) * MM;

		switch (scenario)
		{
		case 1:
			plateauCumProd = deck.PlateauUR_1P_1C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.Gas_Rate = deck.Init_Liquid_Gas_Rate_1P_1C;
				forecastResult.isPlateau = true;
			}
			else
			{

				if (UseExternalForecastprofile == "external")
				{
					forecastResult.Gas_Rate = externalResult.Gas_Rate;
				}
				else
				{
					forecastResult.Gas_Rate = DCA.Get_DCA(deck.Init_Liquid_Gas_Rate_1P_1C,
					deck.Rate_of_Change_Rate_1P_1C, cumprodNoPlateau, method, 
					deck.DeclineExponent_1P_1C, forecastResult.cumDays, isRateCum);
				}
			}
			forecastResult.DeclineRate = deck.Rate_of_Change_Rate_1P_1C;

			if (forecastResult.Gas_Rate < deck.Aband_Liquid_Gas_Rate_1P_1C)
			{
				forecastResult.Gas_Rate = deck.Aband_Liquid_Gas_Rate_1P_1C;
			}

			break;

		case 2:
			plateauCumProd = deck.PlateauUR_2P_2C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.Gas_Rate = deck.Init_Liquid_Gas_Rate_2P_2C;
				forecastResult.isPlateau = true;
			}
			else
			{
				if (UseExternalForecastprofile == "external")
				{
					forecastResult.Gas_Rate = externalResult.Gas_Rate;
				}
				else
				{
					forecastResult.Gas_Rate = DCA.Get_DCA(deck.Init_Liquid_Gas_Rate_2P_2C,
					deck.Rate_of_Change_Rate_2P_2C, cumprodNoPlateau, 
					method, deck.DeclineExponent_2P_2C, forecastResult.cumDays, isRateCum);
				}
			}
			forecastResult.DeclineRate = deck.Rate_of_Change_Rate_2P_2C;
			if (forecastResult.Gas_Rate < deck.Aband_Liquid_Gas_Rate_2P_2C)
			{
				forecastResult.Gas_Rate = deck.Aband_Liquid_Gas_Rate_2P_2C;
			}
			break;

		case 3:
			plateauCumProd = deck.PlateauUR_3P_3C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.Gas_Rate = deck.Init_Liquid_Gas_Rate_3P_3C;
				forecastResult.isPlateau = true;
			}
			else
			{
				if (UseExternalForecastprofile == "external")
				{
					forecastResult.Gas_Rate = externalResult.Gas_Rate;
				}
				else
				{
					forecastResult.Gas_Rate = DCA.Get_DCA(deck.Init_Liquid_Gas_Rate_3P_3C,
					deck.Rate_of_Change_Rate_3P_3C, cumprodNoPlateau, method,
					deck.DeclineExponent_3P_3C, forecastResult.cumDays, isRateCum);
				}
			}
			forecastResult.DeclineRate = deck.Rate_of_Change_Rate_3P_3C;
			if (forecastResult.Gas_Rate < deck.Aband_Liquid_Gas_Rate_3P_3C)
			{
				forecastResult.Gas_Rate = deck.Aband_Liquid_Gas_Rate_3P_3C;
			}
			break;
		}
	}
}

void CalculateDeckVariables::GetVariables(int &scenario, InputDeckStruct &deck,
										  ForecastResult &forecastResult, ForecastResult &forecastResult_old,
										  double &externalCurrentCumProd, bool &isAfetrOptimization)
{

	if (UseExternalForecastprofile == external)
	{
		//std::cout << "external " << "\n";
		if (isAfetrOptimization == false)
		{

			WellActivityResult wellActivityResult = externalForecast.GetWellActivityResult(WellActivities, forecastResult_old.ModuleName);
			int cumProductionIndex = externalForecast.GetCumProductionIndex(externalCurrentCumProd,
																			wellActivityResult, deck.Hydrocarbon_Stream);
			ForecastResult fResult = externalForecast.GetForecastResult(cumProductionIndex,
																		wellActivityResult, deck.Hydrocarbon_Stream, externalCurrentCumProd);
			GetActiveRate(scenario, deck, forecastResult, forecastResult_old, fResult);
			if (deck.Hydrocarbon_Stream == oil)
			{
				forecastResult.GOR = fResult.GOR;
				forecastResult.BSW = fResult.BSW;
			}
			else
			{
				forecastResult.CGR = fResult.CGR;
				forecastResult.WGR = fResult.WGR;
			}
		}
		else
		{

			if (deck.Hydrocarbon_Stream == oil)
			{
				GetActiveCumProd(scenario, deck, forecastResult, forecastResult_old);
				WellActivityResult wellActivityResult = externalForecast.GetWellActivityResult(WellActivities, forecastResult_old.ModuleName);
				int cumProductionIndex = externalForecast.GetCumProductionIndex(forecastResult.Cum_Oil_Prod,
																				wellActivityResult, deck.Hydrocarbon_Stream);
				ForecastResult fResult = externalForecast.GetForecastResult(cumProductionIndex,
																			wellActivityResult, deck.Hydrocarbon_Stream, forecastResult.Cum_Oil_Prod);
				forecastResult.GOR = fResult.GOR;
				forecastResult.BSW = fResult.BSW;
			}
			else
			{
				GetActiveCumProd(scenario, deck, forecastResult, forecastResult_old);
				WellActivityResult wellActivityResult = externalForecast.GetWellActivityResult(WellActivities, forecastResult_old.ModuleName);
				int cumProductionIndex = externalForecast.GetCumProductionIndex(forecastResult.Cum_Gas_Prod,
																				wellActivityResult, deck.Hydrocarbon_Stream);
				ForecastResult fResult = externalForecast.GetForecastResult(cumProductionIndex,
																			wellActivityResult, deck.Hydrocarbon_Stream, forecastResult.Cum_Gas_Prod);
				forecastResult.CGR = fResult.CGR;
				forecastResult.WGR = fResult.WGR;
			}
		}
	}
	else
	{
		GetActiveCumProd(scenario, deck, forecastResult, forecastResult_old);

		GetGasFractionalFlow(scenario, deck, forecastResult, forecastResult_old);

		GetWaterFractionalFlow(scenario, deck, forecastResult, forecastResult_old);
	}

	GetRates(scenario, deck, forecastResult);

	GetCumProds(scenario, deck, forecastResult, forecastResult_old);
}


double CalculateDeckVariables::fun(double ProductionDays)
{
	double rate = DCA.Get_DCA_Exponential2(initial_rate, rate_of_change, ProductionDays);
	return rate;
}

double CalculateDeckVariables::fun2(double ProductionDays)
{
	double rate = DCA.Get_DCA_Exponential2(initial_rate, rate_of_change, ProductionDays);
	return rate;
}

double CalculateDeckVariables::TraplRule(pFUNC fun, double lower, double upper, int subInterval)
{
	int i;
	double k;

	/* Finding step size */
	int stepSize = (upper - lower) / subInterval;

	/* Finding Integration Value */
	double integration = this->fun(lower) + this->fun(upper);

	for (i = 1; i <= subInterval - 1; i++)
	{
		k = lower + i * stepSize;
		integration = integration + 2 * (this->fun(k));
	}

	integration = integration * stepSize / 2;

	return integration;
}

void CalculateDeckVariables::GetActiveCumProd(int &scenario, InputDeckStruct &deck, ForecastResult &forecastResult, ForecastResult &forecastResult_old)
{

	CalculateDeckVariables obj;
	string logger = "";
	double MM = 1000000.0;
	double upperbound = DeltaT;

	switch (scenario)
	{
	case 1:
		rate_of_change = deck.Rate_of_Change_Rate_1P_1C;
		break;

	case 2:
		rate_of_change = deck.Rate_of_Change_Rate_2P_2C;
		break;

	case 3:
		rate_of_change = deck.Rate_of_Change_Rate_3P_3C;
		break;
	}

	if (deck.Hydrocarbon_Stream == oil)
	{
		initial_rate = forecastResult.Liquid_rate_NotTerminated;

		obj.initial_rate = initial_rate;
		obj.rate_of_change = rate_of_change;
		//forecastResult.Cum_Oil_Prod = TraplRule(&CalculateDeckVariables::fun, 0, DeltaT, interval);

		auto fp = bind(&CalculateDeckVariables::fun2, obj, std::placeholders::_1);
		double _liqProd = upperbound * forecastResult.Liquid_rate_NotTerminated; // integration.trapzd(fp, lowerbound, upperbound, interval);
		forecastResult.Cum_Liquid_Prod = forecastResult_old.Cum_Liquid_Prod + _liqProd / MM;
		
		/* logger = logger + 
		"Liquid_rate_NotTerminated Before Optimization = "  + to_string(forecastResult.Liquid_rate_NotTerminated) + " * "
			+  "Cum_Liquid_Prod Old = " + to_string(forecastResult_old.Cum_Liquid_Prod) + " * "
			+  "Cum_Liquid_Prod = " + to_string(forecastResult.Cum_Liquid_Prod) + "\n";

		if(deck.Module == "FO15003L_FO15 P15X_P13"){
			std::cout << logger;
		} */

	}
	else
	{
		initial_rate = forecastResult.Gas_Rate_NotTerminated;

		obj.initial_rate = initial_rate;
		obj.rate_of_change = rate_of_change;

		//auto fp = bind(&CalculateDeckVariables::fun2, obj, std::placeholders::_1);
		double _gasProd = upperbound * forecastResult.Gas_Rate_NotTerminated; // integration.trapzd(fp, lowerbound, upperbound, interval);
		//forecastResult.Cum_Gas_Prod = TraplRule(&CalculateDeckVariables::fun, 0, DeltaT, interval);
		forecastResult.Cum_Gas_Prod = forecastResult_old.Cum_Gas_Prod + _gasProd / MM;

	}
}

void CalculateDeckVariables::GetGasFractionalFlow(int &scenario, InputDeckStruct &deck, ForecastResult &forecastResult,
ForecastResult &forecastResult_old)
{
	double cumprod = 0, plateauCumProd = 0;
	double cumprodNoPlateau = 0;

	double MM = 1000000.0, x1 = 0, x2 = 0;

	if (deck.Hydrocarbon_Stream == oil)
	{
		x1 = deck.Cum_Liq_Prod * MM;
		x2 = forecastResult.Cum_Liquid_Prod * MM;
		cumprod = (forecastResult_old.Cum_Liquid_Prod - deck.Cum_Liq_Prod) * MM;

		switch (scenario)
		{
		case 1:
			plateauCumProd = deck.PlateauUR_1P_1C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.GOR  = deck.Init_GOR_CGR;
			}else{
				forecastResult.GOR = fractionalFlow.Get_Fractional_Flow(deck.Rate_Of_Rate_GOR_CGR_1P1C, x1,
				x2, deck.Init_GOR_CGR, forecastResult.cumDays, isRateCum);
				if (forecastResult.GOR > deck.Aband_GOR_CGR_1P_1C)
				{
					forecastResult.GOR = deck.Aband_GOR_CGR_1P_1C;
				}
			}
		break;

		case 2:
			plateauCumProd = deck.PlateauUR_2P_2C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.GOR  = deck.Init_GOR_CGR;
			}else{
				forecastResult.GOR = fractionalFlow.Get_Fractional_Flow(deck.Rate_Of_Rate_GOR_CGR_2P2C, x1,
				x2, deck.Init_GOR_CGR, forecastResult.cumDays, isRateCum);
				if (forecastResult.GOR > deck.Aband_GOR_CGR_2P_2C)
				{
					forecastResult.GOR = deck.Aband_GOR_CGR_2P_2C;
				}
			}
			break;

		case 3:
			plateauCumProd = deck.PlateauUR_3P_3C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.GOR  = deck.Init_GOR_CGR;
			}else{
				forecastResult.GOR = fractionalFlow.Get_Fractional_Flow(deck.Rate_Of_Rate_GOR_CGR_3P3C, x1,
				x2, deck.Init_GOR_CGR, forecastResult.cumDays, isRateCum);

				if (forecastResult.GOR > deck.Aband_GOR_CGR_3P_3C)
				{
					forecastResult.GOR = deck.Aband_GOR_CGR_3P_3C;
				}
			}
			break;
		}
		if (forecastResult.GOR < 0)
		{
			forecastResult.GOR = 0;
		}
		if (deck.isGasTerminated == true)
		{
			forecastResult.GOR = 0;
		}
	}
	else
	{
		x1 = deck.Gp * MM;
		x2 = forecastResult.Cum_Gas_Prod * MM;
		cumprod = (forecastResult_old.Cum_Gas_Prod - deck.Gp) * MM;

		switch (scenario)
		{
		case 1:
			plateauCumProd = deck.PlateauUR_1P_1C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.CGR  = deck.Init_GOR_CGR;
			}else{
				forecastResult.CGR = fractionalFlow.Get_Fractional_Flow(deck.Rate_Of_Rate_GOR_CGR_1P1C, x1,
				x2, deck.Init_GOR_CGR, forecastResult.cumDays, isRateCum);
				if (forecastResult.CGR <= deck.Aband_GOR_CGR_1P_1C)
				{
					forecastResult.CGR = deck.Aband_GOR_CGR_1P_1C;
				}
			}
			break;

		case 2:
			plateauCumProd = deck.PlateauUR_2P_2C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.CGR  = deck.Init_GOR_CGR;
			}else{
				forecastResult.CGR = fractionalFlow.Get_Fractional_Flow(deck.Rate_Of_Rate_GOR_CGR_2P2C, x1,
				x2, deck.Init_GOR_CGR, forecastResult.cumDays, isRateCum);
				if (forecastResult.CGR <= deck.Aband_GOR_CGR_2P_2C)
				{
					forecastResult.CGR = deck.Aband_GOR_CGR_2P_2C;
				}
			}
			break;

		case 3:
			plateauCumProd = deck.PlateauUR_3P_3C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.CGR  = deck.Init_GOR_CGR;
			}else{
				forecastResult.CGR = fractionalFlow.Get_Fractional_Flow(deck.Rate_Of_Rate_GOR_CGR_3P3C, x1,
				x2, deck.Init_GOR_CGR, forecastResult.cumDays, isRateCum);
				if (forecastResult.CGR <= deck.Aband_GOR_CGR_3P_3C)
				{
					forecastResult.CGR = deck.Aband_GOR_CGR_3P_3C;
				}
			}
			break;
		}
		if (forecastResult.CGR < 0)
		{
			forecastResult.CGR = 0;
		}
		if (deck.isGasTerminated == true)
		{
			forecastResult.CGR = 0;
		}
	}
}

void CalculateDeckVariables::GetWaterFractionalFlow(int &scenario, InputDeckStruct &deck, 
ForecastResult &forecastResult, ForecastResult &forecastResult_old)
{
	double cumprod = 0, plateauCumProd = 0;
	double cumprodNoPlateau = 0;

	double MM = 1000000.0, x1 = 0, x2 = 0;

	if (deck.Hydrocarbon_Stream == oil)
	{
		x1 = deck.Cum_Liq_Prod * MM;
		x2 = forecastResult.Cum_Liquid_Prod * MM;
		cumprod = (forecastResult_old.Cum_Liquid_Prod - deck.Cum_Liq_Prod) * MM;

		switch (scenario)
		{
		case 1:
			plateauCumProd = deck.PlateauUR_1P_1C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.BSW  = deck.Init_BSW_WGR;
			}else{
				forecastResult.BSW = fractionalFlow.Get_Fractional_Flow(deck.Rate_Of_Rate_BSW_WGR_1P1C, x1,
				x2, deck.Init_BSW_WGR, forecastResult.cumDays, isRateCum);

				if (forecastResult.BSW > deck.Aband_BSW_WGR_1P_1C)
				{
					forecastResult.BSW = deck.Aband_BSW_WGR_1P_1C;
				}
			}
			break;

		case 2:
			plateauCumProd = deck.PlateauUR_2P_2C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.BSW  = deck.Init_BSW_WGR;
			}else{
				forecastResult.BSW = fractionalFlow.Get_Fractional_Flow(deck.Rate_Of_Rate_BSW_WGR_2P2C, x1,
				x2, deck.Init_BSW_WGR, forecastResult.cumDays, isRateCum);

				if (forecastResult.BSW > deck.Aband_BSW_WGR_2P_2C)
				{
					forecastResult.BSW = deck.Aband_BSW_WGR_2P_2C;
				}
			}
			break;

		case 3:
			plateauCumProd = deck.PlateauUR_3P_3C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.BSW  = deck.Init_BSW_WGR;
			}else{
				forecastResult.BSW = fractionalFlow.Get_Fractional_Flow(deck.Rate_Of_Rate_BSW_WGR_3P3C, x1,
				x2, deck.Init_BSW_WGR, forecastResult.cumDays, isRateCum);

				if (forecastResult.BSW > deck.Aband_BSW_WGR_3P_3C)
				{
					forecastResult.BSW = deck.Aband_BSW_WGR_3P_3C;
				}
			}
			break;
		}

		if (forecastResult.BSW < 0)
		{
			forecastResult.BSW = 0;
		}
		if (forecastResult.BSW > 1)
		{
			forecastResult.BSW = 1;
		}
		if (deck.isWaterTerminated == true)
		{
			forecastResult.BSW = 0;
		}
	}
	else
	{
		x1 = deck.Gp * MM;
		x2 = forecastResult.Cum_Gas_Prod * MM;
		cumprod = (forecastResult_old.Cum_Gas_Prod - deck.Gp) * MM;

		switch (scenario)
		{
		case 1:
			plateauCumProd = deck.PlateauUR_1P_1C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.WGR  = deck.Init_BSW_WGR;
			}else{
				forecastResult.WGR = fractionalFlow.Get_Fractional_Flow(deck.Rate_Of_Rate_BSW_WGR_1P1C, x1,
				x2, deck.Init_BSW_WGR, forecastResult.cumDays, isRateCum);
				if (forecastResult.WGR > deck.Aband_BSW_WGR_1P_1C)
				{
					forecastResult.WGR = deck.Aband_BSW_WGR_1P_1C;
				}
			}
			break;

		case 2:
			plateauCumProd = deck.PlateauUR_2P_2C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.WGR  = deck.Init_BSW_WGR;
			}else{
				forecastResult.WGR = fractionalFlow.Get_Fractional_Flow(deck.Rate_Of_Rate_BSW_WGR_2P2C, x1,
				x2, deck.Init_BSW_WGR, forecastResult.cumDays, isRateCum);
				if (forecastResult.WGR > deck.Aband_BSW_WGR_2P_2C)
				{
					forecastResult.WGR = deck.Aband_BSW_WGR_2P_2C;
				}
			}
			break;

		case 3:
			plateauCumProd = deck.PlateauUR_3P_3C * MM;
			cumprodNoPlateau = cumprod - plateauCumProd;
			if (cumprodNoPlateau < 0)
			{
				forecastResult.WGR  = deck.Init_BSW_WGR;
			}else{
				forecastResult.WGR = fractionalFlow.Get_Fractional_Flow(deck.Rate_Of_Rate_BSW_WGR_3P3C, x1,
				x2, deck.Init_BSW_WGR, forecastResult.cumDays, isRateCum);
				if (forecastResult.WGR > deck.Aband_BSW_WGR_3P_3C)
				{
					forecastResult.WGR = deck.Aband_BSW_WGR_3P_3C;
				}
			}
			break;
		}
		if (forecastResult.WGR < 0)
		{
			forecastResult.WGR = 0;
		}
		if (deck.isWaterTerminated == true)
		{
			forecastResult.WGR = 0;
		}
	}
}

void CalculateDeckVariables::GetRates(int &scenario, InputDeckStruct &deck, ForecastResult &forecastResult)
{
	double MM = 1000000.0;
	string logger = "";

	if (deck.Hydrocarbon_Stream == oil)
	{
		forecastResult.Water_Rate = forecastResult.Liquid_rate_NotTerminated * forecastResult.BSW;
		forecastResult.Oil_rate = forecastResult.Liquid_rate_NotTerminated * (1 - forecastResult.BSW);
		forecastResult.Oil_rate_NotTerminated = forecastResult.Liquid_rate_NotTerminated * (1 - forecastResult.BSW);
		forecastResult.Gas_Rate = forecastResult.Oil_rate * forecastResult.GOR;
		
		if (forecastResult.Water_Rate < 0)
		{
			forecastResult.Water_Rate = 0;
		}
		if (forecastResult.Gas_Rate < 0)
		{
			forecastResult.Gas_Rate = 0;
		}
		if (forecastResult.Oil_rate < 0)
		{
			forecastResult.Oil_rate = 0;
			forecastResult.Oil_rate_NotTerminated = 0;
		}
	
		forecastResult.Crude_Oil_Lossess = (CurrentFacilityData.Crudeoil_Lossess / 100.0) * forecastResult.Oil_rate;
		forecastResult.Gas_Demand = 0;
		forecastResult.Gas_Own_Use = 0;
		forecastResult.Gas_Flared = 0;

		if (Gas_Capacity > 0)
		{
			forecastResult.Gas_Flared = (CurrentFacilityData.GasFlared * forecastResult.Gas_Rate) / Gas_Capacity;
			forecastResult.Gas_Own_Use = (CurrentFacilityData.GasOwnUse * forecastResult.Gas_Rate) / Gas_Capacity;
	
		}

		forecastResult.Gas_Demand = forecastResult.Gas_Rate - (forecastResult.Gas_Flared + forecastResult.Gas_Own_Use);
		if (forecastResult.Gas_Demand < 0)
		{
			forecastResult.Gas_Demand = 0;
		}

		/* logger = logger + 
		"Gas_Capacity = "  + to_string(Gas_Capacity) + " * " +
		"CurrentFacilityData.GasFlared  = "  + to_string(CurrentFacilityData.GasFlared) + " * " +
		"CurrentFacilityData.GasOwnUse = "  + to_string(CurrentFacilityData.GasOwnUse) + " * " +
		"Gas_Flared = "  + to_string(forecastResult.Gas_Flared) + " * " +
		"Gas_Own_Use Old = " + to_string(forecastResult.Gas_Own_Use) + " * " +
		"Gas_Demand = " + to_string(forecastResult.Gas_Demand) + "\n";
		//std::cout << CurrentDate.day << "/" << CurrentDate.month << "/" << CurrentDate.year << std::endl;

		if(deck.Module == "FO15004L_FO15 R10X_P01"){
			std::cout << logger;
		} */
	}
	else
	{
		forecastResult.Oil_rate = forecastResult.Gas_Rate_NotTerminated * forecastResult.CGR;
		forecastResult.Water_Rate = forecastResult.Gas_Rate_NotTerminated * forecastResult.WGR;
		if (forecastResult.Oil_rate < 0)
		{
			forecastResult.Oil_rate = 0;
		}
		if (forecastResult.Water_Rate < 0)
		{
			forecastResult.Water_Rate = 0;
		}
		forecastResult.Liquid_Rate = forecastResult.Water_Rate + forecastResult.Oil_rate;
		forecastResult.Crude_Oil_Lossess = (CurrentFacilityData.Crudeoil_Lossess / 100.0) * forecastResult.Oil_rate;
		forecastResult.Gas_Demand = 0;
		forecastResult.Gas_Own_Use = 0;
		forecastResult.Gas_Flared = 0;
		if (Gas_Capacity > 0)
		{
			forecastResult.Gas_Flared = (CurrentFacilityData.GasFlared * forecastResult.Gas_Rate) / Gas_Capacity;
			forecastResult.Gas_Own_Use = (CurrentFacilityData.GasOwnUse * forecastResult.Gas_Rate) / Gas_Capacity;
		}

		forecastResult.Gas_Demand = forecastResult.Gas_Rate - (forecastResult.Gas_Flared + forecastResult.Gas_Own_Use);
		if (forecastResult.Gas_Demand < 0)
		{
			forecastResult.Gas_Demand = 0;
		}
	}
}

void CalculateDeckVariables::GetCumProds(int &scenario, InputDeckStruct &deck, ForecastResult &forecastResult, ForecastResult &forecastResult_old)
{

	Method = 1;
	double MM = 1000000.0;
	//double upperbound = DeltaT;
	CalculateDeckVariables obj;
	string logger = "";

	//int interval = 10;
	forecastResult.OptimalSolution = optimalSolution;
	forecastResult.AllWellsLiquidCapacity = allWellsLiquidCapacity;
	forecastResult.AllWellsGasCapacity = allWellsGasCapacity;

	if (deck.Hydrocarbon_Stream == oil)
	{
		double URo = 0;

		switch (scenario)
		{
		case 1:
			URo = deck.URo_1P_1C;
			break;

		case 2:
			URo = deck.URo_2P_2C;
			break;

		case 3:
			URo = deck.URo_3P_3C;
			break;
		}

		forecastResult.optimizationWeight = deck.optimizationWeight;
		forecastResult.Cum_Oil_Prod = forecastResult_old.Cum_Oil_Prod + (forecastResult.Oil_rate * DeltaT) / MM;
		forecastResult.Cum_Gas_Prod = forecastResult_old.Cum_Gas_Prod + (forecastResult.Gas_Rate * DeltaT) / MM;
		forecastResult.Cum_Water_Prod = forecastResult_old.Cum_Water_Prod + (forecastResult.Water_Rate * DeltaT) / MM;

		forecastResult.URo = URo - forecastResult.Cum_Oil_Prod;
		forecastResult.CutBackUpperBound = 1.0;
		forecastResult.URg = 0;
		forecastResult.CutBackUpperBound = forecastResult.URo * MM / (DeltaT * forecastResult.Oil_rate);
		forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
													forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
		if (forecastResult.CutBackUpperBound > 1.0)
		{
			forecastResult.CutBackUpperBound = 1.0;
		}

	}
	else
	{
		double URg = 0;

		switch (scenario)
		{
		case 1:
			URg = deck.URg_1P_1C;
			break;

		case 2:
			URg = deck.URg_2P_2C;
			break;

		case 3:
			URg = deck.URg_3P_3C;
			break;
		}

		forecastResult.optimizationWeight = deck.optimizationWeight;
		forecastResult.Cum_Oil_Prod = forecastResult_old.Cum_Oil_Prod + (forecastResult.Oil_rate * DeltaT) / MM;

		forecastResult.Cum_Water_Prod = forecastResult_old.Cum_Water_Prod + (forecastResult.Water_Rate * DeltaT) / MM;

		forecastResult.URo = 0;
		forecastResult.URg = URg - forecastResult.Cum_Gas_Prod;
		forecastResult.CutBackUpperBound = 1.0;
		forecastResult.IsFlowing = GetIsWellFlowing(forecastResult.isOilTerminated,
													forecastResult.isGasTerminated, forecastResult.isWaterTerminated);
		forecastResult.CutBackUpperBound = forecastResult.URg * MM / (DeltaT * forecastResult.Gas_Rate_NotTerminated);
		if (forecastResult.CutBackUpperBound > 1.0)
		{
			forecastResult.CutBackUpperBound = 1.0;
		}
	}

	WellAbandonmentConditions(scenario, deck, forecastResult, forecastResult_old);
}

void CalculateDeckVariables::WellAbandonmentConditions(int &scenario, InputDeckStruct &deck, ForecastResult &forecastResult, ForecastResult &forecastResult_old)
{

	Method = 1;
	double MM = 1000000.0;
	//double upperbound = DeltaT;
	CalculateDeckVariables obj;
	string logger = "";

	//int interval = 10;
	forecastResult.OptimalSolution = optimalSolution;
	forecastResult.AllWellsLiquidCapacity = allWellsLiquidCapacity;
	forecastResult.AllWellsGasCapacity = allWellsGasCapacity;

	if (deck.Hydrocarbon_Stream == oil)
	{
		double URo = 0;
		double Ql_Aband = 0;
		double GOR_Aband = 0;
		double BSW_Aband = 0;

		switch (scenario)
		{
		case 1:
			URo = deck.URo_1P_1C;
			Ql_Aband = deck.Aband_Liquid_Gas_Rate_1P_1C;
			GOR_Aband = deck.Aband_GOR_CGR_1P_1C;
			BSW_Aband = deck.Aband_BSW_WGR_1P_1C;
			break;

		case 2:
			URo = deck.URo_2P_2C;
			Ql_Aband = deck.Aband_Liquid_Gas_Rate_2P_2C;
			GOR_Aband = deck.Aband_GOR_CGR_2P_2C;
			BSW_Aband = deck.Aband_BSW_WGR_2P_2C;
			break;

		case 3:
			URo = deck.URo_3P_3C;
			Ql_Aband = deck.Aband_Liquid_Gas_Rate_3P_3C;
			GOR_Aband = deck.Aband_GOR_CGR_2P_2C;
			BSW_Aband = deck.Aband_BSW_WGR_3P_3C;
			break;
		}


		/* logger = logger + 
		"Liquid_rate = "  + to_string(forecastResult.Liquid_Rate) + " * " +
		"Oil_rate  = "  + to_string(forecastResult.Oil_rate) + " * " +
		"Gas_Rate = "  + to_string(forecastResult.Gas_Rate) + " * " +
		"Cum_Oil_Prod = "  + to_string(forecastResult.Cum_Oil_Prod) + " * " +
		"Cum_Liquid_Prod Old = " + to_string(forecastResult_old.Cum_Liquid_Prod) + " * " +
		"URo = " + to_string(forecastResult.URo) + " * " +
		"BSW = " + to_string(forecastResult.BSW) + " * " +
		"GOR = " + to_string(forecastResult.GOR) + "\n"; */

		/* 
			Abandon well if there is no reserves
		} */
		if(dURConstrained == true){
			if (forecastResult.URo <= 0){

				forecastResult.IsFlowing = false;
				forecastResult.Gas_Rate = 0;
				forecastResult.Oil_rate = 0;
				forecastResult.Water_Rate = 0;
				forecastResult.Gas_Rate_NotTerminated = 0;
				forecastResult.Oil_rate_NotTerminated = 0;
				forecastResult.Liquid_Rate = 0;
				forecastResult.Liquid_rate_NotTerminated = 0;
				forecastResult.GOR = 0;
				forecastResult.WGR = 0;
				forecastResult.BSW = 0;
				forecastResult.CGR = 0;
				forecastResult.Gas_Demand = 0;
				forecastResult.Gas_Own_Use = 0;
				forecastResult.Gas_Flared = 0;
				forecastResult.reasonForTermination = "Terminated by Oil DUR";
				return;

			}
		}

		/* 
			Abandon well if there is liquid rate is less than or equal to abandonment liquid rate
		} */
		if (forecastResult.Liquid_rate_NotTerminated <= Ql_Aband){

			forecastResult.IsFlowing = false;
			forecastResult.Gas_Rate = 0;
			forecastResult.Oil_rate = 0;
			forecastResult.Water_Rate = 0;
			forecastResult.Gas_Rate_NotTerminated = 0;
			forecastResult.Oil_rate_NotTerminated = 0;
			forecastResult.Liquid_Rate = 0;
			forecastResult.Liquid_rate_NotTerminated = 0;
			forecastResult.GOR = 0;
			forecastResult.WGR = 0;
			forecastResult.BSW = 0;
			forecastResult.CGR = 0;
			forecastResult.Gas_Demand = 0;
			forecastResult.Gas_Own_Use = 0;
			forecastResult.Gas_Flared = 0;
			forecastResult.reasonForTermination = "Terminated by Liquid Abandonment Rate";
			return;
		}


			
		/* //Abandon well if there if GOR is greater than abandonment GOR
		if (forecastResult.GOR >= GOR_Aband &&
			GOR_Aband > 0){

			forecastResult.IsFlowing = false;
			forecastResult.Gas_Rate = 0;
			forecastResult.Oil_rate = 0;
			forecastResult.Water_Rate = 0;
			forecastResult.Gas_Rate_NotTerminated = 0;
			forecastResult.Oil_rate_NotTerminated = 0;
			forecastResult.Liquid_Rate = 0;
			forecastResult.Liquid_rate_NotTerminated = 0;
			forecastResult.GOR = 0;
			forecastResult.WGR = 0;
			forecastResult.BSW = 0;
			forecastResult.CGR = 0;
			forecastResult.Gas_Demand = 0;
			forecastResult.Gas_Own_Use = 0;
			forecastResult.Gas_Flared = 0;
			forecastResult.reasonForTermination = "Terminated by Abandonment GOR";
			return;
		}

 
		//Abandon well if there if BSW is greater than abandonment BSW
		if (forecastResult.BSW >= BSW_Aband && BSW_Aband > 0){

			forecastResult.IsFlowing = false;
			forecastResult.Gas_Rate = 0;
			forecastResult.Oil_rate = 0;
			forecastResult.Water_Rate = 0;
			forecastResult.Gas_Rate_NotTerminated = 0;
			forecastResult.Oil_rate_NotTerminated = 0;
			forecastResult.Liquid_Rate = 0;
			forecastResult.Liquid_rate_NotTerminated = 0;
			forecastResult.GOR = 0;
			forecastResult.WGR = 0;
			forecastResult.BSW = 0;
			forecastResult.CGR = 0;
			forecastResult.Gas_Demand = 0;
			forecastResult.Gas_Own_Use = 0;
			forecastResult.Gas_Flared = 0;
			forecastResult.reasonForTermination = "Terminated by Abandonment BSW";
			return;

		} */
	}
	else
	{
		double URg = 0;
		double Qg_Aband = 0;
		double CGR_Aband = 0;
		double WGR_Aband = 0;
		double InitialCGR = 0;
		double InitialWGR = 0;

		//
		logger = logger + 
		"Liquid_rate = "  + to_string(forecastResult.Liquid_Rate) + " * " +
		"Oil_rate  = "  + to_string(forecastResult.Oil_rate) + " * " +
		"Gas_Rate = "  + to_string(forecastResult.Gas_Rate) + " * " +
		"Cum_Oil_Prod = "  + to_string(forecastResult.Cum_Oil_Prod) + " * " +
		"Cum_Liquid_Prod Old = " + to_string(forecastResult_old.Cum_Liquid_Prod) + " * " +
		"URg = " + to_string(forecastResult.URg) + " * " +
		"WGR = " + to_string(forecastResult.WGR) + " * " +
		"CGR_Aband = " + to_string(deck.Aband_GOR_CGR_1P_1C) + " * " +
		"CGR = " + to_string(forecastResult.CGR) + "\n";
		//std::cout << CurrentDate.day << "/" << CurrentDate.month << "/" << CurrentDate.year << std::endl;

		/* if(deck.Module == "FO12U60T_FO12 U60X_P03"){
			std::cout << logger;
		} */

		switch (scenario)
		{
		case 1:
			URg = deck.URg_1P_1C;
			Qg_Aband = deck.Aband_Liquid_Gas_Rate_1P_1C;
			CGR_Aband = deck.Aband_GOR_CGR_1P_1C;
			WGR_Aband = deck.Aband_BSW_WGR_1P_1C;
			InitialCGR = deck.Init_GOR_CGR;
			break;

		case 2:
			URg = deck.URg_2P_2C;
			Qg_Aband = deck.Aband_Liquid_Gas_Rate_2P_2C;
			CGR_Aband = deck.Aband_GOR_CGR_2P_2C;
			WGR_Aband = deck.Aband_BSW_WGR_2P_2C;
			InitialCGR = deck.Init_GOR_CGR;
			break;

		case 3:
			URg = deck.URg_3P_3C;
			Qg_Aband = deck.Aband_Liquid_Gas_Rate_3P_3C;
			CGR_Aband = deck.Aband_GOR_CGR_3P_3C;
			WGR_Aband = deck.Aband_BSW_WGR_3P_3C;
			InitialCGR = deck.Init_GOR_CGR;
			break;
		}

		/* 
			Abandon well if there is no reserves
		} */
		if(dURConstrained == true){
			if (forecastResult.URg <= 0){

				/* if(deck.Module == "FO12U60T_FO12 U60X_P03"){
					std::cout << "FO12U60T_FO12 U60X_P03 Well Killed by URg \n";
				} */

				forecastResult.IsFlowing = false;
				forecastResult.Gas_Rate = 0;
				forecastResult.Oil_rate = 0;
				forecastResult.Water_Rate = 0;
				forecastResult.Gas_Rate_NotTerminated = 0;
				forecastResult.Oil_rate_NotTerminated = 0;
				forecastResult.Liquid_Rate = 0;
				forecastResult.Liquid_rate_NotTerminated = 0;
				forecastResult.GOR = 0;
				forecastResult.WGR = 0;
				forecastResult.BSW = 0;
				forecastResult.CGR = 0;
				forecastResult.Gas_Demand = 0;
				forecastResult.Gas_Own_Use = 0;
				forecastResult.Gas_Flared = 0;
				forecastResult.reasonForTermination = "Terminated by Gas DUR";
				return;

			}
		}

		/* 
			Abandon well if there is gas rate is less than or equal to abandonment gas rate
		} */
		if (forecastResult.Gas_Rate_NotTerminated <= Qg_Aband){

			logger = logger + 
			"Gas_Rate = "  + to_string(forecastResult.Gas_Rate) + " * " +
			"Gas_Rate_NotTerminated = "  + to_string(forecastResult.Gas_Rate_NotTerminated) + " * " +
			"Qg_Aband = "  + to_string(Qg_Aband) + " * "  + "\n";

			/* if(deck.Module == "FO12U60T_FO12 U60X_P03"){
				std::cout << "FO12U60T_FO12 U60X_P03 Well Killed by Qg_Aband " << logger;
			} */

			forecastResult.IsFlowing = false;
			forecastResult.Gas_Rate = 0;
			forecastResult.Oil_rate = 0;
			forecastResult.Water_Rate = 0;
			forecastResult.Gas_Rate_NotTerminated = 0;
			forecastResult.Oil_rate_NotTerminated = 0;
			forecastResult.Liquid_Rate = 0;
			forecastResult.Liquid_rate_NotTerminated = 0;
			forecastResult.GOR = 0;
			forecastResult.WGR = 0;
			forecastResult.BSW = 0;
			forecastResult.CGR = 0;
			forecastResult.Gas_Demand = 0;
			forecastResult.Gas_Own_Use = 0;
			forecastResult.Gas_Flared = 0;
			forecastResult.reasonForTermination = "Terminated by Abandonment Gas Rate";
			return;

		}


		/* 
			Abandon well if there if CGR is less than or equal to abandonment CGR
		} */
		if (forecastResult.CGR <= CGR_Aband && InitialCGR > 0){

			logger = logger + 
			"CGR = "  + to_string(forecastResult.CGR) + " * " +
			"InitialCGR = "  + to_string(InitialCGR) + " * " +
			"CGR_Aband = "  + to_string(CGR_Aband) + " * "  + "\n";

			/* if(deck.Module == "FO12U60T_FO12 U60X_P03"){
				std::cout << "FO12U60T_FO12 U60X_P03 Well Killed by CGR_Aband " << logger;
			} */

			forecastResult.IsFlowing = false;
			forecastResult.Gas_Rate = 0;
			forecastResult.Oil_rate = 0;
			forecastResult.Water_Rate = 0;
			forecastResult.Gas_Rate_NotTerminated = 0;
			forecastResult.Oil_rate_NotTerminated = 0;
			forecastResult.Liquid_Rate = 0;
			forecastResult.Liquid_rate_NotTerminated = 0;
			forecastResult.GOR = 0;
			forecastResult.WGR = 0;
			forecastResult.BSW = 0;
			forecastResult.CGR = 0;
			forecastResult.Gas_Demand = 0;
			forecastResult.Gas_Own_Use = 0;
			forecastResult.Gas_Flared = 0;
			forecastResult.reasonForTermination = "Terminated by Abandonment CGR";
			return;

		}


		/* 
			Abandon well if there if WGR is greater than or equal to abandonment WGR
		} */
		if (forecastResult.WGR >= WGR_Aband && WGR_Aband > 0){

			/* if(deck.Module == "FO12U60T_FO12 U60X_P03"){
				std::cout << "FO12U60T_FO12 U60X_P03 Well Killed by WGR_Aband \n";
			} */

			forecastResult.IsFlowing = false;
			forecastResult.Gas_Rate = 0;
			forecastResult.Oil_rate = 0;
			forecastResult.Water_Rate = 0;
			forecastResult.Gas_Rate_NotTerminated = 0;
			forecastResult.Oil_rate_NotTerminated = 0;
			forecastResult.Liquid_Rate = 0;
			forecastResult.Liquid_rate_NotTerminated = 0;
			forecastResult.GOR = 0;
			forecastResult.WGR = 0;
			forecastResult.BSW = 0;
			forecastResult.CGR = 0;
			forecastResult.Gas_Demand = 0;
			forecastResult.Gas_Own_Use = 0;
			forecastResult.Gas_Flared = 0;
			forecastResult.reasonForTermination = "Terminated by Abandonment WGR";
			return;

		}
	}

	/* logger = logger + 
	"Liquid_rate = "  + to_string(forecastResult.Liquid_Rate) + " * " +
	"Oil_rate  = "  + to_string(forecastResult.Oil_rate) + " * " +
	"Gas_Rate = "  + to_string(forecastResult.Gas_Rate) + " * " +
	"Cum_Oil_Prod = "  + to_string(forecastResult.Cum_Oil_Prod) + " * " +
	"Cum_Liquid_Prod Old = " + to_string(forecastResult_old.Cum_Liquid_Prod) + " * " +
	"URg = " + to_string(forecastResult.URg) + " * " +
	"WGR = " + to_string(forecastResult.WGR) + " * " +
	"CGR_Aband = " + to_string(deck.Aband_GOR_CGR_1P_1C) + " * " +
	"CGR = " + to_string(forecastResult.CGR) + 
	"CurrentDate = " + to_string(CurrentDate.day) + "/" + to_string(CurrentDate.month) + "/"+ to_string(CurrentDate.year) + "/" + "\n"; */

	/* logger = logger + 
	"Gas_Rate = "  + to_string(forecastResult.Gas_Rate) + " * " +
	"CurrentDate = " + to_string(CurrentDate.day) + "/" + to_string(CurrentDate.month) + "/" + to_string(CurrentDate.year) + "/" + "\n";

	if(deck.Module == "FO12U60T_FO12 U60X_P03"){
		std::cout << checker <<  logger;
	} */
}
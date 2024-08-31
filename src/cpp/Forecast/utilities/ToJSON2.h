#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include <exception>
#include <tuple>
#include "../ProductionForecast/Forecast.h"
#include "../ProductionForecast/Decline_Curve_Analysis.h"
#include "../../MathematicsLibrary/Integration.h"
#include "../ProductionForecast/FractionalFlow.h"
#include "../ProductionForecast/DateCreation.h"
#include "../../MathematicsLibrary/MainSimplex.h"
#include "../../MathematicsLibrary/Arithmetic.h"
#include "../../MathematicsLibrary/Interpolation.h"
#include "../ProductionForecast/Inputdeck.h"
#include "../ProductionForecast/dataPivoting.h"

using namespace std;
using namespace std::placeholders;


class ReportJSON2
{

    public:
		dataPivoting _dataPivoting;
        DateCreation dateCreation;
		vector<FacilityStructExternal> FacilityTable;
		double myZero = 0.00000001;
		FractionalFlow fractionalFlow;
		Decline_Curve_Analysis decline_Curve_Analysis;
		Inputdeck inputdeck;
		RunParameter runParameter;
		Arithmetic arithmetic;
		Interpolation interpolation;
		int nValidatedDecks;
		bool isMonthly = true;

		string GetRow(ForecastResult& r, int &scenario, int& ii, bool& isLastRow);
		string GetRow(ForecastResult& r, int& scenario, int& ii, vector<Date>& dateTimes);
		void GetForecastWellMonthOutput(int& k, int& j, int& scenario,
 		string& table, vector<ForecastResult>& resultsWellNew);
		void GetForecastWellYearlyOutput(string& tableYearly, vector<ForecastResult>& resultsWellNew,
		vector<Date>& datesNew, string& ModuleName, string& FacilityName, int& scenario);
	

		FacilityStructExternal GetMinimumSelectedEquipmentsGasOwnUseByDate(vector<FacilityStructExternal> &gasOwnUse, vector<string> &selectedEquipments, Date date);
		FacilityStructExternal GetMinimumSelectedEquipmentsGasFlaredByDate(vector<FacilityStructExternal> &gasFlared, vector<string> &selectedEquipments, Date date);
		FacilityStructExternal GetSelectedEquipmentGasOwnuseByDate(vector<FacilityStructExternal> &gasOwnUse, string &selectedEquipment, Date date);
		FacilityStructExternal GetSelectedEquipmentGasFlaredByDate(vector<FacilityStructExternal> &gasFlared, string &selectedEquipment, Date date);
		vector<WellSchedule> GetWellSchedulesSheetData(vector<WellReroute>& wellRerouteDecks,
		vector<WellRampUp>& wellRampUpDecks, vector<ShutInOpenUp>& wellShutInOpenDecks,
		Date& StopDate);
		vector<WellSchedule> SortWellSchedules(vector<WellSchedule> &wellSchedules);
		tuple<vector<Node>, vector<Date>> GetNodesSheetData(vector<Node> &nodes,
		vector<FacilityStructExternal> &equipmentCapacities, 
		vector<FacilityStructExternal> &deferments,
		vector<FacilityStructExternal> &crudeOilLosses,
		vector<FacilityStructExternal>& gasOwnUse, 
		vector<FacilityStructExternal>& gasFlared);
		vector<Node> GetNodes(vector<InternalExternalEquipmentName> &internalExternalFacilitiesNames,
		vector<vector<string>> &equipmentConnections);
		vector<FacilityInEquipementConnection> GetFacilitiesInEquipmentConnections(
		vector<InternalExternalEquipmentName> &internalExternalFacilitiesNames,
		vector<vector<string>> &equipmentConnections, int &nodeIndex);
		tuple<vector<FacilityStructExternal>,vector<Date>> GetFacilitiesSheetData(
		vector<FacilityInEquipementConnection> &facilityInEquipementConnections,
		vector<FacilityStructExternal> &equipmentCapacities, vector<FacilityStructExternal> &deferments,
		vector<FacilityStructExternal> &crudeOilLosses,
		vector<FacilityStructExternal>& gasOwnUse, 
		vector<FacilityStructExternal>& gasFlared);
		vector<Date> GetUniqueDatesForFacilities(vector<FacilityStructExternal> &equipmentCapacities,
		vector<FacilityStructExternal> &deferments,
		vector<FacilityStructExternal> &crudeOilLosses,
		vector<FacilityStructExternal>& gasOwnUse, 
		vector<FacilityStructExternal>& gasFlared);
		bool isContainDate(vector<Date> &dates, Date date);
		FacilityStructExternal GetMinimumSelectedEquipmentsCapacityByDate(vector<FacilityStructExternal> &equipmentCapacities, 
		vector<string> &selectedEquipments, Date date);
		FacilityStructExternal GetSelectedEquipmentCapacityByDate(vector<FacilityStructExternal> &equipmentCapacities, 
		string &selectedEquipment, Date date);
		FacilityStructExternal GetMinimumSelectedEquipmentsDefermentByDate(vector<FacilityStructExternal> &deferments, 
		vector<string> &selectedEquipments, Date date);
		FacilityStructExternal GetSelectedEquipmentDefermentByDate(vector<FacilityStructExternal> &deferments, 
		string &selectedEquipment, Date date);
		FacilityStructExternal GetMinimumSelectedEquipmentsCrudeOilLossesByDate(vector<FacilityStructExternal> &crudeOilLosses, 
		vector<string> &selectedEquipments, Date date);
		FacilityStructExternal GetSelectedEquipmentCrudeOilLossesByDate(vector<FacilityStructExternal> &crudeOilLosses, 
		string &selectedEquipment, Date date);
		vector<FacilityStructExternal> SortFacilitiesData(vector<FacilityStructExternal> &facilitiesData);
		string GetForecastOutput(int& scenario,
		vector<vector<FacilityWellsIndicies>>& facilityWellsIndicies, 
		vector<Date>& dateTimes, int& facilityIndex, int& wellIndex,
		string& wellName, string& facilityName);
        map<string, map<string, map<string, string>>> GetForecastOutputAllFacilities(int& scenario,
        vector<vector<FacilityWellsIndicies>>& facilityWellsIndicies, 
        vector<Date>& dateTimes);
        void GetForecastResultsByScenario(
        ResponseData responseData,
        string scenarioName, string SolutionSpace, vector<string> facilityNames);
		map<string, string> GetForecastOutputAsJson(vector<ForecastResult>& results);
		map<string, map<string, string>> GetForecastOutputAsJson(vector<vector<ForecastResult>>& results);


		vector<vector<vector<ForecastResult>>> results;

		ReportJSON2();
		~ReportJSON2();

};

ReportJSON2::ReportJSON2(){

}

ReportJSON2::~ReportJSON2(){

}


map<string, string> ReportJSON2::GetForecastOutputAsJson(vector<ForecastResult>& results)
{

	int nResults = results.size();

	map<string, string> moduleResult;
	string table = "";
	int i = 1;
	bool isLastRow = false;
	for (int ii = 0; ii < nResults; ii++) {

		ForecastResult r = results[ii];

		if(ii == nResults-1){
			isLastRow = true;
		}

		table = table + GetRow(r, i, ii, isLastRow);

	}

	moduleResult["resultWells"] = table;

	return moduleResult;
			
}

map<string, map<string, string>> ReportJSON2::GetForecastOutputAsJson(vector<vector<ForecastResult>>& results)
{
	int nWells = results.size();

	map<string, map<string, string>> decksPerFacility;
	int i = 0;
	for(i = 0; i < nWells; i++){
		map<string, string> deckObject = GetForecastOutputAsJson(results[i]);
		string wellNo = std::to_string(i);
		decksPerFacility[wellNo] = deckObject;
	}
	return decksPerFacility;
}

void ReportJSON2::GetForecastResultsByScenario(ResponseData responseData,
string scenarioName, string SolutionSpace, vector<string> facilityNames){


  for (const auto& outer1 : responseData.monthlyReport) {
    const string& solutionSpace = outer1.first;
    if(solutionSpace == SolutionSpace){
        for (const auto& outer2 : outer1.second) {
            const string& scenario = outer2.first;
            if(scenarioName == scenario) {
                for(const auto& facilityName : facilityNames){
                    for (const auto& outer3 : outer2.second) {
                        const string& facility = outer3.first;
                        if(facilityName == facility){

                            break;
                        }
                    }      
                }
                break;
            }
        }
        break;
    }
  }

}

map<string, map<string, map<string, string>>> ReportJSON2::GetForecastOutputAllFacilities(int& scenario,
vector<vector<FacilityWellsIndicies>>& facilityWellsIndicies, 
vector<Date>& dateTimes)
{
	int  mkdirretval = 0;
	int nDates = dateTimes.size();
   int j = nDates - 1, facilityIndex = 0;
   int wellIndex = 0;
   int nFacilities = facilityWellsIndicies[j].size();
   map<string, map<string, map<string, string>>> FaclitiesObject;
   for(facilityIndex = 0; facilityIndex < nFacilities; facilityIndex++){
		facilityWellsIndicies[j][facilityIndex].Facility;

		int nWells = facilityWellsIndicies[j][facilityIndex].WellNames.size();
        map<string, map<string, string>> decksPerFacility;
		for(wellIndex = 0; wellIndex < nWells; wellIndex++){
			string table = GetForecastOutput(scenario,facilityWellsIndicies,dateTimes, 
			facilityIndex, wellIndex,
			facilityWellsIndicies[j][facilityIndex].WellNames[wellIndex],
			facilityWellsIndicies[j][facilityIndex].Facility);

            map<string, string> deckObject;
            deckObject["resultWells"] = table;
            
			decksPerFacility[facilityWellsIndicies[j][facilityIndex].WellNames[wellIndex]] = deckObject;
		}

		FaclitiesObject[facilityWellsIndicies[j][facilityIndex].Facility] = decksPerFacility;  
   }

   return FaclitiesObject;
}

string ReportJSON2::GetForecastOutput(int& scenario,
vector<vector<FacilityWellsIndicies>>& facilityWellsIndicies, 
vector<Date>& dateTimes, int& facilityIndex, int& wellIndex,
string& wellName, string& facilityName)
{

    int j = 0, mkdirretval = 0;
	string logger = "";
			
	int nDates = dateTimes.size();
	vector<ForecastResult> wellResultsForAggregation;

	for(j = 0; j < nDates; j++){

		if(j > 0){
			
			if(facilityWellsIndicies[j-1][facilityIndex].tables.size() < 
			facilityWellsIndicies[j][facilityIndex].tables.size()){
				facilityWellsIndicies[j][facilityIndex].tables = facilityWellsIndicies[j-1][facilityIndex].tables;
				facilityWellsIndicies[j][facilityIndex].tables.push_back("");
			}else{
				facilityWellsIndicies[j][facilityIndex].tables = facilityWellsIndicies[j-1][facilityIndex].tables;
			}
		}

		if(results[j][facilityIndex][wellIndex].IsFlowing == false) 
		{
			//Clean up unwanted data
			results[j][facilityIndex][wellIndex].InitailizeData2();
			
		}

		wellResultsForAggregation.push_back(results[j][facilityIndex][wellIndex]);
		
	}

	string table = "";
	nDates = wellResultsForAggregation.size();
	for(j = 0; j < nDates; j++){

		table = table +  GetRow(wellResultsForAggregation[j], scenario, j, dateTimes);
	}
	
	return table;

			
}

vector<FacilityStructExternal> ReportJSON2::SortFacilitiesData(vector<FacilityStructExternal> &facilitiesData)
{

	DateCreation dateCreation;
	FacilityStructExternal temp;
	int n = facilitiesData.size();

	for (int j = 0; j <= n - 2; j++)
	{
		for (int i = 0; i <= n - 2; i++)
		{
			if (dateCreation.IsMaximumDate(facilitiesData[i].FacilityDate1P, facilitiesData[i + 1].FacilityDate1P))
			{
				temp = facilitiesData[i + 1];
				facilitiesData[i + 1] = facilitiesData[i];
				facilitiesData[i] = temp;
			}
		}
	}

	return facilitiesData;
}


FacilityStructExternal ReportJSON2::GetSelectedEquipmentCrudeOilLossesByDate(vector<FacilityStructExternal> &crudeOilLosses, string &selectedEquipment, Date date)
{
	FacilityStructExternal selectedCrudeLosses;
	selectedCrudeLosses.Crudeoil_Lossess1P = 0;
	int i = 0, n = crudeOilLosses.size();
	DateCreation dateCreation;
	vector<FacilityStructExternal>  selectedEquipmentCrudeOilLosses;
	for (i = 0; i < n; i++)
	{
		if (crudeOilLosses[i].Primary_Facility == selectedEquipment)
		{
			selectedEquipmentCrudeOilLosses.push_back(crudeOilLosses[i]);
		}
	}

	n = selectedEquipmentCrudeOilLosses.size();

	if(n > 0){

		if (dateCreation.EqualTo(date, selectedEquipmentCrudeOilLosses[0].FacilityDate1P))
		{

			selectedCrudeLosses = selectedEquipmentCrudeOilLosses[0];

			return selectedCrudeLosses;
		}

		if (dateCreation.IsMinimumDate(date, selectedEquipmentCrudeOilLosses[0].FacilityDate1P))
		{
			selectedCrudeLosses = selectedEquipmentCrudeOilLosses[0];
			return selectedCrudeLosses;
		}

	}

	if (n > 1)
	{
		for (i = 1; i < n; i++)
		{

			if (dateCreation.EqualTo(date, selectedEquipmentCrudeOilLosses[i - 1].FacilityDate1P))
			{
				selectedCrudeLosses = selectedEquipmentCrudeOilLosses[i - 1];
				return selectedCrudeLosses;
			}

			if (dateCreation.EqualTo(date, selectedEquipmentCrudeOilLosses[i].FacilityDate1P))
			{
				selectedCrudeLosses = selectedEquipmentCrudeOilLosses[i];

				return selectedCrudeLosses;
			}

			if (dateCreation.IsMaximumDate(date, selectedEquipmentCrudeOilLosses[i - 1].FacilityDate1P) && 
			dateCreation.IsMinimumDate(date, selectedEquipmentCrudeOilLosses[i].FacilityDate1P))
			{
				selectedCrudeLosses = selectedEquipmentCrudeOilLosses[i - 1];
				return selectedCrudeLosses;
			}
		}
	}

	if(n > 0){
		if (dateCreation.IsMaximumDate(date, selectedEquipmentCrudeOilLosses[n - 1].FacilityDate1P))
		{
			selectedCrudeLosses = selectedEquipmentCrudeOilLosses[n - 1];
			return selectedCrudeLosses;
		}
	}

	return selectedCrudeLosses;
}

FacilityStructExternal ReportJSON2::GetSelectedEquipmentGasOwnuseByDate(vector<FacilityStructExternal> &gasOwnUse, string &selectedEquipment, Date date)
{
	FacilityStructExternal selectedGasOwnUse;
	selectedGasOwnUse.GasOwnUse1P = 0;
	int i = 0, n = gasOwnUse.size();
	DateCreation dateCreation;
	vector<FacilityStructExternal>  selectedEquipmentGasOwnUse;
	for (i = 0; i < n; i++)
	{
		if (gasOwnUse[i].Primary_Facility == selectedEquipment)
		{
			selectedEquipmentGasOwnUse.push_back(gasOwnUse[i]);
		}
	}

	n = selectedEquipmentGasOwnUse.size();
	if (n > 0){

		if (dateCreation.EqualTo(date, selectedEquipmentGasOwnUse[0].FacilityDate1P))
		{

			selectedGasOwnUse = selectedEquipmentGasOwnUse[0];

			return selectedGasOwnUse;
		}

		if (dateCreation.IsMinimumDate(date, selectedEquipmentGasOwnUse[0].FacilityDate1P))
		{
			selectedGasOwnUse = selectedEquipmentGasOwnUse[0];
			return selectedGasOwnUse;
		}
	}

	if (n > 1)
	{
		for (i = 1; i < n; i++)
		{

			if (dateCreation.EqualTo(date, selectedEquipmentGasOwnUse[i - 1].FacilityDate1P))
			{
				selectedGasOwnUse = selectedEquipmentGasOwnUse[i - 1];
				return selectedGasOwnUse;
			}

			if (dateCreation.EqualTo(date, selectedEquipmentGasOwnUse[i].FacilityDate1P))
			{
				selectedGasOwnUse = selectedEquipmentGasOwnUse[i];

				return selectedGasOwnUse;
			}

			if (dateCreation.IsMaximumDate(date, selectedEquipmentGasOwnUse[i - 1].FacilityDate1P) && 
			dateCreation.IsMinimumDate(date, selectedEquipmentGasOwnUse[i].FacilityDate1P))
			{
				selectedGasOwnUse = selectedEquipmentGasOwnUse[i - 1];
				return selectedGasOwnUse;
			}
		}
	}

	if(n > 0){
		if (dateCreation.IsMaximumDate(date, selectedEquipmentGasOwnUse[n - 1].FacilityDate1P))
		{
			selectedGasOwnUse = selectedEquipmentGasOwnUse[n - 1];
			return selectedGasOwnUse;
		}
	}

	return selectedGasOwnUse;
}

FacilityStructExternal ReportJSON2::GetSelectedEquipmentGasFlaredByDate(vector<FacilityStructExternal> &gasFlared, string &selectedEquipment, Date date)
{
	FacilityStructExternal selectedGasFlared;
	selectedGasFlared.GasFlared1P = 0;
	int i = 0, n = gasFlared.size();
	DateCreation dateCreation;
	vector<FacilityStructExternal>  selectedEquipmentGasFlared;
	for (i = 0; i < n; i++)
	{
		if (gasFlared[i].Primary_Facility == selectedEquipment)
		{
			selectedEquipmentGasFlared.push_back(gasFlared[i]);
		}
	}

	n = selectedEquipmentGasFlared.size();

	if(n > 0){
		if (dateCreation.EqualTo(date, selectedEquipmentGasFlared[0].FacilityDate1P))
		{

			selectedGasFlared = selectedEquipmentGasFlared[0];

			return selectedGasFlared;
		}

		if (dateCreation.IsMinimumDate(date, selectedEquipmentGasFlared[0].FacilityDate1P))
		{
			selectedGasFlared = selectedEquipmentGasFlared[0];
			return selectedGasFlared;
		}
	}

	if (n > 1)
	{
		for (i = 1; i < n; i++)
		{

			if (dateCreation.EqualTo(date, selectedEquipmentGasFlared[i - 1].FacilityDate1P))
			{
				selectedGasFlared = selectedEquipmentGasFlared[i - 1];
				return selectedGasFlared;
			}

			if (dateCreation.EqualTo(date, selectedEquipmentGasFlared[i].FacilityDate1P))
			{
				selectedGasFlared = selectedEquipmentGasFlared[i];

				return selectedGasFlared;
			}

			if (dateCreation.IsMaximumDate(date, selectedEquipmentGasFlared[i - 1].FacilityDate1P) && 
			dateCreation.IsMinimumDate(date, selectedEquipmentGasFlared[i].FacilityDate1P))
			{
				selectedGasFlared = selectedEquipmentGasFlared[i - 1];
				return selectedGasFlared;
			}
		}
	}

	if(n > 0){
		if (dateCreation.IsMaximumDate(date, selectedEquipmentGasFlared[n - 1].FacilityDate1P))
		{
			selectedGasFlared = selectedEquipmentGasFlared[n - 1];
			return selectedGasFlared;
		}
	}

	return selectedGasFlared;
}

FacilityStructExternal ReportJSON2::GetMinimumSelectedEquipmentsCrudeOilLossesByDate(vector<FacilityStructExternal> &crudeOilLosses, vector<string> &selectedEquipments, Date date)
{
	int i = 0, n = selectedEquipments.size();
	FacilityStructExternal selectedCrudeOilLosses;
	double zero = 0.0000001;

	for (i = 0; i < n; i++)
	{
		selectedCrudeOilLosses = GetSelectedEquipmentCrudeOilLossesByDate(crudeOilLosses, selectedEquipments[i], date);
		if (selectedCrudeOilLosses.Crudeoil_Lossess1P > zero)
		{
			break;
		}
	}

	return selectedCrudeOilLosses;
}

FacilityStructExternal ReportJSON2::GetSelectedEquipmentDefermentByDate(vector<FacilityStructExternal> &deferments, string &selectedEquipment, Date date)
{
	FacilityStructExternal selectedDeferment;
	selectedDeferment.Scheduled_Deferment1P = -9999;
	int i = 0, n = deferments.size();
	DateCreation dateCreation;
	bool check = false;
	vector<FacilityStructExternal>  selectedEquipmentDeferments;
	for (i = 0; i < n; i++)
	{
		if (deferments[i].Primary_Facility == selectedEquipment)
		{
			selectedEquipmentDeferments.push_back(deferments[i]);
		}
	}

	n = selectedEquipmentDeferments.size();

	if(n > 0){

		if (dateCreation.EqualTo(date, selectedEquipmentDeferments[0].FacilityDate1P))
		{

			selectedDeferment = selectedEquipmentDeferments[0];

			return selectedDeferment;
		}

		if (dateCreation.IsMinimumDate(date, selectedEquipmentDeferments[0].FacilityDate1P))
		{
			selectedDeferment = selectedEquipmentDeferments[0];
			return selectedDeferment;
		}
	}

	if (n > 1)
	{
		for (i = 1; i < n; i++)
		{

			if (dateCreation.EqualTo(date, selectedEquipmentDeferments[i - 1].FacilityDate1P))
			{
				selectedDeferment = selectedEquipmentDeferments[i - 1];
				return selectedDeferment;
			}

			if (dateCreation.EqualTo(date, selectedEquipmentDeferments[i].FacilityDate1P))
			{
				selectedDeferment = selectedEquipmentDeferments[i];

				return selectedDeferment;
			}

			if (dateCreation.IsMaximumDate(date, selectedEquipmentDeferments[i - 1].FacilityDate1P) && 
			dateCreation.IsMinimumDate(date, selectedEquipmentDeferments[i].FacilityDate1P))
			{
				selectedDeferment = selectedEquipmentDeferments[i - 1];
				return selectedDeferment;
			}
		}
	}

	if(n > 0){
		if (dateCreation.IsMaximumDate(date, selectedEquipmentDeferments[n - 1].FacilityDate1P))
		{
			selectedDeferment = selectedEquipmentDeferments[n - 1];
			return selectedDeferment;
		}
	}

	return selectedDeferment;
}

FacilityStructExternal ReportJSON2::GetMinimumSelectedEquipmentsDefermentByDate(vector<FacilityStructExternal> &deferments, vector<string> &selectedEquipments, Date date)
{
	int i = 0, n = selectedEquipments.size();
	FacilityStructExternal selectedDeferment;
	bool check1 = false, check2 = false, check3 = false;
	double zero = 0.0000001;

	for (i = 0; i < n; i++)
	{
		selectedDeferment = GetSelectedEquipmentDefermentByDate(deferments, selectedEquipments[i], date);
		if (selectedDeferment.Scheduled_Deferment1P > zero ||
			selectedDeferment.Unscheduled_Deferment1P > zero ||
			selectedDeferment.Thirdparty_Deferment1P > zero)
		{
			break;
		}
	}

	return selectedDeferment;
}

FacilityStructExternal ReportJSON2::GetSelectedEquipmentCapacityByDate(vector<FacilityStructExternal> &equipmentCapacities, string &selectedEquipment, Date date)
{
	
	FacilityStructExternal selectedCapacities;
	selectedCapacities.Gas_Capacity1P = 0;
	selectedCapacities.Liquid_Capacity1P = 0;
	selectedCapacities.AG_Capacity1P = 0;
	selectedCapacities.NAG_Capacity1P = 0;
	selectedCapacities.GasOwnUse1P = 0;
	selectedCapacities.GasDemand1P = 0;
	DateCreation dateCreation;
	int i = 0, n = equipmentCapacities.size();
	vector<FacilityStructExternal>  selectedEquipmentCapacities;
	for (i = 0; i < n; i++)
	{
		if (equipmentCapacities[i].Primary_Facility == selectedEquipment)
		{
			selectedEquipmentCapacities.push_back(equipmentCapacities[i]);
		}
	}

	n = selectedEquipmentCapacities.size();

	if(n > 0){

		if (dateCreation.EqualTo(date, selectedEquipmentCapacities[0].FacilityDate1P))
		{

			selectedCapacities.Gas_Capacity1P = selectedEquipmentCapacities[0].Gas_Capacity1P *
												selectedEquipmentCapacities[0].equityPercentage / 100.0;
			selectedCapacities.Liquid_Capacity1P = selectedEquipmentCapacities[0].Liquid_Capacity1P *
													selectedEquipmentCapacities[0].equityPercentage / 100.0;
			selectedCapacities.Primary_Facility = selectedEquipmentCapacities[0].Primary_Facility;
			selectedCapacities.AG_Capacity1P = selectedEquipmentCapacities[0].AG_Capacity1P *
												selectedEquipmentCapacities[0].equityPercentage / 100.0;
			selectedCapacities.NAG_Capacity1P = selectedEquipmentCapacities[0].NAG_Capacity1P *
												selectedEquipmentCapacities[0].equityPercentage / 100.0;
			selectedCapacities.GasOwnUse1P = selectedEquipmentCapacities[0].GasOwnUse1P *
												selectedEquipmentCapacities[0].equityPercentage / 100.0;
			selectedCapacities.GasDemand1P = selectedEquipmentCapacities[0].GasDemand1P *
												selectedEquipmentCapacities[0].equityPercentage / 100.0;
			selectedCapacities.equityPercentage = selectedEquipmentCapacities[0].equityPercentage;

			return selectedCapacities;
		}

		if (dateCreation.IsMinimumDate(date, selectedEquipmentCapacities[0].FacilityDate1P))
		{
			selectedCapacities.Gas_Capacity1P = selectedEquipmentCapacities[0].Gas_Capacity1P *
												selectedEquipmentCapacities[0].equityPercentage / 100.0;
			selectedCapacities.Liquid_Capacity1P = selectedEquipmentCapacities[0].Liquid_Capacity1P *
													selectedEquipmentCapacities[0].equityPercentage / 100.0;
			selectedCapacities.Primary_Facility = selectedEquipmentCapacities[0].Primary_Facility;
			selectedCapacities.AG_Capacity1P = selectedEquipmentCapacities[0].AG_Capacity1P *
												selectedEquipmentCapacities[0].equityPercentage / 100.0;
			selectedCapacities.NAG_Capacity1P = selectedEquipmentCapacities[0].NAG_Capacity1P *
												selectedEquipmentCapacities[0].equityPercentage / 100.0;
			selectedCapacities.GasOwnUse1P = selectedEquipmentCapacities[0].GasOwnUse1P *
												selectedEquipmentCapacities[0].equityPercentage / 100.0;
			selectedCapacities.GasDemand1P = selectedEquipmentCapacities[0].GasDemand1P *
												selectedEquipmentCapacities[0].equityPercentage / 100.0;
			selectedCapacities.equityPercentage = selectedEquipmentCapacities[0].equityPercentage;
			return selectedCapacities;
		}

	}

	if (n > 1)
	{
		for (i = 1; i < n; i++)
		{

			if (dateCreation.EqualTo(date, selectedEquipmentCapacities[i - 1].FacilityDate1P))
			{
				selectedCapacities.Gas_Capacity1P = selectedEquipmentCapacities[i - 1].Gas_Capacity1P *
											selectedEquipmentCapacities[i - 1].equityPercentage / 100.0;
				selectedCapacities.Liquid_Capacity1P = selectedEquipmentCapacities[i - 1].Liquid_Capacity1P *
														selectedEquipmentCapacities[i - 1].equityPercentage / 100.0;
				selectedCapacities.Primary_Facility = selectedEquipmentCapacities[i - 1].Primary_Facility;
				selectedCapacities.AG_Capacity1P = selectedEquipmentCapacities[i - 1].AG_Capacity1P *
													selectedEquipmentCapacities[i - 1].equityPercentage / 100.0;
				selectedCapacities.NAG_Capacity1P = selectedEquipmentCapacities[i - 1].NAG_Capacity1P *
													selectedEquipmentCapacities[i - 1].equityPercentage / 100.0;
				selectedCapacities.GasOwnUse1P = selectedEquipmentCapacities[i - 1].GasOwnUse1P *
													selectedEquipmentCapacities[i - 1].equityPercentage / 100.0;
				selectedCapacities.GasDemand1P = selectedEquipmentCapacities[i - 1].GasDemand1P *
													selectedEquipmentCapacities[i - 1].equityPercentage / 100.0;
				selectedCapacities.equityPercentage = selectedEquipmentCapacities[i - 1].equityPercentage;
				return selectedCapacities;
			}

			if (dateCreation.EqualTo(date, selectedEquipmentCapacities[i].FacilityDate1P))
			{
				selectedCapacities.Gas_Capacity1P = selectedEquipmentCapacities[i].Gas_Capacity1P *
											selectedEquipmentCapacities[i].equityPercentage / 100.0;
				selectedCapacities.Liquid_Capacity1P = selectedEquipmentCapacities[i].Liquid_Capacity1P *
														selectedEquipmentCapacities[i].equityPercentage / 100.0;
				selectedCapacities.Primary_Facility = selectedEquipmentCapacities[i].Primary_Facility;
				selectedCapacities.AG_Capacity1P = selectedEquipmentCapacities[i].AG_Capacity1P *
													selectedEquipmentCapacities[i].equityPercentage / 100.0;
				selectedCapacities.NAG_Capacity1P = selectedEquipmentCapacities[i].NAG_Capacity1P *
													selectedEquipmentCapacities[i].equityPercentage / 100.0;
				selectedCapacities.GasOwnUse1P = selectedEquipmentCapacities[i].GasOwnUse1P *
													selectedEquipmentCapacities[i].equityPercentage / 100.0;
				selectedCapacities.GasDemand1P = selectedEquipmentCapacities[i].GasDemand1P *
													selectedEquipmentCapacities[i].equityPercentage / 100.0;
				selectedCapacities.equityPercentage = selectedEquipmentCapacities[i].equityPercentage;

				return selectedCapacities;
			}

			if (dateCreation.IsMaximumDate(date, selectedEquipmentCapacities[i - 1].FacilityDate1P) && 
			dateCreation.IsMinimumDate(date, selectedEquipmentCapacities[i].FacilityDate1P))
			{
				selectedCapacities.Gas_Capacity1P = selectedEquipmentCapacities[i - 1].Gas_Capacity1P *
											selectedEquipmentCapacities[i - 1].equityPercentage / 100.0;
				selectedCapacities.Liquid_Capacity1P = selectedEquipmentCapacities[i - 1].Liquid_Capacity1P *
														selectedEquipmentCapacities[i - 1].equityPercentage / 100.0;
				selectedCapacities.Primary_Facility = selectedEquipmentCapacities[i - 1].Primary_Facility;
				selectedCapacities.AG_Capacity1P = selectedEquipmentCapacities[i - 1].AG_Capacity1P *
													selectedEquipmentCapacities[i - 1].equityPercentage / 100.0;
				selectedCapacities.NAG_Capacity1P = selectedEquipmentCapacities[i - 1].NAG_Capacity1P *
													selectedEquipmentCapacities[i - 1].equityPercentage / 100.0;
				selectedCapacities.GasOwnUse1P = selectedEquipmentCapacities[i - 1].GasOwnUse1P *
													selectedEquipmentCapacities[i - 1].equityPercentage / 100.0;
				selectedCapacities.GasDemand1P = selectedEquipmentCapacities[i - 1].GasDemand1P *
													selectedEquipmentCapacities[i - 1].equityPercentage / 100.0;
				selectedCapacities.equityPercentage = selectedEquipmentCapacities[i - 1].equityPercentage;
				return selectedCapacities;
			}
		}
	}

	if(n > 0){

		if (dateCreation.IsMaximumDate(date, selectedEquipmentCapacities[n - 1].FacilityDate1P))
		{
			selectedCapacities.Gas_Capacity1P = selectedEquipmentCapacities[n - 1].Gas_Capacity1P *
												selectedEquipmentCapacities[n - 1].equityPercentage / 100.0;
			selectedCapacities.Liquid_Capacity1P = selectedEquipmentCapacities[n - 1].Liquid_Capacity1P *
													selectedEquipmentCapacities[n - 1].equityPercentage / 100.0;
			selectedCapacities.Primary_Facility = selectedEquipmentCapacities[n - 1].Primary_Facility;
			selectedCapacities.AG_Capacity1P = selectedEquipmentCapacities[n - 1].AG_Capacity1P *
												selectedEquipmentCapacities[n - 1].equityPercentage / 100.0;
			selectedCapacities.NAG_Capacity1P = selectedEquipmentCapacities[n - 1].NAG_Capacity1P *
												selectedEquipmentCapacities[n - 1].equityPercentage / 100.0;
			selectedCapacities.GasOwnUse1P = selectedEquipmentCapacities[n - 1].GasOwnUse1P *
												selectedEquipmentCapacities[n - 1].equityPercentage / 100.0;
			selectedCapacities.GasDemand1P = selectedEquipmentCapacities[n - 1].GasDemand1P *
												selectedEquipmentCapacities[n - 1].equityPercentage / 100.0;
			selectedCapacities.equityPercentage = selectedEquipmentCapacities[n - 1].equityPercentage;
			return selectedCapacities;
		}

	}

	return selectedCapacities;
}

FacilityStructExternal ReportJSON2::GetMinimumSelectedEquipmentsCapacityByDate(vector<FacilityStructExternal> &equipmentCapacities, vector<string> &selectedEquipments, Date date)
{
	int i = 0, n = selectedEquipments.size();
	FacilityStructExternal selectedCapacities;
	double zero = 0.0000001;

	for (i = 0; i < n; i++)
	{
		selectedCapacities = GetSelectedEquipmentCapacityByDate(equipmentCapacities, selectedEquipments[i], date);
		if (selectedCapacities.Gas_Capacity1P > zero ||
			selectedCapacities.Liquid_Capacity1P > zero ||
			selectedCapacities.AG_Capacity1P > zero ||
			selectedCapacities.NAG_Capacity1P > zero)
		{
			break;
		}
	}

	return selectedCapacities;
}

FacilityStructExternal ReportJSON2::GetMinimumSelectedEquipmentsGasOwnUseByDate(vector<FacilityStructExternal> &gasOwnUse, vector<string> &selectedEquipments, Date date)
{
	int i = 0, n = selectedEquipments.size();
	FacilityStructExternal selectedGasOwnUse;
	double zero = 0.0000001;

	for (i = 0; i < n; i++)
	{
		selectedGasOwnUse = GetSelectedEquipmentGasOwnuseByDate(gasOwnUse, selectedEquipments[i], date);
		if (selectedGasOwnUse.GasOwnUse1P > zero)
		{
			break;
		}
	}

	return selectedGasOwnUse;
}

FacilityStructExternal ReportJSON2::GetMinimumSelectedEquipmentsGasFlaredByDate(vector<FacilityStructExternal> &gasFlared, vector<string> &selectedEquipments, Date date)
{
	int i = 0, n = selectedEquipments.size();
	FacilityStructExternal selectedGasFlared;
	double zero = 0.0000001;

	for (i = 0; i < n; i++)
	{
		selectedGasFlared = GetSelectedEquipmentGasFlaredByDate(gasFlared, selectedEquipments[i], date);
		if (selectedGasFlared.GasFlared1P > zero)
		{
			break;
		}
	}

	return selectedGasFlared;
}

bool ReportJSON2::isContainDate(vector<Date> &dates, Date date)
{
	bool check = false;
	int i = 0, n = dates.size();
	for (i = 0; i < n; i++)
	{
		if (dates[i].month == date.month && dates[i].year == date.year)
		{
			check = true;
			break;
		}
	}
	return check;
}

vector<Date> ReportJSON2::GetUniqueDatesForFacilities(vector<FacilityStructExternal> &equipmentCapacities,
		vector<FacilityStructExternal> &deferments,
		vector<FacilityStructExternal> &crudeOilLosses,
		vector<FacilityStructExternal>& gasOwnUse, 
		vector<FacilityStructExternal>& gasFlared)
{
	int i = 0;
	int nEquipmentCapacities = equipmentCapacities.size();
	int nDeferments = deferments.size();
	int nCrudeOilLosses = crudeOilLosses.size();
	int nGasOwnUse = gasOwnUse.size();
	int nGasFlared = gasFlared.size();
	vector<Date> dates;

	for (i = 0; i < nEquipmentCapacities; i++)
	{
		if(equipmentCapacities[i].FacilityDate1P.year < 100){
			double a = 0;
		}

		bool check = isContainDate(dates, equipmentCapacities[i].FacilityDate1P);
		if (check == false)
		{
			dates.push_back(equipmentCapacities[i].FacilityDate1P);
		}
	}

	for (i = 0; i < nDeferments; i++)
	{
		if(deferments[i].FacilityDate1P.year < 100){
			double a = 0;
		}

		bool check = isContainDate(dates, deferments[i].FacilityDate1P);
		if (check == false)
		{
			dates.push_back(deferments[i].FacilityDate1P);
		}
	}

	for (i = 0; i < nCrudeOilLosses; i++)
	{
		if(crudeOilLosses[i].FacilityDate1P.year < 100){
			double a = 0;
		}
		
		bool check = isContainDate(dates, crudeOilLosses[i].FacilityDate1P);
		if (check == false)
		{
			dates.push_back(crudeOilLosses[i].FacilityDate1P);
		}
	}


	for (i = 0; i < nGasOwnUse; i++)
	{
		if(gasOwnUse[i].FacilityDate1P.year < 100){
			double a = 0;
		}

		bool check = isContainDate(dates, gasOwnUse[i].FacilityDate1P);
		if (check == false)
		{
			dates.push_back(gasOwnUse[i].FacilityDate1P);
		}
	}

	for (i = 0; i < nGasFlared; i++)
	{
		if(gasFlared[i].FacilityDate1P.year < 100){
			double a = 0;
		}

		bool check = isContainDate(dates, gasFlared[i].FacilityDate1P);
		if (check == false)
		{
			dates.push_back(gasFlared[i].FacilityDate1P);
		}
	}

	return dates;
}


tuple<vector<FacilityStructExternal>,vector<Date>> ReportJSON2::GetFacilitiesSheetData(
	vector<FacilityInEquipementConnection> &facilityInEquipementConnections,
	vector<FacilityStructExternal> &equipmentCapacities, vector<FacilityStructExternal> &deferments,
	vector<FacilityStructExternal> &crudeOilLosses,
	vector<FacilityStructExternal>& gasOwnUse, 
	vector<FacilityStructExternal>& gasFlared)
{vector<FacilityStructExternal> facilitiesData;
	vector<vector<FacilityStructExternal>> facilitiesMatrixData;
	int j = 0, i = 0, k = 0;
	int nFacilityInEquipementConnections = facilityInEquipementConnections.size();
	int nEquipmentCapacities = equipmentCapacities.size();
	int nDeferments = deferments.size();
	int nCrudeOilLosses = crudeOilLosses.size();
	int nGasOwnUse = gasOwnUse.size();
	int nGasFlared = gasFlared.size();
	DateCreation dateCreation;

	vector<Date> dates = GetUniqueDatesForFacilities(equipmentCapacities, deferments, 
	crudeOilLosses, gasOwnUse, gasFlared); // Sort Dates
	int nDates = dates.size();

	for (j = 0; j < nFacilityInEquipementConnections; j++)
	{
		vector<FacilityStructExternal> facilitiesDataX;
		for (k = 0; k < nDates; k++)
		{
			bool check = false;
			for (i = 0; i < nEquipmentCapacities; i++)
			{
				if (facilityInEquipementConnections[j].facilityName == equipmentCapacities[i].Primary_Facility && 
				dateCreation.EqualTo2(dates[k], equipmentCapacities[i].FacilityDate1P, isMonthly))
				{
					int kk = 0;
					int nMultipleConnections = facilityInEquipementConnections[j].multipleConnections.size();
					FacilityStructExternal facilityStructExternal;
					facilityStructExternal.equipmentType = facilityInEquipementConnections[j].equipmentType;
					facilityStructExternal.Liquid_Capacity1P = 0;
					facilityStructExternal.Gas_Capacity1P = 0;
					facilityStructExternal.Liquid_Capacity2P = 0;
					facilityStructExternal.Gas_Capacity2P = 0;
					facilityStructExternal.Liquid_Capacity3P = 0;
					facilityStructExternal.Gas_Capacity3P = 0;
					facilityStructExternal.AG_Capacity1P = 0;
					facilityStructExternal.AG_Capacity2P = 0;
					facilityStructExternal.AG_Capacity3P = 0;
					facilityStructExternal.NAG_Capacity1P = 0;
					facilityStructExternal.NAG_Capacity2P = 0;
					facilityStructExternal.NAG_Capacity3P = 0;
					facilityStructExternal.GasOwnUse1P = 0;
					facilityStructExternal.GasDemand1P = 0;
					facilityStructExternal.GasFlared1P = 0;
					facilityStructExternal.GasOwnUse2P = 0;
					facilityStructExternal.GasDemand2P = 0;
					facilityStructExternal.GasFlared2P = 0;
					facilityStructExternal.GasOwnUse3P = 0;
					facilityStructExternal.GasDemand3P = 0;
					facilityStructExternal.GasFlared3P = 0;
					facilityStructExternal.equityPercentage = 0;
					facilityStructExternal.FacilityDate1P = equipmentCapacities[i].FacilityDate1P;
					facilityStructExternal.FacilityDate2P = equipmentCapacities[i].FacilityDate1P;
					facilityStructExternal.FacilityDate3P = equipmentCapacities[i].FacilityDate1P;
					facilityStructExternal.Primary_Facility = equipmentCapacities[i].Primary_Facility;
					facilityStructExternal.Secondary_Facility = "";
					facilityStructExternal.Scheduled_Deferment1P = 0;
					facilityStructExternal.Scheduled_Deferment2P = 0;
					facilityStructExternal.Scheduled_Deferment3P = 0;
					facilityStructExternal.Unscheduled_Deferment1P = 0;
					facilityStructExternal.Unscheduled_Deferment2P = 0;
					facilityStructExternal.Unscheduled_Deferment3P = 0;
					facilityStructExternal.Thirdparty_Deferment1P = 0;
					facilityStructExternal.Thirdparty_Deferment2P = 0;
					facilityStructExternal.Thirdparty_Deferment3P = 0;
					facilityStructExternal.Crudeoil_Lossess1P = 0;
					facilityStructExternal.Crudeoil_Lossess2P = 0;
					facilityStructExternal.Crudeoil_Lossess3P = 0;
					facilityStructExternal.FacilityOiProduced = 0;
					facilityStructExternal.FacilityGasProduced = 0;
					facilityStructExternal.FacilityWaterProduced = 0;
					facilityStructExternal.FacilityLiquidProduced = 0;
					facilityStructExternal.FacilityComdensateProduced = 0;
					facilityStructExternal.FacilityNAGProduced = 0;
					facilityStructExternal.FacilityAGProduced = 0;
					facilityStructExternal.ParentNodes = "";
					facilityStructExternal.cutBack = 1;
					facilityStructExternal.gasCutBack = 1;
					facilityStructExternal.liquidCutBack = 1;
					for (kk = 0; kk < nMultipleConnections; kk++)
					{
						FacilityStructExternal selectedCapacities = GetMinimumSelectedEquipmentsCapacityByDate(
							equipmentCapacities, facilityInEquipementConnections[j].multipleConnections[kk], dates[k]);
					    
						facilityStructExternal.nodesConnectionKey = facilityInEquipementConnections[j].nodesConnectionKeys[kk];
							
						if (selectedCapacities.Liquid_Capacity1P > 0)
						{
							facilityStructExternal.Liquid_Capacity1P = selectedCapacities.Liquid_Capacity1P;
							facilityStructExternal.Liquid_Capacity2P = selectedCapacities.Liquid_Capacity1P;
							facilityStructExternal.Liquid_Capacity3P = selectedCapacities.Liquid_Capacity1P;
						}
						if (selectedCapacities.Gas_Capacity1P > 0)
						{
							facilityStructExternal.Gas_Capacity1P = selectedCapacities.Gas_Capacity1P;
							facilityStructExternal.Gas_Capacity2P = selectedCapacities.Gas_Capacity1P;
							facilityStructExternal.Gas_Capacity3P = selectedCapacities.Gas_Capacity1P;
						}
						if (selectedCapacities.NAG_Capacity1P > 0)
						{
							facilityStructExternal.NAG_Capacity1P = selectedCapacities.NAG_Capacity1P;
							facilityStructExternal.NAG_Capacity2P = selectedCapacities.NAG_Capacity1P;
							facilityStructExternal.NAG_Capacity3P = selectedCapacities.NAG_Capacity1P;
						}
						if (selectedCapacities.AG_Capacity1P > 0)
						{
							facilityStructExternal.AG_Capacity1P = selectedCapacities.AG_Capacity1P;
							facilityStructExternal.AG_Capacity2P = selectedCapacities.AG_Capacity1P;
							facilityStructExternal.AG_Capacity3P = selectedCapacities.AG_Capacity1P;
						}
						if (selectedCapacities.GasOwnUse1P > 0)
						{
							facilityStructExternal.GasOwnUse1P = selectedCapacities.GasOwnUse1P;
							facilityStructExternal.GasOwnUse2P = selectedCapacities.GasOwnUse1P;
							facilityStructExternal.GasOwnUse2P = selectedCapacities.GasOwnUse1P;
						}

						if(selectedCapacities.GasDemand1P > 0){
							facilityStructExternal.GasDemand1P = selectedCapacities.GasDemand1P;
							facilityStructExternal.GasDemand2P = selectedCapacities.GasDemand1P;
							facilityStructExternal.GasDemand3P = selectedCapacities.GasDemand1P;
						}else{
							if (selectedCapacities.Gas_Capacity1P > 0)
							{
								facilityStructExternal.GasDemand1P = selectedCapacities.Gas_Capacity1P;
								facilityStructExternal.GasDemand2P = selectedCapacities.Gas_Capacity1P;
								facilityStructExternal.GasDemand3P = selectedCapacities.Gas_Capacity1P;
							}else{
								facilityStructExternal.GasDemand1P = selectedCapacities.NAG_Capacity1P +
								selectedCapacities.AG_Capacity1P;
								facilityStructExternal.GasDemand2P = selectedCapacities.NAG_Capacity1P + 
								selectedCapacities.AG_Capacity1P;
								facilityStructExternal.GasDemand3P = selectedCapacities.NAG_Capacity1P + 
								selectedCapacities.AG_Capacity1P;
							}
						}

						if (selectedCapacities.equityPercentage > 0)
						{
							facilityStructExternal.equityPercentage = selectedCapacities.equityPercentage;
						}

						facilityStructExternal.ParentNodes = facilityStructExternal.ParentNodes +
															 facilityInEquipementConnections[j].toNodes[kk] + "===";
					}

					facilitiesDataX.push_back(facilityStructExternal);
					check = true;
					break;
				}
			}

			if (check == false)
			{
				int lastIndex = facilitiesDataX.size();
				if (lastIndex > 0)
				{
					FacilityStructExternal facilityStructExternal = facilitiesDataX[lastIndex - 1];
					facilityStructExternal.FacilityDate1P = dates[k];
					facilityStructExternal.FacilityDate2P = dates[k];
					facilityStructExternal.FacilityDate3P = dates[k];
					facilitiesDataX.push_back(facilityStructExternal);
				}
			}
		}
		facilitiesMatrixData.push_back(facilitiesDataX);
	}

	for (j = 0; j < nFacilityInEquipementConnections; j++)
	{
		for (k = 0; k < nDates; k++)
		{
			bool check = false;
			for (i = 0; i < nDeferments; i++)
			{
				//dates[k].day == deferments[i].FacilityDate1P.day &&
				if (facilityInEquipementConnections[j].facilityName == deferments[i].Primary_Facility && 
				dateCreation.EqualTo2(dates[k], deferments[i].FacilityDate1P, isMonthly))
				{
					int kk = 0;
					int nMultipleConnections = facilityInEquipementConnections[j].multipleConnections.size();
					for (kk = 0; kk < nMultipleConnections; kk++){
						FacilityStructExternal selectedDeferement = GetMinimumSelectedEquipmentsDefermentByDate(deferments,
						facilityInEquipementConnections[j].multipleConnections[kk], dates[k]);

						if(k < facilitiesMatrixData[j].size()){
							if (selectedDeferement.Scheduled_Deferment1P > 0)
							{
								facilitiesMatrixData[j][k].Scheduled_Deferment1P = selectedDeferement.Scheduled_Deferment1P;
								facilitiesMatrixData[j][k].Scheduled_Deferment2P = selectedDeferement.Scheduled_Deferment1P;
								facilitiesMatrixData[j][k].Scheduled_Deferment3P = selectedDeferement.Scheduled_Deferment1P;
							}

							if (selectedDeferement.Unscheduled_Deferment1P > 0)
							{
								facilitiesMatrixData[j][k].Unscheduled_Deferment1P = selectedDeferement.Unscheduled_Deferment1P;
								facilitiesMatrixData[j][k].Unscheduled_Deferment2P = selectedDeferement.Unscheduled_Deferment1P;
								facilitiesMatrixData[j][k].Unscheduled_Deferment3P = selectedDeferement.Unscheduled_Deferment1P;
							}

							if (selectedDeferement.Thirdparty_Deferment1P > 0)
							{
								facilitiesMatrixData[j][k].Thirdparty_Deferment1P = selectedDeferement.Thirdparty_Deferment1P;
								facilitiesMatrixData[j][k].Thirdparty_Deferment2P = selectedDeferement.Thirdparty_Deferment1P;
								facilitiesMatrixData[j][k].Thirdparty_Deferment3P = selectedDeferement.Thirdparty_Deferment1P;
							}

						}

					}
					
					check = true;
					break;
				}
			}

			if (check == false)
			{
				if (k > 0 && k < facilitiesMatrixData[j].size())
				{
					facilitiesMatrixData[j][k].Scheduled_Deferment1P = facilitiesMatrixData[j][k - 1].Scheduled_Deferment1P;
					facilitiesMatrixData[j][k].Scheduled_Deferment2P = facilitiesMatrixData[j][k - 1].Scheduled_Deferment1P;
					facilitiesMatrixData[j][k].Scheduled_Deferment3P = facilitiesMatrixData[j][k - 1].Scheduled_Deferment1P;
					facilitiesMatrixData[j][k].Unscheduled_Deferment1P = facilitiesMatrixData[j][k - 1].Unscheduled_Deferment1P;
					facilitiesMatrixData[j][k].Unscheduled_Deferment2P = facilitiesMatrixData[j][k - 1].Unscheduled_Deferment1P;
					facilitiesMatrixData[j][k].Unscheduled_Deferment3P = facilitiesMatrixData[j][k - 1].Unscheduled_Deferment1P;
					facilitiesMatrixData[j][k].Thirdparty_Deferment1P = facilitiesMatrixData[j][k - 1].Thirdparty_Deferment1P;
					facilitiesMatrixData[j][k].Thirdparty_Deferment2P = facilitiesMatrixData[j][k - 1].Thirdparty_Deferment1P;
					facilitiesMatrixData[j][k].Thirdparty_Deferment3P = facilitiesMatrixData[j][k - 1].Thirdparty_Deferment1P;
					facilitiesMatrixData[j][k].FacilityDate1P = dates[k];
					facilitiesMatrixData[j][k].FacilityDate2P = dates[k];
					facilitiesMatrixData[j][k].FacilityDate3P = dates[k];
				}
			}
		}
	}

	for (j = 0; j < nFacilityInEquipementConnections; j++)
	{
		for (k = 0; k < nDates; k++)
		{
			bool check = false;
			for (i = 0; i < nCrudeOilLosses; i++)
			{
				//dates[k].day == crudeOilLosses[i].FacilityDate1P.day &&
				if (facilityInEquipementConnections[j].facilityName == crudeOilLosses[i].Primary_Facility && 
					dateCreation.EqualTo2(dates[k], crudeOilLosses[i].FacilityDate1P, isMonthly))
				{
					int kk = 0;
					int nMultipleConnections = facilityInEquipementConnections[j].multipleConnections.size();
					for (kk = 0; kk < nMultipleConnections; kk++){
						FacilityStructExternal selectedCrudeOilLosses = GetMinimumSelectedEquipmentsCrudeOilLossesByDate(
						crudeOilLosses, facilityInEquipementConnections[j].multipleConnections[kk], dates[k]);

						if(k < facilitiesMatrixData[j].size()){
							if (selectedCrudeOilLosses.Crudeoil_Lossess1P > 0)
							{
								facilitiesMatrixData[j][k].Crudeoil_Lossess1P = selectedCrudeOilLosses.Crudeoil_Lossess1P;
								facilitiesMatrixData[j][k].Crudeoil_Lossess2P = selectedCrudeOilLosses.Crudeoil_Lossess1P;
								facilitiesMatrixData[j][k].Crudeoil_Lossess3P = selectedCrudeOilLosses.Crudeoil_Lossess1P;
							}
						}
					}

					check = true;
					break;
				}
			}

			if (check == false)
			{
				if (k > 0 && k < facilitiesMatrixData[j].size())
				{
					facilitiesMatrixData[j][k].Crudeoil_Lossess1P = facilitiesMatrixData[j][k - 1].Crudeoil_Lossess1P;
					facilitiesMatrixData[j][k].Crudeoil_Lossess2P = facilitiesMatrixData[j][k - 1].Crudeoil_Lossess1P;
					facilitiesMatrixData[j][k].Crudeoil_Lossess3P = facilitiesMatrixData[j][k - 1].Crudeoil_Lossess1P;
					facilitiesMatrixData[j][k].FacilityDate1P = dates[k];
					facilitiesMatrixData[j][k].FacilityDate2P = dates[k];
					facilitiesMatrixData[j][k].FacilityDate3P = dates[k];
				}
			}
		}
	}

	for (j = 0; j < nFacilityInEquipementConnections; j++)
	{
		for (k = 0; k < nDates; k++)
		{
			bool check = false;
			for (i = 0; i < nGasOwnUse; i++)
			{
				//dates[k].day == gasOwnUse[i].FacilityDate1P.day &&
				if (facilityInEquipementConnections[j].facilityName == gasOwnUse[i].Primary_Facility && 
					dateCreation.EqualTo2(dates[k], gasOwnUse[i].FacilityDate1P, isMonthly))
				{
					int kk = 0;
					int nMultipleConnections = facilityInEquipementConnections[j].multipleConnections.size();
					for (kk = 0; kk < nMultipleConnections; kk++){
						FacilityStructExternal selectedGasOwnuse = GetMinimumSelectedEquipmentsGasOwnUseByDate(
						gasOwnUse, facilityInEquipementConnections[j].multipleConnections[kk], dates[k]);

						if(k < facilitiesMatrixData[j].size()){
							if (selectedGasOwnuse.GasOwnUse1P > 0)
							{
								facilitiesMatrixData[j][k].GasOwnUse1P = selectedGasOwnuse.GasOwnUse1P;
								facilitiesMatrixData[j][k].GasOwnUse2P = selectedGasOwnuse.GasOwnUse1P;
								facilitiesMatrixData[j][k].GasOwnUse3P = selectedGasOwnuse.GasOwnUse1P;
							}
						}
					}

					check = true;
					break;
				}
			}

			if (check == false)
			{
				if (k > 0 && k < facilitiesMatrixData[j].size())
				{
					facilitiesMatrixData[j][k].GasOwnUse1P = facilitiesMatrixData[j][k - 1].GasOwnUse1P;
					facilitiesMatrixData[j][k].GasOwnUse2P = facilitiesMatrixData[j][k - 1].GasOwnUse2P;
					facilitiesMatrixData[j][k].GasOwnUse3P = facilitiesMatrixData[j][k - 1].GasOwnUse3P;
					facilitiesMatrixData[j][k].FacilityDate1P = dates[k];
					facilitiesMatrixData[j][k].FacilityDate2P = dates[k];
					facilitiesMatrixData[j][k].FacilityDate3P = dates[k];
				}
			}
		}
	}

	for (j = 0; j < nFacilityInEquipementConnections; j++)
	{
		for (k = 0; k < nDates; k++)
		{
			bool check = false;
			for (i = 0; i < nGasFlared; i++)
			{
				//dates[k].day == gasFlared[i].FacilityDate1P.day &&
				if (facilityInEquipementConnections[j].facilityName == gasFlared[i].Primary_Facility && 
					dateCreation.EqualTo2(dates[k], gasFlared[i].FacilityDate1P, isMonthly))
				{
					int kk = 0;
					int nMultipleConnections = facilityInEquipementConnections[j].multipleConnections.size();
					for (kk = 0; kk < nMultipleConnections; kk++){
						FacilityStructExternal selectedGasFlared = GetMinimumSelectedEquipmentsGasFlaredByDate(
						gasFlared, facilityInEquipementConnections[j].multipleConnections[kk], dates[k]);

						if(k < facilitiesMatrixData[j].size()){
							if (selectedGasFlared.GasFlared1P > 0)
							{
								facilitiesMatrixData[j][k].GasFlared1P = selectedGasFlared.GasFlared1P;
								facilitiesMatrixData[j][k].GasFlared2P = selectedGasFlared.GasFlared1P;
								facilitiesMatrixData[j][k].GasFlared3P = selectedGasFlared.GasFlared1P;
							}
						}
					}

					check = true;
					break;
				}
			}

			if (check == false)
			{
				if (k > 0 && k < facilitiesMatrixData[j].size())
				{
					facilitiesMatrixData[j][k].GasFlared1P = facilitiesMatrixData[j][k - 1].GasFlared1P;
					facilitiesMatrixData[j][k].GasFlared2P = facilitiesMatrixData[j][k - 1].GasFlared2P;
					facilitiesMatrixData[j][k].GasFlared3P = facilitiesMatrixData[j][k - 1].GasFlared3P;
					facilitiesMatrixData[j][k].FacilityDate1P = dates[k];
					facilitiesMatrixData[j][k].FacilityDate2P = dates[k];
					facilitiesMatrixData[j][k].FacilityDate3P = dates[k];
				}
			}
		}
	}

	int nRows = facilitiesMatrixData.size();
	for (j = 0; j < nRows; j++)
	{
		int nCols = facilitiesMatrixData[j].size();
		for (i = 0; i < nCols; i++)
		{
			facilitiesData.push_back(facilitiesMatrixData[j][i]);
		}
	}

	for(auto& innerVec : facilitiesMatrixData){
		innerVec.clear();
	}

	facilitiesMatrixData.clear();

	vector<FacilityStructExternal> facilitiesData2 = SortFacilitiesData(facilitiesData);
	facilitiesData.clear();
	facilitiesData.shrink_to_fit();
	return make_tuple(facilitiesData2, dates);
}

vector<FacilityInEquipementConnection> ReportJSON2::GetFacilitiesInEquipmentConnections(
	vector<InternalExternalEquipmentName> &internalExternalFacilitiesNames,
	vector<vector<string>> &equipmentConnections, int &nodeIndex)
{

	vector<FacilityInEquipementConnection> facilityInEquipementConnections;
	int nRows = equipmentConnections.size();
	int nCols = equipmentConnections[0].size();
	int i = 0, j = 0, k = 0, kk = 0;
	int nInternalExternalFacilitiesNames = internalExternalFacilitiesNames.size();
	for (i = 0; i < nInternalExternalFacilitiesNames; i++)
	{
		FacilityInEquipementConnection facilityInEquipementConnection;
		facilityInEquipementConnection.InitailizeData();
		facilityInEquipementConnection.facilityName = "Not Exist";
		for (j = 0; j < nRows; j++)
		{
			if (internalExternalFacilitiesNames[i].externalEquipmentName == equipmentConnections[j][nodeIndex])
			{
				facilityInEquipementConnection.facilityName = internalExternalFacilitiesNames[i].externalEquipmentName;
				facilityInEquipementConnection.equipmentType = internalExternalFacilitiesNames[i].equipmentType;

				//if (nodeIndex + 1 < nCols)
				//{
					vector<string> connections;
					int counter = -1;
					string parentNode;
					for (kk = nodeIndex; kk < nCols; kk++)
					{
						counter++;
						if (counter == 0)
						{
							facilityInEquipementConnection.fromNodes.push_back(equipmentConnections[j][kk]);
						}

						if(nodeIndex == nCols - 1){
							facilityInEquipementConnection.toNodes.push_back(equipmentConnections[j][kk]);
						}

						if (counter == 1)
						{
							//facilityInEquipementConnection.toNodes.push_back(parentNode = equipmentConnections[j][kk]);
							facilityInEquipementConnection.toNodes.push_back(equipmentConnections[j][kk]);
						}
						connections.push_back(equipmentConnections[j][kk]);
					}
					string nodesConnectionKey = "";
					for (kk = 0; kk < nodeIndex + 1; kk++)
					{
						if(k < nCols - 1){
							nodesConnectionKey = nodesConnectionKey + equipmentConnections[j][kk] + "===";
						}
					}
					facilityInEquipementConnection.multipleConnections.push_back(connections);
					facilityInEquipementConnection.nodesConnectionKeys.push_back(nodesConnectionKey);
				//}
			}
		}
		if (facilityInEquipementConnection.facilityName != "Not Exist")
		{
			facilityInEquipementConnections.push_back(facilityInEquipementConnection);
		}
	}

	return facilityInEquipementConnections;
}


vector<Node> ReportJSON2::GetNodes(
	vector<InternalExternalEquipmentName> &internalExternalFacilitiesNames,
	vector<vector<string>> &equipmentConnections)
{

	int nodesCount = equipmentConnections[0].size();
	vector<Node> nodes;
	int i = 0;
	for (i = 0; i < nodesCount; i++)
	{
		Node node;
		node.nodeName = "Node_" + to_string(i);
		node.equipmentInEquipementConnections =
			GetFacilitiesInEquipmentConnections(internalExternalFacilitiesNames, equipmentConnections, i);
		nodes.push_back(node);
	}
	return nodes;
}

tuple<vector<Node>, vector<Date>> ReportJSON2::GetNodesSheetData(
	vector<Node> &nodes,
	vector<FacilityStructExternal> &equipmentCapacities, 
	vector<FacilityStructExternal> &deferments,
	vector<FacilityStructExternal> &crudeOilLosses,
	vector<FacilityStructExternal>& gasOwnUse, 
	vector<FacilityStructExternal>& gasFlared)
{

	vector<Node> updatesNodes;
	vector<Date> dates;
	int nodeCount = nodes.size();
	int i = 0, j = 0;
	for (i = 0; i < nodeCount; i++)
	{
		Node node;
		node.nodeName = nodes[i].nodeName;
		node.equipmentInEquipementConnections = nodes[i].equipmentInEquipementConnections;
		//make_tuple(facilitiesData2, dates)
		tuple<vector<FacilityStructExternal>,vector<Date>> tupleResult =
			GetFacilitiesSheetData(nodes[i].equipmentInEquipementConnections,
								   equipmentCapacities, deferments, crudeOilLosses,
								   gasOwnUse, gasFlared);
		node.equipmentDataInEquipementConnections = get<0>(tupleResult);
		vector<Date> dates2 = get<1>(tupleResult);
		updatesNodes.push_back(node);
		int nDates2 = dates2.size();
		for(j = 0; j < nDates2; j++){
			bool check = isContainDate(dates, dates2[j]);
			if (check == false)
			{
				dates.push_back(dates2[j]);
			}
		}
	}
	return make_tuple(updatesNodes, dates);
}



vector<WellSchedule> ReportJSON2::GetWellSchedulesSheetData(vector<WellReroute>& wellRerouteDecks,
vector<WellRampUp>& wellRampUpDecks, vector<ShutInOpenUp>& wellShutInOpenDecks,
Date& StopDate)
{

	vector<WellSchedule> wellSchedules;
	DateCreation dateCreation;
	int nWellRerouteDecks = wellRerouteDecks.size();
	int nWellRampUpDecks = wellRampUpDecks.size();
	int nWellShutInOpenDecks = wellShutInOpenDecks.size();
	int j = 0;

	for (j = 0; j < nWellRerouteDecks; j++)
	{
		WellReroute wellRerouteDeck = wellRerouteDecks[j];
		WellSchedule wellSchedule;
		wellSchedule.Module = wellRerouteDeck.Module;
		wellSchedule.FromDate = wellRerouteDeck.Date_1P_1C;
		wellSchedule.ToDate = StopDate;
		wellSchedule.ParameterName = wellRerouteDeck.dcaStrategy;
		wellSchedule.declineType = wellRerouteDeck.declineType;
		wellSchedule.declineType2 = wellRerouteDeck.declineType2;
		wellSchedule.startupRate = wellRerouteDeck.startupRate;
		wellSchedule.startupRatePlateau = wellRerouteDeck.startupRatePlateau;
		int numberOfMonths = int(wellSchedule.startupRatePlateau * 12.0);
		wellSchedule.PlateauDate = dateCreation.DateIncrementByMonth(wellSchedule.FromDate, numberOfMonths);
		wellSchedule.declineRate = wellRerouteDeck.declineRate;
		wellSchedule.hyperbolicExponent = wellRerouteDeck.hyperbolicExponent;
		wellSchedule.scheduleKey = WellReroute_String;

		if(wellSchedule.ParameterName == "existingStrategy"){
			wellSchedule.ParameterName2 = existingStrategy;
		}

		if(wellSchedule.ParameterName == "noExistingStrategy"){
			wellSchedule.ParameterName2 = noExistingStrategy;
		}

		if(wellSchedule.ParameterName == "Init_Oil_Gas_Rate_1P_1C"){
			wellSchedule.ParameterName2 = Init_Oil_Gas_Rate_1P_1C;
		}

		if(wellSchedule.ParameterName == "Init_Oil_Gas_Rate_2P_2C"){
			wellSchedule.ParameterName2 = Init_Oil_Gas_Rate_2P_2C;
		}

		if(wellSchedule.ParameterName == "Init_Oil_Gas_Rate_3P_3C"){
			wellSchedule.ParameterName2 = Init_Oil_Gas_Rate_3P_3C;
		}

		if(wellSchedule.ParameterName == "Decline_Rate_1P_1C"){
			wellSchedule.ParameterName2 = Decline_Rate_1P_1C;
		}

		if(wellSchedule.ParameterName == "Decline_Rate_2P_2C"){
			wellSchedule.ParameterName2 = Decline_Rate_2P_2C;
		}

		if(wellSchedule.ParameterName == "Decline_Rate_3P_3C"){
			wellSchedule.ParameterName2 = Decline_Rate_3P_3C;
		}

		if(wellSchedule.ParameterName == "Rate_Of_Rate_GOR_CGR_1P1C"){
			wellSchedule.ParameterName2 = Rate_Of_Rate_GOR_CGR_1P1C;
		}

		if(wellSchedule.ParameterName == "Rate_Of_Rate_GOR_CGR_2P2C"){
			wellSchedule.ParameterName2 = Rate_Of_Rate_GOR_CGR_2P2C;
		}

		if(wellSchedule.ParameterName == "Rate_Of_Rate_GOR_CGR_3P3C"){
			wellSchedule.ParameterName2 = Rate_Of_Rate_GOR_CGR_3P3C;
		}

		if(wellSchedule.ParameterName == "Rate_Of_Rate_BSW_WGR_1P1C"){
			wellSchedule.ParameterName2 = Rate_Of_Rate_BSW_WGR_1P1C;
		}

		if(wellSchedule.ParameterName == "Rate_Of_Rate_BSW_WGR_2P2C"){
			wellSchedule.ParameterName2 = Rate_Of_Rate_BSW_WGR_2P2C;
		}

		if(wellSchedule.ParameterName == "Rate_Of_Rate_BSW_WGR_3P3C"){
			wellSchedule.ParameterName2 = Rate_Of_Rate_BSW_WGR_3P3C;
		}

		if(wellSchedule.ParameterName == "Decline_Exponent_1P1C"){
			wellSchedule.ParameterName2 = Decline_Exponent_1P1C;
		}

		if(wellSchedule.ParameterName == "Decline_Exponent_2P2C"){
			wellSchedule.ParameterName2 = Decline_Exponent_2P2C;
		}

		if(wellSchedule.ParameterName == "Decline_Exponent_3P3C"){
			wellSchedule.ParameterName2 = Decline_Exponent_3P3C;
		}

		if(wellSchedule.ParameterName == "PlateauUR_1P_1C"){
			wellSchedule.ParameterName2 = PlateauUR_1P_1C;
		}

		if(wellSchedule.ParameterName == "PlateauUR_2P_2C"){
			wellSchedule.ParameterName2 = PlateauUR_2P_2C;
		}

		if(wellSchedule.ParameterName == "PlateauUR_3P_3C"){
			wellSchedule.ParameterName2 = PlateauUR_3P_3C;
		}

		wellSchedules.push_back(wellSchedule);
	}

	for (j = 0; j < nWellRampUpDecks; j++)
	{
		WellRampUp wellRampUp = wellRampUpDecks[j];
		WellSchedule wellSchedule;
		wellSchedule.Module = wellRampUp.Module;
		wellSchedule.FromDate = wellRampUp.rampUpDate_1P_1C;
		int numberOfMonths = 1;
		wellSchedule.ToDate = dateCreation.DateIncrementByMonth(wellSchedule.FromDate, numberOfMonths);
		wellSchedule.ParameterName = existingStrategy_String;//wellRampUp.dcaStrategy;
		wellSchedule.declineType = wellRampUp.declineType;
		wellSchedule.startupRate = wellRampUp.maximumPotential;
		wellSchedule.percentOfMaximumPotential = wellRampUp.percentOfMaximumPotential/100.0;
		wellSchedule.startupRatePlateau = 0;
		wellSchedule.PlateauDate = wellRampUp.rampUpDate_1P_1C; // dateCreation.DateIncrementByMonth(wellSchedule.FromDate, numberOfMonths);
		wellSchedule.declineRate = wellRampUp.declineRate;
		wellSchedule.hyperbolicExponent = wellRampUp.hyperbolicExponent;
		wellSchedule.declineType2  = wellRampUp.declineType2;
		wellSchedule.scheduleKey = WellRampUp_String;

		if(wellSchedule.ParameterName == "existingStrategy"){
			wellSchedule.ParameterName2 = existingStrategy;
		}
		

		if(wellSchedule.ParameterName == "noExistingStrategy"){
			wellSchedule.ParameterName2 = noExistingStrategy;
		}

		if(wellSchedule.ParameterName == "Init_Oil_Gas_Rate_1P_1C"){
			wellSchedule.ParameterName2 = Init_Oil_Gas_Rate_1P_1C;
		}

		if(wellSchedule.ParameterName == "Init_Oil_Gas_Rate_2P_2C"){
			wellSchedule.ParameterName2 = Init_Oil_Gas_Rate_2P_2C;
		}

		if(wellSchedule.ParameterName == "Init_Oil_Gas_Rate_3P_3C"){
			wellSchedule.ParameterName2 = Init_Oil_Gas_Rate_3P_3C;
		}

		if(wellSchedule.ParameterName == "Decline_Rate_1P_1C"){
			wellSchedule.ParameterName2 = Decline_Rate_1P_1C;
		}

		if(wellSchedule.ParameterName == "Decline_Rate_2P_2C"){
			wellSchedule.ParameterName2 = Decline_Rate_2P_2C;
		}

		if(wellSchedule.ParameterName == "Decline_Rate_3P_3C"){
			wellSchedule.ParameterName2 = Decline_Rate_3P_3C;
		}

		if(wellSchedule.ParameterName == "Rate_Of_Rate_GOR_CGR_1P1C"){
			wellSchedule.ParameterName2 = Rate_Of_Rate_GOR_CGR_1P1C;
		}

		if(wellSchedule.ParameterName == "Rate_Of_Rate_GOR_CGR_2P2C"){
			wellSchedule.ParameterName2 = Rate_Of_Rate_GOR_CGR_2P2C;
		}

		if(wellSchedule.ParameterName == "Rate_Of_Rate_GOR_CGR_3P3C"){
			wellSchedule.ParameterName2 = Rate_Of_Rate_GOR_CGR_3P3C;
		}

		if(wellSchedule.ParameterName == "Rate_Of_Rate_BSW_WGR_1P1C"){
			wellSchedule.ParameterName2 = Rate_Of_Rate_BSW_WGR_1P1C;
		}

		if(wellSchedule.ParameterName == "Rate_Of_Rate_BSW_WGR_2P2C"){
			wellSchedule.ParameterName2 = Rate_Of_Rate_BSW_WGR_2P2C;
		}

		if(wellSchedule.ParameterName == "Rate_Of_Rate_BSW_WGR_3P3C"){
			wellSchedule.ParameterName2 = Rate_Of_Rate_BSW_WGR_3P3C;
		}

		if(wellSchedule.ParameterName == "Decline_Exponent_1P1C"){
			wellSchedule.ParameterName2 = Decline_Exponent_1P1C;
		}

		if(wellSchedule.ParameterName == "Decline_Exponent_2P2C"){
			wellSchedule.ParameterName2 = Decline_Exponent_2P2C;
		}

		if(wellSchedule.ParameterName == "Decline_Exponent_3P3C"){
			wellSchedule.ParameterName2 = Decline_Exponent_3P3C;
		}

		if(wellSchedule.ParameterName == "PlateauUR_1P_1C"){
			wellSchedule.ParameterName2 = PlateauUR_1P_1C;
		}

		if(wellSchedule.ParameterName == "PlateauUR_2P_2C"){
			wellSchedule.ParameterName2 = PlateauUR_2P_2C;
		}

		if(wellSchedule.ParameterName == "PlateauUR_3P_3C"){
			wellSchedule.ParameterName2 = PlateauUR_3P_3C;
		}

		wellSchedules.push_back(wellSchedule);
	}

	//==============Well Shut In Schedules
	for (j = 0; j < nWellShutInOpenDecks; j++)
	{
		ShutInOpenUp wellShutInOpenDeck = wellShutInOpenDecks[j];
		if(wellShutInOpenDeck.event == WellShutIn_String){
			WellSchedule wellSchedule;
			wellSchedule.Module = wellShutInOpenDeck.Module;
			wellSchedule.FromDate = wellShutInOpenDeck.eventDate_1P_1C;
			wellSchedule.ToDate = StopDate;
			wellSchedule.ParameterName = wellShutInOpenDeck.dcaStrategy;
			wellSchedule.declineType = wellShutInOpenDeck.declineType;
			wellSchedule.startupRate = 0;
			wellSchedule.startupRatePlateau = 0;
			int numberOfMonths = int(wellSchedule.startupRatePlateau * 12.0);
			wellSchedule.PlateauDate = dateCreation.DateIncrementByMonth(wellSchedule.FromDate, numberOfMonths);
			wellSchedule.declineRate = 0;
			wellSchedule.hyperbolicExponent = wellShutInOpenDeck.hyperbolicExponent;
			wellSchedule.scheduleKey = WellShutIn_String;
			wellSchedule.declineType2  = wellShutInOpenDeck.declineType2;

			if(wellSchedule.ParameterName == "existingStrategy"){
				wellSchedule.ParameterName2 = existingStrategy;
			}

			if(wellSchedule.ParameterName == "noExistingStrategy"){
				wellSchedule.ParameterName2 = noExistingStrategy;
			}

			if(wellSchedule.ParameterName == "Init_Oil_Gas_Rate_1P_1C"){
				wellSchedule.ParameterName2 = Init_Oil_Gas_Rate_1P_1C;
			}

			if(wellSchedule.ParameterName == "Init_Oil_Gas_Rate_2P_2C"){
				wellSchedule.ParameterName2 = Init_Oil_Gas_Rate_2P_2C;
			}

			if(wellSchedule.ParameterName == "Init_Oil_Gas_Rate_3P_3C"){
				wellSchedule.ParameterName2 = Init_Oil_Gas_Rate_3P_3C;
			}

			if(wellSchedule.ParameterName == "Decline_Rate_1P_1C"){
				wellSchedule.ParameterName2 = Decline_Rate_1P_1C;
			}

			if(wellSchedule.ParameterName == "Decline_Rate_2P_2C"){
				wellSchedule.ParameterName2 = Decline_Rate_2P_2C;
			}

			if(wellSchedule.ParameterName == "Decline_Rate_3P_3C"){
				wellSchedule.ParameterName2 = Decline_Rate_3P_3C;
			}

			if(wellSchedule.ParameterName == "Rate_Of_Rate_GOR_CGR_1P1C"){
				wellSchedule.ParameterName2 = Rate_Of_Rate_GOR_CGR_1P1C;
			}

			if(wellSchedule.ParameterName == "Rate_Of_Rate_GOR_CGR_2P2C"){
				wellSchedule.ParameterName2 = Rate_Of_Rate_GOR_CGR_2P2C;
			}

			if(wellSchedule.ParameterName == "Rate_Of_Rate_GOR_CGR_3P3C"){
				wellSchedule.ParameterName2 = Rate_Of_Rate_GOR_CGR_3P3C;
			}

			if(wellSchedule.ParameterName == "Rate_Of_Rate_BSW_WGR_1P1C"){
				wellSchedule.ParameterName2 = Rate_Of_Rate_BSW_WGR_1P1C;
			}

			if(wellSchedule.ParameterName == "Rate_Of_Rate_BSW_WGR_2P2C"){
				wellSchedule.ParameterName2 = Rate_Of_Rate_BSW_WGR_2P2C;
			}

			if(wellSchedule.ParameterName == "Rate_Of_Rate_BSW_WGR_3P3C"){
				wellSchedule.ParameterName2 = Rate_Of_Rate_BSW_WGR_3P3C;
			}

			if(wellSchedule.ParameterName == "Decline_Exponent_1P1C"){
				wellSchedule.ParameterName2 = Decline_Exponent_1P1C;
			}

			if(wellSchedule.ParameterName == "Decline_Exponent_2P2C"){
				wellSchedule.ParameterName2 = Decline_Exponent_2P2C;
			}

			if(wellSchedule.ParameterName == "Decline_Exponent_3P3C"){
				wellSchedule.ParameterName2 = Decline_Exponent_3P3C;
			}

			if(wellSchedule.ParameterName == "PlateauUR_1P_1C"){
				wellSchedule.ParameterName2 = PlateauUR_1P_1C;
			}

			if(wellSchedule.ParameterName == "PlateauUR_2P_2C"){
				wellSchedule.ParameterName2 = PlateauUR_2P_2C;
			}

			if(wellSchedule.ParameterName == "PlateauUR_3P_3C"){
				wellSchedule.ParameterName2 = PlateauUR_3P_3C;
			}

			wellSchedules.push_back(wellSchedule);

		}
	}


	//==============Well OpenUp Schedules
	for (j = 0; j < nWellShutInOpenDecks; j++)
	{
		ShutInOpenUp wellShutInOpenDeck = wellShutInOpenDecks[j];
		if(wellShutInOpenDeck.event == WellOpenUp_String){
			WellSchedule wellSchedule;
			wellSchedule.Module = wellShutInOpenDeck.Module;
			wellSchedule.FromDate = wellShutInOpenDeck.eventDate_1P_1C;
			wellSchedule.ToDate = StopDate;
			wellSchedule.ParameterName = wellShutInOpenDeck.dcaStrategy;
			wellSchedule.declineType = wellShutInOpenDeck.declineType;
			wellSchedule.startupRate = wellShutInOpenDeck.startupRate;
			wellSchedule.startupRatePlateau = wellShutInOpenDeck.startupRatePlateau;
			int numberOfMonths = int(wellSchedule.startupRatePlateau * 12.0);
			wellSchedule.PlateauDate = dateCreation.DateIncrementByMonth(wellSchedule.FromDate, numberOfMonths);
			wellSchedule.declineRate = wellShutInOpenDeck.declineRate;
			wellSchedule.hyperbolicExponent = wellShutInOpenDeck.hyperbolicExponent;
			wellSchedule.scheduleKey = WellOpenUp_String;
			wellSchedule.declineType2  = wellShutInOpenDeck.declineType2;

			if(wellSchedule.ParameterName == "existingStrategy"){
				wellSchedule.ParameterName2 = existingStrategy;
			}

			if(wellSchedule.ParameterName == "noExistingStrategy"){
				wellSchedule.ParameterName2 = noExistingStrategy;
			}

			if(wellSchedule.ParameterName == "Init_Oil_Gas_Rate_1P_1C"){
				wellSchedule.ParameterName2 = Init_Oil_Gas_Rate_1P_1C;
			}

			if(wellSchedule.ParameterName == "Init_Oil_Gas_Rate_2P_2C"){
				wellSchedule.ParameterName2 = Init_Oil_Gas_Rate_2P_2C;
			}

			if(wellSchedule.ParameterName == "Init_Oil_Gas_Rate_3P_3C"){
				wellSchedule.ParameterName2 = Init_Oil_Gas_Rate_3P_3C;
			}

			if(wellSchedule.ParameterName == "Decline_Rate_1P_1C"){
				wellSchedule.ParameterName2 = Decline_Rate_1P_1C;
			}

			if(wellSchedule.ParameterName == "Decline_Rate_2P_2C"){
				wellSchedule.ParameterName2 = Decline_Rate_2P_2C;
			}

			if(wellSchedule.ParameterName == "Decline_Rate_3P_3C"){
				wellSchedule.ParameterName2 = Decline_Rate_3P_3C;
			}

			if(wellSchedule.ParameterName == "Rate_Of_Rate_GOR_CGR_1P1C"){
				wellSchedule.ParameterName2 = Rate_Of_Rate_GOR_CGR_1P1C;
			}

			if(wellSchedule.ParameterName == "Rate_Of_Rate_GOR_CGR_2P2C"){
				wellSchedule.ParameterName2 = Rate_Of_Rate_GOR_CGR_2P2C;
			}

			if(wellSchedule.ParameterName == "Rate_Of_Rate_GOR_CGR_3P3C"){
				wellSchedule.ParameterName2 = Rate_Of_Rate_GOR_CGR_3P3C;
			}

			if(wellSchedule.ParameterName == "Rate_Of_Rate_BSW_WGR_1P1C"){
				wellSchedule.ParameterName2 = Rate_Of_Rate_BSW_WGR_1P1C;
			}

			if(wellSchedule.ParameterName == "Rate_Of_Rate_BSW_WGR_2P2C"){
				wellSchedule.ParameterName2 = Rate_Of_Rate_BSW_WGR_2P2C;
			}

			if(wellSchedule.ParameterName == "Rate_Of_Rate_BSW_WGR_3P3C"){
				wellSchedule.ParameterName2 = Rate_Of_Rate_BSW_WGR_3P3C;
			}

			if(wellSchedule.ParameterName == "Decline_Exponent_1P1C"){
				wellSchedule.ParameterName2 = Decline_Exponent_1P1C;
			}

			if(wellSchedule.ParameterName == "Decline_Exponent_2P2C"){
				wellSchedule.ParameterName2 = Decline_Exponent_2P2C;
			}

			if(wellSchedule.ParameterName == "Decline_Exponent_3P3C"){
				wellSchedule.ParameterName2 = Decline_Exponent_3P3C;
			}

			if(wellSchedule.ParameterName == "PlateauUR_1P_1C"){
				wellSchedule.ParameterName2 = PlateauUR_1P_1C;
			}

			if(wellSchedule.ParameterName == "PlateauUR_2P_2C"){
				wellSchedule.ParameterName2 = PlateauUR_2P_2C;
			}

			if(wellSchedule.ParameterName == "PlateauUR_3P_3C"){
				wellSchedule.ParameterName2 = PlateauUR_3P_3C;
			}

			wellSchedules.push_back(wellSchedule);

		}
	}

	wellSchedules = SortWellSchedules(wellSchedules);
	return wellSchedules;
}


vector<WellSchedule> ReportJSON2::SortWellSchedules(vector<WellSchedule> &wellSchedules)
{

	DateCreation dateCreation;
	WellSchedule temp;
	int n = wellSchedules.size();

	for (int j = 0; j <= n - 2; j++)
	{
		for (int i = 0; i <= n - 2; i++)
		{
			if (dateCreation.IsMaximumDate(wellSchedules[i].FromDate, wellSchedules[i + 1].FromDate))
			{
				temp = wellSchedules[i + 1];
				wellSchedules[i + 1] = wellSchedules[i];
				wellSchedules[i] = temp;
			}
		}
	}

	return wellSchedules;
}

void ReportJSON2::GetForecastWellYearlyOutput(string& tableYearly, vector<ForecastResult>& resultsWellNew,
			vector<Date>& datesNew, string& ModuleName, string& FacilityName, int& scenario)
{
	bool isForChart = false;
	bool isByYear = !isMonthly;
	int timeSteps = resultsWellNew.size();

	if(timeSteps > 0){
		
		vector<ForecastResult> resultsWellYearly 
		= _dataPivoting.GetYearlyForcastResultModuleLevel(resultsWellNew, 
		datesNew, isForChart, isByYear);
	

		int nresultsWell = resultsWellYearly.size();

		for (int ii = 0; ii < nresultsWell; ii++) {
		
			bool isLastRow = false;
			if(ii == nresultsWell - 1)
			{
				isLastRow = true;
			}

			tableYearly = tableYearly + GetRow(resultsWellYearly[ii], scenario, ii, isLastRow);
			ModuleName = resultsWellYearly[ii].ModuleName;
			FacilityName = resultsWellYearly[ii].Flow_station;

		}

	}
}

void ReportJSON2::GetForecastWellMonthOutput(int& k, int& j, int& scenario,
 string& table, vector<ForecastResult>& resultsWellNew)
{

	int lastRow = results[k][j].size();

	int ij = -1;

	
	for (int ii = 0; ii < lastRow; ii++) {

		Date startDate;
		startDate.day = results[k][j][ii].startDay;
		startDate.month = results[k][j][ii].startMonth;
		startDate.year = results[k][j][ii].StartYear;

		bool isLastRow = false;
		if(ii == lastRow-1){
			isLastRow = true;
		}

		if(startDate.year != 2900) // (dateCreation.IsMaximumDate(date, startDate)  || dateCreation.EqualTo(date, startDate)) 
		{
			ij++;
			table = table + GetRow(results[k][j][ii], scenario, ij, isLastRow);
			resultsWellNew.push_back(results[k][j][ii]);
			
		}

	}
}

string ReportJSON2::GetRow(ForecastResult& r, int& scenario, int& ii, bool& isLastRow){

string row = "";
string columnDelimeter = "@#$%";
string rowDelimeter = "@#*$%";

std::string uniqueId = r.ModuleName + r.Flow_station + to_string(scenario) + "P" + to_string(scenario) + "C" +  to_string(ii);

double oilRate = 0, condensateRate = 0;
oilRate = r.Oil_rate;
condensateRate = r.Condensate_Rate;

/* if(r.HyrocarbonStream == "oil"){
	oilRate = r.Oil_rate;
	condensateRate = 0;
}else{
	condensateRate = r.Condensate_Rate;
	oilRate = 0;
} */

double liquid =  r.Liquid_Rate;

/* if(r.HyrocarbonStream == "oil"){
	liquid =  oilRate + r.Water_Rate;
}else{
	liquid =  condensateRate + r.Water_Rate;
} */

string lastrow = std::to_string(r.DeclineRate) +  rowDelimeter;
if(isLastRow == true){
	lastrow = std::to_string(r.DeclineRate); // no new line
}

//isLastRow
row = uniqueId +  columnDelimeter
		+ r.Version_Name +  columnDelimeter
		+ r.Field +  columnDelimeter
		+ r.Reservoir +  columnDelimeter
		+ r.Drainage_Point +  columnDelimeter
		+ r.Production_String +  columnDelimeter
		+ r.TRANCHE +  columnDelimeter
		+ r.Asset_Team +  columnDelimeter
		+ r.Flow_station +  columnDelimeter
		+ r.ModuleName +  columnDelimeter
		+ std::to_string(r.Day) +  columnDelimeter
		+ std::to_string(r.Month) +  columnDelimeter
		+ std::to_string(r.Year) +  columnDelimeter
		+ std::to_string(oilRate) +  columnDelimeter
		+ std::to_string(r.Gas_Rate) +  columnDelimeter
		+ std::to_string(r.Water_Rate) +  columnDelimeter
		+ std::to_string(liquid) +  columnDelimeter
		+ std::to_string(r.Cum_Oil_Prod) +  columnDelimeter
		+ std::to_string(r.Cum_Gas_Prod) +  columnDelimeter
		+ std::to_string(r.Cum_Water_Prod) +  columnDelimeter
		+ std::to_string(r.GOR) +  columnDelimeter
		+ std::to_string(r.BSW) +  columnDelimeter
		+ std::to_string(r.CGR) +  columnDelimeter
		+ std::to_string(r.WGR) +  columnDelimeter
		+ std::to_string(r.CutBack) +  columnDelimeter
		+ r.HyrocarbonStream +  columnDelimeter
		+ r.hydrocarbonType +  columnDelimeter
		+ r.terminal +  columnDelimeter
		+ std::to_string(r.URo) +  columnDelimeter
		+ std::to_string(r.URg) +  columnDelimeter
		+ std::to_string(r.Gas_Own_Use) +  columnDelimeter
		+ std::to_string(r.Gas_Demand) +  columnDelimeter
		+ std::to_string(r.Gas_Flared) +  columnDelimeter
		+ std::to_string(r.Crude_Oil_Lossess) +  columnDelimeter
		+ std::to_string(r.CutBack) +  columnDelimeter
		+ r.projectCode +  columnDelimeter
		+ r.projectName +  columnDelimeter
		+ std::to_string(0) +  columnDelimeter
		+  std::to_string(r.OptimalSolution) +  columnDelimeter
		+  std::to_string(r.AllWellsLiquidCapacity) +  columnDelimeter
		+  std::to_string(r.AllWellsGasCapacity) +  columnDelimeter
		+ r.resourceClass +  columnDelimeter
		+ std::to_string(condensateRate) +  columnDelimeter
		+ r.reasonForTermination +  columnDelimeter
		+ lastrow;

		return row;

}

string ReportJSON2::GetRow(ForecastResult& r, int& scenario, int& ii, vector<Date>& dateTimes){

string row = "";
string columnDelimeter = "@#$%";
string rowDelimeter = "@#*$%";
int days = dateCreation.DateDiff_TotalDays(dateTimes[ii], dateTimes[0]);

std::string uniqueId = r.ModuleName + r.Flow_station + to_string(scenario) + "P" + to_string(scenario) + "C" +  to_string(ii);

double oilRate = 0, condensateRate = 0;
if(r.HyrocarbonStream == "oil"){
	oilRate = r.Oil_rate;
	condensateRate = 0;
}else{
	condensateRate = r.Oil_rate;
	oilRate = 0;
}

if(r.isOilTerminated == true){
	 oilRate = 0;
	 condensateRate = 0;
}

if(r.isGasTerminated == true){
	 r.Gas_Rate = 0;
}

if(r.isWaterTerminated == true){
	 r.Water_Rate = 0;
}


double liquid =  0;
if(r.HyrocarbonStream == "oil"){
	liquid =  oilRate + r.Water_Rate;
}else{
	liquid =  condensateRate + r.Water_Rate;
}

string lastrow = std::to_string(r.DeclineRate) +  rowDelimeter;


//isLastRow
row = uniqueId +  columnDelimeter
		+ r.Version_Name +  columnDelimeter
		+ r.Field +  columnDelimeter
		+ r.Reservoir +  columnDelimeter
		+ r.Drainage_Point +  columnDelimeter
		+ r.Production_String +  columnDelimeter
		+ r.TRANCHE +  columnDelimeter
		+ r.Asset_Team +  columnDelimeter
		+ r.Flow_station +  columnDelimeter
		+ r.ModuleName +  columnDelimeter
		+ std::to_string(r.Day) +  columnDelimeter
		+ std::to_string(r.Month) +  columnDelimeter
		+ std::to_string(r.Year) +  columnDelimeter
		+ std::to_string(oilRate) +  columnDelimeter
		+ std::to_string(r.Gas_Rate) +  columnDelimeter
		+ std::to_string(r.Water_Rate) +  columnDelimeter
		+ std::to_string(liquid) +  columnDelimeter
		+ std::to_string(r.Cum_Oil_Prod) +  columnDelimeter
		+ std::to_string(r.Cum_Gas_Prod) +  columnDelimeter
		+ std::to_string(r.Cum_Water_Prod) +  columnDelimeter
		+ std::to_string(r.GOR) +  columnDelimeter
		+ std::to_string(r.BSW) +  columnDelimeter
		+ std::to_string(r.CGR) +  columnDelimeter
		+ std::to_string(r.WGR) +  columnDelimeter
		+ std::to_string(r.CutBack) +  columnDelimeter
		+ r.HyrocarbonStream +  columnDelimeter
		+ r.hydrocarbonType +  columnDelimeter
		+ r.terminal +  columnDelimeter
		+ std::to_string(r.URo) +  columnDelimeter
		+ std::to_string(r.URg) +  columnDelimeter
		+ std::to_string(r.Gas_Own_Use) +  columnDelimeter
		+ std::to_string(r.Gas_Demand) +  columnDelimeter
		+ std::to_string(r.Gas_Flared) +  columnDelimeter
		+ std::to_string(r.Crude_Oil_Lossess) +  columnDelimeter
		+ std::to_string(r.CutBack) +  columnDelimeter
		+ r.projectCode +  columnDelimeter
		+ r.projectName +  columnDelimeter
		+ std::to_string(days) +  columnDelimeter
		+  std::to_string(r.OptimalSolution) +  columnDelimeter
		+  std::to_string(r.AllWellsLiquidCapacity) +  columnDelimeter
		+  std::to_string(r.AllWellsGasCapacity) +  columnDelimeter
		+ r.resourceClass +  columnDelimeter
		+ std::to_string(condensateRate) +  columnDelimeter
		+ r.reasonForTermination +  columnDelimeter
		+ lastrow;

		return row;

}

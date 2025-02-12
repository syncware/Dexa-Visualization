#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <algorithm>
#include "Forecast.h"
#include "FractionalFlow.h"
#include "Decline_Curve_Analysis.h"
#include "DateCreation.h"

using namespace std;

class Inputdeck
{
private:
	FractionalFlow fractionalFlow;
	Decline_Curve_Analysis decline_Curve_Analysis;
	DateCreation dateCreation;



public:
	Inputdeck();
	vector<FacilityStruct> FacilityTable_Actual;
	vector<vector<FacilityStruct>> FacilityTables_Actual;
	void customGetline(string const &str, const char &delimeter,
					   vector<string> &out);
	void tokenize(string const &str, const char &delimeter, vector<string> &out);
	void tokenize(string const &str, const string &delimeter,
				  vector<string> &out);
	void GetFacilityTablePointer(const char *filepath, const char delimeter);
	bool IsContains(vector<string> &Faclities, string &Facility);
	vector<FacilityStruct> SortFacilities(vector<FacilityStruct> &facilityRows);
	vector<string> GetFacilities(vector<InputDeckStruct> &_inputdeckss, int size, vector<Date> &dateList, int &scenario);
	void GetRunParameters(const char *filepath, const char delimeter);
	vector<vector<vector<InputDeckStruct>>> GetModulesByFacility(vector<string> &Faclities, 
	vector<InputDeckStruct> &decks,
	int size, vector<WellReroute> wellRerouteDecks, vector<Date> dates, int scenario, 
	vector<WellSchedule>& wellSchedules, vector<Prioritization>& priotizations);
	vector<vector<vector<InputDeckStruct>>> GetModulesByFacility_Obsolete(vector<string> &Faclities, 
	vector<InputDeckStruct> &decks,
	int size, vector<WellReroute> wellRerouteDecks, vector<Date> dates, int scenario, 
	vector<WellSchedule>& wellSchedules, vector<Prioritization>& priotizations);
	void ValidateDeck(InputDeckStruct &extendedInputDeck);
	vector<FacilityStruct> ResizeTempFacilities(vector<FacilityStruct> &tempFacilities, vector<Date> &dateList);
	vector<string> GetUniqueReroutedWells(vector<WellReroute> &inputdecks, int size);
	/* map<string, vector<WellReroute>> GetGrouppedRoutedWells(
		vector<WellReroute>& inputdecks, vector<string> wellNames); */
	void ToLower(string &x);
	~Inputdeck();
	vector<InputDeckStruct> inputdecks;
	vector<WellReroute> wellRerouteDecks;
	vector<WellRampUp> wellRampUpDecks;
	vector<ShutInOpenUp> wellShutInOpenUpDecks;
	vector<FacilityStructExternal> FacilityTable;
	double myZero = 0.00000001;
	RunParameter runParameter;
	vector<vector<vector<InputDeckStruct>>> FacilitiesAllIndicies;
	bool CheckWellName(vector<string> wellNames, string wellName);
	vector<vector<FacilityWellsIndicies>> facilityWellsIndicies;
	vector<vector<Prioritization>> priotizationsFacilities;
	void InitilizeModule(InputDeckStruct &extendedInputDeck);
	void InitilizeModules();
	void CalculateDeclineParameters(InputDeckStruct &extendedInputDeck);
	vector<DeclineParameterResult> InitilizeDefaultDeclineParameters();
	double cumProdDays;
	bool isRateCum;
	Date stopDate;
	Date startDate;
};

Inputdeck::Inputdeck()
{
}

Inputdeck::~Inputdeck()
{
}

void Inputdeck::tokenize(string const &str, const char &delimeter,
						 vector<string> &out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delimeter, end)) != string::npos)
	{
		end = str.find(delimeter, start);
		out.push_back(str.substr(start, end - start));
	}
}

void Inputdeck::customGetline(string const &str, const char &delimeter,
							  vector<string> &out)
{
	//create a stream from the string
	//stringstream s(str);
	//string s2;
	/* while (getline(s, s2, delimeter))
	{
		out.push_back(s2);
	} */
}

void Inputdeck::tokenize(string const &str, const string &delimeter,
						 vector<string> &out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delimeter, end)) != string::npos)
	{
		end = str.find(delimeter, start);
		out.push_back(str.substr(start, end - start));
	}
}

void Inputdeck::ToLower(string &str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void Inputdeck::ValidateDeck(InputDeckStruct &extendedInputDeck)
{
	string Description = "no error";
	string newline = "\n";

	bool isLinear = false;

	if (extendedInputDeck.Hydrocarbon_Stream.empty() == true)
	{
		Description = Description + "Hydrocarbon stream cannot be undefined" + newline;
		extendedInputDeck.Description = Description;
		return;
	}

	bool check_DGOR_CGR_1P1C = false;
	bool check_DGOR_CGR_2P2C = false;
	bool check_DGOR_CGR_3P3C = false;
	bool check_DBSW_WGR_1P1C = false;
	bool check_DBSW_WGR_2P2C = false;
	bool check_DBSW_WGR_3P3C = false;
	bool check_Rate_1P1C = false;
	bool check_Rate_2P2C = false;
	bool check_Rate_3P3C = false;
	bool check_UR_1P1C = false;
	bool check_UR_2P2C = false;
	bool check_UR_3P3C = false;
	double MM = 1000000.0;
	double x1 = 0, x2 = 0;

	if(extendedInputDeck.Hydrocarbon_Stream == oil){
		
		extendedInputDeck.PlateauUR_1P_1C = extendedInputDeck.Plateau_Oil_Gas * 365.0 * extendedInputDeck.Init_Liquid_Gas_Rate_1P_1C / MM;

		extendedInputDeck.PlateauUR_2P_2C = extendedInputDeck.Plateau_Oil_Gas * 365.0 * extendedInputDeck.Init_Liquid_Gas_Rate_2P_2C / MM;

		extendedInputDeck.PlateauUR_3P_3C = extendedInputDeck.Plateau_Oil_Gas * 365.0 * extendedInputDeck.Init_Liquid_Gas_Rate_3P_3C / MM;
	}else{
		
		extendedInputDeck.PlateauUR_1P_1C = extendedInputDeck.Plateau_Oil_Gas * (extendedInputDeck.URg_1P_1C - extendedInputDeck.Gp);

		extendedInputDeck.PlateauUR_2P_2C = extendedInputDeck.Plateau_Oil_Gas * (extendedInputDeck.URg_2P_2C - extendedInputDeck.Gp);

		extendedInputDeck.PlateauUR_3P_3C = extendedInputDeck.Plateau_Oil_Gas * (extendedInputDeck.URg_3P_3C - extendedInputDeck.Gp);
	}


	if (extendedInputDeck.Hydrocarbon_Stream == "oil")
	{

		if (extendedInputDeck.URo_1P_1C <= myZero)
		{
			check_UR_1P1C = true;
			Description = Description + "Ultimate oil recovery cannot be less than or equal zero (1P/1C)" + newline;
		}

		if (extendedInputDeck.URo_2P_2C <= myZero)
		{
			check_UR_2P2C = true;
			Description = Description + "Ultimate oil recovery cannot be less than or equal zero (2P/2C)" + newline;
		}

		if (extendedInputDeck.URo_3P_3C <= myZero)
		{
			check_UR_3P3C = true;
			Description = Description + "Ultimate oil recovery cannot be less than or equal zero (3P/3C)" + newline;
		}

		if (extendedInputDeck.Init_Liquid_Gas_Rate_1P_1C <= myZero)
		{
			check_Rate_1P1C = true;
			Description = Description + "Initial liquid rate cannot be less than or equal zero (1P/1C)" + newline;
		}

		if (extendedInputDeck.Init_Liquid_Gas_Rate_2P_2C <= myZero)
		{
			check_Rate_2P2C = true;
			Description = Description + "Initial liquid rate cannot be less than or equal zero (2P/2C)" + newline;
		}

		if (extendedInputDeck.Init_Liquid_Gas_Rate_3P_3C <= myZero)
		{
			check_Rate_2P2C = true;
			Description = Description + "Initial liquid rate cannot be less than or equal zero (3P/3C)" + newline;
		}

		if (extendedInputDeck.Init_Liquid_Gas_Rate_1P_1C <= extendedInputDeck.Aband_Liquid_Gas_Rate_1P_1C)
		{
			check_Rate_1P1C = true;
			Description = Description + "Initial liquid rate cannot be less than or equal abandonment liquid rate (1P/1C)" + newline;
		}

		if (extendedInputDeck.Init_Liquid_Gas_Rate_2P_2C <= extendedInputDeck.Aband_Liquid_Gas_Rate_2P_2C)
		{
			check_Rate_2P2C = true;
			Description = Description + "Initial liquid rate cannot be less than or equal abandonment liquid rate (2P/2C)" + newline;
		}

		if (extendedInputDeck.Init_Liquid_Gas_Rate_3P_3C <= extendedInputDeck.Aband_Liquid_Gas_Rate_3P_3C)
		{
			check_Rate_3P3C = true;
			Description = Description + "Initial liquid rate cannot be less than or equal abandonment liquid rate (3P/3C)" + newline;
		}

		if (extendedInputDeck.Np >= extendedInputDeck.URo_1P_1C)
		{
			check_DGOR_CGR_1P1C = true;
			check_DBSW_WGR_1P1C = true;
			Description = Description + "Cumulative oil in place cannot be greater than or equal to ulimate oil recovery (1P/1C)" + newline;
		}
		if (extendedInputDeck.Np >= extendedInputDeck.URo_2P_2C)
		{
			check_DBSW_WGR_2P2C = true;
			check_DGOR_CGR_2P2C = true;
			Description = Description + "Cumulative oil in place cannot be greater than or equal to ulimate oil recovery (2P/2C)" + newline;
		}
		if (extendedInputDeck.Np >= extendedInputDeck.URo_3P_3C)
		{
			check_DBSW_WGR_3P3C = true;
			check_DGOR_CGR_3P3C = true;
			Description = Description + "Cumulative oil in place cannot be greater than or equal to ulimate oil recovery (3P/3C)" + newline;
		}

		if (extendedInputDeck.Init_BSW_WGR > extendedInputDeck.Aband_BSW_WGR_1P_1C)
		{
			check_DBSW_WGR_1P1C = true;
			Description = Description + "Initial BSW cannot be greater than or equal to abandonment BSW (1P/1C)" + newline;
		}
		if (extendedInputDeck.Init_BSW_WGR > extendedInputDeck.Aband_BSW_WGR_2P_2C)
		{
			check_DBSW_WGR_2P2C = true;
			Description = Description + "Initial BSW cannot be greater than or equal to abandonment BSW (2P/2C)" + newline;
		}
		if (extendedInputDeck.Init_BSW_WGR > extendedInputDeck.Aband_BSW_WGR_3P_3C)
		{
			check_DBSW_WGR_3P3C = true;
			Description = Description + "Initial BSW cannot be greater than or equal to abandonment BSW (3P/3C)" + newline;
		}

		if (extendedInputDeck.Init_GOR_CGR > extendedInputDeck.Aband_GOR_CGR_1P_1C)
		{
			check_DGOR_CGR_1P1C = true;
			Description = Description + "Initial GOR cannot be greater than or equal to abandonment GOR (1P/1C)" + newline;
		}
		if (extendedInputDeck.Init_GOR_CGR > extendedInputDeck.Aband_GOR_CGR_2P_2C)
		{
			check_DGOR_CGR_2P2C = true;
			Description = Description + "Initial GOR cannot be greater than or equal to abandonment GOR (2P/2C)" + newline;
		}
		if (extendedInputDeck.Init_GOR_CGR > extendedInputDeck.Aband_GOR_CGR_3P_3C)
		{
			check_DGOR_CGR_3P3C = true;
			Description = Description + "Initial GOR cannot be greater than or equal to abandonment GOR (3P/3C)" + newline;
		}
	}

	if (extendedInputDeck.Hydrocarbon_Stream == "gas")
	{
		if (extendedInputDeck.URg_1P_1C <= myZero)
		{
			check_UR_1P1C = true;
			Description = Description + "Ultimate gas recovery cannot be less than or equal zero (1P/1C)" + newline;
		}

		if (extendedInputDeck.URg_2P_2C <= myZero)
		{
			check_UR_2P2C = true;
			Description = Description + "Ultimate gas recovery cannot be less than or equal zero (2P/2C)" + newline;
		}

		if (extendedInputDeck.URg_3P_3C <= myZero)
		{
			check_UR_3P3C = true;
			Description = Description + "Ultimate gas recovery cannot be less than or equal zero (3P/3C)" + newline;
		}

		if (extendedInputDeck.Init_Liquid_Gas_Rate_1P_1C <= myZero)
		{
			check_Rate_1P1C = true;
			Description = Description + "Initial gas rate cannot be less than or equal zero (1P/1C)" + newline;
		}

		if (extendedInputDeck.Init_Liquid_Gas_Rate_2P_2C <= myZero)
		{
			check_Rate_2P2C = true;
			Description = Description + "Initial gas rate cannot be less than or equal zero (2P/2C)" + newline;
		}

		if (extendedInputDeck.Init_Liquid_Gas_Rate_3P_3C <= myZero)
		{
			check_Rate_3P3C = true;
			Description = Description + "Initial gas rate cannot be less than or equal zero (3P/3C)" + newline;
		}

		if (extendedInputDeck.Init_Liquid_Gas_Rate_1P_1C <= extendedInputDeck.Aband_Liquid_Gas_Rate_1P_1C)
		{
			check_Rate_1P1C = true;
			Description = Description + "Initial gas rate cannot be less than or equal abandonment gas rate (1P/1C)" + newline;
		}

		if (extendedInputDeck.Init_Liquid_Gas_Rate_2P_2C <= extendedInputDeck.Aband_Liquid_Gas_Rate_2P_2C)
		{
			check_Rate_2P2C = true;
			Description = Description + "Initial gas rate cannot be less than or equal abandonment gas rate (2P/2C)" + newline;
		}

		if (extendedInputDeck.Init_Liquid_Gas_Rate_3P_3C <= extendedInputDeck.Aband_Liquid_Gas_Rate_3P_3C)
		{
			check_Rate_3P3C = true;
			Description = Description + "Initial gas rate cannot be less than or equal abandonment gas rate (3P/3C)" + newline;
		}

		if (extendedInputDeck.Gp >= extendedInputDeck.URg_1P_1C)
		{
			check_DGOR_CGR_1P1C = true;
			check_DBSW_WGR_1P1C = true;
			Description = Description + "Cumulative gas in place cannot be greater than or equal to ulimate gas recovery (1P/1C)" + newline;
		}
		if (extendedInputDeck.Gp >= extendedInputDeck.URg_2P_2C)
		{
			check_DBSW_WGR_2P2C = true;
			check_DGOR_CGR_2P2C = true;
			Description = Description + "Cumulative gas in place cannot be greater than or equal to ulimate gas recovery (2P/2C)" + newline;
		}
		if (extendedInputDeck.Gp >= extendedInputDeck.URg_3P_3C)
		{
			check_DBSW_WGR_3P3C = true;
			check_DGOR_CGR_3P3C = true;
			Description = Description + "Cumulative gas in place cannot be greater than or equal to ulimate gas recovery (3P/3C)" + newline;
		}

		if (extendedInputDeck.Init_BSW_WGR > extendedInputDeck.Aband_BSW_WGR_1P_1C)
		{
			check_DBSW_WGR_1P1C = true;
			Description = Description + "Initial WGR cannot be greater than or equal to abandonment WGR (1P/1C)" + newline;
		}
		if (extendedInputDeck.Init_BSW_WGR > extendedInputDeck.Aband_BSW_WGR_2P_2C)
		{
			check_DBSW_WGR_2P2C = true;
			Description = Description + "Initial WGR cannot be greater than or equal to abandonment WGR (2P/2C)" + newline;
		}
		if (extendedInputDeck.Init_BSW_WGR > extendedInputDeck.Aband_BSW_WGR_3P_3C)
		{
			check_DBSW_WGR_3P3C = true;
			Description = Description + "Initial WGR cannot be greater than or equal to abandonment WGR (3P/3C)" + newline;
		}

		if (extendedInputDeck.Init_GOR_CGR < extendedInputDeck.Aband_GOR_CGR_1P_1C)
		{
			check_DGOR_CGR_1P1C = true;
			Description = Description + "Initial CGR cannot be less than or equal to abandonment CGR (1P/1C)" + newline;
		}
		if (extendedInputDeck.Init_GOR_CGR < extendedInputDeck.Aband_GOR_CGR_2P_2C)
		{
			check_DGOR_CGR_2P2C = true;
			Description = Description + "Initial CGR cannot be less than or equal to abandonment CGR (2P/2C)" + newline;
		}
		if (extendedInputDeck.Init_GOR_CGR < extendedInputDeck.Aband_GOR_CGR_3P_3C)
		{
			check_DGOR_CGR_3P3C = true;
			Description = Description + "Initial CGR cannot be less than or equal to abandonment CGR (3P/3C)" + newline;
		}
	}

	extendedInputDeck.Description = Description;

	// double cumProdDays_1P_1C = dateCreation.DateDiff_TotalDays(stopDate, extendedInputDeck.Date_1P_1C);
	// double cumProdDays_2P_2C = dateCreation.DateDiff_TotalDays(stopDate, extendedInputDeck.Date_2P_2C);
	// double cumProdDays_3P_3C = dateCreation.DateDiff_TotalDays(stopDate, extendedInputDeck.Date_3P_3C);

	double cumProdDays_1P_1C = dateCreation.DateDiff_TotalDays(stopDate, startDate);
	double cumProdDays_2P_2C = dateCreation.DateDiff_TotalDays(stopDate, startDate);
	double cumProdDays_3P_3C = dateCreation.DateDiff_TotalDays(stopDate, startDate);

	if (extendedInputDeck.Hydrocarbon_Stream == "oil")
	{

		if (check_DBSW_WGR_1P1C == false && check_UR_1P1C == false)
		{
			x1 = extendedInputDeck.Np * MM;
			x2 = extendedInputDeck.URo_1P_1C * MM;

			extendedInputDeck.Rate_Of_Rate_BSW_WGR_1P1C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
				x1, x2, extendedInputDeck.Init_BSW_WGR,
				extendedInputDeck.Aband_BSW_WGR_1P_1C, cumProdDays_1P_1C, isRateCum, isLinear);
		}
		if (check_DBSW_WGR_2P2C == false && check_UR_2P2C == false)
		{
			x1 = extendedInputDeck.Np * MM;
			x2 = extendedInputDeck.URo_2P_2C * MM;

			extendedInputDeck.Rate_Of_Rate_BSW_WGR_2P2C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
				x1, x2, extendedInputDeck.Init_BSW_WGR,
				extendedInputDeck.Aband_BSW_WGR_2P_2C, cumProdDays_2P_2C, isRateCum, isLinear);
		}
		if (check_DBSW_WGR_3P3C == false && check_UR_3P3C == false)
		{
			x1 = extendedInputDeck.Np * MM;
			x2 = extendedInputDeck.URo_3P_3C * MM;

			extendedInputDeck.Rate_Of_Rate_BSW_WGR_3P3C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
				x1, x2, extendedInputDeck.Init_BSW_WGR,
				extendedInputDeck.Aband_BSW_WGR_3P_3C, cumProdDays_3P_3C, isRateCum, isLinear);
		}

		if (check_DGOR_CGR_1P1C == false && check_UR_1P1C == false)
		{
			x1 = extendedInputDeck.Np * MM;
			x2 = extendedInputDeck.URo_1P_1C * MM;

			extendedInputDeck.Rate_Of_Rate_GOR_CGR_1P1C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
				x1, x2, extendedInputDeck.Init_GOR_CGR,
				extendedInputDeck.Aband_GOR_CGR_1P_1C, cumProdDays_1P_1C, isRateCum, isLinear);
		}
		if (check_DGOR_CGR_2P2C == false && check_UR_2P2C == false)
		{
			x1 = extendedInputDeck.Np * MM;
			x2 = extendedInputDeck.URo_2P_2C * MM;

			extendedInputDeck.Rate_Of_Rate_GOR_CGR_2P2C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
				x1, x2, extendedInputDeck.Init_GOR_CGR,
				extendedInputDeck.Aband_GOR_CGR_2P_2C, cumProdDays_2P_2C, isRateCum, isLinear);
		}
		if (check_DGOR_CGR_3P3C == false && check_UR_3P3C == false)
		{
			x1 = extendedInputDeck.Np * MM;
			x2 = extendedInputDeck.URo_3P_3C * MM;

			extendedInputDeck.Rate_Of_Rate_GOR_CGR_3P3C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
				x1, x2, extendedInputDeck.Init_GOR_CGR,
				extendedInputDeck.Aband_GOR_CGR_3P_3C, cumProdDays_3P_3C, isRateCum, isLinear);
		}

		if (check_Rate_1P1C == false && check_UR_1P1C == false)
		{
			x1 = extendedInputDeck.Np * MM;
			x2 = extendedInputDeck.URo_1P_1C * MM;
			extendedInputDeck.Rate_of_Change_Rate_1P_1C = decline_Curve_Analysis.Get_DeclineFactor(
				extendedInputDeck.Init_Liquid_Gas_Rate_1P_1C, extendedInputDeck.Aband_Liquid_Gas_Rate_1P_1C,
				x1, x2, extendedInputDeck.DeclineMethod, cumProdDays_1P_1C, isRateCum);
		}
		if (check_Rate_2P2C == false && check_UR_2P2C == false)
		{
			x1 = extendedInputDeck.Np * MM;
			x2 = extendedInputDeck.URo_2P_2C * MM;

			extendedInputDeck.Rate_of_Change_Rate_2P_2C = decline_Curve_Analysis.Get_DeclineFactor(
				extendedInputDeck.Init_Liquid_Gas_Rate_2P_2C, extendedInputDeck.Aband_Liquid_Gas_Rate_2P_2C,
				x1, x2, extendedInputDeck.DeclineMethod, cumProdDays_2P_2C, isRateCum);
		}
		if (check_Rate_3P3C == false && check_UR_3P3C == false)
		{
			x1 = extendedInputDeck.Np * MM;
			x2 = extendedInputDeck.URo_3P_3C * MM;

			extendedInputDeck.Rate_of_Change_Rate_3P_3C = decline_Curve_Analysis.Get_DeclineFactor(
				extendedInputDeck.Init_Liquid_Gas_Rate_3P_3C, extendedInputDeck.Aband_Liquid_Gas_Rate_3P_3C,
				x1, x2, extendedInputDeck.DeclineMethod, cumProdDays_3P_3C, isRateCum);
		}
	}

	if (extendedInputDeck.Hydrocarbon_Stream == "gas")
	{
		if (check_DBSW_WGR_1P1C == false && check_UR_1P1C == false)
		{
			x1 = extendedInputDeck.Gp * MM;
			x2 = extendedInputDeck.URg_1P_1C * MM;
			//Get_Fractional_Rate_Of_Change_Exponential(double& X_init, double& X_last, double& Y_init, double& Y_last)

			extendedInputDeck.Rate_Of_Rate_BSW_WGR_1P1C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
				x1, x2, extendedInputDeck.Init_BSW_WGR,
				extendedInputDeck.Aband_BSW_WGR_1P_1C, cumProdDays_1P_1C, isRateCum, isLinear);
		}
		if (check_DBSW_WGR_2P2C == false && check_UR_2P2C == false)
		{
			x1 = extendedInputDeck.Gp * MM;
			x2 = extendedInputDeck.URg_2P_2C * MM;

			extendedInputDeck.Rate_Of_Rate_BSW_WGR_2P2C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
				x1, x2, extendedInputDeck.Init_BSW_WGR,
				extendedInputDeck.Aband_BSW_WGR_2P_2C, cumProdDays_2P_2C, isRateCum, isLinear);
		}
		if (check_DBSW_WGR_3P3C == false && check_UR_3P3C == false)
		{
			x1 = extendedInputDeck.Gp * MM;
			x2 = extendedInputDeck.URg_3P_3C * MM;

			extendedInputDeck.Rate_Of_Rate_BSW_WGR_3P3C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
				x1, x2, extendedInputDeck.Init_BSW_WGR,
				extendedInputDeck.Aband_BSW_WGR_3P_3C, cumProdDays_3P_3C, isRateCum, isLinear);
		}

		if (check_DGOR_CGR_1P1C == false && check_UR_1P1C == false)
		{
			x1 = extendedInputDeck.Gp * MM;
			x2 = extendedInputDeck.URg_1P_1C * MM;

			extendedInputDeck.Rate_Of_Rate_GOR_CGR_1P1C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
				x1, x2, extendedInputDeck.Init_GOR_CGR,
				extendedInputDeck.Aband_GOR_CGR_1P_1C, cumProdDays_1P_1C, isRateCum, isLinear);
		}
		if (check_DGOR_CGR_2P2C == false && check_UR_2P2C == false)
		{
			x1 = extendedInputDeck.Gp * MM;
			x2 = extendedInputDeck.URg_2P_2C * MM;

			extendedInputDeck.Rate_Of_Rate_GOR_CGR_2P2C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
				x1, x2, extendedInputDeck.Init_GOR_CGR,
				extendedInputDeck.Aband_GOR_CGR_2P_2C, cumProdDays_2P_2C, isRateCum, isLinear);
		}
		if (check_DGOR_CGR_3P3C == false && check_UR_3P3C == false)
		{
			x1 = extendedInputDeck.Gp * MM;
			x2 = extendedInputDeck.URg_3P_3C * MM;

			extendedInputDeck.Rate_Of_Rate_GOR_CGR_3P3C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
				x1, x2, extendedInputDeck.Init_GOR_CGR,
				extendedInputDeck.Aband_GOR_CGR_3P_3C, cumProdDays_3P_3C, isRateCum, isLinear);
		}

		if (check_Rate_1P1C == false && check_UR_1P1C == false)
		{
			x1 = extendedInputDeck.Gp * MM;
			x2 = extendedInputDeck.URg_1P_1C * MM;

			extendedInputDeck.Rate_of_Change_Rate_1P_1C = decline_Curve_Analysis.Get_DeclineFactor(
				extendedInputDeck.Init_Liquid_Gas_Rate_1P_1C, extendedInputDeck.Aband_Liquid_Gas_Rate_1P_1C,
				x1, x2, extendedInputDeck.DeclineMethod, cumProdDays_1P_1C, isRateCum);
		}
		if (check_Rate_2P2C == false && check_UR_2P2C == false)
		{
			x1 = extendedInputDeck.Gp * MM;
			x2 = extendedInputDeck.URg_2P_2C * MM;

			extendedInputDeck.Rate_of_Change_Rate_2P_2C = decline_Curve_Analysis.Get_DeclineFactor(
				extendedInputDeck.Init_Liquid_Gas_Rate_2P_2C, extendedInputDeck.Aband_Liquid_Gas_Rate_2P_2C,
				x1, x2, extendedInputDeck.DeclineMethod, cumProdDays_2P_2C, isRateCum);
		}
		if (check_Rate_3P3C == false && check_UR_3P3C == false)
		{
			x1 = extendedInputDeck.Gp * MM;
			x2 = extendedInputDeck.URg_3P_3C * MM;

			extendedInputDeck.Rate_of_Change_Rate_3P_3C = decline_Curve_Analysis.Get_DeclineFactor(
				extendedInputDeck.Init_Liquid_Gas_Rate_3P_3C, extendedInputDeck.Aband_Liquid_Gas_Rate_3P_3C,
				x1, x2, extendedInputDeck.DeclineMethod, cumProdDays_3P_3C, isRateCum);
		}

	}
}

void Inputdeck::CalculateDeclineParameters(InputDeckStruct &extendedInputDeck)
{


	double MM = 1000000.0;
	double x1 = 0, x2 = 0;
	bool isLinear = false;
	double days365 = 360.0;
	double UR_NoPlateau1P1C = 0, UR_NoPlateau2P2C = 0, UR_NoPlateau3P3C;

	double PlateauDays1P1C = 0, PlateauDays2P2C = 0, PlateauDays3P3C = 0;

	if(extendedInputDeck.Hydrocarbon_Stream == oil){
		
		PlateauDays1P1C = extendedInputDeck.Plateau_Oil_Gas * days365;
		extendedInputDeck.PlateauUR_1P_1C = extendedInputDeck.Plateau_Oil_Gas * days365
		* (extendedInputDeck.Init_Liquid_Gas_Rate_1P_1C/(1 - extendedInputDeck.Init_BSW_WGR)) / MM;

		UR_NoPlateau1P1C = extendedInputDeck.URo_1P_1C - (extendedInputDeck.PlateauUR_1P_1C * (1 - extendedInputDeck.Init_BSW_WGR));

		PlateauDays2P2C = extendedInputDeck.Plateau_Oil_Gas * days365;
		extendedInputDeck.PlateauUR_2P_2C = extendedInputDeck.Plateau_Oil_Gas * days365 
		* (extendedInputDeck.Init_Liquid_Gas_Rate_2P_2C/(1 - extendedInputDeck.Init_BSW_WGR)) / MM;

		UR_NoPlateau2P2C = extendedInputDeck.URo_2P_2C - (extendedInputDeck.PlateauUR_2P_2C * (1 - extendedInputDeck.Init_BSW_WGR));


		PlateauDays3P3C = extendedInputDeck.Plateau_Oil_Gas * days365;
		extendedInputDeck.PlateauUR_3P_3C = extendedInputDeck.Plateau_Oil_Gas * days365
		* (extendedInputDeck.Init_Liquid_Gas_Rate_3P_3C/(1 - extendedInputDeck.Init_BSW_WGR)) / MM;

		UR_NoPlateau3P3C = extendedInputDeck.URo_3P_3C - (extendedInputDeck.PlateauUR_3P_3C * (1 - extendedInputDeck.Init_BSW_WGR));
	}else{
		
		extendedInputDeck.PlateauUR_1P_1C = extendedInputDeck.Plateau_Oil_Gas * (extendedInputDeck.URg_1P_1C - extendedInputDeck.Gp);
		PlateauDays1P1C = extendedInputDeck.PlateauUR_1P_1C/extendedInputDeck.Init_Liquid_Gas_Rate_1P_1C;

		UR_NoPlateau1P1C = extendedInputDeck.URg_1P_1C - extendedInputDeck.PlateauUR_1P_1C;

		extendedInputDeck.PlateauUR_2P_2C = extendedInputDeck.Plateau_Oil_Gas * (extendedInputDeck.URg_2P_2C - extendedInputDeck.Gp);
		PlateauDays2P2C = extendedInputDeck.PlateauUR_2P_2C/extendedInputDeck.Init_Liquid_Gas_Rate_2P_2C;

		UR_NoPlateau2P2C = extendedInputDeck.URg_2P_2C - extendedInputDeck.PlateauUR_2P_2C;

		extendedInputDeck.PlateauUR_3P_3C = extendedInputDeck.Plateau_Oil_Gas * (extendedInputDeck.URg_3P_3C - extendedInputDeck.Gp);
		PlateauDays3P3C = extendedInputDeck.PlateauUR_3P_3C/extendedInputDeck.Init_Liquid_Gas_Rate_3P_3C;

		UR_NoPlateau3P3C = extendedInputDeck.URg_3P_3C - extendedInputDeck.PlateauUR_3P_3C;
	}

	double cumProdDays_1P_1C = dateCreation.DateDiff_TotalDays(stopDate, extendedInputDeck.Date_1P_1C) - PlateauDays1P1C;
	double cumProdDays_2P_2C = dateCreation.DateDiff_TotalDays(stopDate, extendedInputDeck.Date_2P_2C) - PlateauDays2P2C;
	double cumProdDays_3P_3C = dateCreation.DateDiff_TotalDays(stopDate, extendedInputDeck.Date_3P_3C) - PlateauDays3P3C;

	if(cumProdDays_1P_1C < 0){
		cumProdDays_1P_1C = 0;
	}

	if(cumProdDays_2P_2C < 0){
		cumProdDays_2P_2C = 0;
	}

	if(cumProdDays_3P_3C < 0){
		cumProdDays_3P_3C = 0;
	}

	if(UR_NoPlateau1P1C < 0){
		UR_NoPlateau1P1C = 0;
	}

	if(UR_NoPlateau2P2C < 0){
		UR_NoPlateau2P2C = 0;
	}

	if(UR_NoPlateau3P3C < 0){
		UR_NoPlateau3P3C = 0;
	}

	//(1) DeclineFactor : 1.40569292346369E-04 : denominator = EndOfDate - WellOSD

	//(2) DeclineFactor : 1.07361963190184E-03 : denominator = UR - IntCumProd

	//(3) DeclineFactor : 1.21137221349169E-04 : denominator = EndOfDate - StartDate

	// double cumProdDays_1P_1C = dateCreation.DateDiff_TotalDays(stopDate, startDate);
	// double cumProdDays_2P_2C = dateCreation.DateDiff_TotalDays(stopDate, startDate);
	// double cumProdDays_3P_3C = dateCreation.DateDiff_TotalDays(stopDate, startDate);

	if (extendedInputDeck.Hydrocarbon_Stream == "oil")
	{

		x1 = 0;//extendedInputDeck.Np * MM;
		x2 = UR_NoPlateau1P1C * MM;

		extendedInputDeck.Rate_Of_Rate_BSW_WGR_1P1C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
		x1, x2, extendedInputDeck.Init_BSW_WGR,
		extendedInputDeck.Aband_BSW_WGR_1P_1C, cumProdDays_1P_1C, isRateCum, isLinear);

		x1 = 0;//extendedInputDeck.Np * MM;
		x2 = UR_NoPlateau2P2C * MM;


		extendedInputDeck.Rate_Of_Rate_BSW_WGR_2P2C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
		x1, x2, extendedInputDeck.Init_BSW_WGR,
		extendedInputDeck.Aband_BSW_WGR_2P_2C, cumProdDays_2P_2C, isRateCum, isLinear);

		x1 = 0;//extendedInputDeck.Np * MM;
		x2 = UR_NoPlateau3P3C * MM;

		extendedInputDeck.Rate_Of_Rate_BSW_WGR_3P3C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
		x1, x2, extendedInputDeck.Init_BSW_WGR,
		extendedInputDeck.Aband_BSW_WGR_3P_3C, cumProdDays_3P_3C, isRateCum, isLinear);

		x1 = 0;//extendedInputDeck.Np * MM;
		x2 = UR_NoPlateau1P1C * MM;

		extendedInputDeck.Rate_Of_Rate_GOR_CGR_1P1C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
		x1, x2, extendedInputDeck.Init_GOR_CGR,
		extendedInputDeck.Aband_GOR_CGR_1P_1C, cumProdDays_1P_1C, isRateCum, isLinear);

		if(extendedInputDeck.Module == "FO20E10S_FO20 E10X_P12"){
			double df = 0;
		}

		x1 = 0;//extendedInputDeck.Np * MM;
		x2 = UR_NoPlateau2P2C * MM;

		extendedInputDeck.Rate_Of_Rate_GOR_CGR_2P2C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
		x1, x2, extendedInputDeck.Init_GOR_CGR,
		extendedInputDeck.Aband_GOR_CGR_2P_2C, cumProdDays_2P_2C, isRateCum, isLinear);

		x1 = 0;//extendedInputDeck.Np * MM;
		x2 = UR_NoPlateau3P3C * MM;

		extendedInputDeck.Rate_Of_Rate_GOR_CGR_3P3C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
		x1, x2, extendedInputDeck.Init_GOR_CGR,
		extendedInputDeck.Aband_GOR_CGR_3P_3C, cumProdDays_3P_3C, isRateCum, isLinear);

		x1 = 0;//extendedInputDeck.Np * MM;
		x2 = UR_NoPlateau1P1C * MM;
		// Here Init_Liquid_Gas_Rate_1P_1C is Initial oil rate
		extendedInputDeck.Rate_of_Change_Rate_1P_1C = decline_Curve_Analysis.Get_DeclineFactor(
		extendedInputDeck.Init_Liquid_Gas_Rate_1P_1C, extendedInputDeck.Aband_Liquid_Gas_Rate_1P_1C,
		x1, x2, extendedInputDeck.DeclineMethod, cumProdDays_1P_1C, isRateCum);

		x1 = 0;//extendedInputDeck.Np * MM;
		x2 = UR_NoPlateau2P2C * MM;

		extendedInputDeck.Rate_of_Change_Rate_2P_2C = decline_Curve_Analysis.Get_DeclineFactor(
		extendedInputDeck.Init_Liquid_Gas_Rate_2P_2C, extendedInputDeck.Aband_Liquid_Gas_Rate_2P_2C,
		x1, x2, extendedInputDeck.DeclineMethod, cumProdDays_2P_2C, isRateCum);

		x1 = 0;//extendedInputDeck.Np * MM;
		x2 = UR_NoPlateau3P3C * MM;

		extendedInputDeck.Rate_of_Change_Rate_3P_3C = decline_Curve_Analysis.Get_DeclineFactor(
		extendedInputDeck.Init_Liquid_Gas_Rate_3P_3C, extendedInputDeck.Aband_Liquid_Gas_Rate_3P_3C,
		x1, x2, extendedInputDeck.DeclineMethod, cumProdDays_3P_3C, isRateCum);
	}

	if (extendedInputDeck.Hydrocarbon_Stream == "gas")
	{
		x1 = 0;//extendedInputDeck.Gp * MM;
		x2 = UR_NoPlateau1P1C * MM;

		extendedInputDeck.Rate_Of_Rate_BSW_WGR_1P1C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
		x1, x2, extendedInputDeck.Init_BSW_WGR,
		extendedInputDeck.Aband_BSW_WGR_1P_1C, cumProdDays_1P_1C, isRateCum, isLinear);

		x1 = 0;//extendedInputDeck.Gp * MM;
		x2 = UR_NoPlateau2P2C * MM;

		extendedInputDeck.Rate_Of_Rate_BSW_WGR_2P2C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
		x1, x2, extendedInputDeck.Init_BSW_WGR,
		extendedInputDeck.Aband_BSW_WGR_2P_2C, cumProdDays_2P_2C, isRateCum, isLinear);

		x1 = 0;//extendedInputDeck.Gp * MM;
		x2 = UR_NoPlateau3P3C * MM;

		extendedInputDeck.Rate_Of_Rate_BSW_WGR_3P3C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
		x1, x2, extendedInputDeck.Init_BSW_WGR,
		extendedInputDeck.Aband_BSW_WGR_3P_3C, cumProdDays_3P_3C, isRateCum, isLinear);

		x1 = 0;//extendedInputDeck.Gp * MM;
		x2 = UR_NoPlateau1P1C * MM;
		//isLinear = false;

		extendedInputDeck.Rate_Of_Rate_GOR_CGR_1P1C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
		x1, x2, extendedInputDeck.Init_GOR_CGR,
		extendedInputDeck.Aband_GOR_CGR_1P_1C, cumProdDays_1P_1C, isRateCum, isLinear);

		x1 = 0;//extendedInputDeck.Gp * MM;
		x2 = UR_NoPlateau2P2C * MM;

		extendedInputDeck.Rate_Of_Rate_GOR_CGR_2P2C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
		x1, x2, extendedInputDeck.Init_GOR_CGR,
		extendedInputDeck.Aband_GOR_CGR_2P_2C, cumProdDays_2P_2C, isRateCum, isLinear);

		x1 = 0;//extendedInputDeck.Gp * MM;
		x2 = UR_NoPlateau3P3C * MM;

		extendedInputDeck.Rate_Of_Rate_GOR_CGR_3P3C = fractionalFlow.Get_Fractional_Rate_Of_Change_Exponential(
		x1, x2, extendedInputDeck.Init_GOR_CGR,
		extendedInputDeck.Aband_GOR_CGR_3P_3C, cumProdDays_3P_3C, isRateCum, isLinear);

		x1 = 0;//extendedInputDeck.Gp * MM;
		x2 = UR_NoPlateau1P1C * MM;

		extendedInputDeck.Rate_of_Change_Rate_1P_1C = decline_Curve_Analysis.Get_DeclineFactor(
		extendedInputDeck.Init_Liquid_Gas_Rate_1P_1C, extendedInputDeck.Aband_Liquid_Gas_Rate_1P_1C,
		x1, x2, extendedInputDeck.DeclineMethod, cumProdDays_1P_1C, isRateCum);

		x1 = 0;//extendedInputDeck.Gp * MM;
		x2 = UR_NoPlateau2P2C * MM;

		extendedInputDeck.Rate_of_Change_Rate_2P_2C = decline_Curve_Analysis.Get_DeclineFactor(
		extendedInputDeck.Init_Liquid_Gas_Rate_2P_2C, extendedInputDeck.Aband_Liquid_Gas_Rate_2P_2C,
		x1, x2, extendedInputDeck.DeclineMethod, cumProdDays_2P_2C, isRateCum);

		x1 = 0;//extendedInputDeck.Gp * MM;
		x2 = UR_NoPlateau3P3C * MM;

		extendedInputDeck.Rate_of_Change_Rate_3P_3C = decline_Curve_Analysis.Get_DeclineFactor(
		extendedInputDeck.Init_Liquid_Gas_Rate_3P_3C, extendedInputDeck.Aband_Liquid_Gas_Rate_3P_3C,
		x1, x2, extendedInputDeck.DeclineMethod, cumProdDays_3P_3C, isRateCum);


	}
}


void Inputdeck::InitilizeModules()
{
	int i = 0, n = inputdecks.size();
	for(i = 0; i < n; i++){
		CalculateDeclineParameters(inputdecks[i]);
		InitilizeModule(inputdecks[i]);
	}
}


vector<DeclineParameterResult> Inputdeck::InitilizeDefaultDeclineParameters()
{
	int i = 0, n = inputdecks.size();
	vector<DeclineParameterResult> declineParametersList;
	for(i = 0; i < n; i++){
		CalculateDeclineParameters(inputdecks[i]);
		InitilizeModule(inputdecks[i]);
		InputDeckStruct InputDeckRow = inputdecks[i];

		
		DeclineParameterResult declineParameters;
		declineParameters.forecastVersion=InputDeckRow.Version_Name;
		declineParameters.asset=InputDeckRow.Asset_Team;
		declineParameters.field=InputDeckRow.Field;
		declineParameters.reservoir=InputDeckRow.Reservoir;
		declineParameters.drainagePoint=InputDeckRow.Drainage_Point;
		declineParameters.productionString=InputDeckRow.Production_String;
		declineParameters.module=InputDeckRow.Module;
		declineParameters.hydrocarbonStream=InputDeckRow.Hydrocarbon_Stream;
		declineParameters.hydrocarbonType=InputDeckRow.hydrocarbonType;
		declineParameters.DeclineMethod=InputDeckRow.DeclineMethod;
		
		declineParameters.initOilGasRate1P1C=InputDeckRow.Init_Liquid_Gas_Rate_1P_1C;
		declineParameters.initOilGasRate2P2C=InputDeckRow.Init_Liquid_Gas_Rate_2P_2C;
		declineParameters.initOilGasRate3P3C=InputDeckRow.Init_Liquid_Gas_Rate_3P_3C;
		
		declineParameters.rateofChangeRate1P1C=InputDeckRow.Rate_of_Change_Rate_1P_1C;
		declineParameters.rateofChangeRate2P2C=InputDeckRow.Rate_of_Change_Rate_2P_2C;
		declineParameters.rateofChangeRate3P3C=InputDeckRow.Rate_of_Change_Rate_3P_3C;

		declineParameters.rateOfChangeGORCGR1P1C=InputDeckRow.Rate_Of_Rate_GOR_CGR_1P1C;
		declineParameters.rateOfChangeGORCGR2P2C=InputDeckRow.Rate_Of_Rate_GOR_CGR_2P2C;
		declineParameters.rateOfChangeGORCGR3P3C=InputDeckRow.Rate_Of_Rate_GOR_CGR_3P3C;

		declineParameters.rateOfChangeBSWWGR1P1C=InputDeckRow.Rate_Of_Rate_BSW_WGR_1P1C;
		declineParameters.rateOfChangeBSWWGR2P2C=InputDeckRow.Rate_Of_Rate_BSW_WGR_2P2C;
		declineParameters.rateOfChangeBSWWGR3P3C=InputDeckRow.Rate_Of_Rate_BSW_WGR_3P3C;

		double zro = 0.0;
		declineParameters.declineExponent1P1C= zro;
		declineParameters.declineExponent2P2C= zro;
		declineParameters.declineExponent3P3C=zro;
		
		string declineMethod = "exponential";
		if(InputDeckRow.DeclineMethod == 1)
		{
			declineMethod = "exponential";
		}
		else if(InputDeckRow.DeclineMethod == 2)
		{
			declineMethod = "hyperbolic";
		}
		else
		{
			declineMethod = "harmonic";
		}

		declineParameters.declineMethod=declineMethod;

		declineParametersList.push_back(declineParameters);
	}

	return declineParametersList;
}

void Inputdeck::InitilizeModule(InputDeckStruct &extendedInputDeck)
{

	double MM = 1000000.0;
	double x1 = 0, x2 = 0;

	if (extendedInputDeck.Hydrocarbon_Stream == "oil")
	{
		double fac = 1;

		double oilRate1 = extendedInputDeck.Init_Liquid_Gas_Rate_1P_1C;
		double one_minus_bsw1 = (1 - extendedInputDeck.Init_BSW_WGR);
		double liqRate1 = oilRate1 / one_minus_bsw1;
		extendedInputDeck.Init_Liquid_Gas_Rate_1P_1C = liqRate1;
		double declineRate1 = extendedInputDeck.Rate_of_Change_Rate_1P_1C * fac;
		extendedInputDeck.Rate_of_Change_Rate_1P_1C = declineRate1;
		extendedInputDeck.Aband_Liquid_Gas_Rate_1P_1C = extendedInputDeck.Aband_Liquid_Gas_Rate_1P_1C/ one_minus_bsw1;

		double oilRate2 = extendedInputDeck.Init_Liquid_Gas_Rate_2P_2C;
		double one_minus_bsw2 = (1 - extendedInputDeck.Init_BSW_WGR);
		double liqRate2 = oilRate2 / one_minus_bsw2;
		extendedInputDeck.Init_Liquid_Gas_Rate_2P_2C = liqRate2;
		double declineRate2 = extendedInputDeck.Rate_of_Change_Rate_2P_2C * fac;
		extendedInputDeck.Rate_of_Change_Rate_2P_2C = declineRate2;
		extendedInputDeck.Aband_Liquid_Gas_Rate_2P_2C = extendedInputDeck.Aband_Liquid_Gas_Rate_2P_2C/ one_minus_bsw2;

		double oilRate3 = extendedInputDeck.Init_Liquid_Gas_Rate_3P_3C;
		double one_minus_bsw3 = (1 - extendedInputDeck.Init_BSW_WGR);
		double liqRate3 = oilRate3 / one_minus_bsw3;
		extendedInputDeck.Init_Liquid_Gas_Rate_3P_3C = liqRate3;
		double declineRate3 = extendedInputDeck.Rate_of_Change_Rate_3P_3C * fac;
		extendedInputDeck.Rate_of_Change_Rate_3P_3C = declineRate3;
		extendedInputDeck.Aband_Liquid_Gas_Rate_3P_3C = extendedInputDeck.Aband_Liquid_Gas_Rate_3P_3C/ one_minus_bsw3;


		extendedInputDeck.Cum_Water_Prod = extendedInputDeck.Np * extendedInputDeck.Init_BSW_WGR /
									(1 - extendedInputDeck.Init_BSW_WGR);
		extendedInputDeck.Gp = extendedInputDeck.Np * extendedInputDeck.Init_GOR_CGR;
		extendedInputDeck.Cum_Liq_Prod = extendedInputDeck.Np + extendedInputDeck.Cum_Water_Prod;
	}

	if (extendedInputDeck.Hydrocarbon_Stream == "gas")
	{

		extendedInputDeck.Cum_Water_Prod = extendedInputDeck.Gp * extendedInputDeck.Init_BSW_WGR;
		extendedInputDeck.Np = extendedInputDeck.Gp * extendedInputDeck.Init_GOR_CGR;
		extendedInputDeck.Cum_Liq_Prod = extendedInputDeck.Np + extendedInputDeck.Cum_Water_Prod;
	}
}

bool Inputdeck::IsContains(vector<string> &Faclities, string &Facility)
{
	bool check = false;
	int Faclitiessize = Faclities.size();
	for (int i = 0; i < Faclitiessize; i++)
	{
		if (Faclities[i] == Facility)
		{
			check = true;
			break;
		}
	}

	return check;
}

vector<FacilityStruct> Inputdeck::SortFacilities(vector<FacilityStruct> &facilityRows)
{

	FacilityStruct temp;
	int n = facilityRows.size();

	for (int j = 0; j <= n - 2; j++)
	{
		for (int i = 0; i <= n - 2; i++)
		{
			if (dateCreation.IsMaximumDate(facilityRows[i].FacilityDate, facilityRows[i + 1].FacilityDate))
			{
				temp = facilityRows[i + 1];
				facilityRows[i + 1] = facilityRows[i];
				facilityRows[i] = temp;
			}
		}
	}

	return facilityRows;
}

vector<FacilityStruct> Inputdeck::ResizeTempFacilities(vector<FacilityStruct> &tempFacilities, vector<Date> &dateList)
{
	vector<FacilityStruct> tempFacilities2;
	int i = 0, j = 0, nth1 = tempFacilities.size(), nth2 = dateList.size();
	for (i = 0; i < nth2; i++)
	{
		tempFacilities2.push_back(tempFacilities[0]);
	}

	for (i = 0; i < nth2; i++)
	{
		if (dateCreation.IsMinimumDate(dateList[i], tempFacilities[0].FacilityDate))
		{
			tempFacilities2[i] = tempFacilities[0];
		}

		for (j = 1; j < nth1; j++)
		{
			if (dateCreation.EqualTo(dateList[i], tempFacilities[j - 1].FacilityDate))
			{
				tempFacilities2[i] = tempFacilities[j - 1];
				break;
			}

			if (dateCreation.EqualTo(dateList[i], tempFacilities[j].FacilityDate))
			{
				tempFacilities2[i] = tempFacilities[j - 1];
				break;
			}
			else if (dateCreation.IsMaximumDate(dateList[i], tempFacilities[j - 1].FacilityDate) &&
					 dateCreation.IsMinimumDate(dateList[i], tempFacilities[j].FacilityDate))
			{
				tempFacilities2[i] = tempFacilities[j - 1];
				break;
			}
		}

		if (dateCreation.IsMaximumDate(dateList[i], tempFacilities[nth1 - 1].FacilityDate))
		{
			tempFacilities2[i] = tempFacilities[nth1 - 1];
		}
	}

	return tempFacilities2;
}

vector<string> Inputdeck::GetFacilities(vector<InputDeckStruct> &inputdecks, int size, vector<Date> &dateList, int &scenario)
{
	//std::cout << "GetFacilities Called " << std::endl;
	vector<string> Faclities;
	FacilityStruct FacilityStructTemp;
	FacilityTable_Actual.clear();
	FacilityTables_Actual.clear();
	string ctab = "\t";

	for (int i = 0; i < size; i++)
	{

		if (IsContains(Faclities, inputdecks[i].Flow_station) == false)
		{
			//std::cout << "Condition 1 Seen" << std::endl;
			vector<FacilityStruct> tempFacilities;
			bool check = false;
			int FacilityTablesize = FacilityTable.size();
			for (int j = 0; j < FacilityTablesize; j++)
			{
				if (FacilityTable[j].Primary_Facility == inputdecks[i].Flow_station)
				{
					//std::cout << "Condition 2 Seen " << std::endl;

					switch (scenario)
					{
					case 1:
						FacilityStructTemp.Primary_Facility = FacilityTable[j].Primary_Facility;
						FacilityStructTemp.Secondary_Facility = FacilityTable[j].Secondary_Facility;
						FacilityStructTemp.Liquid_Capacity = FacilityTable[j].Liquid_Capacity1P;
						FacilityStructTemp.Gas_Capacity = FacilityTable[j].Gas_Capacity1P;
						FacilityStructTemp.AG_Capacity = FacilityTable[j].AG_Capacity1P;
						FacilityStructTemp.NAG_Capacity = FacilityTable[j].NAG_Capacity1P;
						FacilityStructTemp.Scheduled_Deferment = FacilityTable[j].Scheduled_Deferment1P;
						FacilityStructTemp.Unscheduled_Deferment = FacilityTable[j].Unscheduled_Deferment1P;
						FacilityStructTemp.Thirdparty_Deferment = FacilityTable[j].Thirdparty_Deferment1P;
						FacilityStructTemp.Crudeoil_Lossess = FacilityTable[j].Crudeoil_Lossess1P;
						FacilityStructTemp.GasOwnUse = FacilityTable[j].GasOwnUse1P;
						FacilityStructTemp.GasDemand = FacilityTable[j].GasDemand1P;
						FacilityStructTemp.GasFlared = FacilityTable[j].GasFlared1P;
						FacilityStructTemp.FDate = FacilityTable[j].FDate1P;
						FacilityStructTemp.FacilityDate = FacilityTable[j].FacilityDate1P;
						//std::cout << "FacilityTable[j].Primary_Facility = " << FacilityTable[j].Primary_Facility << std::endl;
						break;

					case 2:
						FacilityStructTemp.Primary_Facility = FacilityTable[j].Primary_Facility;
						FacilityStructTemp.Secondary_Facility = FacilityTable[j].Secondary_Facility;
						FacilityStructTemp.Liquid_Capacity = FacilityTable[j].Liquid_Capacity2P;
						FacilityStructTemp.Gas_Capacity = FacilityTable[j].Gas_Capacity2P;
						FacilityStructTemp.AG_Capacity = FacilityTable[j].AG_Capacity2P;
						FacilityStructTemp.NAG_Capacity = FacilityTable[j].NAG_Capacity2P;
						FacilityStructTemp.Scheduled_Deferment = FacilityTable[j].Scheduled_Deferment2P;
						FacilityStructTemp.Unscheduled_Deferment = FacilityTable[j].Unscheduled_Deferment2P;
						FacilityStructTemp.Thirdparty_Deferment = FacilityTable[j].Thirdparty_Deferment2P;
						FacilityStructTemp.Crudeoil_Lossess = FacilityTable[j].Crudeoil_Lossess2P;
						FacilityStructTemp.GasOwnUse = FacilityTable[j].GasOwnUse2P;
						FacilityStructTemp.GasDemand = FacilityTable[j].GasDemand2P;
						FacilityStructTemp.GasFlared = FacilityTable[j].GasFlared2P;
						FacilityStructTemp.FDate = FacilityTable[j].FDate2P;
						FacilityStructTemp.FacilityDate = FacilityTable[j].FacilityDate2P;
						break;

					case 3:
						FacilityStructTemp.Primary_Facility = FacilityTable[j].Primary_Facility;
						FacilityStructTemp.Secondary_Facility = FacilityTable[j].Secondary_Facility;
						FacilityStructTemp.Liquid_Capacity = FacilityTable[j].Liquid_Capacity3P;
						FacilityStructTemp.Gas_Capacity = FacilityTable[j].Gas_Capacity3P;
						FacilityStructTemp.AG_Capacity = FacilityTable[j].AG_Capacity3P;
						FacilityStructTemp.NAG_Capacity = FacilityTable[j].NAG_Capacity3P;
						FacilityStructTemp.Scheduled_Deferment = FacilityTable[j].Scheduled_Deferment3P;
						FacilityStructTemp.Unscheduled_Deferment = FacilityTable[j].Unscheduled_Deferment3P;
						FacilityStructTemp.Thirdparty_Deferment = FacilityTable[j].Thirdparty_Deferment3P;
						FacilityStructTemp.Crudeoil_Lossess = FacilityTable[j].Crudeoil_Lossess3P;
						FacilityStructTemp.GasOwnUse = FacilityTable[j].GasOwnUse3P;
						FacilityStructTemp.GasDemand = FacilityTable[j].GasDemand3P;
						FacilityStructTemp.GasFlared = FacilityTable[j].GasFlared3P;
						FacilityStructTemp.FDate = FacilityTable[j].FDate3P;
						FacilityStructTemp.FacilityDate = FacilityTable[j].FacilityDate3P;
						break;
					}

					FacilityTable_Actual.push_back(FacilityStructTemp);
					check = true;
					break;
				}
			}

			FacilityTablesize = FacilityTable.size();
			for (int j = 0; j < FacilityTablesize; j++)
			{
				if (FacilityTable[j].Primary_Facility == inputdecks[i].Flow_station)
				{

					switch (scenario)
					{
					case 1:
						FacilityStructTemp.Primary_Facility = FacilityTable[j].Primary_Facility;
						FacilityStructTemp.Secondary_Facility = FacilityTable[j].Secondary_Facility;
						FacilityStructTemp.Liquid_Capacity = FacilityTable[j].Liquid_Capacity1P;
						FacilityStructTemp.Gas_Capacity = FacilityTable[j].Gas_Capacity1P;
						FacilityStructTemp.AG_Capacity = FacilityTable[j].AG_Capacity1P;
						FacilityStructTemp.NAG_Capacity = FacilityTable[j].NAG_Capacity1P;
						FacilityStructTemp.Scheduled_Deferment = FacilityTable[j].Scheduled_Deferment1P;
						FacilityStructTemp.Unscheduled_Deferment = FacilityTable[j].Unscheduled_Deferment1P;
						FacilityStructTemp.Thirdparty_Deferment = FacilityTable[j].Thirdparty_Deferment1P;
						FacilityStructTemp.Crudeoil_Lossess = FacilityTable[j].Crudeoil_Lossess1P;
						FacilityStructTemp.GasOwnUse = FacilityTable[j].GasOwnUse1P;
						FacilityStructTemp.GasDemand = FacilityTable[j].GasDemand1P;
						FacilityStructTemp.GasFlared = FacilityTable[j].GasFlared1P;
						FacilityStructTemp.FDate = FacilityTable[j].FDate1P;
						FacilityStructTemp.FacilityDate = FacilityTable[j].FacilityDate1P;
						break;

					case 2:
						FacilityStructTemp.Primary_Facility = FacilityTable[j].Primary_Facility;
						FacilityStructTemp.Secondary_Facility = FacilityTable[j].Secondary_Facility;
						FacilityStructTemp.Liquid_Capacity = FacilityTable[j].Liquid_Capacity2P;
						FacilityStructTemp.Gas_Capacity = FacilityTable[j].Gas_Capacity2P;
						FacilityStructTemp.AG_Capacity = FacilityTable[j].AG_Capacity2P;
						FacilityStructTemp.NAG_Capacity = FacilityTable[j].NAG_Capacity2P;
						FacilityStructTemp.Scheduled_Deferment = FacilityTable[j].Scheduled_Deferment2P;
						FacilityStructTemp.Unscheduled_Deferment = FacilityTable[j].Unscheduled_Deferment2P;
						FacilityStructTemp.Thirdparty_Deferment = FacilityTable[j].Thirdparty_Deferment2P;
						FacilityStructTemp.Crudeoil_Lossess = FacilityTable[j].Crudeoil_Lossess2P;
						FacilityStructTemp.GasOwnUse = FacilityTable[j].GasOwnUse2P;
						FacilityStructTemp.GasDemand = FacilityTable[j].GasDemand2P;
						FacilityStructTemp.GasFlared = FacilityTable[j].GasFlared2P;
						FacilityStructTemp.FDate = FacilityTable[j].FDate2P;
						FacilityStructTemp.FacilityDate = FacilityTable[j].FacilityDate2P;
						break;

					case 3:
						FacilityStructTemp.Primary_Facility = FacilityTable[j].Primary_Facility;
						FacilityStructTemp.Secondary_Facility = FacilityTable[j].Secondary_Facility;
						FacilityStructTemp.Liquid_Capacity = FacilityTable[j].Liquid_Capacity3P;
						FacilityStructTemp.Gas_Capacity = FacilityTable[j].Gas_Capacity3P;
						FacilityStructTemp.AG_Capacity = FacilityTable[j].AG_Capacity3P;
						FacilityStructTemp.NAG_Capacity = FacilityTable[j].NAG_Capacity3P;
						FacilityStructTemp.Scheduled_Deferment = FacilityTable[j].Scheduled_Deferment3P;
						FacilityStructTemp.Unscheduled_Deferment = FacilityTable[j].Unscheduled_Deferment3P;
						FacilityStructTemp.Thirdparty_Deferment = FacilityTable[j].Thirdparty_Deferment3P;
						FacilityStructTemp.Crudeoil_Lossess = FacilityTable[j].Crudeoil_Lossess3P;
						FacilityStructTemp.GasOwnUse = FacilityTable[j].GasOwnUse3P;
						FacilityStructTemp.GasDemand = FacilityTable[j].GasDemand3P;
						FacilityStructTemp.GasFlared = FacilityTable[j].GasFlared3P;
						FacilityStructTemp.FDate = FacilityTable[j].FDate3P;
						FacilityStructTemp.FacilityDate = FacilityTable[j].FacilityDate3P;
						break;
					}

					tempFacilities.push_back(FacilityStructTemp);
				}
			}

			SortFacilities(tempFacilities);
			vector<FacilityStruct> tempFacilities2 = ResizeTempFacilities(tempFacilities, dateList);

			if (check == true)
			{
				FacilityTables_Actual.push_back(tempFacilities2);
				Faclities.push_back(inputdecks[i].Flow_station);
				tempFacilities.clear();
				tempFacilities2.clear();
				tempFacilities.shrink_to_fit();
				tempFacilities2.shrink_to_fit();
			}
		}
	}

	return Faclities;
}

bool Inputdeck::CheckWellName(vector<string> wellNames, string wellName)
{
	bool check = false;
	int i = 0, nWellNames = wellNames.size();
	for(i = 0; i < nWellNames; i++){
		if(wellNames[i] == wellName){
			check = true;
			break;
		}
	}
	return check;
}

vector<vector<vector<InputDeckStruct>>> Inputdeck::GetModulesByFacility_Obsolete(vector<string> &Faclities,
				vector<InputDeckStruct> &_inputdecks, int size,
				vector<WellReroute> wellRerouteDecks, vector<Date> dates, int scenario,
				vector<WellSchedule>& wellSchedules, vector<Prioritization>& priotizations)
{
	vector<vector<vector<InputDeckStruct>>> FacilitiesAll;
	vector<vector<InputDeckStruct>> Facilities;
	vector<vector<InputDeckStruct>> FacilitiesOld;
	vector<InputDeckStruct> Facility;

	int Faclitiessize = Faclities.size();
	int nWellRerouteDecks = wellRerouteDecks.size();
	int nDates = dates.size();
	int i, j, k, jj, ii, kk, nFacility;
	int nWellSchedules = wellSchedules.size();
	int nFacilities, nPrioritizations = priotizations.size();
	bool check;

	vector<Prioritization> priotizationFacilities;
	for (j = 0; j < Faclitiessize; j++)
	{

		Facility.clear();
		for (i = 0; i < size; i++)
		{
			if (Faclities[j] == _inputdecks[i].Flow_station)
			{
				InputDeckStruct newDeck = _inputdecks[i];
				newDeck.isTerminated = false;
				//initialize termination date for this well
				switch (scenario)
				{
				case 1:
					newDeck.TerminationDate_1P_1C = dates[nDates-1];
					break;
				case 2:
					newDeck.TerminationDate_2P_2C = dates[nDates-1];
					break;
				case 3:
					newDeck.TerminationDate_3P_3C = dates[nDates-1];
					break;
				}
				
				Facility.push_back(newDeck);
			}
		
		}

		nFacility = Facility.size();
		if(nFacility > 0){
			Facilities.push_back(Facility);
		}

		/* Prioritization priotization;
		priotization.facilityName = Faclities[j];
		priotization.typeOfPrioritization = "None"; */

		priotizationFacilities.push_back(priotizations[j]);
		/* for(i = 0; i < nPrioritizations; i++){
			if(priotizations[i].facilityName == Faclities[j]){
				if(dateCreation.IsMaximumDate(dates[0], priotizations[i].FromDate) &&
				dateCreation.IsMinimumDate(dates[0],  priotizations[i].ToDate))
				{
					priotizationFacilities[j] = priotizations[i];
					break;
				}
			}
		} */
		
	}


	FacilitiesAll.push_back(Facilities);
	priotizationsFacilities.push_back(priotizationFacilities);
				

	for (jj = 1; jj < nDates; jj++)
	{
		Facilities.clear();
		FacilitiesOld = FacilitiesAll[jj-1];
		
		for (j = 0; j < FacilitiesOld.size(); j++)
		{
			Facilities.push_back(FacilitiesOld[j]);
		}

		nFacilities = Facilities.size();

		for (j = 0; j < nFacilities; j++)
		{

			for (i = 0; i < nWellRerouteDecks; i++)
			{
				switch (scenario)
				{
				case 1:
				
					if (Facilities[j][0].Flow_station == wellRerouteDecks[i].Flow_station)
					{
						if(dateCreation.IsMinimumDate(dates[jj-1], wellRerouteDecks[i].Date_1P_1C) &&
						dateCreation.IsMaximumDate(dates[jj], wellRerouteDecks[i].Date_1P_1C))
						{
							check = false;
							nFacility = Facilities[j].size();
							for (ii = 0; ii < nFacility; ii++)
							{
								if (Facilities[j][ii].Module == wellRerouteDecks[i].Module)
								{
									check = true;
									break;
								}
							}
							if (check == false)
							{
								for (ii = 0; ii < size; ii++)
								{
									if (wellRerouteDecks[i].Module == _inputdecks[ii].Module) //fetch other data from original deck
									{
										//Terminate this well flowing into other facilities before making it flow into this facility
										InputDeckStruct newDeck = _inputdecks[ii];
										
										for (k = 0; k < nFacilities; k++)
										{
											nFacility = Facilities[k].size();
											if(j != k){
												for(kk = 0; kk < nFacility; kk++){
													if(newDeck.Module == Facilities[k][kk].Module){
														Facilities[k][kk].isTerminated = true;
														break;
													}
												}
											}
										}

										newDeck.Date_1P_1C = wellRerouteDecks[i].Date_1P_1C;
										newDeck.isTerminated = false;
										newDeck.Flow_station = wellRerouteDecks[i].Flow_station;
										Facilities[j].push_back(newDeck);

										break;
									}
								}
							}
							
						}
					}
					break;
				case 2:
				
					if (Facilities[j][0].Flow_station == wellRerouteDecks[i].Flow_station)
					{
						if(dateCreation.IsMinimumDate(dates[jj-1], wellRerouteDecks[i].Date_2P_2C) &&
						dateCreation.IsMaximumDate(dates[jj], wellRerouteDecks[i].Date_2P_2C))
						{
							check = false;
							nFacility = Facilities[j].size();
							for (ii = 0; ii < nFacility; ii++)
							{
								if (Facilities[j][ii].Module == wellRerouteDecks[i].Module)
								{
									check = true;
									break;
								}
							}
							if (check == false)
							{
								for (ii = 0; ii < size; ii++)
								{
									if (wellRerouteDecks[i].Module == _inputdecks[ii].Module) //fetch other data from original deck
									{
										//Terminate this well flowing into other facilities before making it flow into this facility
										InputDeckStruct newDeck = _inputdecks[ii];
										
										for (k = 0; k < nFacilities; k++)
										{
											nFacility = Facilities[k].size();
											if(j != k){
												for(kk = 0; kk < nFacility; kk++){
													if(newDeck.Module == Facilities[k][kk].Module){
														Facilities[k][kk].isTerminated = true;
														break;
													}
												}
											}
										}

										newDeck.Date_2P_2C = wellRerouteDecks[i].Date_2P_2C;
										newDeck.isTerminated = false;
										newDeck.Flow_station = wellRerouteDecks[i].Flow_station;
										Facilities[j].push_back(newDeck);

										break;
									}
								}
							}
							
						}
					}
					break;
				case 3:
				
					if (Facilities[j][0].Flow_station == wellRerouteDecks[i].Flow_station)
					{
						if(dateCreation.IsMinimumDate(dates[jj-1], wellRerouteDecks[i].Date_3P_3C) &&
						dateCreation.IsMaximumDate(dates[jj], wellRerouteDecks[i].Date_3P_3C))
						{
							check = false;
							nFacility = Facilities[j].size();
							for (ii = 0; ii < nFacility; ii++)
							{
								if (Facilities[j][ii].Module == wellRerouteDecks[i].Module)
								{
									check = true;
									break;
								}
							}
							if (check == false)
							{
								for (ii = 0; ii < size; ii++)
								{
									if (wellRerouteDecks[i].Module == _inputdecks[ii].Module) //fetch other data from original deck
									{
										//Terminate this well flowing into other facilities before making it flow into this facility
										InputDeckStruct newDeck = _inputdecks[ii];
										
										for (k = 0; k < nFacilities; k++)
										{
											nFacility = Facilities[k].size();
											if(j != k){
												for(kk = 0; kk < nFacility; kk++){
													if(newDeck.Module == Facilities[k][kk].Module){
														Facilities[k][kk].isTerminated = true;
														break;
													}
												}
											}
										}

										newDeck.Date_3P_3C = wellRerouteDecks[i].Date_3P_3C;
										newDeck.isTerminated = false;
										newDeck.Flow_station = wellRerouteDecks[i].Flow_station;
										Facilities[j].push_back(newDeck);

										break;
									}
								}
							}
							
						}
					}
					break;
				}
			}
		}
		
		
		priotizationFacilities.clear();
		for(j = 0; j < nFacilities; j++){
			int nWells = Facilities[j].size();
			for(i = 0; i < nWells; i++){
				//==================Initialize Well Schedule===================================
				Facilities[j][i].scheduleKey =  "";

				for(k = 0; k < nWellSchedules; k++)
				{
					if(Facilities[j][i].Module == wellSchedules[k].Module)
					{
						if (wellSchedules[k].ParameterName2 == PlateauUR_1P_1C ||
						wellSchedules[k].ParameterName2 == PlateauUR_2P_2C ||
						wellSchedules[k].ParameterName2 == PlateauUR_3P_3C)
						{
							
						}
						else
						{
							switch (scenario)
							{
							case 1:
								if(dateCreation.IsMaximumDate(dates[jj], wellSchedules[k].FromDate) &&
								dateCreation.IsMinimumDate(dates[jj],  wellSchedules[k].ToDate))
								{
									switch (wellSchedules[k].ParameterName2)
									{
									case existingStrategy:
										Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
										Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
										Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
										Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
										Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
										Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
										Facilities[j][i].declineType =  wellSchedules[k].declineType;
										Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
										Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
										Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
										Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
										Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
										break;
									case noExistingStrategy:
										Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
										Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
										Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
										Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
										Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
										Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
										Facilities[j][i].declineType =  wellSchedules[k].declineType;
										Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
										Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
										Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
										Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
										Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
										break;
									case Init_Oil_Gas_Rate_1P_1C:
										Facilities[j][i].Init_Liquid_Gas_Rate_1P_1C =  wellSchedules[k].ParameterValue;
										break;
									case Decline_Rate_1P_1C:
										Facilities[j][i].Rate_of_Change_Rate_1P_1C =  wellSchedules[k].ParameterValue;
										break;
									case Rate_Of_Rate_GOR_CGR_1P1C:
										Facilities[j][i].Rate_Of_Rate_GOR_CGR_1P1C =  wellSchedules[k].ParameterValue;
										break;
									case Rate_Of_Rate_BSW_WGR_1P1C:
										Facilities[j][i].Rate_Of_Rate_BSW_WGR_1P1C =  wellSchedules[k].ParameterValue;
										break;
									case Decline_Exponent_1P1C:
										Facilities[j][i].DeclineExponent_1P_1C =  wellSchedules[k].ParameterValue;
										break;
									}
								}
								break;
							case 2:
								if(dateCreation.IsMaximumDate(dates[jj], wellSchedules[k].FromDate) &&
								dateCreation.IsMinimumDate(dates[jj],  wellSchedules[k].ToDate))
								{
									switch (wellSchedules[k].ParameterName2)
									{
									case existingStrategy:
										Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
										Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
										Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
										Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
										Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
										Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
										Facilities[j][i].declineType =  wellSchedules[k].declineType;
										Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
										Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
										Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
										Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
										Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
										break;
									case noExistingStrategy:
										Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
										Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
										Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
										Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
										Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
										Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
										Facilities[j][i].declineType =  wellSchedules[k].declineType;
										Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
										Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
										Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
										Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
										Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
										break;
									case Init_Oil_Gas_Rate_2P_2C:
										Facilities[j][i].Init_Liquid_Gas_Rate_2P_2C =  wellSchedules[k].ParameterValue;
										break;
									case Decline_Rate_2P_2C:
										Facilities[j][i].Rate_of_Change_Rate_2P_2C =  wellSchedules[k].ParameterValue;
										break;
									case Rate_Of_Rate_GOR_CGR_2P2C:
										Facilities[j][i].Rate_Of_Rate_GOR_CGR_2P2C =  wellSchedules[k].ParameterValue;
										break;
									case Rate_Of_Rate_BSW_WGR_2P2C:
										Facilities[j][i].Rate_Of_Rate_BSW_WGR_2P2C =  wellSchedules[k].ParameterValue;
										break;
									case Decline_Exponent_2P2C:
										Facilities[j][i].DeclineExponent_2P_2C =  wellSchedules[k].ParameterValue;
										break;
									}
								}
								break;
							case 3:
								if(dateCreation.IsMaximumDate(dates[jj], wellSchedules[k].FromDate) &&
								dateCreation.IsMinimumDate(dates[jj],  wellSchedules[k].ToDate))
								{
									switch (wellSchedules[k].ParameterName2)
									{
									case existingStrategy:
										Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
										Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
										Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
										Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
										Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
										Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
										Facilities[j][i].declineType =  wellSchedules[k].declineType;
										Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
										Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
										Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
										Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
										Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
										break;
									case noExistingStrategy:
										Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
										Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
										Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
										Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
										Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
										Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
										Facilities[j][i].declineType =  wellSchedules[k].declineType;
										Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
										Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
										Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
										Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
										Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
										break;
									case Init_Oil_Gas_Rate_3P_3C:
										Facilities[j][i].Init_Liquid_Gas_Rate_3P_3C =  wellSchedules[k].ParameterValue;
										break;
									case Decline_Rate_3P_3C:
										Facilities[j][i].Rate_of_Change_Rate_3P_3C =  wellSchedules[k].ParameterValue;
										break;
									case Rate_Of_Rate_GOR_CGR_3P3C:
										Facilities[j][i].Rate_Of_Rate_GOR_CGR_3P3C =  wellSchedules[k].ParameterValue;
										break;
									case Rate_Of_Rate_BSW_WGR_3P3C:
										Facilities[j][i].Rate_Of_Rate_BSW_WGR_3P3C =  wellSchedules[k].ParameterValue;
										break;
									case Decline_Exponent_3P3C:
										Facilities[j][i].DeclineExponent_3P_3C =  wellSchedules[k].ParameterValue;
										break;
									}
								}
								break;
							}
						}
					}
				}
			}
		

			/* Prioritization priotization;
			priotization.facilityName = Faclities[j];
			priotization.typeOfPrioritization = "None"; */

			priotizationFacilities.push_back(priotizations[j]);
			/* for(i = 0; i < nPrioritizations; i++){
				if(priotizations[i].facilityName == Faclities[j]){
					if(dateCreation.IsMaximumDate(dates[jj], priotizations[i].FromDate) &&
					dateCreation.IsMinimumDate(dates[jj],  priotizations[i].ToDate))
					{
						priotizationFacilities[j] = priotizations[i];
						break;
					}
				}
			} */
		
		}

		FacilitiesAll.push_back(Facilities);
		priotizationsFacilities.push_back(priotizationFacilities);
	}


	for(j = 0; j < nDates; j++){
		nFacilities = FacilitiesAll[j].size();
		vector<FacilityWellsIndicies> facilityWellsIndicies_Level_1;
		for(i = 0; i < nFacilities; i++){
			FacilityWellsIndicies facilityWellsIndicies_Level_2;
			facilityWellsIndicies_Level_2.Facility = FacilitiesAll[j][i][0].Flow_station;
			facilityWellsIndicies_Level_1.push_back(facilityWellsIndicies_Level_2);
		}
		facilityWellsIndicies.push_back(facilityWellsIndicies_Level_1);
	}
	
	for(j = 0; j < nDates; j++){
		nFacilities = FacilitiesAll[j].size();
		for(i = 0; i < nFacilities; i++){
			int nWells = FacilitiesAll[j][i].size();
			for(k = 0; k < nWells; k++){
				check = CheckWellName(facilityWellsIndicies[j][i].WellNames,  
				FacilitiesAll[j][i][k].Module);
				if(check == false){
					facilityWellsIndicies[j][i].WellNames.push_back(FacilitiesAll[j][i][k].Module);
					facilityWellsIndicies[j][i].WellIndicies.push_back(k);
					facilityWellsIndicies[j][i].rows.push_back("");
					facilityWellsIndicies[j][i].tables.push_back("");
				}
			}
		}
	}
	return FacilitiesAll;
}


vector<vector<vector<InputDeckStruct>>> Inputdeck::GetModulesByFacility(vector<string> &Faclities,
				vector<InputDeckStruct> &_inputdecks, int size,
				vector<WellReroute> wellRerouteDecks, vector<Date> dates, int scenario,
				vector<WellSchedule>& wellSchedules, vector<Prioritization>& priotizations)
{
	vector<vector<vector<InputDeckStruct>>> FacilitiesAll;
	vector<vector<InputDeckStruct>> Facilities;
	vector<vector<InputDeckStruct>> FacilitiesOld;
	vector<InputDeckStruct> Facility;

	int Faclitiessize = Faclities.size();
	int nWellRerouteDecks = wellRerouteDecks.size();
	int nDates = dates.size();
	int i, j, k, jj, ii, kk, nFacility;
	int nWellSchedules = wellSchedules.size();
	int nFacilities, nPrioritizations = priotizations.size();
	bool check;

	vector<Prioritization> priotizationFacilities;
	for (j = 0; j < Faclitiessize; j++)
	{

		Facility.clear();
		for (i = 0; i < size; i++)
		{
			if (Faclities[j] == _inputdecks[i].Flow_station)
			{
				InputDeckStruct newDeck = _inputdecks[i];
				newDeck.isTerminated = false;
				//initialize termination date for this well
				switch (scenario)
				{
				case 1:
					newDeck.TerminationDate_1P_1C = dates[nDates-1];
					break;
				case 2:
					newDeck.TerminationDate_2P_2C = dates[nDates-1];
					break;
				case 3:
					newDeck.TerminationDate_3P_3C = dates[nDates-1];
					break;
				}
				
				Facility.push_back(newDeck);
			}
		
		}

		nFacility = Facility.size();
		if(nFacility > 0){
			Facilities.push_back(Facility);
		}

		/* Prioritization priotization;
		priotization.facilityName = Faclities[j];
		priotization.typeOfPrioritization = "None"; */

		priotizationFacilities.push_back(priotizations[j]);
		/* for(i = 0; i < nPrioritizations; i++){
			if(priotizations[i].facilityName == Faclities[j]){
				if(dateCreation.IsMaximumDate(dates[0], priotizations[i].FromDate) &&
				dateCreation.IsMinimumDate(dates[0],  priotizations[i].ToDate))
				{
					priotizationFacilities[j] = priotizations[i];
					break;
				}
			}
		} */
		
	}

				
	//==================For time t = 0============================================
	jj = 0;
	/* FacilitiesOld = Facilities;
	
	for (j = 0; j < FacilitiesOld.size(); j++)
	{
		Facilities.push_back(FacilitiesOld[j]);
	} */

	nFacilities = Facilities.size();

	for (j = 0; j < nFacilities; j++)
	{

		for (i = 0; i < nWellRerouteDecks; i++)
		{
			switch (scenario)
			{
			case 1:
			
				if (Facilities[j][0].Flow_station == wellRerouteDecks[i].Flow_station)
				{
					if(dates[jj].month == wellRerouteDecks[i].Date_1P_1C.month &&  
					dates[jj].year == wellRerouteDecks[i].Date_1P_1C.year)
					{
						check = false;
						nFacility = Facilities[j].size();
						for (ii = 0; ii < nFacility; ii++)
						{
							if (Facilities[j][ii].Module == wellRerouteDecks[i].Module)
							{
								check = true;
								break;
							}
						}
						if (check == false)
						{
							for (ii = 0; ii < size; ii++)
							{
								if (wellRerouteDecks[i].Module == _inputdecks[ii].Module) //fetch other data from original deck
								{
									//Terminate this well flowing into other facilities before making it flow into this facility
									InputDeckStruct newDeck = _inputdecks[ii];
									
									for (k = 0; k < nFacilities; k++)
									{
										nFacility = Facilities[k].size();
										if(j != k){
											for(kk = 0; kk < nFacility; kk++){
												if(newDeck.Module == Facilities[k][kk].Module){
													if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water_gas){
														Facilities[k][kk].isTerminated = true;
														Facilities[k][kk].isOilTerminated = true;
														Facilities[k][kk].isGasTerminated = true;
														Facilities[k][kk].isWaterTerminated = true;
													}

													if(wellRerouteDecks[i].Reroute_Fluid_Type == gas){
														Facilities[k][kk].isTerminated = true;
														Facilities[k][kk].isOilTerminated = false;
														Facilities[k][kk].isGasTerminated = true;
														Facilities[k][kk].isWaterTerminated = false;
													}

													if(wellRerouteDecks[i].Reroute_Fluid_Type == oil){
														Facilities[k][kk].isTerminated = true;
														Facilities[k][kk].isOilTerminated = true;
														Facilities[k][kk].isGasTerminated = false;
														Facilities[k][kk].isWaterTerminated = false;
													}

													if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water){
														Facilities[k][kk].isTerminated = true;
														Facilities[k][kk].isOilTerminated = true;
														Facilities[k][kk].isGasTerminated = false;
														Facilities[k][kk].isWaterTerminated = true;
													}
													
													break;
												}
											}
										}
									}

									newDeck.Date_1P_1C = wellRerouteDecks[i].Date_1P_1C;
									if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water_gas){
										newDeck.isTerminated = false;
										newDeck.isOilTerminated = false;
										newDeck.isGasTerminated = false;
										newDeck.isWaterTerminated = false;
									}

									if(wellRerouteDecks[i].Reroute_Fluid_Type == gas){
										newDeck.isTerminated = false;
										newDeck.isOilTerminated = true;
										newDeck.isGasTerminated = false;
										newDeck.isWaterTerminated = true;
									}

									if(wellRerouteDecks[i].Reroute_Fluid_Type == oil){
										newDeck.isTerminated = false;
										newDeck.isOilTerminated = false;
										newDeck.isGasTerminated = true;
										newDeck.isWaterTerminated = true;
									}

									if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water){
										newDeck.isTerminated = false;
										newDeck.isOilTerminated = false;
										newDeck.isGasTerminated = true;
										newDeck.isWaterTerminated = false;
									}
									newDeck.Flow_station = wellRerouteDecks[i].Flow_station;
									Facilities[j].push_back(newDeck);

									break;
								}
							}
						}
						
					}
				}
				break;
			case 2:
			
				if (Facilities[j][0].Flow_station == wellRerouteDecks[i].Flow_station)
				{
					if(dates[jj].month == wellRerouteDecks[i].Date_2P_2C.month &&  
					dates[jj].year == wellRerouteDecks[i].Date_2P_2C.year)
					{
						check = false;
						nFacility = Facilities[j].size();
						for (ii = 0; ii < nFacility; ii++)
						{
							if (Facilities[j][ii].Module == wellRerouteDecks[i].Module)
							{
								check = true;
								break;
							}
						}
						if (check == false)
						{
							for (ii = 0; ii < size; ii++)
							{
								if (wellRerouteDecks[i].Module == _inputdecks[ii].Module) //fetch other data from original deck
								{
									//Terminate this well flowing into other facilities before making it flow into this facility
									InputDeckStruct newDeck = _inputdecks[ii];
									
									for (k = 0; k < nFacilities; k++)
									{
										nFacility = Facilities[k].size();
										if(j != k){
											for(kk = 0; kk < nFacility; kk++){
												if(newDeck.Module == Facilities[k][kk].Module){
													if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water_gas){
														Facilities[k][kk].isTerminated = true;
														Facilities[k][kk].isOilTerminated = true;
														Facilities[k][kk].isGasTerminated = true;
														Facilities[k][kk].isWaterTerminated = true;
													}

													if(wellRerouteDecks[i].Reroute_Fluid_Type == gas){
														Facilities[k][kk].isTerminated = true;
														Facilities[k][kk].isOilTerminated = false;
														Facilities[k][kk].isGasTerminated = true;
														Facilities[k][kk].isWaterTerminated = false;
													}

													if(wellRerouteDecks[i].Reroute_Fluid_Type == oil){
														Facilities[k][kk].isTerminated = true;
														Facilities[k][kk].isOilTerminated = true;
														Facilities[k][kk].isGasTerminated = false;
														Facilities[k][kk].isWaterTerminated = false;
													}

													if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water){
														Facilities[k][kk].isTerminated = true;
														Facilities[k][kk].isOilTerminated = true;
														Facilities[k][kk].isGasTerminated = false;
														Facilities[k][kk].isWaterTerminated = true;
													}

													break;
												}
											}
										}
									}

									newDeck.Date_2P_2C = wellRerouteDecks[i].Date_2P_2C;
									if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water_gas){
										newDeck.isTerminated = false;
										newDeck.isOilTerminated = false;
										newDeck.isGasTerminated = false;
										newDeck.isWaterTerminated = false;
									}

									if(wellRerouteDecks[i].Reroute_Fluid_Type == gas){
										newDeck.isTerminated = false;
										newDeck.isOilTerminated = true;
										newDeck.isGasTerminated = false;
										newDeck.isWaterTerminated = true;
									}

									if(wellRerouteDecks[i].Reroute_Fluid_Type == oil){
										newDeck.isTerminated = false;
										newDeck.isOilTerminated = false;
										newDeck.isGasTerminated = true;
										newDeck.isWaterTerminated = true;
									}

									if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water){
										newDeck.isTerminated = false;
										newDeck.isOilTerminated = false;
										newDeck.isGasTerminated = true;
										newDeck.isWaterTerminated = false;
									}
									newDeck.Flow_station = wellRerouteDecks[i].Flow_station;
									Facilities[j].push_back(newDeck);

									break;
								}
							}
						}
						
					}
				}
				break;
			case 3:
			
				if (Facilities[j][0].Flow_station == wellRerouteDecks[i].Flow_station)
				{
					if(dates[jj].month == wellRerouteDecks[i].Date_3P_3C.month &&  
					dates[jj].year == wellRerouteDecks[i].Date_3P_3C.year)
					{
						check = false;
						nFacility = Facilities[j].size();
						for (ii = 0; ii < nFacility; ii++)
						{
							if (Facilities[j][ii].Module == wellRerouteDecks[i].Module)
							{
								check = true;
								break;
							}
						}
						if (check == false)
						{
							for (ii = 0; ii < size; ii++)
							{
								if (wellRerouteDecks[i].Module == _inputdecks[ii].Module) //fetch other data from original deck
								{
									//Terminate this well flowing into other facilities before making it flow into this facility
									InputDeckStruct newDeck = _inputdecks[ii];
									
									for (k = 0; k < nFacilities; k++)
									{
										nFacility = Facilities[k].size();
										if(j != k){
											for(kk = 0; kk < nFacility; kk++){
												if(newDeck.Module == Facilities[k][kk].Module){
													if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water_gas){
														Facilities[k][kk].isTerminated = true;
														Facilities[k][kk].isOilTerminated = true;
														Facilities[k][kk].isGasTerminated = true;
														Facilities[k][kk].isWaterTerminated = true;
													}

													if(wellRerouteDecks[i].Reroute_Fluid_Type == gas){
														Facilities[k][kk].isTerminated = true;
														Facilities[k][kk].isOilTerminated = false;
														Facilities[k][kk].isGasTerminated = true;
														Facilities[k][kk].isWaterTerminated = false;
													}

													if(wellRerouteDecks[i].Reroute_Fluid_Type == oil){
														Facilities[k][kk].isTerminated = true;
														Facilities[k][kk].isOilTerminated = true;
														Facilities[k][kk].isGasTerminated = false;
														Facilities[k][kk].isWaterTerminated = false;
													}

													if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water){
														Facilities[k][kk].isTerminated = true;
														Facilities[k][kk].isOilTerminated = true;
														Facilities[k][kk].isGasTerminated = false;
														Facilities[k][kk].isWaterTerminated = true;
													}
													break;
												}
											}
										}
									}

									newDeck.Date_3P_3C = wellRerouteDecks[i].Date_3P_3C;
									if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water_gas){
										newDeck.isTerminated = false;
										newDeck.isOilTerminated = false;
										newDeck.isGasTerminated = false;
										newDeck.isWaterTerminated = false;
									}

									if(wellRerouteDecks[i].Reroute_Fluid_Type == gas){
										newDeck.isTerminated = false;
										newDeck.isOilTerminated = true;
										newDeck.isGasTerminated = false;
										newDeck.isWaterTerminated = true;
									}

									if(wellRerouteDecks[i].Reroute_Fluid_Type == oil){
										newDeck.isTerminated = false;
										newDeck.isOilTerminated = false;
										newDeck.isGasTerminated = true;
										newDeck.isWaterTerminated = true;
									}

									if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water){
										newDeck.isTerminated = false;
										newDeck.isOilTerminated = false;
										newDeck.isGasTerminated = true;
										newDeck.isWaterTerminated = false;
									}
									newDeck.Flow_station = wellRerouteDecks[i].Flow_station;
									Facilities[j].push_back(newDeck);

									break;
								}
							}
						}
						
					}
				}
				break;
			}
		}
	}
	
	
	priotizationFacilities.clear();
	for(j = 0; j < nFacilities; j++){
		int nWells = Facilities[j].size();
		for(i = 0; i < nWells; i++){
			//==================Initialize Well Schedule===================================
			Facilities[j][i].scheduleKey =  "";

			for(k = 0; k < nWellSchedules; k++)
			{
				if(Facilities[j][i].Module == wellSchedules[k].Module)
				{
					if (wellSchedules[k].ParameterName2 == PlateauUR_1P_1C ||
					wellSchedules[k].ParameterName2 == PlateauUR_2P_2C ||
					wellSchedules[k].ParameterName2 == PlateauUR_3P_3C)
					{
						
					}
					else
					{
						switch (scenario)
						{
						case 1:
							if(dateCreation.IsMaximumDate(dates[jj], wellSchedules[k].FromDate) &&
							dateCreation.IsMinimumDate(dates[jj],  wellSchedules[k].ToDate))
							{
								switch (wellSchedules[k].ParameterName2)
								{
								case existingStrategy:
									Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
									Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
									Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
									Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
									Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
									Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
									Facilities[j][i].declineType =  wellSchedules[k].declineType;
									Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
									Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
									Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
									Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
									Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
									break;
								case noExistingStrategy:
									Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
									Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
									Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
									Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
									Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
									Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
									Facilities[j][i].declineType =  wellSchedules[k].declineType;
									Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
									Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
									Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
									Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
									Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
									break;
								case Init_Oil_Gas_Rate_1P_1C:
									Facilities[j][i].Init_Liquid_Gas_Rate_1P_1C =  wellSchedules[k].ParameterValue;
									break;
								case Decline_Rate_1P_1C:
									Facilities[j][i].Rate_of_Change_Rate_1P_1C =  wellSchedules[k].ParameterValue;
									break;
								case Rate_Of_Rate_GOR_CGR_1P1C:
									Facilities[j][i].Rate_Of_Rate_GOR_CGR_1P1C =  wellSchedules[k].ParameterValue;
									break;
								case Rate_Of_Rate_BSW_WGR_1P1C:
									Facilities[j][i].Rate_Of_Rate_BSW_WGR_1P1C =  wellSchedules[k].ParameterValue;
									break;
								case Decline_Exponent_1P1C:
									Facilities[j][i].DeclineExponent_1P_1C =  wellSchedules[k].ParameterValue;
									break;
								}
							}
							break;
						case 2:
							if(dateCreation.IsMaximumDate(dates[jj], wellSchedules[k].FromDate) &&
							dateCreation.IsMinimumDate(dates[jj],  wellSchedules[k].ToDate))
							{
								switch (wellSchedules[k].ParameterName2)
								{
								case existingStrategy:
									Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
									Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
									Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
									Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
									Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
									Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
									Facilities[j][i].declineType =  wellSchedules[k].declineType;
									Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
									Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
									Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
									Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
									Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
									break;
								case noExistingStrategy:
									Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
									Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
									Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
									Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
									Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
									Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
									Facilities[j][i].declineType =  wellSchedules[k].declineType;
									Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
									Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
									Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
									Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
									Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
									break;
								case Init_Oil_Gas_Rate_2P_2C:
									Facilities[j][i].Init_Liquid_Gas_Rate_2P_2C =  wellSchedules[k].ParameterValue;
									break;
								case Decline_Rate_2P_2C:
									Facilities[j][i].Rate_of_Change_Rate_2P_2C =  wellSchedules[k].ParameterValue;
									break;
								case Rate_Of_Rate_GOR_CGR_2P2C:
									Facilities[j][i].Rate_Of_Rate_GOR_CGR_2P2C =  wellSchedules[k].ParameterValue;
									break;
								case Rate_Of_Rate_BSW_WGR_2P2C:
									Facilities[j][i].Rate_Of_Rate_BSW_WGR_2P2C =  wellSchedules[k].ParameterValue;
									break;
								case Decline_Exponent_2P2C:
									Facilities[j][i].DeclineExponent_2P_2C =  wellSchedules[k].ParameterValue;
									break;
								}
							}
							break;
						case 3:
							if(dateCreation.IsMaximumDate(dates[jj], wellSchedules[k].FromDate) &&
							dateCreation.IsMinimumDate(dates[jj],  wellSchedules[k].ToDate))
							{
								switch (wellSchedules[k].ParameterName2)
								{
								case existingStrategy:
									Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
									Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
									Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
									Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
									Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
									Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
									Facilities[j][i].declineType =  wellSchedules[k].declineType;
									Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
									Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
									Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
									Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
									Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
									break;
								case noExistingStrategy:
									Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
									Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
									Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
									Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
									Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
									Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
									Facilities[j][i].declineType =  wellSchedules[k].declineType;
									Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
									Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
									Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
									Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
									Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
									break;
								case Init_Oil_Gas_Rate_3P_3C:
									Facilities[j][i].Init_Liquid_Gas_Rate_3P_3C =  wellSchedules[k].ParameterValue;
									break;
								case Decline_Rate_3P_3C:
									Facilities[j][i].Rate_of_Change_Rate_3P_3C =  wellSchedules[k].ParameterValue;
									break;
								case Rate_Of_Rate_GOR_CGR_3P3C:
									Facilities[j][i].Rate_Of_Rate_GOR_CGR_3P3C =  wellSchedules[k].ParameterValue;
									break;
								case Rate_Of_Rate_BSW_WGR_3P3C:
									Facilities[j][i].Rate_Of_Rate_BSW_WGR_3P3C =  wellSchedules[k].ParameterValue;
									break;
								case Decline_Exponent_3P3C:
									Facilities[j][i].DeclineExponent_3P_3C =  wellSchedules[k].ParameterValue;
									break;
								}
							}
							break;
						}
					}
				}
			}
		}
	

		priotizationFacilities.push_back(priotizations[j]);
	
	}


	FacilitiesAll.push_back(Facilities);
	priotizationsFacilities.push_back(priotizationFacilities);

	//====================================================================//
	for (jj = 1; jj < nDates; jj++)
	{
		Facilities.clear();
		FacilitiesOld = FacilitiesAll[jj-1];
		
		for (j = 0; j < FacilitiesOld.size(); j++)
		{
			Facilities.push_back(FacilitiesOld[j]);
		}

		nFacilities = Facilities.size();

		for (j = 0; j < nFacilities; j++)
		{

			for (i = 0; i < nWellRerouteDecks; i++)
			{
				switch (scenario)
				{
				case 1:
				
					if (Facilities[j][0].Flow_station == wellRerouteDecks[i].Flow_station)
					{
						if(dateCreation.IsMinimumDate(dates[jj-1], wellRerouteDecks[i].Date_1P_1C) &&
						dateCreation.IsMaximumDate(dates[jj], wellRerouteDecks[i].Date_1P_1C))
						{
							check = false;
							nFacility = Facilities[j].size();
							for (ii = 0; ii < nFacility; ii++)
							{
								if (Facilities[j][ii].Module == wellRerouteDecks[i].Module)
								{
									check = true;
									break;
								}
							}
							if (check == false)
							{
								for (ii = 0; ii < size; ii++)
								{
									if (wellRerouteDecks[i].Module == _inputdecks[ii].Module) //fetch other data from original deck
									{
										//Terminate this well flowing into other facilities before making it flow into this facility
										InputDeckStruct newDeck = _inputdecks[ii];
										
										for (k = 0; k < nFacilities; k++)
										{
											nFacility = Facilities[k].size();
											if(j != k){
												for(kk = 0; kk < nFacility; kk++){
													if(newDeck.Module == Facilities[k][kk].Module){
														if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water_gas){
															Facilities[k][kk].isTerminated = true;
															Facilities[k][kk].isOilTerminated = true;
															Facilities[k][kk].isGasTerminated = true;
															Facilities[k][kk].isWaterTerminated = true;
														}

														if(wellRerouteDecks[i].Reroute_Fluid_Type == gas){
															Facilities[k][kk].isTerminated = true;
															Facilities[k][kk].isOilTerminated = false;
															Facilities[k][kk].isGasTerminated = true;
															Facilities[k][kk].isWaterTerminated = false;
														}

														if(wellRerouteDecks[i].Reroute_Fluid_Type == oil){
															Facilities[k][kk].isTerminated = true;
															Facilities[k][kk].isOilTerminated = true;
															Facilities[k][kk].isGasTerminated = false;
															Facilities[k][kk].isWaterTerminated = false;
														}

														if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water){
															Facilities[k][kk].isTerminated = true;
															Facilities[k][kk].isOilTerminated = true;
															Facilities[k][kk].isGasTerminated = false;
															Facilities[k][kk].isWaterTerminated = true;
														}
														
														break;
													}
												}
											}
										}

										newDeck.Date_1P_1C = wellRerouteDecks[i].Date_1P_1C;
										if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water_gas){
											newDeck.isTerminated = false;
											newDeck.isOilTerminated = false;
											newDeck.isGasTerminated = false;
											newDeck.isWaterTerminated = false;
										}

										if(wellRerouteDecks[i].Reroute_Fluid_Type == gas){
											newDeck.isTerminated = false;
											newDeck.isOilTerminated = true;
											newDeck.isGasTerminated = false;
											newDeck.isWaterTerminated = true;
										}

										if(wellRerouteDecks[i].Reroute_Fluid_Type == oil){
											newDeck.isTerminated = false;
											newDeck.isOilTerminated = false;
											newDeck.isGasTerminated = true;
											newDeck.isWaterTerminated = true;
										}

										if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water){
											newDeck.isTerminated = false;
											newDeck.isOilTerminated = false;
											newDeck.isGasTerminated = true;
											newDeck.isWaterTerminated = false;
										}
										newDeck.Flow_station = wellRerouteDecks[i].Flow_station;
										Facilities[j].push_back(newDeck);

										break;
									}
								}
							}
							
						}
					}
					break;
				case 2:
				
					if (Facilities[j][0].Flow_station == wellRerouteDecks[i].Flow_station)
					{
						if(dateCreation.IsMinimumDate(dates[jj-1], wellRerouteDecks[i].Date_2P_2C) &&
						dateCreation.IsMaximumDate(dates[jj], wellRerouteDecks[i].Date_2P_2C))
						{
							check = false;
							nFacility = Facilities[j].size();
							for (ii = 0; ii < nFacility; ii++)
							{
								if (Facilities[j][ii].Module == wellRerouteDecks[i].Module)
								{
									check = true;
									break;
								}
							}
							if (check == false)
							{
								for (ii = 0; ii < size; ii++)
								{
									if (wellRerouteDecks[i].Module == _inputdecks[ii].Module) //fetch other data from original deck
									{
										//Terminate this well flowing into other facilities before making it flow into this facility
										InputDeckStruct newDeck = _inputdecks[ii];
										
										for (k = 0; k < nFacilities; k++)
										{
											nFacility = Facilities[k].size();
											if(j != k){
												for(kk = 0; kk < nFacility; kk++){
													if(newDeck.Module == Facilities[k][kk].Module){
														if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water_gas){
															Facilities[k][kk].isTerminated = true;
															Facilities[k][kk].isOilTerminated = true;
															Facilities[k][kk].isGasTerminated = true;
															Facilities[k][kk].isWaterTerminated = true;
														}

														if(wellRerouteDecks[i].Reroute_Fluid_Type == gas){
															Facilities[k][kk].isTerminated = true;
															Facilities[k][kk].isOilTerminated = false;
															Facilities[k][kk].isGasTerminated = true;
															Facilities[k][kk].isWaterTerminated = false;
														}

														if(wellRerouteDecks[i].Reroute_Fluid_Type == oil){
															Facilities[k][kk].isTerminated = true;
															Facilities[k][kk].isOilTerminated = true;
															Facilities[k][kk].isGasTerminated = false;
															Facilities[k][kk].isWaterTerminated = false;
														}

														if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water){
															Facilities[k][kk].isTerminated = true;
															Facilities[k][kk].isOilTerminated = true;
															Facilities[k][kk].isGasTerminated = false;
															Facilities[k][kk].isWaterTerminated = true;
														}

														break;
													}
												}
											}
										}

										newDeck.Date_2P_2C = wellRerouteDecks[i].Date_2P_2C;
										if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water_gas){
											newDeck.isTerminated = false;
											newDeck.isOilTerminated = false;
											newDeck.isGasTerminated = false;
											newDeck.isWaterTerminated = false;
										}

										if(wellRerouteDecks[i].Reroute_Fluid_Type == gas){
											newDeck.isTerminated = false;
											newDeck.isOilTerminated = true;
											newDeck.isGasTerminated = false;
											newDeck.isWaterTerminated = true;
										}

										if(wellRerouteDecks[i].Reroute_Fluid_Type == oil){
											newDeck.isTerminated = false;
											newDeck.isOilTerminated = false;
											newDeck.isGasTerminated = true;
											newDeck.isWaterTerminated = true;
										}

										if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water){
											newDeck.isTerminated = false;
											newDeck.isOilTerminated = false;
											newDeck.isGasTerminated = true;
											newDeck.isWaterTerminated = false;
										}
										newDeck.Flow_station = wellRerouteDecks[i].Flow_station;
										Facilities[j].push_back(newDeck);

										break;
									}
								}
							}
							
						}
					}
					break;
				case 3:
				
					if (Facilities[j][0].Flow_station == wellRerouteDecks[i].Flow_station)
					{
						if(dateCreation.IsMinimumDate(dates[jj-1], wellRerouteDecks[i].Date_3P_3C) &&
						dateCreation.IsMaximumDate(dates[jj], wellRerouteDecks[i].Date_3P_3C))
						{
							check = false;
							nFacility = Facilities[j].size();
							for (ii = 0; ii < nFacility; ii++)
							{
								if (Facilities[j][ii].Module == wellRerouteDecks[i].Module)
								{
									check = true;
									break;
								}
							}
							if (check == false)
							{
								for (ii = 0; ii < size; ii++)
								{
									if (wellRerouteDecks[i].Module == _inputdecks[ii].Module) //fetch other data from original deck
									{
										//Terminate this well flowing into other facilities before making it flow into this facility
										InputDeckStruct newDeck = _inputdecks[ii];
										
										for (k = 0; k < nFacilities; k++)
										{
											nFacility = Facilities[k].size();
											if(j != k){
												for(kk = 0; kk < nFacility; kk++){
													if(newDeck.Module == Facilities[k][kk].Module){
														if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water_gas){
															Facilities[k][kk].isTerminated = true;
															Facilities[k][kk].isOilTerminated = true;
															Facilities[k][kk].isGasTerminated = true;
															Facilities[k][kk].isWaterTerminated = true;
														}

														if(wellRerouteDecks[i].Reroute_Fluid_Type == gas){
															Facilities[k][kk].isTerminated = true;
															Facilities[k][kk].isOilTerminated = false;
															Facilities[k][kk].isGasTerminated = true;
															Facilities[k][kk].isWaterTerminated = false;
														}

														if(wellRerouteDecks[i].Reroute_Fluid_Type == oil){
															Facilities[k][kk].isTerminated = true;
															Facilities[k][kk].isOilTerminated = true;
															Facilities[k][kk].isGasTerminated = false;
															Facilities[k][kk].isWaterTerminated = false;
														}

														if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water){
															Facilities[k][kk].isTerminated = true;
															Facilities[k][kk].isOilTerminated = true;
															Facilities[k][kk].isGasTerminated = false;
															Facilities[k][kk].isWaterTerminated = true;
														}
														break;
													}
												}
											}
										}

										newDeck.Date_3P_3C = wellRerouteDecks[i].Date_3P_3C;
										if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water_gas){
											newDeck.isTerminated = false;
											newDeck.isOilTerminated = false;
											newDeck.isGasTerminated = false;
											newDeck.isWaterTerminated = false;
										}

										if(wellRerouteDecks[i].Reroute_Fluid_Type == gas){
											newDeck.isTerminated = false;
											newDeck.isOilTerminated = true;
											newDeck.isGasTerminated = false;
											newDeck.isWaterTerminated = true;
										}

										if(wellRerouteDecks[i].Reroute_Fluid_Type == oil){
											newDeck.isTerminated = false;
											newDeck.isOilTerminated = false;
											newDeck.isGasTerminated = true;
											newDeck.isWaterTerminated = true;
										}

										if(wellRerouteDecks[i].Reroute_Fluid_Type == oil_water){
											newDeck.isTerminated = false;
											newDeck.isOilTerminated = false;
											newDeck.isGasTerminated = true;
											newDeck.isWaterTerminated = false;
										}
										newDeck.Flow_station = wellRerouteDecks[i].Flow_station;
										Facilities[j].push_back(newDeck);

										break;
									}
								}
							}
							
						}
					}
					break;
				}
			}
		}
		
		
		priotizationFacilities.clear();
		for(j = 0; j < nFacilities; j++){
			int nWells = Facilities[j].size();
			for(i = 0; i < nWells; i++){
				//==================Initialize Well Schedule===================================
				Facilities[j][i].scheduleKey =  "";

				for(k = 0; k < nWellSchedules; k++)
				{
					if(Facilities[j][i].Module == wellSchedules[k].Module)
					{
						if (wellSchedules[k].ParameterName2 == PlateauUR_1P_1C ||
						wellSchedules[k].ParameterName2 == PlateauUR_2P_2C ||
						wellSchedules[k].ParameterName2 == PlateauUR_3P_3C)
						{
							
						}
						else
						{
							switch (scenario)
							{
							case 1:
								if(dateCreation.IsMaximumDate(dates[jj], wellSchedules[k].FromDate) &&
								dateCreation.IsMinimumDate(dates[jj],  wellSchedules[k].ToDate))
								{
									switch (wellSchedules[k].ParameterName2)
									{
									case existingStrategy:
										Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
										Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
										Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
										Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
										Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
										Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
										Facilities[j][i].declineType =  wellSchedules[k].declineType;
										Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
										Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
										Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
										Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
										Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
										break;
									case noExistingStrategy:
										Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
										Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
										Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
										Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
										Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
										Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
										Facilities[j][i].declineType =  wellSchedules[k].declineType;
										Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
										Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
										Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
										Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
										Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
										break;
									case Init_Oil_Gas_Rate_1P_1C:
										Facilities[j][i].Init_Liquid_Gas_Rate_1P_1C =  wellSchedules[k].ParameterValue;
										break;
									case Decline_Rate_1P_1C:
										Facilities[j][i].Rate_of_Change_Rate_1P_1C =  wellSchedules[k].ParameterValue;
										break;
									case Rate_Of_Rate_GOR_CGR_1P1C:
										Facilities[j][i].Rate_Of_Rate_GOR_CGR_1P1C =  wellSchedules[k].ParameterValue;
										break;
									case Rate_Of_Rate_BSW_WGR_1P1C:
										Facilities[j][i].Rate_Of_Rate_BSW_WGR_1P1C =  wellSchedules[k].ParameterValue;
										break;
									case Decline_Exponent_1P1C:
										Facilities[j][i].DeclineExponent_1P_1C =  wellSchedules[k].ParameterValue;
										break;
									}
								}
								break;
							case 2:
								if(dateCreation.IsMaximumDate(dates[jj], wellSchedules[k].FromDate) &&
								dateCreation.IsMinimumDate(dates[jj],  wellSchedules[k].ToDate))
								{
									switch (wellSchedules[k].ParameterName2)
									{
									case existingStrategy:
										Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
										Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
										Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
										Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
										Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
										Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
										Facilities[j][i].declineType =  wellSchedules[k].declineType;
										Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
										Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
										Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
										Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
										Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
										break;
									case noExistingStrategy:
										Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
										Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
										Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
										Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
										Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
										Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
										Facilities[j][i].declineType =  wellSchedules[k].declineType;
										Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
										Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
										Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
										Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
										Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
										break;
									case Init_Oil_Gas_Rate_2P_2C:
										Facilities[j][i].Init_Liquid_Gas_Rate_2P_2C =  wellSchedules[k].ParameterValue;
										break;
									case Decline_Rate_2P_2C:
										Facilities[j][i].Rate_of_Change_Rate_2P_2C =  wellSchedules[k].ParameterValue;
										break;
									case Rate_Of_Rate_GOR_CGR_2P2C:
										Facilities[j][i].Rate_Of_Rate_GOR_CGR_2P2C =  wellSchedules[k].ParameterValue;
										break;
									case Rate_Of_Rate_BSW_WGR_2P2C:
										Facilities[j][i].Rate_Of_Rate_BSW_WGR_2P2C =  wellSchedules[k].ParameterValue;
										break;
									case Decline_Exponent_2P2C:
										Facilities[j][i].DeclineExponent_2P_2C =  wellSchedules[k].ParameterValue;
										break;
									}
								}
								break;
							case 3:
								if(dateCreation.IsMaximumDate(dates[jj], wellSchedules[k].FromDate) &&
								dateCreation.IsMinimumDate(dates[jj],  wellSchedules[k].ToDate))
								{
									switch (wellSchedules[k].ParameterName2)
									{
									case existingStrategy:
										Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
										Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
										Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
										Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
										Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
										Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
										Facilities[j][i].declineType =  wellSchedules[k].declineType;
										Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
										Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
										Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
										Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
										Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
										break;
									case noExistingStrategy:
										Facilities[j][i].FromDate =  wellSchedules[k].FromDate;
										Facilities[j][i].ToDate =  wellSchedules[k].ToDate;
										Facilities[j][i].PlateauDate =  wellSchedules[k].PlateauDate;
										Facilities[j][i].dcaStrategy =  wellSchedules[k].ParameterName;
										Facilities[j][i].startupRate =  wellSchedules[k].startupRate;
										Facilities[j][i].declineRate =  wellSchedules[k].declineRate;
										Facilities[j][i].declineType =  wellSchedules[k].declineType;
										Facilities[j][i].declineType2 = wellSchedules[k].declineType2;
										Facilities[j][i].hyperbolicExponent =  wellSchedules[k].hyperbolicExponent;
										Facilities[j][i].startupRatePlateau =  wellSchedules[k].startupRatePlateau;
										Facilities[j][i].percentOfMaximumPotential =  wellSchedules[k].percentOfMaximumPotential;
										Facilities[j][i].scheduleKey =  wellSchedules[k].scheduleKey;
										break;
									case Init_Oil_Gas_Rate_3P_3C:
										Facilities[j][i].Init_Liquid_Gas_Rate_3P_3C =  wellSchedules[k].ParameterValue;
										break;
									case Decline_Rate_3P_3C:
										Facilities[j][i].Rate_of_Change_Rate_3P_3C =  wellSchedules[k].ParameterValue;
										break;
									case Rate_Of_Rate_GOR_CGR_3P3C:
										Facilities[j][i].Rate_Of_Rate_GOR_CGR_3P3C =  wellSchedules[k].ParameterValue;
										break;
									case Rate_Of_Rate_BSW_WGR_3P3C:
										Facilities[j][i].Rate_Of_Rate_BSW_WGR_3P3C =  wellSchedules[k].ParameterValue;
										break;
									case Decline_Exponent_3P3C:
										Facilities[j][i].DeclineExponent_3P_3C =  wellSchedules[k].ParameterValue;
										break;
									}
								}
								break;
							}
						}
					}
				}
			}
		

			/* Prioritization priotization;
			priotization.facilityName = Faclities[j];
			priotization.typeOfPrioritization = "None"; */

			priotizationFacilities.push_back(priotizations[j]);
			/* for(i = 0; i < nPrioritizations; i++){
				if(priotizations[i].facilityName == Faclities[j]){
					if(dateCreation.IsMaximumDate(dates[jj], priotizations[i].FromDate) &&
					dateCreation.IsMinimumDate(dates[jj],  priotizations[i].ToDate))
					{
						priotizationFacilities[j] = priotizations[i];
						break;
					}
				}
			} */
		
		}

		FacilitiesAll.push_back(Facilities);
		priotizationsFacilities.push_back(priotizationFacilities);
	}


	for(j = 0; j < nDates; j++){
		nFacilities = FacilitiesAll[j].size();
		vector<FacilityWellsIndicies> facilityWellsIndicies_Level_1;
		for(i = 0; i < nFacilities; i++){
			FacilityWellsIndicies facilityWellsIndicies_Level_2;
			facilityWellsIndicies_Level_2.Facility = FacilitiesAll[j][i][0].Flow_station;
			facilityWellsIndicies_Level_1.push_back(facilityWellsIndicies_Level_2);
		}
		facilityWellsIndicies.push_back(facilityWellsIndicies_Level_1);
	}
	
	for(j = 0; j < nDates; j++){
		nFacilities = FacilitiesAll[j].size();
		for(i = 0; i < nFacilities; i++){
			int nWells = FacilitiesAll[j][i].size();
			for(k = 0; k < nWells; k++){
				check = CheckWellName(facilityWellsIndicies[j][i].WellNames,  
				FacilitiesAll[j][i][k].Module);
				if(check == false){
					facilityWellsIndicies[j][i].WellNames.push_back(FacilitiesAll[j][i][k].Module);
					facilityWellsIndicies[j][i].WellIndicies.push_back(k);
					facilityWellsIndicies[j][i].rows.push_back("");
					facilityWellsIndicies[j][i].tables.push_back("");
				}
			}
		}
	}
	return FacilitiesAll;
}

void Inputdeck::GetFacilityTablePointer(const char *filepath, const char delimeter)
{

	ifstream ifile;

	string line;
	ifstream myfile(filepath);

	FacilityStruct deck;

	double MM = 1000000.0;
	double M = 1000.0;

	int counter = 0, j = -1;
	if (myfile.is_open())
	{
		/* while (getline(myfile, line))
		{
			counter++;
			 if (counter > 2)
			{
				j++;

				vector<string> strings;

				tokenize(line, delimeter, strings);

				int i = 0;
				deck.Primary_Facility = strings[i];
				i++;
				//deck.Secondary_Facility = strings[i]; i++;
				deck.Liquid_Capacity = strtod(strings[i].c_str(), NULL) * M;
				i++;
				deck.Gas_Capacity = strtod(strings[i].c_str(), NULL) * MM;
				i++;
				deck.Scheduled_Deferment = strtod(strings[i].c_str(), NULL);
				i++;
				deck.Unscheduled_Deferment = strtod(strings[i].c_str(), NULL);
				i++;
				deck.Thirdparty_Deferment = strtod(strings[i].c_str(), NULL);
				i++;
				deck.Crudeoil_Lossess = strtod(strings[i].c_str(), NULL);
				i++;
				deck.GasOwnUse = strtod(strings[i].c_str(), NULL) * MM;
				i++;
				deck.GasDemand = strtod(strings[i].c_str(), NULL) * MM;
				i++;
				deck.FDate = strings[i];
				i++;

				tm tm1;
				sscanf(deck.FDate.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);

				deck.FacilityDate.day = tm1.tm_mday;
				deck.FacilityDate.month = tm1.tm_mon;
				deck.FacilityDate.year = tm1.tm_year;

				//FacilityTable.push_back(deck);
			
		} } */

		myfile.close();
	}

	else
		cout << "Unable to open file";
}

void Inputdeck::GetRunParameters(const char *filepath, const char delimeter)
{
	ifstream ifile;

	string line;
	ifstream myfile(filepath);

	int counter = 0, j = -1;
	if (myfile.is_open())
	{
		/* while (getline(myfile, line))
		{
			counter++;
			if (counter > 1)
			{
				j++;

				vector<string> strings;

				tokenize(line, delimeter, strings);

				int i = 0;
				runParameter.StopDay = stoi(strings[i]);
				i++;
				runParameter.StopMonth = stoi(strings[i]);
				i++;
				runParameter.StopYear = stoi(strings[i]);
				i++;
				runParameter.TimeFrequency = strings[i];
				i++;
				runParameter.TargetFluid = strings[i];
				i++;
				runParameter.isDefered = stoi(strings[i]);
			}
		} */

		myfile.close();
	}

	else
		cout << "Unable to open file";
}

vector<string> Inputdeck::GetUniqueReroutedWells(vector<WellReroute> &inputdecks, int size)
{
	vector<string> ReroutedWells;

	for (int i = 0; i < size; i++)
	{

		if (IsContains(ReroutedWells, inputdecks[i].Module) == false)
		{
			ReroutedWells.push_back(inputdecks[i].Module);
		}
	}

	return ReroutedWells;
}

/* map<string, vector<WellReroute>> Inputdeck::GetGrouppedRoutedWells(
		vector<WellReroute>& inputdecks, vector<string> wellNames) {


	map<string, vector<WellReroute>> grouppedRoutedWells;
	int nInputDecks = inputdecks.size();
	int nWellNames = wellNames.size();
	int i = 0, j = 0;

	for(j = 0; j < nWellNames; j++){
		vector<WellReroute> wells;
		for(i = 0; i < nInputDecks; i++){
			if(wellNames[j] == inputdecks[i].Module){
				wells.push_back(inputdecks[i]);
			}
		}
		grouppedRoutedWells.insert(pair<string, vector<WellReroute>>(wellNames[j], wells));
	}
	//-------------------To be Used Latter------------//

	for(auto pair : grouppedRoutedWells){
		cout << pair.first << " - ";
		for(auto attack : pair.second) {
			cout << attack.Module << ", ";
			cout << attack.Flow_station << ", ";
		}
		cout << endl;
	}


	return grouppedRoutedWells;

} */

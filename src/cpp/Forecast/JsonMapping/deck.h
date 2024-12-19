#pragma once
/* #include <napi.h> */
// #include "node_modules/node-addon-api/napi.h"
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
#include "../ProductionForecast/Decline_Curve_Analysis.h"
#include "../../MathematicsLibrary/Integration.h"
#include "../ProductionForecast/FractionalFlow.h"
#include "../ProductionForecast/DateCreation.h"
#include "../../MathematicsLibrary/MainSimplex.h"
#include "../../MathematicsLibrary/Arithmetic.h"
#include "../../MathematicsLibrary/Interpolation.h"
#include "../ProductionForecast/dataPivoting.h"
#include "../ProductionForecast/Forecast.h"
#include "../../nlohmann/json.hpp"
#include "../ProductionForecast/Inputdeck.h"
Inputdeck inputdeck;

using namespace std;
using json = nlohmann::json;

struct MyStruct
{
	std::string name;
	int value;
};

void from_json(const json &j, InputDeckStruct &deck)
{

	if (j.contains("forecastVersion"))
		j.at("forecastVersion").get_to(deck.Version_Name);
	if (j.contains("asset"))
		j.at("asset").get_to(deck.Asset_Team);
	if (j.contains("field"))
		j.at("field").get_to(deck.Field);
	if (j.contains("reservoir"))
		j.at("reservoir").get_to(deck.Reservoir);
	if (j.contains("drainagePoint"))
		j.at("drainagePoint").get_to(deck.Drainage_Point);
	if (j.contains("string"))
		j.at("string").get_to(deck.Production_String);
	if (j.contains("module"))
		j.at("module").get_to(deck.Module);
	if (j.contains("projectCode"))
		j.at("projectCode").get_to(deck.PEEP_Project);
	if (j.contains("projectName"))
		j.at("projectName").get_to(deck.Activity_Entity);
	if (j.contains("facilities"))
		j.at("facilities").get_to(deck.Flow_station);
	if (j.contains("hydrocarbonStream"))
	{
		j.at("hydrocarbonStream").get_to(deck.Hydrocarbon_Stream);
		inputdeck.ToLower(deck.Hydrocarbon_Stream);
	}

	if (j.contains("hydrocarbonType"))
	{
		j.at("hydrocarbonType").get_to(deck.hydrocarbonType);
		inputdeck.ToLower(deck.hydrocarbonType);
	}

	if (j.contains("terminal"))
	{
		j.at("terminal").get_to(deck.terminal);
		inputdeck.ToLower(deck.terminal);
	}

	if (j.contains("resourceClass"))
	{
		j.at("resourceClass").get_to(deck.Resource_Class);
		inputdeck.ToLower(deck.Resource_Class);
	}

	if (j.contains("oilUR1P1C"))
		j.at("oilUR1P1C").get_to(deck.URo_1P_1C);
	if (j.contains("oilUR2P2C"))
		j.at("oilUR2P2C").get_to(deck.URo_2P_2C);
	if (j.contains("oilUR3P3C"))
		j.at("oilUR3P3C").get_to(deck.URo_3P_3C);
	if (j.contains("Np"))
		j.at("Np").get_to(deck.Np);
	if (j.contains("gasUR1P1C"))
		j.at("gasUR1P1C").get_to(deck.URg_1P_1C);
	if (j.contains("gasUR2P2C"))
		j.at("gasUR2P2C").get_to(deck.URg_2P_2C);
	if (j.contains("gasUR3P3C"))
		j.at("gasUR3P3C").get_to(deck.URg_3P_3C);
	if (j.contains("Gp"))
		j.at("Gp").get_to(deck.Gp);
	if (j.contains("initOilGasRate1P1C"))
		j.at("initOilGasRate1P1C").get_to(deck.Init_Liquid_Gas_Rate_1P_1C);
	if (j.contains("initOilGasRate2P2C"))
		j.at("initOilGasRate2P2C").get_to(deck.Init_Liquid_Gas_Rate_2P_2C);
	if (j.contains("initOilGasRate3P3C"))
		j.at("initOilGasRate3P3C").get_to(deck.Init_Liquid_Gas_Rate_3P_3C);
	if (j.contains("abandOilGasRate1P1C"))
		j.at("abandOilGasRate1P1C").get_to(deck.Aband_Liquid_Gas_Rate_1P_1C);
	if (j.contains("abandOilGasRate2P2C"))
		j.at("abandOilGasRate2P2C").get_to(deck.Aband_Liquid_Gas_Rate_2P_2C);
	if (j.contains("abandOilGasRate3P3C"))
		j.at("abandOilGasRate3P3C").get_to(deck.Aband_Liquid_Gas_Rate_3P_3C);
	if (j.contains("initBSWWGR"))
		j.at("initBSWWGR").get_to(deck.Init_BSW_WGR);
	if (deck.Init_BSW_WGR == 0)
		deck.Init_BSW_WGR = 0.00000001;
	if (j.contains("abandBSWWGR1P1C"))
		j.at("abandBSWWGR1P1C").get_to(deck.Aband_BSW_WGR_1P_1C);
	if (j.contains("abandBSWWGR2P2C"))
		j.at("abandBSWWGR2P2C").get_to(deck.Aband_BSW_WGR_2P_2C);
	if (j.contains("abandBSWWGR3P3C"))
		j.at("abandBSWWGR3P3C").get_to(deck.Aband_BSW_WGR_3P_3C);
	if (j.contains("initGORCGR"))
		j.at("initGORCGR").get_to(deck.Init_GOR_CGR);
	if (deck.Init_GOR_CGR == 0)
		deck.Init_GOR_CGR = 0.00000001;
	if (j.contains("abandGORCGR1P1C"))
		j.at("abandGORCGR1P1C").get_to(deck.Aband_GOR_CGR_1P_1C);
	if (j.contains("abandGORCGR2P2C"))
		j.at("abandGORCGR2P2C").get_to(deck.Aband_GOR_CGR_2P_2C);
	if (j.contains("abandGORCGR3P3C"))
		j.at("abandGORCGR3P3C").get_to(deck.Aband_GOR_CGR_3P_3C);
	if (j.contains("plateauPeriod"))
		j.at("plateauPeriod").get_to(deck.Plateau_Oil_Gas);
	deck.optimizationWeight2 = "normal";
	if (j.contains("onStreamDate1P1C"))
		j.at("onStreamDate1P1C").get_to(deck.On_stream_Date_1P_1C);
	if (j.contains("onStreamDate2P2C"))
		j.at("onStreamDate2P2C").get_to(deck.On_stream_Date_2P_2C);
	if (j.contains("onStreamDate3P3C"))
		j.at("onStreamDate3P3C").get_to(deck.On_stream_Date_3P_3C);
	if (j.contains("remarks"))
		j.at("remarks").get_to(deck.Remarks);
	if (j.contains("developmentTranche"))
		j.at("developmentTranche").get_to(deck.TRANCHE);
	if (j.contains("rateofChangeRate1P1C"))
		j.at("rateofChangeRate1P1C").get_to(deck.Rate_of_Change_Rate_1P_1C);
	if (j.contains("rateofChangeRate2P2C"))
		j.at("rateofChangeRate2P2C").get_to(deck.Rate_of_Change_Rate_2P_2C);
	if (j.contains("rateofChangeRate3P3C"))
		j.at("rateofChangeRate3P3C").get_to(deck.Rate_of_Change_Rate_3P_3C);
	if (j.contains("declineExponent1P1C"))
		j.at("declineExponent1P1C").get_to(deck.DeclineExponent_1P_1C);
	if (j.contains("declineExponent2P2C"))
		j.at("declineExponent2P2C").get_to(deck.DeclineExponent_2P_2C);
	if (j.contains("declineExponent3P3C"))
		j.at("declineExponent3P3C").get_to(deck.DeclineExponent_3P_3C);
	if (j.contains("rateOfChangeGORCGR1P1C"))
		j.at("rateOfChangeGORCGR1P1C").get_to(deck.Rate_Of_Rate_GOR_CGR_1P1C);
	if (j.contains("rateOfChangeGORCGR2P2C"))
		j.at("rateOfChangeGORCGR2P2C").get_to(deck.Rate_Of_Rate_GOR_CGR_2P2C);
	if (j.contains("rateOfChangeGORCGR3P3C"))
		j.at("rateOfChangeGORCGR3P3C").get_to(deck.Rate_Of_Rate_GOR_CGR_3P3C);
	if (j.contains("rateOfChangeBSWWGR1P1C"))
		j.at("rateOfChangeBSWWGR1P1C").get_to(deck.Rate_Of_Rate_BSW_WGR_1P1C);
	if (j.contains("rateOfChangeBSWWGR2P2C"))
		j.at("rateOfChangeBSWWGR2P2C").get_to(deck.Rate_Of_Rate_BSW_WGR_2P2C);
	if (j.contains("rateOfChangeBSWWGR3P3C"))
		j.at("rateOfChangeBSWWGR3P3C").get_to(deck.Rate_Of_Rate_BSW_WGR_3P3C);
	string DeclineMethod;
	if (j.contains("declineMethod"))
		j.at("declineMethod").get_to(DeclineMethod);
	inputdeck.ToLower(DeclineMethod);

	if (DeclineMethod == "exponential")
	{
		deck.DeclineMethod = 1;
	}
	else if (DeclineMethod == "hyperbolic")
	{
		deck.DeclineMethod = 2;
	}
	else
	{
		deck.DeclineMethod = 3;
	}

	if (j.contains("day1P1C"))
		j.at("day1P1C").get_to(deck.day_1P_1C);
	if (j.contains("day2P2C"))
		j.at("day2P2C").get_to(deck.day_2P_2C);
	if (j.contains("day3P3C"))
		j.at("day3P3C").get_to(deck.day_3P_3C);
	if (j.contains("month1P1C"))
		j.at("month1P1C").get_to(deck.month_1P_1C);
	if (j.contains("month2P2C"))
		j.at("month2P2C").get_to(deck.month_2P_2C);
	if (j.contains("month3P3C"))
		j.at("month3P3C").get_to(deck.month_3P_3C);
	if (j.contains("year1P1C"))
		j.at("year1P1C").get_to(deck.year_1P_1C);
	if (j.contains("year2P2C"))
		j.at("year2P2C").get_to(deck.year_2P_2C);
	if (j.contains("year3P3C"))
		j.at("year3P3C").get_to(deck.year_3P_3C);
	if (j.contains("plateauUR1P1C"))
		j.at("plateauUR1P1C").get_to(deck.PlateauUR_1P_1C);
	if (j.contains("plateauUR2P2C"))
		j.at("plateauUR2P2C").get_to(deck.PlateauUR_2P_2C);
	if (j.contains("plateauUR3P3C"))
		j.at("plateauUR3P3C").get_to(deck.PlateauUR_3P_3C);

	deck.Date_1P_1C.day = deck.day_1P_1C;
	deck.Date_1P_1C.month = deck.month_1P_1C;
	deck.Date_1P_1C.year = deck.year_1P_1C;
	deck.Date_2P_2C.day = deck.day_2P_2C;
	deck.Date_2P_2C.month = deck.month_2P_2C;
	deck.Date_2P_2C.year = deck.year_2P_2C;
	deck.Date_3P_3C.day = deck.day_3P_3C;
	deck.Date_3P_3C.month = deck.month_3P_3C;
	deck.Date_3P_3C.year = deck.year_3P_3C;
	if (j.contains("description"))
		j.at("description").get_to(deck.Description);

	if (j.contains("optimizationWeight"))
		j.at("optimizationWeight").get_to(deck.optimizationWeight2);
}

/* vector<InputDeckStruct> from_napi(Napi::Array& wrappedDecks,
		Napi::Array wrappedProdPrioritization,
		int nWrappedDecks, int nWrappedProdPrioritization, Napi::Env& env) {


	int lent = nWrappedDecks;
	std::cout << "getDecks started" << std::endl;

	vector<InputDeckStruct> InputDecks;

	for (int i = 0; i < lent; i++) {
		Napi::Object wrappedDeck = wrappedDecks.Get(i).As<Napi::Object>();

		InputDeckStruct deck;
		deck.Version_Name = (wrappedDeck.Get(Napi::String::New(env, "forecastVersion"))).As<Napi::String>();
		deck.Asset_Team = (wrappedDeck.Get(Napi::String::New(env, "asset"))).As<Napi::String>();
		deck.Field = (wrappedDeck.Get(Napi::String::New(env, "field"))).As<Napi::String>();
		deck.Reservoir = (wrappedDeck.Get(Napi::String::New(env, "reservoir"))).As<Napi::String>();
		deck.Drainage_Point = (wrappedDeck.Get(Napi::String::New(env, "drainagePoint"))).As<Napi::String>();
		deck.Production_String = (wrappedDeck.Get(Napi::String::New(env, "string"))).As<Napi::String>();
		deck.Module = (wrappedDeck.Get(Napi::String::New(env, "module"))).As<Napi::String>();
		deck.PEEP_Project = (wrappedDeck.Get(Napi::String::New(env, "projectCode"))).As<Napi::String>();
		deck.Activity_Entity = (wrappedDeck.Get(Napi::String::New(env, "projectName"))).As<Napi::String>();
		deck.Flow_station = (wrappedDeck.Get(Napi::String::New(env, "facilities"))).As<Napi::String>();
		deck.Hydrocarbon_Stream = (wrappedDeck.Get(Napi::String::New(env, "hydrocarbonStream"))).As<Napi::String>();
		inputdeck.ToLower(deck.Hydrocarbon_Stream);
		deck.hydrocarbonType = (wrappedDeck.Get(Napi::String::New(env, "hydrocarbonType"))).As<Napi::String>();
		inputdeck.ToLower(deck.hydrocarbonType);
		deck.terminal = (wrappedDeck.Get(Napi::String::New(env, "terminal"))).As<Napi::String>();
		inputdeck.ToLower(deck.terminal);


		deck.Resource_Class = (wrappedDeck.Get(Napi::String::New(env, "resourceClass"))).As<Napi::String>();
		inputdeck.ToLower(deck.Resource_Class);
		deck.URo_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "oilUR1P1C"))).As<Napi::Number>();
		deck.URo_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "oilUR2P2C"))).As<Napi::Number>();
		deck.URo_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "oilUR3P3C"))).As<Napi::Number>();
		deck.Np = (wrappedDeck.Get(Napi::String::New(env, "Np"))).As<Napi::Number>();
		deck.URg_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "gasUR1P1C"))).As<Napi::Number>();
		deck.URg_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "gasUR2P2C"))).As<Napi::Number>();
		deck.URg_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "gasUR3P3C"))).As<Napi::Number>();
		deck.Gp = (wrappedDeck.Get(Napi::String::New(env, "Gp"))).As<Napi::Number>();
		//std::cout << "getDecks Called 2" << std::endl;



		deck.Init_Liquid_Gas_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate1P1C"))).As<Napi::Number>();
		deck.Init_Liquid_Gas_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate2P2C"))).As<Napi::Number>();
		deck.Init_Liquid_Gas_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "initOilGasRate3P3C"))).As<Napi::Number>();
		deck.Aband_Liquid_Gas_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate1P1C"))).As<Napi::Number>();
		deck.Aband_Liquid_Gas_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate2P2C"))).As<Napi::Number>();
		deck.Aband_Liquid_Gas_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandOilGasRate3P3C"))).As<Napi::Number>();

		deck.Init_BSW_WGR = (wrappedDeck.Get(Napi::String::New(env, "initBSWWGR"))).As<Napi::Number>();
		if (deck.Init_BSW_WGR == 0) deck.Init_BSW_WGR = 0.00000001;
		deck.Aband_BSW_WGR_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandBSWWGR1P1C"))).As<Napi::Number>();
		deck.Aband_BSW_WGR_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandBSWWGR2P2C"))).As<Napi::Number>();
		deck.Aband_BSW_WGR_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandBSWWGR3P3C"))).As<Napi::Number>();
		deck.Init_GOR_CGR = (wrappedDeck.Get(Napi::String::New(env, "initGORCGR"))).As<Napi::Number>();
		if (deck.Init_GOR_CGR == 0) deck.Init_GOR_CGR = 0.00000001;
		deck.Aband_GOR_CGR_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "abandGORCGR1P1C"))).As<Napi::Number>();
		deck.Aband_GOR_CGR_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "abandGORCGR2P2C"))).As<Napi::Number>();
		deck.Aband_GOR_CGR_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "abandGORCGR3P3C"))).As<Napi::Number>();
		deck.Plateau_Oil_Gas = (wrappedDeck.Get(Napi::String::New(env, "plateauPeriod"))).As<Napi::Number>();


		if(nWrappedProdPrioritization > 0 && nWrappedProdPrioritization == lent){
			Napi::Object prodPrioritizationRow = wrappedProdPrioritization.Get(i).As<Napi::Object>();
			string optimizationWeight = (prodPrioritizationRow.Get(Napi::String::New(env, "optimizationWeight"))).As<Napi::String>();
			//std::cout << "optimizationWeight: "  << optimizationWeight << std::endl;
			deck.optimizationWeight2 = optimizationWeight;
			inputdeck.ToLower(deck.optimizationWeight2);
		}else{
			deck.optimizationWeight2 = "normal";
		}

		//std::cout << "getDecks Called 3" << std::endl;
		deck.On_stream_Date_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "onStreamDate1P1C"))).As<Napi::String>();
		deck.On_stream_Date_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "onStreamDate2P2C"))).As<Napi::String>();
		deck.On_stream_Date_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "onStreamDate3P3C"))).As<Napi::String>();
		deck.Remarks = (wrappedDeck.Get(Napi::String::New(env, "remarks"))).As<Napi::String>();
		deck.TRANCHE = (wrappedDeck.Get(Napi::String::New(env, "developmentTranche"))).As<Napi::String>();

		//std::cout << "rateofChangeRate1P1C" << std::endl;
		deck.Rate_of_Change_Rate_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "rateofChangeRate1P1C"))).As<Napi::Number>();
		deck.Rate_of_Change_Rate_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "rateofChangeRate2P2C"))).As<Napi::Number>();
		deck.Rate_of_Change_Rate_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "rateofChangeRate3P3C"))).As<Napi::Number>();

		//std::cout << "rateofChangeRate3P3C" << std::endl;

		deck.DeclineExponent_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "declineExponent1P1C"))).As<Napi::Number>();
		deck.DeclineExponent_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "declineExponent2P2C"))).As<Napi::Number>();
		deck.DeclineExponent_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "declineExponent3P3C"))).As<Napi::Number>();
		deck.Rate_Of_Rate_GOR_CGR_1P1C = (wrappedDeck.Get(Napi::String::New(env, "rateOfChangeGORCGR1P1C"))).As<Napi::Number>();
		deck.Rate_Of_Rate_GOR_CGR_2P2C = (wrappedDeck.Get(Napi::String::New(env, "rateOfChangeGORCGR2P2C"))).As<Napi::Number>();
		deck.Rate_Of_Rate_GOR_CGR_3P3C = (wrappedDeck.Get(Napi::String::New(env, "rateOfChangeGORCGR3P3C"))).As<Napi::Number>();
		deck.Rate_Of_Rate_BSW_WGR_1P1C = (wrappedDeck.Get(Napi::String::New(env, "rateOfChangeBSWWGR1P1C"))).As<Napi::Number>();
		deck.Rate_Of_Rate_BSW_WGR_2P2C = (wrappedDeck.Get(Napi::String::New(env, "rateOfChangeBSWWGR2P2C"))).As<Napi::Number>();
		deck.Rate_Of_Rate_BSW_WGR_3P3C = (wrappedDeck.Get(Napi::String::New(env, "rateOfChangeBSWWGR3P3C"))).As<Napi::Number>();

		string DeclineMethod = (wrappedDeck.Get(Napi::String::New(env, "declineMethod"))).As<Napi::String>();
		inputdeck.ToLower(DeclineMethod);

		if(DeclineMethod == "exponential")
		{
			deck.DeclineMethod = 1;
		}
		else if(DeclineMethod == "hyperbolic")
		{
			deck.DeclineMethod = 2;
		}
		else
		{
			deck.DeclineMethod = 3;
		}


		deck.day_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "day1P1C"))).As<Napi::Number>();
		deck.day_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "day2P2C"))).As<Napi::Number>();
		deck.day_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "day3P3C"))).As<Napi::Number>();


		deck.month_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "month1P1C"))).As<Napi::Number>();
		deck.month_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "month2P2C"))).As<Napi::Number>();
		deck.month_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "month3P3C"))).As<Napi::Number>();

		deck.year_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "year1P1C"))).As<Napi::Number>();
		deck.year_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "year2P2C"))).As<Napi::Number>();
		deck.year_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "year3P3C"))).As<Napi::Number>();

		deck.PlateauUR_1P_1C = (wrappedDeck.Get(Napi::String::New(env, "plateauUR1P1C"))).As<Napi::Number>();
		deck.PlateauUR_2P_2C = (wrappedDeck.Get(Napi::String::New(env, "plateauUR2P2C"))).As<Napi::Number>();
		deck.PlateauUR_3P_3C = (wrappedDeck.Get(Napi::String::New(env, "plateauUR3P3C"))).As<Napi::Number>();

		deck.Date_1P_1C.day = deck.day_1P_1C;
		deck.Date_1P_1C.month = deck.month_1P_1C;
		deck.Date_1P_1C.year = deck.year_1P_1C;
		deck.Date_2P_2C.day = deck.day_2P_2C;
		deck.Date_2P_2C.month = deck.month_2P_2C;
		deck.Date_2P_2C.year = deck.year_2P_2C;
		deck.Date_3P_3C.day = deck.day_3P_3C;
		deck.Date_3P_3C.month = deck.month_3P_3C;
		deck.Date_3P_3C.year = deck.year_3P_3C;

		deck.Description = (wrappedDeck.Get(Napi::String::New(env, "description"))).As<Napi::String>();

		if (deck.Description == "no error")
		{
			InputDecks.push_back(deck);

		}


	}

	std::cout << "getDecks completed" << std::endl;

	return InputDecks;
} */

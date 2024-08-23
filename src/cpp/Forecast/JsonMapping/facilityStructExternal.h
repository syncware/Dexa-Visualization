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
#include "../ProductionForecast/Forecast.h"
#include "../../nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;


void from_json(const json& j, FacilityStructExternal& fse) {

    double MM = 1000000.0;
    double M = 1000.0;

    j.at("Primary_Facility").get_to(fse.Primary_Facility);
    j.at("FDate1P").get_to(fse.FDate1P);
    j.at("FDate2P").get_to(fse.FDate2P);
    j.at("FDate3P").get_to(fse.FDate3P);

    tm tm1, tm2, tm3;
		sscanf(fse.FDate1P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
		sscanf(fse.FDate2P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
		sscanf(fse.FDate3P.c_str(), "%d/%d/%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);

		fse.FacilityDate1P.day = tm1.tm_mday;
		fse.FacilityDate1P.month = tm1.tm_mon;
		fse.FacilityDate1P.year = tm1.tm_year;

		fse.FacilityDate2P.day = tm2.tm_mday;
		fse.FacilityDate2P.month = tm2.tm_mon;
		fse.FacilityDate2P.year = tm2.tm_year;

		fse.FacilityDate3P.day = tm3.tm_mday;
		fse.FacilityDate3P.month = tm3.tm_mon;
		fse.FacilityDate3P.year = tm3.tm_year;

    if (j.contains("Scheduled_Deferment1P")) j.at("Scheduled_Deferment1P").get_to(fse.Scheduled_Deferment1P);
    if (j.contains("Scheduled_Deferment2P")) j.at("Scheduled_Deferment2P").get_to(fse.Scheduled_Deferment2P);
    if (j.contains("Scheduled_Deferment3P")) j.at("Scheduled_Deferment3P").get_to(fse.Scheduled_Deferment3P);

    if (j.contains("Unscheduled_Deferment1P")) j.at("Unscheduled_Deferment1P").get_to(fse.Unscheduled_Deferment1P);
    if (j.contains("Unscheduled_Deferment2P")) j.at("Unscheduled_Deferment2P").get_to(fse.Unscheduled_Deferment2P);
    if (j.contains("Unscheduled_Deferment3P")) j.at("Unscheduled_Deferment3P").get_to(fse.Unscheduled_Deferment3P);

    if (j.contains("Thirdparty_Deferment1P")) j.at("Thirdparty_Deferment1P").get_to(fse.Thirdparty_Deferment1P);
    if (j.contains("Thirdparty_Deferment2P")) j.at("Thirdparty_Deferment2P").get_to(fse.Thirdparty_Deferment2P);
    if (j.contains("Thirdparty_Deferment3P")) j.at("Thirdparty_Deferment3P").get_to(fse.Thirdparty_Deferment3P);

    if (j.contains("Crudeoil_Lossess1P")) j.at("Crudeoil_Lossess1P").get_to(fse.Crudeoil_Lossess1P);
    if (j.contains("Crudeoil_Lossess2P")) j.at("Crudeoil_Lossess2P").get_to(fse.Crudeoil_Lossess2P);
    if (j.contains("Crudeoil_Lossess3P")) j.at("Crudeoil_Lossess3P").get_to(fse.Crudeoil_Lossess3P);

    if (j.contains("Liquid_Capacity1P")) {
      j.at("Liquid_Capacity1P").get_to(fse.Liquid_Capacity1P);
      fse.Liquid_Capacity1P = fse.Liquid_Capacity1P * M;
    }

    if (j.contains("Liquid_Capacity2P")) {
      j.at("Liquid_Capacity2P").get_to(fse.Liquid_Capacity2P);
      fse.Liquid_Capacity2P = fse.Liquid_Capacity2P * M;
    }

    if (j.contains("Liquid_Capacity3P")) {
      j.at("Liquid_Capacity3P").get_to(fse.Liquid_Capacity3P);
      fse.Liquid_Capacity3P = fse.Liquid_Capacity3P * M;
    }

    if (j.contains("AG_Capacity1P")) {
      j.at("AG_Capacity1P").get_to(fse.AG_Capacity1P);
      fse.AG_Capacity1P = fse.AG_Capacity1P * MM;
    }
    if (j.contains("AG_Capacity2P")) {
      j.at("AG_Capacity2P").get_to(fse.AG_Capacity2P);
      fse.AG_Capacity2P = fse.AG_Capacity2P * MM;
    }
    if (j.contains("AG_Capacity3P")) {
      j.at("AG_Capacity3P").get_to(fse.AG_Capacity3P);
      fse.AG_Capacity3P = fse.AG_Capacity3P * MM;
    }

    if (j.contains("NAG_Capacity1P")) {
      j.at("NAG_Capacity1P").get_to(fse.NAG_Capacity1P);
      fse.NAG_Capacity1P = fse.NAG_Capacity1P * MM;
    }
    if (j.contains("NAG_Capacity2P")) {
      j.at("NAG_Capacity2P").get_to(fse.NAG_Capacity2P);
      fse.NAG_Capacity2P = fse.NAG_Capacity2P * MM;
    }
    if (j.contains("NAG_Capacity3P")) {
      j.at("NAG_Capacity3P").get_to(fse.NAG_Capacity3P);
      fse.NAG_Capacity3P = fse.NAG_Capacity3P * MM;
    }

    double equityPercentage1P = 0, equityPercentage2P = 0, equityPercentage3P = 0;
    if (j.contains("ProductionShareLow")) j.at("ProductionShareLow").get_to(equityPercentage1P);
    if (j.contains("ProductionShareBase")) {
      j.at("ProductionShareBase").get_to(equityPercentage2P);
      fse.equityPercentage = equityPercentage2P;
    }
    if (j.contains("ProductionShareHigh")) j.at("ProductionShareHigh").get_to(equityPercentage3P);

    fse.GasOwnUse1P = 0;
    if (j.contains("GasOwnUse1P")) {
      j.at("GasOwnUse1P").get_to(fse.GasOwnUse1P);
      fse.GasOwnUse1P = fse.GasOwnUse1P * MM;
    }

		fse.GasOwnUse2P = 0;
    if (j.contains("GasOwnUse2P")) {
      j.at("GasOwnUse2P").get_to(fse.GasOwnUse2P);
      fse.GasOwnUse2P = fse.GasOwnUse2P * MM;
    }

		fse.GasOwnUse3P = 0;
    if (j.contains("GasOwnUse3P")) {
      j.at("GasOwnUse3P").get_to(fse.GasOwnUse3P);
      fse.GasOwnUse3P = fse.GasOwnUse3P * MM;
    }

    fse.GasDemand1P = 0;
    if (j.contains("GasDemand1P")) {
      j.at("GasDemand1P").get_to(fse.GasDemand1P);
      fse.GasDemand1P = fse.GasDemand1P * MM;
    }

		fse.GasDemand2P = 0;
    if (j.contains("GasDemand2P")) {
      j.at("GasDemand2P").get_to(fse.GasDemand2P);
      fse.GasDemand2P = fse.GasDemand2P * MM;
    }

		fse.GasDemand3P = 0;
    if (j.contains("GasDemand3P")) {
      j.at("GasDemand3P").get_to(fse.GasDemand3P);
      fse.GasDemand3P = fse.GasDemand3P * MM;
    }

    fse.GasFlared1P = 0;
    if (j.contains("GasFlared1P")) {
      j.at("GasFlared1P").get_to(fse.GasFlared1P);
      fse.GasFlared1P = fse.GasFlared1P * MM;
    }

		fse.GasFlared2P = 0;
    if (j.contains("GasFlared2P")) {
      j.at("GasFlared2P").get_to(fse.GasFlared2P);
      fse.GasFlared2P = fse.GasFlared2P * MM;
    }

		fse.GasFlared3P = 0;
    if (j.contains("GasFlared3P")) {
      j.at("GasFlared3P").get_to(fse.GasFlared3P);
      fse.GasFlared3P = fse.GasFlared3P * MM;
    }

    if (j.contains("Gas_Capacity1P")) {
      j.at("Gas_Capacity1P").get_to(fse.Gas_Capacity1P);
      fse.Gas_Capacity1P = fse.Gas_Capacity1P * MM;
      fse.GasDemand1P = fse.Gas_Capacity1P * equityPercentage1P;
      if(fse.Gas_Capacity1P <= 0){
        fse.GasDemand1P = (fse.AG_Capacity1P + fse.NAG_Capacity1P) * equityPercentage1P;
      }
    }
    if (j.contains("Gas_Capacity2P")) {
      j.at("Gas_Capacity2P").get_to(fse.Gas_Capacity2P);
      fse.Gas_Capacity2P = fse.Gas_Capacity2P * MM;
      fse.GasDemand2P = fse.Gas_Capacity2P * equityPercentage2P;
      if(fse.Gas_Capacity2P <= 0){
        fse.GasDemand2P = 
        (fse.AG_Capacity2P + fse.NAG_Capacity2P) * equityPercentage2P;
      }
    }
    if (j.contains("Gas_Capacity3P")) {
      j.at("Gas_Capacity3P").get_to(fse.Gas_Capacity3P);
      fse.Gas_Capacity3P = fse.Gas_Capacity3P * MM;
      fse.GasDemand3P = fse.Gas_Capacity3P * equityPercentage3P;
      if(fse.Gas_Capacity3P <= 0){
        fse.GasDemand3P = (fse.AG_Capacity3P + fse.NAG_Capacity3P) * equityPercentage3P;
      }
    }
		
}
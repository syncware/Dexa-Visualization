#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <time.h>
#include <iomanip>
#include <functional>
#include <map>
// #include "DateCreation.h"
// #include "Inputdeck.h"

using namespace std;


// DateCreation dateCreation;
// Inputdeck deckobj;


typedef struct _Address
{
    string city;
    string zip;
}Address;

typedef struct _Person
{
    string name;
    int age;
    int year;
    Address address;
    vector<string> hobbies;
}Person;



typedef struct _Date
{
    int day;
    int month;
    int year;
}Date;

typedef enum _DeclineMethod
{
    exponential,
    harmonic,
    hyperbolic

}DeclineMethod;

typedef enum ForecastProfileEnum
{
    Default,
    MBAL,
    ECLIPSE
};

typedef struct _InterpParams
{
    vector<double> Xs1;
    vector<double> Ys1;
    vector<double> Xs2;
    vector<double> Ys2;

}InterpParams;

typedef struct _WellFacilityData
{
    Date LastDate;
    double Rate;
    string Flow_station;
    string ModuleName;
    double UR;
    double CumProd;
}WellFacilityData;

typedef struct _ForecastResult
{
    int Day;
    int Month;
    int Year;
    int startDay;
    int startMonth;
    int StartYear;
    double Oil_rate;
    double Condensate_Rate;
    double Gas_Rate;
    double Water_Rate;
    double Oil_rate_NotTerminated;
    double Gas_Rate_NotTerminated;
    double Water_Rate_NotTerminated;
    double Liquid_rate_NotTerminated;
    double GOR;
    double CGR;
    double BSW;
    double WGR;
    double Cum_Oil_Prod;
    double Cum_Condensate_Prod;
    double Cum_Gas_Prod;
    double Cum_Water_Prod;
    double Cum_Liquid_Prod;
    string Description;
    double Decision_Variable;
    double Gas_Own_Use;
    double Gas_Demand;
    double Gas_Flared;
    double Crude_Oil_Lossess;
    string ModuleName;
    string CustomDate;
    string HyrocarbonStream;
    string hydrocarbonType;
    string terminal;
    double CutBack;
    double URo;
    double URg;
    bool IsFlowing;
    double CutBackUpperBound;
    bool  isPlateau;
    double DeclineRate;
    double Liquid_Rate;
    double optimizationWeight;
    double OptimalSolution;
    string liquidCutBackText;
    string gasCutBackText;
    string nodeConnections;

    string Version_Name;
    string Asset_Team;
    string Field;
    string Reservoir;
    string Drainage_Point;
    string Production_String;
    string Flow_station;
    string TRANCHE;
    string uniqueId;
    string projectCode;
    string projectName;
    string resourceClass;
    bool isTerminated;
    bool isOilTerminated;
    bool isGasTerminated;
    bool isWaterTerminated;
    int index;
    int wellIndex;
    string optimizationWeight2;
    double AllWellsLiquidCapacity;
	double AllWellsGasCapacity;
    string dcaStrategy;
    string declineType;
    double startupRate;
    double startupRatePlateau;
    double declineRate;
    double hyperbolicExponent;
    double percentOfMaximumPotential;
    string scheduleKey;
    int declineType2;
    Date FromDate;
	Date ToDate;
    Date PlateauDate;
    double oilRateAbandonment;
    double gasRateAbandonment;
    double liquidRateAbandonmemt;
    double fluidFraction;
    double prodDays;
    string reasonForTermination;
    double deltaDay;
    double cumDays;

    double getVariableByName(const std::string& variableName) const {
        if (variableName == "oilRate") return Oil_rate;
        if (variableName == "gasRate") return Gas_Rate;
        if (variableName == "waterRate") return Water_Rate;
        if (variableName == "liquidRate") return Liquid_Rate;
        if (variableName == "condensateRate") return Condensate_Rate;
        if (variableName == "ownUseGas") return Gas_Own_Use;
        if (variableName == "gasDemand") return Gas_Demand;
        if (variableName == "flareGas") return Gas_Flared;
        if (variableName == "crudeOilLossess") return Crude_Oil_Lossess;
     

        throw std::invalid_argument("Invalid variable name");
    }

    void InitailizeData()
    {
        deltaDay = 0;
        cumDays = 0;
        reasonForTermination = "";
        prodDays = 0;
        fluidFraction = 0;
        oilRateAbandonment = 0;
        gasRateAbandonment = 0;
        liquidRateAbandonmemt = 0;
        wellIndex = 0;
        startDay = 1;
        startMonth = 1;
        StartYear = 2900;
        Oil_rate = 0.0;
        Gas_Rate = 0.0;
        Water_Rate = 0.0;
        GOR = 0.0;
        CGR = 0.0;
        BSW = 0.0;
        WGR = 0.0;
        Cum_Oil_Prod = 0.0;
        Cum_Gas_Prod = 0.0;
        Cum_Water_Prod = 0.0;
        Cum_Liquid_Prod = 0.0;
        Decision_Variable = 0.0;
        Gas_Own_Use = 0.0;
        Gas_Demand = 0.0;
        Gas_Flared = 0;
        Crude_Oil_Lossess = 0.0;
        CutBack = 0.0;
        URo = 0.0;
        URg = 0.0;
        IsFlowing = false;
        isPlateau = false;
        DeclineRate = 0;
        Liquid_Rate = 0;
        hydrocarbonType = "";
        terminal = "";
        Version_Name = "";
        Asset_Team = "";
        Field = "";
        Reservoir = "";
        Drainage_Point = "";
        Production_String = "";
        TRANCHE = "";
        Flow_station = "";
        uniqueId = "";
        projectCode = "";
        projectName = "";
        resourceClass = "";
        index = 0;
        OptimalSolution = 0;
        AllWellsLiquidCapacity = 0;
	    AllWellsGasCapacity = 0;
        optimizationWeight2 = "Normal";
        declineType = "";
        startupRate = 0;
        startupRatePlateau = 0;
        declineRate = 0;
        hyperbolicExponent = 0;
        percentOfMaximumPotential = 0;
        scheduleKey = "";
        dcaStrategy = "existingStrategy";
        declineType2 = 1;
        Oil_rate_NotTerminated = 0;
        Gas_Rate_NotTerminated = 0;
        Water_Rate_NotTerminated = 0;
        Liquid_rate_NotTerminated = 0;

    }

    void InitailizeData2()
    {
        oilRateAbandonment = 0;
        gasRateAbandonment = 0;
        liquidRateAbandonmemt = 0;
        wellIndex = 0;
        Oil_rate = 0.0;
        Gas_Rate = 0.0;
        Water_Rate = 0.0;
        GOR = 0.0;
        CGR = 0.0;
        BSW = 0.0;
        WGR = 0.0;
        Cum_Oil_Prod = 0.0;
        Cum_Gas_Prod = 0.0;
        Cum_Water_Prod = 0.0;
        Cum_Liquid_Prod = 0.0;
        Decision_Variable = 0.0;
        Gas_Own_Use = 0.0;
        Gas_Demand = 0.0;
        Gas_Flared = 0;
        Crude_Oil_Lossess = 0.0;
        CutBack = 0.0;
        URo = 0.0;
        URg = 0.0;
        IsFlowing = false;
        isPlateau = false;
        DeclineRate = 0;
        Liquid_Rate = 0;
        index = 0;
        OptimalSolution = 0;
        AllWellsLiquidCapacity = 0;
	    AllWellsGasCapacity = 0;
        optimizationWeight2 = "Normal";
        declineType = "";
        startupRate = 0;
        startupRatePlateau = 0;
        declineRate = 0;
        hyperbolicExponent = 0;
        percentOfMaximumPotential = 0;
        scheduleKey = "";
        dcaStrategy = "existingStrategy";
        declineType2 = 1;
        Oil_rate_NotTerminated = 0;
        Gas_Rate_NotTerminated = 0;
        Water_Rate_NotTerminated = 0;
        Liquid_rate_NotTerminated = 0;

    }

}ForecastResult;

typedef struct ForecastResultForChart
{
    double data;
    int Day;
    int Month;
    int Year;

    void InitailizeData()
    {
        Day = 0;
        Month = 0;
        Year = 0;
        data = 0;
    }

}ForecastResultForChart;

typedef struct _InputDeckStruct
{
    string Version_Name;
    string Asset_Team;
    string Field;
    string Reservoir;
    string Drainage_Point;
    string Production_String;
    string Module;
    string PEEP_Project;
    string Activity_Entity;
    string Flow_station;
    string Hydrocarbon_Stream;
    string hydrocarbonType;
    string terminal;
    string Resource_Class;
    string Change_Category;
    string Technique_1P;
    double URo_1P_1C; //MMSTB
    double URo_Low;   //MMSTB
    double URo_2P_2C; //MMSTB
    double URo_3P_3C; //MMSTB
    double Np;        //MMSTB
    double Cum_Liq_Prod; //MMSTB
    double Cum_Water_Prod; //MMSTB
    double URg_1P_1C; //BSCF
    double URg_Low;   //BSCF
    double URg_2P_2C; //BSCF
    double URg_3P_3C; //BSCF
    double Gp;        //BSCF
    double Init_Liquid_Gas_Rate_1P_1C; //STB/day or MMSCF/day
    double Init_Liquid_Gas_Rate_Low;   //STB/day or MMSCF/day
    double Init_Liquid_Gas_Rate_2P_2C; //STB/ady or MMSCF/day
    double Init_Liquid_Gas_Rate_3P_3C; //STB/day or MMSCF/day
    double Aband_Liquid_Gas_Rate_1P_1C; //STB/day or MMSCF/day
    double Aband_Liquid_Gas_Rate_2P_2C; //STB/day or MMSCF/day
    double Aband_Liquid_Gas_Rate_3P_3C; //STB/day or MMSCF/day
    double Init_BSW_WGR;             //Fraction or STB/MMSCF
    double Aband_BSW_WGR_1P_1C;      //Fracion  or STB/MMSCF
    double Aband_BSW_WGR_2P_2C;      //Fraction or STB/MMSCF
    double Aband_BSW_WGR_3P_3C;      //Fraction or STB/MMSCF
    double Init_GOR_CGR;             //SCF/STB or STB/MMSCF
    double Aband_GOR_CGR_1P_1C;      //SCF/STB or STB/MMSCF
    double Aband_GOR_CGR_2P_2C;      //SCF/STB or STB/MMSCF
    double Aband_GOR_CGR_3P_3C;      //SCF/STB or STB/MMSCF
    double lift_Gas_Rate;
    double Plateau_Oil_Gas;         // 1.0 means one year
    string In_year_Booking;
    string LE_LV;
    string PRCS;
    string On_stream_Date_1P_1C;
    string On_stream_Date_2P_2C;
    string On_stream_Date_3P_3C;
    string Remarks;
    string TRANCHE;

    string Description;

    //Calculated Variables

    double Rate_Of_Rate_GOR_CGR_1P1C;
    double Rate_Of_Rate_GOR_CGR_2P2C;
    double Rate_Of_Rate_GOR_CGR_3P3C;
    double Rate_Of_Rate_BSW_WGR_1P1C;
    double Rate_Of_Rate_BSW_WGR_2P2C;
    double Rate_Of_Rate_BSW_WGR_3P3C;

    double Rate_of_Change_Rate_1P_1C;
    double Rate_of_Change_Rate_2P_2C;
    double Rate_of_Change_Rate_3P_3C;

    double DeclineExponent_1P_1C;
    double DeclineExponent_2P_2C;
    double DeclineExponent_3P_3C;

    int DeclineMethod;

    Date Date_1P_1C;
    Date Date_2P_2C;
    Date Date_3P_3C;

    Date TerminationDate_1P_1C;
    Date TerminationDate_2P_2C;
    Date TerminationDate_3P_3C;
    double PlateauUR_1P_1C;
    double PlateauUR_2P_2C;
    double PlateauUR_3P_3C;

    int day_1P_1C;
    int day_2P_2C;
    int day_3P_3C;

    int month_1P_1C;
    int month_2P_2C;
    int month_3P_3C;

    int year_1P_1C;
    int year_2P_2C;
    int year_3P_3C;
    double optimizationWeight = 0.01;
    bool isTerminated = false;
    bool isOilTerminated = false;
    bool isGasTerminated = false;
    bool isWaterTerminated = false;
    int Index;
    string optimizationWeight2;
    string declineType;
    double startupRate;
    double startupRatePlateau;
    double declineRate;
    double hyperbolicExponent;
    double percentOfMaximumPotential;
    string scheduleKey;
    string dcaStrategy;
    int declineType2;
    Date FromDate;
    Date ToDate;
    Date PlateauDate;
    int nWrappedProdPrioritization;
} InputDeckStruct;


typedef struct _FacilityWellsIndicies {
    vector<string> WellNames;
    vector<int> WellIndicies;
    vector<string> tables;
    vector<string> rows;
    string Facility;
}FacilityWellsIndicies;

typedef struct _FacilityStruct
{
    string Primary_Facility;
    string Secondary_Facility;
    double Liquid_Capacity;  //STB/day
    double Gas_Capacity; // SCF/day
    double AG_Capacity; // SCF/day
    double NAG_Capacity; // SCF/day
    double Scheduled_Deferment; //%
    double Unscheduled_Deferment; //%
    double Thirdparty_Deferment; //%
    double Crudeoil_Lossess; //%
    double GasOwnUse;
    double GasDemand;
    double GasFlared;
    string FDate;
    Date FacilityDate;
} FacilityStruct;

typedef struct _RunParameter
{
    int StopDay;
    int StopMonth;
    int StopYear;
    string TimeFrequency;
    string TargetFluid;
    int isDefered;
    string forecastCase;
    bool isMonthly;
} RunParameter;

typedef struct _FacilityStructExternal
{
    string nodesConnectionKey;
    string equipmentType;
    string Primary_Facility;
    string Secondary_Facility;
    double Liquid_Capacity1P;  //STB/day
    double Gas_Capacity1P; // SCF/day
    double AG_Capacity1P; // SCF/day
    double NAG_Capacity1P; // SCF/day
    double Scheduled_Deferment1P; //%
    double Unscheduled_Deferment1P; //%
    double Thirdparty_Deferment1P; //%
    double Crudeoil_Lossess1P; //%
    double GasOwnUse1P;
    double GasDemand1P;
    double GasFlared1P;
    string FDate1P;
    Date FacilityDate1P;
    double Liquid_Capacity2P;  //STB/day
    double Gas_Capacity2P; // SCF/day
    double AG_Capacity2P; // SCF/day
    double NAG_Capacity2P; // SCF/day
    double Scheduled_Deferment2P; //%
    double Unscheduled_Deferment2P; //%
    double Thirdparty_Deferment2P; //%
    double Crudeoil_Lossess2P; //%
    double GasOwnUse2P;
    double GasDemand2P;
    double GasFlared2P;
    string FDate2P;
    Date FacilityDate2P;
    double Liquid_Capacity3P;  //STB/day
    double Gas_Capacity3P; // SCF/day
    double AG_Capacity3P; // SCF/day
    double NAG_Capacity3P; // SCF/day
    double Scheduled_Deferment3P; //%
    double Unscheduled_Deferment3P; //%
    double Thirdparty_Deferment3P; //%
    double Crudeoil_Lossess3P; //%
    double GasOwnUse3P;
    double GasDemand3P;
    double GasFlared3P;
    string FDate3P;
    Date FacilityDate3P;
    double equityPercentage;
    double FacilityOiProduced;
    double FacilityWaterProduced;
	double FacilityGasProduced;
    double FacilityAGProduced;
    double FacilityNAGProduced;
    double FacilityComdensateProduced;
	double FacilityLiquidProduced;
    double cutBack;
    string ParentNodes;
    bool isGasFlow;
    double liquidCutBack;
    double gasCutBack;
} FacilityStructExternal;

typedef struct _MBALForecastModel
{
    string uniqueId;
    string time;
    string status;
    double tankPressure;
    double deltaPPressure;
    double fBHP;
    double deltaPTubing;
    double dPChoke;
    double manPress;
    double oilRate;
    double gasRate;
    double waterRate;
    double liquidRate;
    double waterCut;
    double wGR;
    double gOR;
    double cGR;
    double gLR;
    double cumOilProduced;
    double cumGasProduced;
    double cumWaterProduced;
    int numberOfWells;

    void InitailizeData()
    {
        uniqueId = "";
        time = "";
        status = "";
        tankPressure = 0;
        deltaPPressure = 0;
        fBHP = 0;
        deltaPTubing = 0;
        dPChoke = 0;
        manPress = 0;
        oilRate = 0;
        gasRate = 0;
        waterRate = 0;
        liquidRate = 0;
        waterCut = 0;
        wGR = 0;
        gOR = 0;
        cGR = 0;
        cumOilProduced = 0;
        cumGasProduced = 0;
        cumWaterProduced = 0;
        numberOfWells = 0;
    }

}MBALForecastModel;

typedef struct _WellActivityResult
{
    string ModuleName;
    string table;
    ForecastProfileEnum ForecastProfile;
    vector<ForecastResult> externalForecastProfile;
    vector<MBALForecastModel> mBALForecastProfile;
    int startRowIndex;

     void InitializeData(){
        ModuleName = "";
        table = "";
        startRowIndex = 0;
    }
    
}WellActivityResult;


typedef struct _DeclineCureParameters
{
    string versionName;
    string assetTeam;
    string field;
    string reservoir;
    string drainagePoint;
    string productionString;
    string module;
    double initLiquidGasRate1P1C; //STB/day or MMSCF/day
    double initLiquidGasRate2P2C; //STB/ady or MMSCF/day
    double initLiquidGasRate3P3C; //STB/day or MMSCF/day
    double rateofChangeRate1P1C;
    double rateofChangeRate2P2C;
    double rateofChangeRate3P3C;
    double declineExponent1P1C;
    double declineExponent2P2C;
    double declineExponent3P3C;

    string HyrocarbonStream;
    string hydrocarbonType;

    double rateOfChangeGORCGR1P1C;
    double rateOfChangeGORCGR2P2C;
    double rateOfChangeGORCGR3P3C;
    double rateOfChangeBSWWGR1P1C;
    double rateOfChangeBSWWGR2P2C;
    double rateOfChangeBSWWGR3P3C;
    string declineMethod;

} DeclineCureParameters;

typedef struct _PrioritizationModel
{
    vector<string> ParameterNames;
    vector<double> ParameterWeights;
}PrioritizationModel;

typedef struct _Priotization
{
    string targetFluid;
    string methodOfPrioritization;
    string typeOfPrioritization; //None by default
    string typeOfStream;
    string useSecondaryFacility;
    string FacilityName;
    Date FromDate;
    Date ToDate;
    PrioritizationModel prioritizationModel;
    string ochestrationVariable;
    string ochestrationMethod;
}Priotization;

typedef struct _WellPrioritizationModel
{
    string module;
    string optimizationWeight;
}WellPrioritizationModel;


typedef struct _FacilityActivityResult  {
	string FacilityName;
	vector<WellActivityResult> WellActivityResults;
}FacilityActivityResult;

typedef struct _ScenarioModel
{
    string scenarioName;
    vector<FacilityActivityResult> result;
}ScenarioModel;


typedef struct _MBALVariableHeaders
{
    string time;
    string status;
    string tankPressure;
    string deltaPPressure;
    string fBHP;
    string deltaPTubing;
    string dPChoke;
    string manPress;
    string oilRate;
    string gasRate;
    string waterRate;
    string liquidRate;
    string waterCut;
    string wGR;
    string gOR;
    string cGR;
    string gLR;
    string cumOilProduced;
    string cumGasProduced;
    string cumWaterProduced;
    string numberOfWells;

    void InitailizeData()
    {
        time = "Time";
        status = "Status";
        tankPressure = "Tank Pressure";
        deltaPPressure = "Delta P Pressure";
        fBHP = "FBHP";
        deltaPTubing = "Delta P Tubing";
        dPChoke = "dP Choke";
        manPress = "Man Press";
        oilRate = "Oil Rate";
        gasRate = "Gas Rate";
        waterRate = "Water Rate";
        liquidRate = "Liquid Rate";
        waterCut = "Water Cut";
        wGR = "WGR";
        gOR = "GOR";
        cGR = "CGR";
        gLR = "GLR";
        cumOilProduced = "Cum Oil Produced";
        cumGasProduced = "Cum Gas Produced";
        cumWaterProduced = "Cum Wat. Produced";
        numberOfWells = "Number Of Wells";
    }

}MBALVariableHeaders;

typedef struct _WellReroute
{
    string Module;
    string Flow_station;
    string Reroute_Date_1P_1C;
    string Reroute_Date_2P_2C;
    string Reroute_Date_3P_3C;
    Date Date_1P_1C;
    Date Date_2P_2C;
    Date Date_3P_3C;
    string dcaStrategy;
    string declineType;
    double startupRate;
    double startupRatePlateau;
    double declineRate;
    double hyperbolicExponent;
    int declineType2;
    string Reroute_Fluid_Type;
} WellReroute;

typedef struct _WellRampUp
{
    string Module;
    double maximumPotential;
    string rampUpDateString_1P_1C;
    string rampUpDateString_2P_2C;
    string rampUpDateString_3P_3C;
    Date rampUpDate_1P_1C;
    Date rampUpDate_2P_2C;
    Date rampUpDate_3P_3C;
    string dcaStrategy;
    string declineType;
    double percentOfMaximumPotential;
    double startupRatePlateau;
    double declineRate;
    double hyperbolicExponent;
    int declineType2;
} WellRampUp;

typedef struct _ShutInOpenUp
{
    string Module;
    string eventDateString_1P_1C;
    string eventDateString_2P_2C;
    string eventDateString_3P_3C;
    Date eventDate_1P_1C;
    Date eventDate_2P_2C;
    Date eventDate_3P_3C;
    string event;
    string dcaStrategy;
    string declineType;
    double startupRate;
    double startupRatePlateau;
    double declineRate;
    double hyperbolicExponent;
    int declineType2;
} ShutInOpenUp;

typedef struct _WellSchedule
{
   //Module	From Date	To Date	Parameter	Value	Unit
   string Module;
   string FromDate2;
   string ToDate2;
   string ParameterName;
   int ParameterName2;
   double ParameterValue;
   string declineType;
    double startupRate;
    double startupRatePlateau;
    double declineRate;
    double hyperbolicExponent;
    double percentOfMaximumPotential;
    string scheduleKey;
    string dcaStrategy;
    int declineType2;
   Date FromDate;
   Date ToDate;
   Date PlateauDate;
   string Reroute_Fluid_Type;
 
}WellSchedule;


typedef struct _FacilityInEquipementConnection {
    string facilityName;
    double equityPercentage;
    vector<string> connections;
    vector<vector<string>> multipleConnections;
    vector<string> nodesConnectionKeys;
    vector<string> fromNodes;
    vector<string> toNodes;
    string equipmentType;

    void InitailizeData(){
        equityPercentage = 100.0;
    }
}FacilityInEquipementConnection;

typedef struct _InternalExternalEquipmentName {
    string internalEquipmentName;
    string externalEquipmentName;
    string equipmentType;
}InternalExternalEquipmentName;

typedef struct _FacilityReroute {
    string FacilityFrom;
    string FacilityTo;
    string Reroute_Date_String;
    Date Reroute_Date;
    string Reroute_Fluid_Type;
}FacilityReroute;

typedef struct _Node {
    string nodeName;
    vector<FacilityInEquipementConnection> equipmentInEquipementConnections;
    vector<FacilityStructExternal> equipmentDataInEquipementConnections;
    vector<Priotization> priotizations;
}Node;

typedef struct _FacilityThreadParams {
    int ij;
    int i;
    vector<vector<vector<InputDeckStruct>>> Faclities;
    vector<int> daysList;
    int scenario;
    vector<FacilityStruct> FacilityTable;
    vector<string> FaclitiesNames;
    vector<WellReroute> routedWells; 
    string forecastCase;
    vector<vector<Priotization>> priotizationsFacilities;
    vector<Node> updatesNodes;
}FacilityThreadParams;

typedef struct _Well {
    vector<ForecastResult> resultWells;
}Well;

typedef struct _ChatPayload {
    vector<Well> wells;
    bool isByYear;
    bool isForChart;
    int nWells;
}ChatPayload;

typedef struct _Payload {
    vector<InputDeckStruct> decks;
    vector<InternalExternalEquipmentName> internalExternalFacilitiesNames;
    int nInternalExternalFacilitiesNames;
    vector<vector<string>> equipmentConnections;
    int nEquipmentConnections;
    vector<FacilityStructExternal> deferments;
    int nDeferments;
    vector<FacilityStructExternal> crudeOilLosses;
    int nCrudeOilLosses;
    vector<FacilityStructExternal> equipmentCapacities;
    int nEquipmentCapacities;
    int numberOfNodes;
    vector<FacilityStructExternal> gasOwnUse;
    int nGasOwnUse;
    vector<FacilityStructExternal> flaredGases;
    int nFlaredGases;
    vector<string> forecastSolutionSpaces;
    int nForecastSolutionSpaces;
    vector<bool> forecastSolutionSpacesIsDURConstrained;
    int nForecastSolutionSpacesIsDURConstrained;
    vector<ForecastResult> forecastProfiles;
    int nForecastProfiles;
    int nDecks;
    string isForecastProfiles;
    vector<WellReroute> wellRerouteDecks;
    int nWellRerouteDecks;
    vector<WellRampUp> wellRampUpDecks;
    int nWellRampUpDecks;
    vector<ShutInOpenUp> wellShutInOpenUpDecks;
    int nWellShutInOpenUpDecks;
    RunParameter runparameters;
    Priotization prioritization;
    vector<Priotization> nodalPriotizations;
    int nNodalPriotizations;
    vector<InputDeckStruct> productionPrioritization;
    int nProductionPrioritization;
}Payload;

/* typedef struct _ResponseData4 {
    map<string, string> wells;
}ResponseData4;

typedef struct _ResponseData3 {
    map<string, map<string, string>> facilities;
}ResponseData2;

typedef struct _ResponseData3 {
    map<string, map<string, map<string, string>>> scenarios;
}ResponseData2;

typedef struct _ResponseData1 {
    map<string, map<string, map<string, map<string, string>>>> solutionSpaces;
}ResponseData1; */

typedef struct _ResponseData {
    map<string, map<string, map<string, map<string, map<string, string>>>>> monthlyReport;
}ResponseData;

typedef struct _ResponseChatData {
    map<string, map<string, string>> response;
}ResponseChatData;

typedef struct _MonthlyReport{

}MonthlyReport;

typedef struct _StoredForecastResult {
    MonthlyReport monthlyReport;
}StoredForecastResult;

typedef struct _ModuleResultMonthly {
    vector<ForecastResult> resultWells;
}ModuleResultMonthly;

typedef struct _InputObject {
    vector<ModuleResultMonthly> wells;
    bool isByYear;
    bool isForChart;
    int nWells;
}InputObject;

typedef struct _YObj {
    string forecastResultId;
    string id;
    string name;
    string title;
    string path;
    vector<double> y;  // Assuming `y` is a vector of doubles
    vector<string> x;  // Assuming `x` is a vector of strings
}YObj;

typedef struct _ForecastResultsByModule {
    string forecastResultsId;
    string ModuleName;
    string FacilityName;
    string ScenarioName;
    string ModuleKey;
    string SolutionSpace;
    string forecastResults;
    string forecastInputId;
}ForecastResultsByModule;


typedef struct _ForecastResultsPayload {
    vector<ForecastResultsByModule> moduleResults;
}ForecastResultsPayload;

typedef struct _ChatInputPayload {
    vector<string> forecastResultsIds;
    vector<string> selectedModulePaths;
    vector<string> selectedVariables;
    bool shouldAggregate;
    vector<string> forecastSolutionSpaces;
    bool isMonthly;
}ChatInputPayload;



const int Init_Oil_Gas_Rate_1P_1C = 0;
const int Init_Oil_Gas_Rate_2P_2C = 1;
const int Init_Oil_Gas_Rate_3P_3C = 2;
const int Decline_Rate_1P_1C = 3;
const int Decline_Rate_2P_2C = 4;
const int Decline_Rate_3P_3C = 5;
const int Rate_Of_Rate_GOR_CGR_1P1C = 6;
const int Rate_Of_Rate_GOR_CGR_2P2C = 7;
const int Rate_Of_Rate_GOR_CGR_3P3C = 8;
const int Rate_Of_Rate_BSW_WGR_1P1C = 9;
const int Rate_Of_Rate_BSW_WGR_2P2C = 10;
const int Rate_Of_Rate_BSW_WGR_3P3C = 11;
const int Decline_Exponent_1P1C = 12;
const int Decline_Exponent_2P2C = 13;
const int Decline_Exponent_3P3C = 14;
const int PlateauUR_1P_1C = 15;
const int PlateauUR_2P_2C = 16;
const int PlateauUR_3P_3C = 17;
const int noExistingStrategy = 18;
const int existingStrategy = 19;

const string noExistingStrategy_String = "noExistingStrategy";
const string existingStrategy_String = "existingStrategy";
const string WellShutIn_String = "WellShutIn";
const string WellOpenUp_String = "WellOpenUp";
const string WellRampUp_String = "WellRampUp";
const string WellReroute_String = "WellReroute";
const string wellPrioritization = "wellPrioritization";
const string noWellPrioritization = "No Prioritization";
const string weighted = "weighted";
const string sequential = "sequential";
const string condensate = "condensate";
const string oil = "oil";
const string gas = "gas";
const string  ag = "ag";
const string nag = "nag";
const string water = "water";
const string liquid = "liquid";
const string streamPrioritization = "streamPrioritization";
const string resourceClassPrioritization = "resourceClassPrioritization";
const string projectPrioritization = "projectPrioritization";
const string nodalPrioritization = "nodalPrioritization";
const string High = "high";
const string Normal = "normal";
const string Low = "low";
const string external = "external";
const string potential = "potential";
//const string None = "None";
const string internal = "internal";
const string availability = "availability";
const string delivered = "deliverability";
const string offtake = "offtake";
const string oil_water_gas = "oil_water_gas";
const string oil_water = "oil_water";   
const string water_gas = "water_gas";
const string oil_gas = "oil_gas";
const string gas_plant = "gas plant";
const string flow_station = "flow station";
const string oil_asset = "oil asset";
const string gas_asset = "gas asset";
const string ag_asset = "ag asset";
const string nag_asset = "nag asset";
const string condensate_asset = "condensate asset";
//const string exponential = "exponential";
//const string hyperbolic = "hyperbolic";
//const string harmonic = "harmonic";
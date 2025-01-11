from dca import exponential_decline, get_decline_factor_exponential
from json_data_io import writeJsonData
from aggregate import convert_monthly_to_yearly, get_yearly_dates
from date_utils import date_array
from datetime import datetime

M = pow(10, 3)
MM = pow(10, 6)
B = pow(10, 9)
isRateCum = True
daysPerYear = 365
monthlyModuleForecastResults = {}
yearlyModuleForecastResults = {}

module = {
                "forecastVersion": "",
                "asset": "",
                "reservoir": "FO17 D30X",
                "field": "FO17",
                "drainagePoint": "FO17009T_FO17 D30X_P12",
                "string": "T",
                "module": "FO17009T_FO17 D30X_P12",
                "projectCode": "P12",
                "projectName": "PROJECT DEV PHASE 4",
                "facilities": "ABU_FS3",
                "hydrocarbonStream": "oil",
                "hydrocarbonType": "",
                "terminal": "",
                "resourceClass": "",
                "oilUR1P1C": 0.375299999999999,
                "oilUR2P2C": 1.415541175,
                "oilUR3P3C": 0.5685,
                "Np": 0,
                "gasUR1P1C": 0,
                "gasUR2P2C": 0,
                "gasUR3P3C": 0,
                "Gp": 0,
                "initOilGasRate1P1C": 200,
                "initOilGasRate2P2C": 200,
                "initOilGasRate3P3C": 200,
                "abandOilGasRate1P1C": 50,
                "abandOilGasRate2P2C": 50,
                "abandOilGasRate3P3C": 50,
                "initBSWWGR": 0.95,
                "abandBSWWGR1P1C": 0.99,
                "abandBSWWGR2P2C": 0.99,
                "abandBSWWGR3P3C": 0.99,
                "initGORCGR": 350,
                "abandGORCGR1P1C": 700,
                "abandGORCGR2P2C": 700,
                "abandGORCGR3P3C": 700,
                "plateauPeriod": 9.0,
                "onStreamDate1P1C": "1/6/2033",
                "onStreamDate2P2C": "1/6/2033",
                "onStreamDate3P3C": "1/6/2033",
                "remarks": "",
                "developmentTranche": "",
                "description": "no error",
                "day1P1C": 1,
                "day2P2C": 1,
                "day3P3C": 1,
                "month1P1C": 6,
                "month2P2C": 6,
                "month3P3C": 6,
                "year1P1C": 2033,
                "year2P2C": 2033,
                "year3P3C": 2033,
                "rateofChangeRate1P1C": 0,
                "rateofChangeRate2P2C": 0,
                "rateofChangeRate3P3C": 0,
                "declineExponent1P1C": 0,
                "declineExponent2P2C": 0,
                "declineExponent3P3C": 0,
                "declineMethod": "exponential",
                "rateOfChangeGORCGR1P1C": 0,
                "rateOfChangeGORCGR2P2C": 0,
                "rateOfChangeGORCGR3P3C": 0,
                "rateOfChangeBSWWGR1P1C": 0,
                "rateOfChangeBSWWGR2P2C": 0,
                "rateOfChangeBSWWGR3P3C": 0,
                "plateauUR1P1C": 0,
                "plateauUR2P2C": 0,
                "plateauUR3P3C": 0
            }

initWaterFraction = 0
initGasFraction = 0
initRate = 0
AbandRate = 0
UR = 0
UR_no_plateau = 0
initCumProd = 0
PlateauUR = 0
abandWaterFraction = 0
abandGasFraction = 0
rateDecline = 0
waterFractionSlope = 0
gasFractionSlope = 0
OSD = datetime.strptime(module["onStreamDate2P2C"], "%d/%m/%Y")

startDate = datetime(2024, 1, 1, 0, 0, 0)
endDate = datetime(2070, 12, 31, 0, 0, 0)

dates = date_array(startDate, endDate, 'months')

datesYearly = get_yearly_dates(dates)

nt = len(dates)
ntYearly = len(datesYearly)

cum_days = (endDate - OSD).days
#cum_days = (endDate - startDate).days

if module["hydrocarbonStream"] == "gas":
    initWaterFraction = module["initBSWWGR"] / MM or pow(10, -12)
    initGasFraction = module["initGORCGR"] / MM or pow(10, -12)
    initRate = module["initOilGasRate2P2C"] * MM
    AbandRate = module["abandOilGasRate2P2C"] * MM
    UR = module["gasUR2P2C"] * B
    initCumProd = module["Gp"] * B
    PlateauUR = module["plateauPeriod"] * (UR - initCumProd)
    UR_no_plateau = UR - PlateauUR
    if UR_no_plateau < 0 :
        UR_no_plateau = 0
    abandWaterFraction = module["plateauPeriod"]
    abandGasFraction = module["abandGORCGR2P2C"]

    rateDecline = get_decline_factor_exponential(
        initRate, AbandRate,
        initCumProd, UR_no_plateau,
        cum_days, isRateCum
    )


    waterFractionSlope = get_decline_factor_exponential(
        initWaterFraction, abandWaterFraction,
        initCumProd, UR_no_plateau,
        cum_days, isRateCum
    )

    gasFractionSlope = get_decline_factor_exponential(
        initGasFraction, abandGasFraction,
        initCumProd, UR_no_plateau,
        cum_days, isRateCum
    )

else:

    initWaterFraction = module["initBSWWGR"] or pow(10, -8)
    initGasFraction = module["initGORCGR"] or pow(10, -8)
    initRate = module["initOilGasRate2P2C"]
    AbandRate = module["abandOilGasRate2P2C"]
    AbandLiqRate =  module["abandOilGasRate2P2C"]
    UR = module["oilUR2P2C"] * MM
    initCumProd = module["Np"] * MM
    PlateauUR = module["plateauPeriod"] * daysPerYear * initRate
    UR_no_plateau = UR - PlateauUR
    if UR_no_plateau < 0 :
        UR_no_plateau = 0
    abandWaterFraction = module["plateauPeriod"]
    abandGasFraction = module["abandGORCGR2P2C"]

    rateDecline = get_decline_factor_exponential(
        initRate, AbandLiqRate,
        initCumProd, UR_no_plateau,
        cum_days, isRateCum
    )

    waterFractionSlope = get_decline_factor_exponential(
        initWaterFraction, abandWaterFraction,
        initCumProd, UR_no_plateau,
        cum_days, isRateCum
    )

    gasFractionSlope = get_decline_factor_exponential(
        initGasFraction, abandGasFraction,
        initCumProd, UR_no_plateau,
        cum_days, isRateCum
    )

declineRates = [0] * nt
liquidRates = [0] * nt
oilRates = [0] * nt
cumLiqProd = [0] * nt
cumOilProd = [0] * nt
cumGasProd = [0] * nt
cumWaterProd = [0] * nt
condensateRate = [0] * nt
waterFraction = [0] * nt
gasFraction = [0] * nt
actualURs = [0] * nt
gasRates = [0] * nt
waterRates = [0] * nt

for k in range(nt):
    if dates[k] >= OSD:
        if module["hydrocarbonStream"] == "gas":

            kk = k - 1 if k > 0 else k
            cumGasProd[kk] = initCumProd
            gasRates[kk] = initRate
            waterFraction[kk] = initWaterFraction
            gasFraction[kk] = initGasFraction
            condensateRate[kk] = gasRates[kk] * gasFraction[kk]
            waterRates[kk] = gasRates[kk] * waterFraction[kk]
            liquidRates[kk] = condensateRate[kk] + waterRates[kk]
            declineRates[kk] = rateDecline
            actualURs[kk] = UR
            cumOilProd[kk] = cumGasProd[kk] * gasFraction[kk]
            cumWaterProd[kk] = cumGasProd[kk] * waterFraction[kk]
            oilRates[kk] = 0

        else:

            kk = k - 1 if k > 0 else k
            
            cumOilProd[kk] = initCumProd
            oilRates[kk] = initRate
            declineRates[kk] = rateDecline
            actualURs[kk] = UR
            waterFraction[kk] = initWaterFraction
            gasFraction[kk] = initGasFraction
            liquidRates[kk] = oilRates[kk] / (1 - waterFraction[kk])
            gasRates[kk] = oilRates[kk] * gasFraction[kk]
            cumLiqProd[kk] = cumOilProd[kk] / (1 - waterFraction[kk])
            cumWaterProd[kk] = liquidRates[kk] * waterFraction[kk]
            condensateRate[kk] = 0

        break  # Equivalent to Exit For in VBA

#=====
delta_t = 30
cum_days = 0
cum_days2 = 0
monthlyModuleForecastResults = {}
yearlyModuleForecastResults = {}
HFPTModuleForecastResults = {}

for k in range(1, nt):
    if dates[k] >= OSD:
        cum_days2 += delta_t
        if module["hydrocarbonStream"] == "GAS":
            
            declineRates[k] = rateDecline
            cum_prod = cumGasProd[k - 1] - initCumProd
            
            cum_gas_prod_no_plateau = cum_prod - PlateauUR
            if cum_gas_prod_no_plateau > 0:
                cum_days += delta_t
            
            gasRates[k] = exponential_decline(
                initRate, rateDecline, cum_prod, 
                PlateauUR, cum_days, isRateCum
            )
            
            gasProd = delta_t * gasRates[k]
            cumGasProd[k] = cumGasProd[k - 1] + gasProd
            cum_prod = cumGasProd[k] - initCumProd
            
            waterFraction[k] = exponential_decline(
                initWaterFraction, waterFractionSlope, cum_prod, 
                PlateauUR, cum_days, isRateCum
            )
            gasFraction[k] = exponential_decline(
                initGasFraction, gasFractionSlope, cum_prod, 
                PlateauUR, cum_days, isRateCum
            )
            
            condensateRate[k] = gasRates[k] * gasFraction[k]
            cumOilProd[k] = cumOilProd[k - 1] + (delta_t * condensateRate[k])
            actualURs[k] = UR - cumGasProd[k]
            oilRates[k] = 0
            waterRates[k] = gasRates[k] * waterFraction[k]
            liquidRates[k] = condensateRate[k] + waterRates[k]
            
        else:  # Not "GAS"

            declineRates[k] = rateDecline
            cum_prod = cumOilProd[k - 1] - initCumProd
            
            cum_liquid_prod_no_plateau = cum_prod - PlateauUR
            if cum_liquid_prod_no_plateau > 0:
                cum_days += delta_t
            
            oilRates[k] = exponential_decline(
                initRate, rateDecline, cum_prod, 
                PlateauUR, cum_days, isRateCum
            )
            
            oil_prod = delta_t * oilRates[k]
            cumOilProd[k] = cumOilProd[k - 1] + oil_prod
            cum_prod = cumOilProd[k] - initCumProd
            
            waterFraction[k] = exponential_decline(
                initWaterFraction, waterFractionSlope, cum_prod, 
                PlateauUR, cum_days, isRateCum
            )
            gasFraction[k] = exponential_decline(
                initGasFraction, gasFractionSlope, cum_prod, 
                PlateauUR, cum_days, isRateCum
            )
            
            liquidRates[k] = oilRates[k] / (1 - waterFraction[k])
            gasRates[k] = oilRates[k] * gasFraction[k]
            cumLiqProd[k] = cumLiqProd[k - 1] + (delta_t * liquidRates[k])
            actualURs[k] = UR - cumOilProd[k]
            condensateRate[k] = 0
        
        # Abandonment checks
        if module["hydrocarbonStream"] == "GAS":
            if gasRates[k] < AbandRate:
                declineRates[k] = 0
                liquidRates[k] = 0
                cumGasProd[k] = cumGasProd[k - 1]
                waterFraction[k] = 0
                gasFraction[k] = 0
                cumOilProd[k] = cumLiqProd[k - 1]
                oilRates[k] = 0
                actualURs[k] = 0
                condensateRate[k] = 0
                gasRates[k] = 0
        else:
            if oilRates[k] < AbandRate:
                declineRates[k] = 0
                liquidRates[k] = 0
                cumLiqProd[k] = cumLiqProd[k - 1]
                waterFraction[k] = 0
                gasFraction[k] = 0
                cumOilProd[k] = cumLiqProd[k - 1]
                oilRates[k] = 0
                actualURs[k] = 0
                condensateRate[k] = 0
                gasRates[k] = 0


# Decline Rate
declineRatesYearly = convert_monthly_to_yearly(datesYearly, dates, declineRates)
#monthlyModuleForecastResults["dates"] = dates
#monthlyModuleForecastResults["declineRates"] = declineRates

#yearlyModuleForecastResults["datesYearly"] = datesYearly
#yearlyModuleForecastResults["declineRatesYearly"] = declineRatesYearly

# Liquid Rates
liquidRatesYearly = convert_monthly_to_yearly(datesYearly, dates, liquidRates)
monthlyModuleForecastResults["liquidRates"] = liquidRates
yearlyModuleForecastResults["liquidRatesYearly"] = liquidRatesYearly

# Gas Rates
gasRatesYearly = convert_monthly_to_yearly(datesYearly, dates, gasRates)
monthlyModuleForecastResults["gasRates"] = [value / M for value in gasRates]
yearlyModuleForecastResults["gasRatesYearly"] = [value / M for value in gasRatesYearly]

# Oil Rates
oilRatesYearly = convert_monthly_to_yearly(datesYearly, dates, oilRates)
monthlyModuleForecastResults["oilRates"] = oilRates
yearlyModuleForecastResults["oilRatesYearly"] = oilRatesYearly


# Write Condensate Rate
condensateRateYearly = convert_monthly_to_yearly(datesYearly, dates, condensateRate)
monthlyModuleForecastResults["condensateRate"] = condensateRate
yearlyModuleForecastResults["condensateRateYearly"] = condensateRateYearly



# Handle GAS or other hydrocarbon streams
if module["hydrocarbonStream"] == "GAS":
    monthlyModuleForecastResults["waterFraction"] = waterFraction
    monthlyModuleForecastResults["gasFraction"] = gasFraction
else:
    monthlyModuleForecastResults["waterFraction"] = waterFraction
    monthlyModuleForecastResults["gasFraction"] = gasFraction


single_well_monthly_report_file_path = "single_well_monthly_report.json"
writeJsonData(single_well_monthly_report_file_path, monthlyModuleForecastResults)

single_well_yearly_report_file_path = "single_well_yearly_report.json"
writeJsonData(single_well_yearly_report_file_path, yearlyModuleForecastResults)
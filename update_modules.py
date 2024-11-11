from spreadsheet_io import read_spread_sheet_data, get_column_names, read_spread_sheet_data_2
from json_data_io import readJsonData, writeJsonData

def update_decks(file_path, sheet_name, columns_to_read, decks_file_path, updated_decks_file_path):

    decks_calculated = read_spread_sheet_data(file_path, sheet_name, columns_to_read)
    modules = decks_calculated[0]
    plateau_periods = decks_calculated[1]

    json_data = readJsonData(decks_file_path)

    decks = json_data['payload']['decks']

    i = -1
    for deck in decks:
        i = i + 1
        j = -1
        for module in modules:
            j = j + 1
            if module == deck['module']:
                decks[i]["plateauPeriod"] = plateau_periods[j]
                break

    json_data['payload']['decks'] = decks
    writeJsonData(updated_decks_file_path, json_data)


def update_decks2(file_path, sheet_name, columns_to_read, decks_file_path, updated_decks_file_path):

    decks_calculated = read_spread_sheet_data_2(file_path, sheet_name, columns_to_read)
    modules = decks_calculated["UniqueID"]
    n = len(modules)

    json_data = readJsonData(decks_file_path)

    decks = []

    M = 1000
    MM = 1000000


    for i in range(n):
       timestamp = decks_calculated['Onstream Date'][i]

       day = timestamp.day
       month = timestamp.month
       year = timestamp.year
       onstream_date = f"{day}/{month}/{year}"
       deck = {
                "forecastVersion": "",
                "asset": "",
                "reservoir": decks_calculated['Reservoir'][i],
                "field": decks_calculated["Field"][i],
                "drainagePoint": "",
                "string": decks_calculated['String'][i],
                "module": decks_calculated["UniqueID"][i],
                "projectCode": decks_calculated['Project Code'][i],
                "projectName": decks_calculated['Project'][i],
                "facilities": decks_calculated['Facilities'][i],
                "hydrocarbonStream": decks_calculated['HC Stream'][i].lower(),
                "hydrocarbonType": "",
                "terminal": "",
                "resourceClass": "",
                "oilUR1P1C": decks_calculated['URo 1P/1C  [mmstb]'][i],
                "oilUR2P2C": decks_calculated['URo 2P/2C  [mmstb]'][i],
                "oilUR3P3C": decks_calculated['URo 3P/3C  [mmstb]'][i],
                "Np": decks_calculated['Np  [mmstb]'][i],
                "gasUR1P1C":decks_calculated['URg 1P/1C  [Bscf]'][i] * M,
                "gasUR2P2C": decks_calculated['URg 2P/2C  [Bscf]'][i]* M,
                "gasUR3P3C": decks_calculated['URg 3P/3C  [Bscf]'][i]* M,
                "Gp": decks_calculated['Gp  [Bscf]'][i]* M,
                "initOilGasRate1P1C": decks_calculated['Initial Rates [stb/d]/ [MMscf/d]'][i],
                "initOilGasRate2P2C": decks_calculated['Initial Rates [stb/d]/ [MMscf/d]'][i],
                "initOilGasRate3P3C": decks_calculated['Initial Rates [stb/d]/ [MMscf/d]'][i],
                "abandOilGasRate1P1C": decks_calculated['Abandonment Rates  [stb/d] / [MMscf/d]'][i],
                "abandOilGasRate2P2C": decks_calculated['Abandonment Rates  [stb/d] / [MMscf/d]'][i],
                "abandOilGasRate3P3C": decks_calculated['Abandonment Rates  [stb/d] / [MMscf/d]'][i],
                "initBSWWGR": decks_calculated['Init. BSW/WGR  [fraction] / [stb/MMscf]'][i],
                "abandBSWWGR1P1C": decks_calculated['Aband. BSW/WGR [fraction] / [stb/MMscf]'][i],
                "abandBSWWGR2P2C": decks_calculated['Aband. BSW/WGR [fraction] / [stb/MMscf]'][i],
                "abandBSWWGR3P3C": decks_calculated['Aband. BSW/WGR [fraction] / [stb/MMscf]'][i],
                "initGORCGR": decks_calculated['Init. GOR/CGR  [scf/stb] / [stb/MMscf]'][i],
                "abandGORCGR1P1C": decks_calculated['Aband. GOR/CGR  [scf/stb] / [stb/MMscf]'][i],
                "abandGORCGR2P2C": decks_calculated['Aband. GOR/CGR  [scf/stb] / [stb/MMscf]'][i],
                "abandGORCGR3P3C": decks_calculated['Aband. GOR/CGR  [scf/stb] / [stb/MMscf]'][i],
                "plateauPeriod": decks_calculated['Plateau Period [Oil/Gas] [int. Year] / [fraction]  [int. Year] / [fraction]'][i],
                "onStreamDate1P1C": onstream_date,
                "onStreamDate2P2C": onstream_date,
                "onStreamDate3P3C": onstream_date,
                "remarks": "",
                "developmentTranche": "",
                "description": "no error",
                "day1P1C": day,
                "day2P2C": day,
                "day3P3C": day,
                "month1P1C": month,
                "month2P2C": month,
                "month3P3C": month,
                "year1P1C": year,
                "year2P2C": year,
                "year3P3C": year,
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
       
       if deck["hydrocarbonStream"] == "gas":
           deck["initOilGasRate1P1C"] = deck["initOilGasRate1P1C"] * MM
           deck["initOilGasRate2P2C"] = deck["initOilGasRate2P2C"] * MM
           deck["initOilGasRate3P3C"] = deck["initOilGasRate3P3C"] * MM

           deck["abandOilGasRate1P1C"] = deck["abandOilGasRate1P1C"] * MM
           deck["abandOilGasRate2P2C"] = deck["abandOilGasRate2P2C"] * MM
           deck["abandOilGasRate3P3C"] = deck["abandOilGasRate3P3C"] * MM

           deck["initBSWWGR"] = deck["initBSWWGR"] / MM
           deck["abandBSWWGR1P1C"] = deck["abandBSWWGR1P1C"] / MM
           deck["abandBSWWGR2P2C"] = deck["abandBSWWGR2P2C"] / MM
           deck["abandBSWWGR3P3C"] = deck["abandBSWWGR3P3C"] / MM

           deck["initGORCGR"] = deck["initGORCGR"] / MM
           deck["abandGORCGR1P1C"] = deck["abandGORCGR1P1C"] / MM
           deck["abandGORCGR2P2C"] = deck["abandGORCGR2P2C"] / MM
           deck["abandGORCGR3P3C"] = deck["abandGORCGR3P3C"] / MM
       
       decks.append(deck)
       
       
               

    json_data['payload']['decks'] = decks
    writeJsonData(updated_decks_file_path, json_data)


file_path = 'files/Test Forecasting Input Data_v2.xlsm'
sheet_name = 'Modules Updated'
columns_to_read = get_column_names(file_path, sheet_name) # ['UniqueID', 'Plateau_Period']
decks_file_path = 'files/forecast_input_data.json'
updated_decks_file_path = 'files/forecast_input_data_updated.json'

update_decks2(file_path, sheet_name, columns_to_read, decks_file_path, updated_decks_file_path)
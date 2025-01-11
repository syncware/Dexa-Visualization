import numpy as np
from json_data_io import readJsonData, writeJsonData

hfpt_forecastResults_well_by_well_file_path = "hfpt_forecastResults_well_by_well.json"
hfpt_forecastResults = readJsonData(hfpt_forecastResults_well_by_well_file_path)
forecast_input_data_updated_old_file_path = "forecast_input_data_updated_old.json"
input_data = readJsonData(forecast_input_data_updated_old_file_path)

module_names = list(hfpt_forecastResults.keys())

n_module_names = len(module_names)

variable_name_hfpt_oil = "oilRatesYearly"
variable_name_hfpt_gas = "gasRatesYearly"

def get_hydrocarbon_stream(module_name):
    for deck in input_data["payload"]["decks"]:
        if deck["module"] == module_name:
            return deck["hydrocarbonStream"]
        
    return ""  

def update_deck_ur(module_name, estimated_ur, hydrocarbon_stream):
    i = -1
    for deck in input_data["payload"]["decks"]:
        i = i + 1
        if deck["module"] == module_name:
            if hydrocarbon_stream == "oil":
                input_data["payload"]["decks"][i]["oilUR2P2C"] = estimated_ur
                break
            else:
                input_data["payload"]["decks"][i]["gasUR2P2C"] = estimated_ur
                break

modules_urs = {}

for module_name in module_names:
   
    hydrocarbon_stream = get_hydrocarbon_stream(module_name)
    if hydrocarbon_stream == "oil":
        y_values_hfpt = [value for value in  hfpt_forecastResults[module_name][variable_name_hfpt_oil]]
        n_y_values_hfpt = len(y_values_hfpt)
        x_values_hfpt = [i * 360 for i in range(n_y_values_hfpt)]
        estimated_ur = np.trapz(y_values_hfpt, x_values_hfpt) / pow(10, 6)
        modules_urs[module_name] = {"ur": estimated_ur, "hydrocarbonStream": hydrocarbon_stream}
        update_deck_ur(module_name, estimated_ur, hydrocarbon_stream)
    else:
        y_values_hfpt = [value for value in  hfpt_forecastResults[module_name][variable_name_hfpt_gas]]
        n_y_values_hfpt = len(y_values_hfpt)
        x_values_hfpt = [i * 360 for i in range(n_y_values_hfpt)]
        estimated_ur = np.trapz(y_values_hfpt, x_values_hfpt) / pow(10, 3)
        modules_urs[module_name] = {"ur": estimated_ur, "hydrocarbonStream": hydrocarbon_stream}
        update_deck_ur(module_name, estimated_ur, hydrocarbon_stream)
    


estimated_ur_file_path = "modules_urs.json"
writeJsonData(estimated_ur_file_path, modules_urs)
forecast_input_data_updated_file_path = "forecast_input_data_updated.json"
writeJsonData(forecast_input_data_updated_file_path, input_data)
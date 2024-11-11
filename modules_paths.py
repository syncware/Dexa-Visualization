import json
import matplotlib.pyplot as plt
from data import selected_facilities
from json_data_io import readJsonData
from json_data_io import writeJsonData

facilities = selected_facilities
file_path = 'files/apex_forecast_db.forecast_forecastresults.json'
output_file_path = 'files/module_paths.json'

def getModulePathsPerFacility(facilityName, json_data):
    # Load the JSON data from a file

    # Access the data
    facilityIndex = facilities[facilityName]
    nodules_data = json_data[0]['treeResult']['treeModel'][0]['children'][facilityIndex]['children']

    # Loop through the 'nodules_data' list and plot each series
    module_paths = []
    for entry in nodules_data:
        module_path = entry['path']
        module_paths.append(module_path)

    return module_paths


def getModulePathsPerSelectedFacilities(facilityNames, json_data):
    modulePaths = []
    for facilityName in facilityNames:
        module_paths_per_facility = getModulePathsPerFacility(facilityName, json_data)
        for module_path in module_paths_per_facility:
            modulePaths.append(module_path)

    return modulePaths

facilityNames = [
    "ABU_FS1",
    "ABU_FS2",
    "ABU_FS3",
    "ABU_FS4",
    "ABU_FS5",
    "ABU_FS6",
    "ABU_FS7",
    "REO_GP1",
    "REO_GP2",
    "REO_GP3",
    "REO_GP4",
    "REO_GP5"
]
json_data = readJsonData(file_path)
modulePaths = getModulePathsPerSelectedFacilities(facilityNames, json_data)
writeJsonData(output_file_path, modulePaths)

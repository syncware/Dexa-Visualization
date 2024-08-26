import json
import matplotlib.pyplot as plt

# Load the JSON data from a file
with open('forecast_result.json', 'r') as file:
    json_data = json.load(file)

# Access the data
nodules_data = json_data['treeResult']['treeModel'][0]['children'][0]['children']

# Loop through the 'nodules_data' list and plot each series
module_paths = []
for entry in nodules_data:
    module_path = entry['path']
    module_paths.append(module_path)


# Specify the file name
file_name = 'module_paths.json'

# Writing the list to a JSON file
with open(file_name, 'w') as json_file:
    json.dump(module_paths, json_file, indent=4)

print(f"Module paths has been written to {file_name}")
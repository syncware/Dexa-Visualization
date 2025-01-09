import json

def readJsonData(file_name):
    with open(file_name, 'r') as file:
        json_data = json.load(file)

    return json_data

def writeJsonData(file_name, data):

    # Writing the list to a JSON file
    with open(file_name, 'w') as json_file:
        json.dump(data, json_file, indent=4)

    print(f"Json data written to {file_name}")
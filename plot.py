import json
from datetime import datetime
import matplotlib.pyplot as plt
from json_data_io import readJsonData

def plotDataPerFacility(file_name, solution_space, 
                        scenario, forecastResultIndex, variable,
                        x_axis_label, y_axis_label, title):
    # Load the JSON data from a file
    json_data = readJsonData(file_name)

    # Access the data
    #data = json_data['data']['1']['1P_1C']['potential']
    data = json_data[scenario][solution_space]

    # Parse the JSON data
    #data = json.loads(json_data)

    # Loop through the 'variableObject' list and plot each series
    variableObject = data[variable]
    for entry in variableObject:
        x = entry['x']
        y = entry['y']
        
        # Convert x (datetime strings) to a more suitable format for plotting
        #x = [date[:10] for date in x]  # Keep only the date part (YYYY-MM-DD)
        x = [datetime.strptime(date, '%d/%m/%Y').strftime('%Y-%m-%d') for date in x]

        plt.ion()

        # Plot the data
        plt.plot(x, y, label=entry['name'])

    # Customize the plot
    plt.xlabel(x_axis_label)
    plt.ylabel(y_axis_label)
    plt.title(title)
    plt.xticks(rotation=45)
    plt.legend()

    # Show the plot
    plt.tight_layout()
    plt.show(block=True)

file_name = "files/forecast_chat_data_output.json"
solution_space = "POTENTIAL1P_1C"
scenario = "1P_1C" 
forecastResultIndex = "1"
variable = "oilRate"
x_axis_label = "Production Date"
y_axis_label = "Oil Rate (bbl/d)"
title = "Forecast Oil Rate"
plotDataPerFacility(file_name, solution_space, 
                    scenario, forecastResultIndex, variable,
                    x_axis_label, y_axis_label, title)

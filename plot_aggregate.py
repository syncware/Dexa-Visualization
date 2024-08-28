import matplotlib.pyplot as plt
import json
from datetime import datetime
from json_data_io import readJsonData

def plot_aggregated_data(file_name, solution_space, 
                        scenario, forecastResultIndex, variable,
                        x_axis_label, y_axis_label, title, label_title):
    # Load the JSON data from a file
    json_data = readJsonData(file_name)

    # Extracting the relevant data
    variable_data = json_data[scenario][solution_space][variable]
    #x_values = [datetime.strptime(date, "%Y-%m-%dT%H:%M:%S.%fZ") for date in variable_data["x"]]
    x_values = [datetime.strptime(date, '%d/%m/%Y').strftime('%Y-%m-%d') for date in variable_data["x"]]
    y_values = variable_data["y"]

    # Plotting the data
    plt.figure(figsize=(10, 5))
    #plt.plot(x_values, y_values, marker='o', linestyle='-', color='b')
    plt.plot(x_values, y_values, label=label_title)

    # Adding title and labels
    plt.title(title)
    plt.xlabel(x_axis_label)
    plt.ylabel(y_axis_label)

    # Display the plot
    plt.grid(True)
    plt.xticks(rotation=45)
    plt.tight_layout()
    plt.show(block=True)

file_name = "files/forecast_chat_data_output.json"
solution_space = "potential"
scenario = "1P_1C" 
forecastResultIndex = "1"
variable = "oilRate"
x_axis_label = "Production Date"
y_axis_label = "Oil Rate (bbl/d)"
title = "Forecast Oil Rate"
label_title = "Facilit 1"
plot_aggregated_data(file_name, solution_space, 
                    scenario, forecastResultIndex, variable,
                    x_axis_label, y_axis_label, title, label_title)

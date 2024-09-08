import matplotlib.pyplot as plt
import pandas as pd
import json
from datetime import datetime
from json_data_io import readJsonData
from text_file_data_io import read_text_file

def plot_aggregated_data(file_name, solution_space, 
                        scenario, forecastResultIndex, variable,
                        x_axis_label, y_axis_label, title, label_title,
                        actual_file_name, divisor):
    # Load the JSON data from a file
    json_data = readJsonData(file_name)

    # Extracting the relevant data
    variable_data = json_data[scenario][solution_space][variable]
    #x_values = [datetime.strptime(date, "%Y-%m-%dT%H:%M:%S.%fZ") for date in variable_data["x"]]
    x_values = [datetime.strptime(date, '%d/%m/%Y').strftime('%Y-%m-%d') for date in variable_data["x"]]
    y_values = [value / divisor for value in  variable_data["y"]]

    actual_data = read_text_file(actual_file_name)
    x_actual = actual_data["x"]
    #x_actual_date = [datetime.strptime(date, "%m/%d/%Y").date() for date in x_actual]
    x_actual_date = [datetime.strptime(date, '%d/%m/%Y').strftime('%Y-%m-%d') for date in x_actual]
    y_actual = actual_data["y"]
    

    # Plotting the data
    plt.figure(figsize=(10, 5))
    #plt.plot(x_values, y_values, marker='o', linestyle='-', color='b')
    plt.plot(x_values, y_values, label=label_title)

    # plt.plot(x_actual_date, y_actual, label="Actual")

    #plt.gcf().autofmt_xdate()

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
solution_space = "POTENTIAL3P_3C"
scenario = "3P_3C" 
forecastResultIndex = "1"
variable = "flareGas"
x_axis_label = "Production Date"
y_axis_label = "flareGas (MMscf/d)"
title = "Forecast Gas Rate"
label_title = "Facilit 1"
actual_file_name = 'files/oIl_rate group_1.txt'
divisor = 1000000
plot_aggregated_data(file_name, solution_space, 
                    scenario, forecastResultIndex, variable,
                    x_axis_label, y_axis_label, title, label_title,
                    actual_file_name, divisor)

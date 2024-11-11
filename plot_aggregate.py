import matplotlib.pyplot as plt
import pandas as pd
import json
from datetime import datetime
from json_data_io import readJsonData
from text_file_data_io import write_json_to_textfile
from read_hfpt_variable_wells_result import get_values_wells_for_facilities

def plot_aggregated_data(file_name, solution_space, 
                        scenario, variable,
                        x_axis_label, y_axis_label, title, label_title,
                        divisor, profile_type, 
                        solution_space_hfpt, facilities, scenario_hfpt):
    # Load the JSON data from a file
    json_data = readJsonData(file_name)

    # Extracting the relevant data
    variable_data = json_data[scenario][solution_space][variable]
    x_values = [datetime.strptime(date, '%d/%m/%Y').strftime('%Y-%m-%d') for date in variable_data["x"]]
    y_values = [value / divisor for value in  variable_data["y"]]
    

    y_actual = get_values_wells_for_facilities(facilities, scenario_hfpt, profile_type, solution_space_hfpt, 2024, 2070)

    # Plotting the data
    plt.figure(figsize=(10, 5))
    #plt.plot(x_values, y_values, marker='o', linestyle='-', color='b')
    plt.plot(x_values, y_values, label=label_title)

    y_actual = y_actual[:-1]

    y_actual = [value / divisor for value in  y_actual]
    plt.plot(x_values, y_actual, label="Third Party")


    plt.legend()

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
solution_space = "POTENTIAL2P_2C"
solution_space_hfpt = "POTENTIAL"
scenario = "2P_2C" 
variable = "oilRate"
profile_type = "Oil (b/d)"
x_axis_label = "Production Date"
y_axis_label = "Produced Oil (Mbbl/d)"
title = "Produced Oil"
label_title = "Apex"
divisor = 1000
scenario_hfpt = "Base Case"
facilities = ["ABU_FS1", "ABU_FS2", "ABU_FS3", "ABU_FS4", "ABU_FS5", "REO_GP1", "REO_GP3"]
plot_aggregated_data(file_name, solution_space, 
                    scenario, variable,
                    x_axis_label, y_axis_label, title, label_title,
                    divisor, profile_type, solution_space_hfpt,
                    facilities, scenario_hfpt)

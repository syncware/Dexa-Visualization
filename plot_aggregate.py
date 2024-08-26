import matplotlib.pyplot as plt
import json
from datetime import datetime

# Load the JSON data from a file
with open('chat_data.json', 'r') as file:
    json_data = json.load(file)

# Extracting the relevant data
oil_rate_data = json_data["data"]["1"]["1P_1C"]["potential"]["oilRate"]
x_values = [datetime.strptime(date, "%Y-%m-%dT%H:%M:%S.%fZ") for date in oil_rate_data["x"]]
y_values = oil_rate_data["y"]

# Plotting the data
plt.figure(figsize=(10, 5))
#plt.plot(x_values, y_values, marker='o', linestyle='-', color='b')
plt.plot(x_values, y_values, label='oilRate')

# Adding title and labels
plt.title('Oil Rate Over Time')
plt.xlabel('Date')
plt.ylabel(f'Oil Rate ({json_data["units"]["oilRate"]})')

# Display the plot
plt.grid(True)
plt.xticks(rotation=45)
plt.tight_layout()
plt.show(block=True)

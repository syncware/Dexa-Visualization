import json
import matplotlib.pyplot as plt

# Load the JSON data from a file
with open('chat_data.json', 'r') as file:
    json_data = json.load(file)

# Access the data
#data = json_data['data']['1']['1P_1C']['potential']
data = json_data['data']['1']['1P_1C']['potential']

# Parse the JSON data
#data = json.loads(json_data)

# Loop through the 'oilRate' list and plot each series
oilRate = data['oilRate']
for entry in oilRate:
    x = entry['x']
    y = entry['y']
    
    # Convert x (datetime strings) to a more suitable format for plotting
    x = [date[:10] for date in x]  # Keep only the date part (YYYY-MM-DD)

    plt.ion()

    # Plot the data
    plt.plot(x, y, label=entry['name'])

# Customize the plot
plt.xlabel('Date')
plt.ylabel('Y Values')
plt.title('Oil Rate Forecast')
plt.xticks(rotation=45)
plt.legend()

# Show the plot
plt.tight_layout()
plt.show(block=True)

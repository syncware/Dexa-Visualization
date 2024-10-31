import json
# Step 1: Read the data from the file
#file_path = 'oIl_rate group_1.txt'  # replace with your actual file path

def read_text_file(file_path):
    # Initialize lists for x and y
    x = []
    y = []

    # Step 2: Open and read the file
    with open(file_path, 'r') as file:
        for line in file:
            # Step 3: Split each line into x and y components
            values = line.split()
            x_value = "31/12/" + values[0].split('.')[0]  # First column is x
            y_value = float(values[1])  # Second column is y
            
            # Append the values to the respective lists
            if x_value not in x:
                x.append(x_value)
                y.append(y_value)

    return {
        "x": x,
        "y": y
    }

def dump_json_to_textfile(file_path, json_data):
    with open(file_path, "w") as file:
        json.dump(json_data, file, indent=4)

def write_json_to_textfile(file_path, json_data):
    with open(file_path, "w") as file:
        # Writing the header
        file.write("x\t\ty\n")
    
        # Writing the data row by row
        for entry in json_data:
            file.write(f"{entry['x']}\t{entry['y']}\n")

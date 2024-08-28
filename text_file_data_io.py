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
            x_value = float(values[0])  # First column is x
            y_value = float(values[1])  # Second column is y
            
            # Append the values to the respective lists
            x.append(x_value)
            y.append(y_value)

    return {
        "x": x,
        "y": y
    }

file_path = 'oIl_rate group_1.txt'
xy = read_text_file(file_path)
print("x:", xy["x"])
print("y:", xy["y"])


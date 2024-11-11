import pandas as pd

def get_column_names(file_path, sheet_name):

    # Load only the header (first row) to get the column names
    df = pd.read_excel(file_path, sheet_name=sheet_name, nrows=0)

    # Get column names as a list
    column_names = df.columns.tolist()

    return column_names

def read_spread_sheet_data(file_path, sheet_name, columns_to_read):
    # Load the Excel file and specify the sheet name
    excel_data = pd.read_excel(file_path, sheet_name=sheet_name)

    # Read specific columns by name
    # Replace 'Column1' and 'Column2' with the names of your columns
    # selected_columns = excel_data[columns_to_read]

    results = []
    n = len(columns_to_read)
    for column_to_read in columns_to_read:
        results.append(excel_data[column_to_read].tolist())

    return results


def read_spread_sheet_data_2(file_path, sheet_name, columns_to_read):
    # Load the Excel file and specify the sheet name
    excel_data = pd.read_excel(file_path, sheet_name=sheet_name)
    
    # Initialize a dictionary to store the results
    results = {}
    
    # Extract each column and store it in the results dictionary
    for column in columns_to_read:
        results[column] = excel_data[column].tolist()

    return results

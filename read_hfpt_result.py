from spreadsheet_io import read_spread_sheet_data_2
from json_data_io import readJsonData, writeJsonData

def get_result_columns(fixed_columns_to_read, start_year, end_year):

    year_list = [f"Y{year}" for year in range(start_year, end_year + 1)]

    result_columns = fixed_columns_to_read + year_list

    return result_columns

    

def fetch_write_hfpt_result(file_path, sheet_name, columns_to_read, hfpt_result_file_path):

    raw_hfpt_result = read_spread_sheet_data_2(file_path, sheet_name, columns_to_read)

    
    writeJsonData(hfpt_result_file_path, raw_hfpt_result)


file_path = 'files/SPDC Forecast Outputs_PIVOT_v2.xlsx'
sheet_name = 'Forecast Outputs'
fixed_columns_to_read = ['UniqueID', 'Reservoir', 'Well', 'String', 'Project', 'Project_Code','Facilities' ,'Case',
                         'TYPE', 'PROFILETYPE']
start_year = 2024
end_year = 2070
hfpt_result_file_path = 'files/hfpt_results.json'

result_columns = get_result_columns(fixed_columns_to_read, start_year, end_year)

fetch_write_hfpt_result(file_path, sheet_name, result_columns, hfpt_result_file_path)
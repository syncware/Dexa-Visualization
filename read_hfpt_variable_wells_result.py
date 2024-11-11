from json_data_io import readJsonData
from text_file_data_io import dump_json_to_textfile

def get_years_of_forecast(start_year, end_year):

    year_list = [f"Y{year}" for year in range(start_year, end_year + 1)]

    return year_list

def get_unique_modules_for_facility(data, facility):
    modules = data["UniqueID"]
    facilities = data["Facilities"]
    
    # Use a set to keep only unique wells for the specified facility
    unique_wells = {modules[i] for i in range(len(facilities)) if facilities[i] == facility}
    
    return list(unique_wells)

def get_values_per_well_internal(data, module, facility, case, profile_type, solution_space, number_columns):
    # Get indexes where all conditions match
    indexes = [
        i for i in range(len(data["UniqueID"]))
        if data["UniqueID"][i] == module and
           data["Facilities"][i] == facility and
           data["Case"][i] == case and
           data["TYPE"][i] == solution_space and
           data["PROFILETYPE"][i] == profile_type
    ]
    
    # Extract values for each number column at the matched indexes
    # results = {col: [data[col][i] for i in indexes] for col in number_columns}
    results = [data[col][indexes[0]] for col in number_columns] if indexes else []

    return results

def get_values_per_well(module, facility, case, profile_type, solution_space, start_year, end_year):

    file_name = "files/hfpt_results.json"
    data = readJsonData(file_name)

    number_columns = get_years_of_forecast(start_year, end_year)

    # Extract values for each number column at the matched indexes
    # results = {col: [data[col][i] for i in indexes] for col in number_columns}
    results = get_values_per_well_internal(data, module, facility, case, profile_type, solution_space, number_columns)

    
    return results


def get_values_wells_per_facility(facility, case, profile_type, solution_space, start_year, end_year):

    file_name = "files/hfpt_results.json"
    data = readJsonData(file_name)
    unique_IDs = get_unique_modules_for_facility(data, facility)

    number_columns = get_years_of_forecast(start_year, end_year)

    aggregated_values = []
    i = -1
    for unique_ID in unique_IDs:

        i = i + 1

        results = get_values_per_well_internal(data, unique_ID, facility, case, profile_type, solution_space, number_columns)

        if i == 0:
            for result in results:
                aggregated_values.append(result)
        else:
            j = -1
            for result in results:
                j = j + 1
                aggregated_values[j] = aggregated_values[j] + result
    
    return aggregated_values


def get_values_wells_for_facilities(facilities, case, profile_type, solution_space, start_year, end_year):

    file_name = "files/hfpt_results.json"
    data = readJsonData(file_name)
    aggregated_values = []
    number_columns = get_years_of_forecast(start_year, end_year)
    i = -1

    for facility in facilities:
        unique_IDs_per_facility = get_unique_modules_for_facility(data, facility)

        for unique_ID in unique_IDs_per_facility:

            i = i + 1

            results = get_values_per_well_internal(data, unique_ID, facility, case, profile_type, solution_space, number_columns)

            if i == 0:
                for result in results:
                    aggregated_values.append(result)
            else:
                j = -1
                for result in results:
                    j = j + 1
                    aggregated_values[j] = aggregated_values[j] + result
    
    return aggregated_values




# Specify the parameters

module = "FO26006T_FO26 G10X_P13"
facility = "ABU_FS1"
case = "Base Case"
profile_type = "Oil (b/d)"
solution_space = "POTENTIAL"

start_year = 2024
end_year = 2070

# results = get_values_per_well(module, facility, case, profile_type, solution_space, start_year, end_year)
# dump_json_to_textfile(module + ".json", results)
# print(results)


# results = get_values_wells_per_facility(facility, case, profile_type, solution_space, start_year, end_year)
# print(results)

# facilities = ["ABU_FS1", "ABU_FS2", "ABU_FS3", "ABU_FS4", "ABU_FS5", "REO_GP1", "REO_GP3"]
# results = get_values_wells_for_facilities(facilities, case, profile_type, solution_space, start_year, end_year)
# print(results)


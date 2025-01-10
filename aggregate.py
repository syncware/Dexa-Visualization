from datetime import datetime

def is_contain_year(yr, yearly_dates):
    """
    Check if any date in the list contains the given year.

    Args:
        yr (int): The year to check.
        yearly_dates (list): A list of date strings or datetime objects.

    Returns:
        bool: True if the year is found, False otherwise.
    """
    for date in yearly_dates:
        # Convert to datetime object if it's a string
        if isinstance(date, str):
            date = datetime.strptime(date, '%Y-%m-%d')
        if date.year == yr:
            return True
    return False

# # Example Usage
# dates = ['2023-01-01', '2024-05-15', '2025-07-20']
# year_to_check = 2024
# print(is_contain_year(year_to_check, dates))  # Output: True


def get_yearly_dates(dates):
    """
    Get a list of dates ensuring only one date per year is included.

    Args:
        dates (list): A list of date strings in 'YYYY-MM-DD' format or datetime objects.

    Returns:
        list: A list of unique yearly dates.
    """
    yearly_dates = []
    
    for i, date in enumerate(dates):
        # Convert string to datetime if necessary
        if isinstance(date, str):
            date = datetime.strptime(date, '%Y-%m-%d')
        
        if i == 0:
            yearly_dates.append(date)
        else:
            yr = date.year
            if not is_contain_year(yr, yearly_dates):
                yearly_dates.append(date)
    
    return yearly_dates

# # Example Usage
# dates = ['2023-01-01', '2023-06-15', '2024-05-15', '2025-07-20', '2025-08-10']
# result = get_yearly_dates(dates)
# print([d.strftime('%Y-%m-%d') for d in result])
# # Output: ['2023-01-01', '2024-05-15', '2025-07-20']


def convert_monthly_to_yearly(yearly_dates, dates, rates):
    """
    Convert monthly rates into yearly averages.

    Args:
        yearly_dates (list): List of unique yearly dates (datetime objects).
        dates (list): List of all dates (datetime objects).
        rates (list): List of corresponding rates for the dates.

    Returns:
        list: Yearly rates calculated based on the provided monthly rates.
    """
    yearly_rates = [0] * len(yearly_dates)

    for i, yearly_date in enumerate(yearly_dates):
        volume = 0
        dt30 = 30  # Days in a standard month
        prodays_per_year = 0
        
        for j, date in enumerate(dates):
            if date.year == yearly_date.year:
                if rates[j] > 0:
                    prodays_per_year += dt30
                volume += rates[j] * dt30

        if prodays_per_year > 0:
            yearly_rates[i] = volume / 360  # Using fixed 360 days

    return yearly_rates

# # Example Usage
# yearly_dates = [datetime(2023, 1, 1), datetime(2024, 1, 1), datetime(2025, 1, 1)]
# dates = [
#     datetime(2023, 1, 1), datetime(2023, 2, 1), datetime(2024, 3, 1),
#     datetime(2025, 4, 1), datetime(2025, 5, 1)
# ]
# rates = [10, 20, 30, 40, 50]

# result = convert_monthly_to_yearly(yearly_dates, dates, rates)
# print(result)
# # Example Output: [1.6666666666666667, 2.5, 7.5]
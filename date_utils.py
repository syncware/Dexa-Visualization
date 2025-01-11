from datetime import datetime, timedelta

def date_array(start_date, end_date, interval):
    """
    Generate a list of dates between start_date and end_date at a given interval.

    Args:
        start_date (datetime): The start date.
        end_date (datetime): The end date.
        interval (str): The interval for increment ('days', 'weeks', 'months').

    Returns:
        list: A list of datetime objects.
    """
    def add_interval(date, interval):
        if interval == 'days':
            return date + timedelta(days=1)
        elif interval == 'weeks':
            return date + timedelta(weeks=1)
        elif interval == 'months':
            # Add a month while accounting for varying days in months
            month = date.month + 1
            year = date.year + (month - 1) // 12
            month = (month - 1) % 12 + 1
            day = min(date.day, [31, 28 + (year % 4 == 0 and (year % 100 != 0 or year % 400 == 0)), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31][month - 1])
            return datetime(year, month, day)
        else:
            raise ValueError("Invalid interval. Use 'days', 'weeks', or 'months'.")

    # Ensure both start_date and end_date are datetime.datetime objects
    if not isinstance(start_date, datetime):
        start_date = datetime.combine(start_date, datetime.min.time())
    if not isinstance(end_date, datetime):
        end_date = datetime.combine(end_date, datetime.min.time())

    dates = [start_date]
    while dates[-1] < end_date:
        next_date = add_interval(dates[-1], interval)
        if next_date > end_date:
            break
        dates.append(next_date)

    return dates

# # Example Usage
# start_date = datetime(2023, 1, 1)
# end_date = datetime(2023, 1, 10)
# interval = 'days'

# result = date_array(start_date, end_date, interval)
# print([d.strftime('%Y-%m-%d') for d in result])
# # Output: ['2023-01-01', '2023-01-02', '2023-01-03', ..., '2023-01-10']
import math

def get_decline_factor_exponential(initial_rate, aband_rate, init_cum_prod, ur, cum_days, is_rate_cum=True):
    """
    Calculate the decline factor for an exponential decline model.

    Args:
        initial_rate (float): The initial production rate.
        aband_rate (float): The abandonment rate.
        init_cum_prod (float): Initial cumulative production.
        ur (float): Ultimate recovery.
        cum_days (int): Cumulative production days.
        is_rate_cum (bool, optional): If True, calculate based on rate and cumulative. Defaults to True.

    Returns:
        float: The calculated decline factor, or -9999 if inputs are invalid.
    """
    decline_factor = -9999  # Default value for invalid input
    
    if is_rate_cum:
        if (ur - init_cum_prod) > 0:
            decline_factor = (initial_rate - aband_rate) / (ur - init_cum_prod)
    else:
        if aband_rate == 0:
            aband_rate = 10**-8  # Avoid division by zero
        if cum_days > 0:
            decline_factor = -1 * math.log(aband_rate / initial_rate) / cum_days
    
    return decline_factor

# # Example Usage
# initial_rate = 1000
# aband_rate = 100
# init_cum_prod = 5000
# ur = 10000
# cum_days = 365
# is_rate_cum = True

# result = get_decline_factor_exponential(initial_rate, aband_rate, init_cum_prod, ur, cum_days, is_rate_cum)
# print(result)

def get_decline_factor_linear(initial_rate, aband_rate, init_cum_prod, ur, cum_days, is_rate_cum=True):
    """
    Calculate the decline factor for a linear decline model.

    Args:
        initial_rate (float): The initial production rate.
        aband_rate (float): The abandonment rate.
        init_cum_prod (float): Initial cumulative production.
        ur (float): Ultimate recovery.
        cum_days (int): Cumulative production days.
        is_rate_cum (bool, optional): If True, calculate based on rate and cumulative. Defaults to True.

    Returns:
        float: The calculated decline factor, or -9999 if inputs are invalid.
    """
    decline_factor = -9999  # Default value for invalid input
    
    if is_rate_cum:
        if (ur - init_cum_prod) != 0:
            decline_factor = (aband_rate - initial_rate) / (ur - init_cum_prod)
    else:
        if cum_days > 0:
            decline_factor = (aband_rate - initial_rate) / cum_days
    
    return decline_factor

# # Example Usage
# initial_rate = 1000
# aband_rate = 100
# init_cum_prod = 5000
# ur = 10000
# cum_days = 365
# is_rate_cum = True

# result = get_decline_factor_linear(initial_rate, aband_rate, init_cum_prod, ur, cum_days, is_rate_cum)
# print(result)


def exponential_decline(initial_rate, rate_of_change, cum_prod, plateau_cum_prod, cum_days, is_rate_cum=True):
    """
    Calculate the current rate for an exponential decline model.

    Args:
        initial_rate (float): The initial production rate.
        rate_of_change (float): The rate of change in production.
        cum_prod (float): The cumulative production.
        plateau_cum_prod (float): The plateau cumulative production.
        cum_days (int): Cumulative production days.
        is_rate_cum (bool, optional): If True, use rate and cumulative production. Defaults to True.

    Returns:
        float: The current production rate.
    """
    cumprod_no_plateau = cum_prod - plateau_cum_prod
    
    if rate_of_change == -9999:
        current_rate = 0
    elif cumprod_no_plateau <= 0:
        current_rate = initial_rate
    elif not is_rate_cum:
        current_rate = initial_rate * math.exp(-rate_of_change * cum_days)
    else:
        current_rate = initial_rate - rate_of_change * cumprod_no_plateau
    
    return current_rate

# # Example Usage
# initial_rate = 1000
# rate_of_change = 0.02
# cum_prod = 5000
# plateau_cum_prod = 2000
# cum_days = 365
# is_rate_cum = True

# result = exponential_decline(initial_rate, rate_of_change, cum_prod, plateau_cum_prod, cum_days, is_rate_cum)
# print(result)

def exponential_decline2(initial_rate, rate_of_change, cum_prod, cum_days, is_rate_cum=True):
    """
    Calculate the current rate for an exponential decline model (variant 2).

    Args:
        initial_rate (float): The initial production rate.
        rate_of_change (float): The rate of change in production.
        cum_prod (float): The cumulative production.
        cum_days (int): Cumulative production days.
        is_rate_cum (bool, optional): If True, use rate and cumulative production. Defaults to True.

    Returns:
        float: The current production rate.
    """
    if rate_of_change == -9999:
        current_rate = 0
    elif not is_rate_cum:
        current_rate = initial_rate * math.exp(-rate_of_change * cum_days)
    else:
        current_rate = initial_rate - rate_of_change * cum_prod
    
    return current_rate

# # Example Usage
# initial_rate = 1000
# rate_of_change = 0.02
# cum_prod = 5000
# cum_days = 365
# is_rate_cum = True

# result = exponential_decline2(initial_rate, rate_of_change, cum_prod, cum_days, is_rate_cum)
# print(result)


def linear_decline(initial_rate, rate_of_change, cum_prod, plateau_cum_prod, cum_days=0):
    """
    Calculate the current rate for a linear decline model.

    Args:
        initial_rate (float): The initial production rate.
        rate_of_change (float): The rate of change in production.
        cum_prod (float): The cumulative production.
        plateau_cum_prod (float): The plateau cumulative production.
        cum_days (int, optional): Cumulative production days. Defaults to 0.

    Returns:
        float: The current production rate.
    """
    cumprod_no_plateau = cum_prod - plateau_cum_prod
    
    if rate_of_change == -9999:
        current_rate = 0
    elif cumprod_no_plateau < 0:
        current_rate = initial_rate
    else:
        current_rate = rate_of_change * cum_days + initial_rate
    
    return current_rate

# # Example Usage
# initial_rate = 1000
# rate_of_change = -10
# cum_prod = 5000
# plateau_cum_prod = 2000
# cum_days = 365

# result = linear_decline(initial_rate, rate_of_change, cum_prod, plateau_cum_prod, cum_days)
# print(result)

import matplotlib.pyplot as plt

series1 = [
        0,
            338.22,
            509.7,
            436.18,
            374.43,
            320.74,
            275.64,
            236.88,
            203.54,
            174.87,
            150.29,
            55.937,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0
        ]

series2 = [
         0,
        340.63176630177213,
        518.4636915514765,
        444.7195106842789,
        381.4644041734755,
        327.2064484589942,
        280.66592516050355,
        240.74513786996218,
        206.5025220816627,
        177.13043762122032,
        151.93611978975053,
        67.66086063626094,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
        ]


x_values_series1 = [i * 360 for i in range(len(series1))]
x_values_series2 = [i * 360 for i in range(len(series2))]

#series2 = [value / 1000 for value in  series2]

plt.figure(figsize=(10, 5))
plt.plot(x_values_series1, series1, label="HFPT")
plt.plot(x_values_series2, series2, label="CPP Dexa")

plt.legend()

# Display the plot
plt.grid(True)
plt.xticks(rotation=45)
plt.tight_layout()
plt.show(block=True)
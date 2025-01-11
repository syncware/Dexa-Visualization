import tkinter as tk
from tkinter import Tk, Canvas, Frame, Scrollbar, ttk
import matplotlib.pyplot as plt
from matplotlib.widgets import Button
from json_data_io import readJsonData

forecast_well_by_well_output_data_file_path = "forecast_well_by_well_output_data_yearly.json"
hfpt_forecastResults_well_by_well_file_path = "hfpt_forecastResults_well_by_well.json"

monthly_forecastResults_cpp = readJsonData(forecast_well_by_well_output_data_file_path)
hfpt_forecastResults = readJsonData(hfpt_forecastResults_well_by_well_file_path)

module_names = list(hfpt_forecastResults.keys())

n_module_names = len(module_names)

current_column_index = 0
variable_name_hfpt = "gasRatesYearly"
variable_name_dexa = "gasRate"
x_axis_label = "Days"
y_axis_label = "Gas Prod"
divisor_dexa = 1000
divisor_hfpt = 1

# Plotting function
def plot_columns(index, ax):
    ax.clear()  # Clear the chart area only
    module_name = module_names[index]

    y_values_dexa = [value / (divisor_dexa) for value in  monthly_forecastResults_cpp[module_name][variable_name_dexa]]
    y_values_hfpt = [value / divisor_hfpt for value in  hfpt_forecastResults[module_name][variable_name_hfpt]]

    n_y_values_dexa = len(y_values_dexa)
    n_y_values_hfpt = len(y_values_hfpt)

    x_values_dexa = [i * 360 for i in range(n_y_values_dexa)]
    x_values_hfpt = [i * 360 for i in range(n_y_values_hfpt)]

    ax.plot(x_values_dexa, y_values_dexa, label="Dexa")
    ax.plot(x_values_hfpt, y_values_hfpt, label="HFPT")


    ax.set_title(module_name)

    ax.legend()
    plt.draw()  # Redraw the updated figure

# Button callbacks
def next_column(event):
    global current_column_index
    global variable_name_hfpt
    global variable_name_dexa
    global x_axis_label
    global y_axis_label
    global divisor_dexa
    global divisor_hfpt
    if current_column_index < n_module_names - 1:
        current_column_index += 1
        plot_columns(current_column_index, ax)

def prev_column(event):
    global current_column_index
    global variable_name_hfpt
    global variable_name_dexa
    global x_axis_label
    global y_axis_label
    global divisor_dexa
    global divisor_hfpt
    if current_column_index > 0:
        current_column_index -= 1
        plot_columns(current_column_index, ax)

def view_data(event):
    # Create a new Tkinter window
    root = Tk()
    root.title(f"Data for Module: {module_names[current_column_index]}")

    # Maximize window
    screen_width = root.winfo_screenwidth()
    screen_height = root.winfo_screenheight()
    root.geometry(f"{screen_width}x{screen_height}")

    # Configure root to expand content on resize
    root.rowconfigure(0, weight=1)
    root.columnconfigure(0, weight=1)

    # Create a frame for the table
    frame = Frame(root)
    frame.grid(row=0, column=0, sticky="nsew")

    # Configure frame to expand
    frame.rowconfigure(0, weight=1)
    frame.columnconfigure(0, weight=1)

    # Create a canvas and scrollbar
    canvas = Canvas(frame)
    scrollbar = Scrollbar(frame, orient="vertical", command=canvas.yview)
    canvas.configure(yscrollcommand=scrollbar.set)

    # Place canvas and scrollbar
    canvas.grid(row=0, column=0, sticky="nsew")
    scrollbar.grid(row=0, column=1, sticky="ns")

    # Create a scrollable frame inside the canvas
    scrollable_frame = Frame(canvas)
    scrollable_frame.bind(
        "<Configure>",
        lambda e: canvas.configure(scrollregion=canvas.bbox("all"))
    )
    canvas.create_window((0, 0), window=scrollable_frame, anchor="nw")

    # Get data for the current module
    module_name = module_names[current_column_index]
    y_values_dexa = [value / divisor_dexa for value in monthly_forecastResults_cpp[module_name][variable_name_dexa]]
    y_values_hfpt = [value / divisor_hfpt for value in hfpt_forecastResults[module_name][variable_name_hfpt]]
    x_values_dexa = [i * 30 for i in range(len(y_values_dexa))]
    x_values_hfpt = [i * 360 for i in range(len(y_values_hfpt))]

    # Create a table
    columns = ["Index", "Dexa (x)", "Dexa (y)", "HFPT (x)", "HFPT (y)"]
    tree = ttk.Treeview(scrollable_frame, columns=columns, show="headings")
    for col in columns:
        tree.heading(col, text=col)
        tree.column(col, anchor="center", width=100)

    # Add data to the table
    max_rows = max(len(x_values_dexa), len(x_values_hfpt))
    for i in range(max_rows):
        tree.insert(
            "",
            "end",
            values=(
                i,
                x_values_dexa[i] if i < len(x_values_dexa) else "",
                y_values_dexa[i] if i < len(y_values_dexa) else "",
                x_values_hfpt[i] if i < len(x_values_hfpt) else "",
                y_values_hfpt[i] if i < len(y_values_hfpt) else "",
            ),
        )

    # Configure table size to match window
    def adjust_table_size(event):
        tree.pack(fill="both", expand=True)
        #tree.config(height=event.height, width=event.width)
        tree.config(height=screen_height, width=screen_width)

    # Bind resize event to adjust the table
    root.bind("<Configure>", adjust_table_size)
    tree.pack(fill="both", expand=True)

    root.mainloop()

def show_dropdown():
    # Create a Tkinter window
    dropdown_window = tk.Tk()
    dropdown_window.title("Select Module")
    
    # Variable to store the selected module
    selected_module = tk.StringVar()
    selected_module.set(module_names[0])  # Set default value

    # Create dropdown menu
    dropdown = ttk.Combobox(dropdown_window, textvariable=selected_module, values=module_names)
    dropdown.pack(pady=10)

    def confirm_selection():
        global current_column_index
        global variable_name_hfpt
        global variable_name_dexa
        global x_axis_label
        global y_axis_label
        global divisor_dexa
        global divisor_hfpt
        s_module = selected_module.get()
        current_column_index = module_names.index(s_module)
        plot_columns(current_column_index, ax)
        dropdown_window.destroy()

    # Confirm button
    confirm_button = ttk.Button(dropdown_window, text="Confirm", command=confirm_selection)
    confirm_button.pack(pady=10)

    dropdown_window.mainloop()


# Initial plot
fig, ax = plt.subplots()
plt.subplots_adjust(bottom=0.2)  # Leave space for buttons
plot_columns(current_column_index, ax)

# Buttons
axprev = plt.axes([0.5, 0.05, 0.1, 0.075])  # Button for 'Back'
axnext = plt.axes([0.61, 0.05, 0.1, 0.075])  # Button for 'Next'
axview = plt.axes([0.72, 0.05, 0.1, 0.075])  # Button for 'View Data'


btn_next = Button(axnext, "Next")
btn_prev = Button(axprev, "Back")
btn_view = Button(axview, "View Data")

btn_next.on_clicked(next_column)
btn_prev.on_clicked(prev_column)
btn_view.on_clicked(view_data)

# Dropdown
#axdropdown = plt.axes([0.1, 0.05, 0.3, 0.075])  # Position for the dropdown

# Add a button in the matplotlib figure to trigger the dropdown
axdropdown = plt.axes([0.1, 0.05, 0.2, 0.075])
btn_dropdown = Button(axdropdown, "Select Module")
btn_dropdown.on_clicked(lambda event: show_dropdown())

plt.show()
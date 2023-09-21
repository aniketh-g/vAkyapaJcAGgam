# SPA Plotter
This utility is used to generate tables of longitude vs Earth-Sun distance and thus plot the geocentric orbit of the Sun.

To plot orbits:
1. Enter the list of start dates and the step interval in `date_list_generator.py`. This will prepare lists of dates for one year starting from the date at the desired interval.
2. Run `make plot`, and the code in `simultaneous_plotter.ipynb`. (`plotter.py` is not functioning as expected, likely due to a python bug).
3. This will create a graph in the `graphs` directory. Some example graphs are already present.
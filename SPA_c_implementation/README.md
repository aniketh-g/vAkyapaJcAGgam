# Yogyādivākya generator
To generate Yogyādivākya-s for a given AD year using longitudes computed according to the Solar Positioning Algorithm:
1. In the file `yogyadi_vakya_calculator.c`, set the Julian Day to a day after Meṣasaṅkrānti on the desired AD year
2. Run `make generate_yogyadi_vakyas`

This generates the vākya-s for the year in the `tables` directory. The notebook `yogyadi_vakya_variation_plots.ipynb` contains graphs plotted from these tables to analyze the short-term and long-term variations in the vākya-s. The table `siddhanta_yogyadi_vakyas.csv` was generated in `siddhanta_spa_comparison_plots.ipynb`. It is a list of vakya-s as computed by the siddhanta algorithm.

# Comparisons between Siddhānta and modern algorithms
The notebook `siddhanta_spa_comparison_plots.ipynb` contains different types of comparisons between the predicted values of Siddhānta and SPA over different years.
## Ayanāṃśa
The `spa.c` program was modified to incorporate the Lahiri Ayanāṃśa. The algorithm used for ayanacalana is from the paper `Determination of the date of the First Point of Aries held fixed using a combined method of Astronomy and Astrology`
## Conversions between Ahargaṇa and Julian Day
The Siddhānta model employs Ahargaṇa for computations whereas SPA requires the Julian Day. The formula for converting between the epochs was taken as `Kali Ahargana Date = Julian Date - 588464.54` according to [this article](https://medium.com/thoughts-on-jyotish/the-kali-epoch-and-ahargana-part-6-utilising-julian-day-number-to-determine-ahargana-9068deac032c).

# SPA Plotter
This utility is used to generate tables of longitude vs Earth-Sun distance and thus plot the geocentric orbit of the Sun.

To plot orbits:
1. Enter the list of start dates and the step interval in `date_list_generator.py`. This will prepare lists of dates for one year starting from the date at the desired interval.
2. Run `make plot`, and the code in `simultaneous_plotter.ipynb`. (`plotter.py` is not functioning as expected, likely due to a python bug).
3. This will create a graph in the `graphs` directory. Some example graphs are already present.
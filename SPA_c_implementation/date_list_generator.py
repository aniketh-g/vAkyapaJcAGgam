import astropy.time
import math
import csv

date_list_csv = "outputs/date_list.csv"

start_dates = [astropy.time.Time("2023-03-21 00:00:00", scale="utc"),
               astropy.time.Time("3523-03-21 00:00:00", scale="utc"),
               astropy.time.Time("3523-03-21 00:00:00", scale="utc"),
               astropy.time.Time("3523-03-21 00:00:00", scale="utc")]
m = []
n = 1 #interval in days
for sd in start_dates:
    with open("./outputs/date_list_%s.csv"%f'{sd.ymdhms.year:04}', 'w', newline="", ) as date_list_csv:
        data = [[(sd+i*n).ymdhms.year,(sd+i*n).ymdhms.month,(sd+i*n).ymdhms.day,(sd+i*n).ymdhms.hour,(sd+i*n).ymdhms.minute,(sd+i*n).ymdhms.second] for i in range(math.floor(365/n))]
        csv.writer(date_list_csv).writerows(data)
        m.append([len(data), sd.ymdhms.year])


with open("./outputs/list_of_years.txt", 'w') as list_of_years_csv:
    for sd in start_dates:
        list_of_years_csv.write("./outputs/date_list_%s.csv\n"%f'{sd.ymdhms.year:04}')

with open("./outputs/plot_list.txt", 'w') as list_of_years_csv:
    for sd in start_dates:
        list_of_years_csv.write("./outputs/plot_data_%s.csv\n"%f'{sd.ymdhms.year:04}')
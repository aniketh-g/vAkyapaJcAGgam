import astropy.time
import math
import csv

date_list_csv = ".outputs/date_list.csv"

start_dates = [astropy.time.Time("2001-03-21 0:00:00", scale="utc"),
        #        astropy.time.Time("1701-03-21 0:00:00", scale="utc"),
               astropy.time.Time("1501-03-21 0:00:00", scale="utc"),
        #        astropy.time.Time("1001-03-21 0:00:00", scale="utc"),
               astropy.time.Time("0501-03-21 0:00:00", scale="utc")] #8h41m11.97s after sunrise in Ujjain which is 5h3m9.24s ahead of greenwich
m = []
n = 1 #interval in days
for sd in start_dates:
    with open("./outputs/date_list_%s.csv"%f'{sd.ymdhms.year:04}', 'w', newline="", ) as date_list_csv:
        data = [[(sd+i*n).ymdhms.year,(sd+i*n).ymdhms.month,(sd+i*n).ymdhms.day,(sd+i*n).ymdhms.hour,(sd+i*n).ymdhms.minute,(sd+i*n).ymdhms.second] for i in range(math.floor(365/n))]
        csv.writer(date_list_csv).writerows(data)
        m.append([len(data), sd.ymdhms.year])

with open("./outputs/list_of_years.txt", 'w') as list_of_years_csv:
        [list_of_years_csv.write("./outputs/date_list_%s.csv\n"%f'{sd.ymdhms.year:04}') for sd in start_dates]
with open("./outputs/plot_list.txt", 'w') as list_of_years_csv:
        [list_of_years_csv.write("./tables/spa_the_rs_%s.csv\n"%f'{sd.ymdhms.year:04}') for sd in start_dates]
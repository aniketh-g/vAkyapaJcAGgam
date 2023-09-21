#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "spa.h"  //include the SPA header file

#define MAXCHAR 1000

int main (int argc, char *argv[])
{
    spa_data spa;  //declare the SPA structure
    int result;
    float min, sec;

    //enter required input values into SPA structure
    spa.timezone      = 0;
    spa.delta_ut1     = 0;
    spa.delta_t       = 69.2;
    spa.longitude     = 0;
    spa.latitude      = 0;
    spa.elevation     = 0;
    spa.pressure      = 1013.25;
    spa.temperature   = 25;
    spa.slope         = 0;
    spa.azm_rotation  = 0;
    spa.atmos_refract = 0.5667;
    spa.function      = SPA_ALL;

    FILE *f_date_list, *f_plot_data, *f_list_of_years;
    char row[MAXCHAR];
    char *token;
    int year, month, day, hour, minute;
    double second;
    char date_list_name[MAXCHAR] = "./outputs/date_list_xxxx.csv";
    char plot_data_name[MAXCHAR] = "./outputs/plot_data_";
    char line[MAXCHAR];
    

    f_list_of_years = fopen("./outputs/list_of_years.txt","r");
    while(fgets(date_list_name, MAXCHAR, f_list_of_years)){
        strtok(date_list_name, "\n");
        for(int i=20;date_list_name[i] != '\0';i++){
            plot_data_name[i] = date_list_name[i];
        }
        
        f_date_list = fopen(date_list_name,"r");
        f_plot_data = fopen(plot_data_name, "w+");
        fprintf(f_plot_data,"theta,r\n");
        
        while (feof(f_date_list) != true)
        {
            //read data from data_list.csv
            fgets(row, MAXCHAR, f_date_list);
            if (feof(f_date_list)) break;
            token = strtok(row, ",");
            year = atoi(token);
            token = strtok(NULL, ",");
            month = atoi(token);
            token = strtok(NULL, ",");
            day = atoi(token);
            token = strtok(NULL, ",");
            hour = atoi(token);
            token = strtok(NULL, ",");
            minute = atoi(token);
            token = strtok(NULL, ",");
            second = atof(token);

            //enter required input values into SPA structure
            spa.year          = year;
            spa.month         = month;
            spa.day           = day;
            spa.hour          = hour;
            spa.minute        = minute;
            spa.second        = second;

            //call the SPA calculate function and pass the SPA structure
            result = spa_calculate(&spa);

            if (result == 0)  //check for SPA errors
            {
                fprintf(f_plot_data,"%f,%f\n", spa.alpha, spa.r);
                //display the results inside the SPA structure
                // printf("Longitude: %f degrees\n", spa.lamda);
                // printf("Right Ascension: %dd%dm%fs\n", (int) spa.alpha, (int) (60*(spa.alpha-(int) spa.alpha)), 60*(60*(spa.alpha-(int) spa.alpha)) - 60*((int) (60*(spa.alpha-(int) spa.alpha))) );
                // printf("Radius: %f\n", spa.r);

            } else printf("SPA Error Code: %d\n", result);
        }
        printf("Successfully generated "); puts(plot_data_name);
    }

    printf("Successfully computed longitudes and radii for all years\n");
    return 0;
}
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

    //location parameters
    spa.timezone      = 0;
    spa.delta_ut1     = 0;
    spa.delta_t       = 69.2; //2023AD
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
    double second;
    char date_list_name[MAXCHAR] = "./outputs/date_list_xxxx.csv";
    char plot_data_name[MAXCHAR] = "./tables/spa_the_rs_xxxx.csv";
    char line[MAXCHAR];
    

    f_list_of_years = fopen("./outputs/list_of_years.txt","r");
    while(fgets(date_list_name, MAXCHAR, f_list_of_years)){
        strtok(date_list_name, "\n");
        for(int i=20;date_list_name[i] != '\0';i++){
            plot_data_name[i] = date_list_name[i];
        }
        
        f_date_list = fopen(date_list_name,"r");
        f_plot_data = fopen(plot_data_name, "w+");
        fprintf(f_plot_data,"jd,theta_na,theta_sa,r\n");
        
        while (feof(f_date_list) != true)
        {
            //read data from data_list.csv
            fgets(row, MAXCHAR, f_date_list);
            if (feof(f_date_list)) break;

            //enter required input values into SPA structure
            spa.year          = atoi(strtok(row, ","));
            spa.month         = atoi(strtok(NULL, ","));
            spa.day           = atoi(strtok(NULL, ","));
            spa.hour          = atoi(strtok(NULL, ","));
            spa.minute        = atoi(strtok(NULL, ","));
            spa.second        = atof(strtok(NULL, ","));

            //call the SPA calculate function and pass the SPA structure

            if (spa_calculate(&spa, 'f') == 0)  fprintf(f_plot_data,"%f,%f,%f,%f\n", spa.jd, spa.lambda_na, spa.lambda, spa.r);
            else printf("SPA Error Code: %d\n", result);
        }
        printf("Successfully generated "); puts(plot_data_name);
    }

    printf("Successfully computed longitudes and radii for all years\n");
    return 0;
}
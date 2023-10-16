#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "spa.h"  //include the SPA header file
#include "useful_functions.c"

#define MAXCHAR 1000

int main (int argc, char *argv[])
{
    int result;
    float min, sec;

    //location parameters
    spa.timezone      = 0;
    spa.delta_ut1     = 0;
    spa.delta_t       = 69.2; //2023AD
    spa.longitude     = 75.7683;
    spa.latitude      = 0;
    spa.elevation     = 0;
    spa.pressure      = 1013.25;
    spa.temperature   = 25;
    spa.slope         = 0;
    spa.azm_rotation  = 0;
    spa.atmos_refract = 0.5667;
    spa.function      = SPA_ALL;

    FILE *f_plot_data;
    char plot_data_name[MAXCHAR] = "./tables/spa_longitudes_and_distances_jd";
    char julday[MAXCHAR];

    spa.jd = 2342072.736209;
    // set_to_target_na_longitude(0);
    float jd_start = spa.jd;
    sprintf(julday, "%f.csv", spa.jd);
    strcat(plot_data_name, julday);

    f_plot_data = fopen(plot_data_name, "w+");
    fprintf(f_plot_data,"jd,theta_na,theta_sa,r\n");

    //enter required input values into SPA structure
    for(; spa.jd <= jd_start+365*400; spa.jd+=5){
        //call the SPA calculate function and pass the SPA structure
        result = spa_calculate(&spa, 't');
        if (result == 0)  fprintf(f_plot_data,"%f,%f,%f,%f\n", spa.jd, spa.lambda_na, spa.lambda, spa.r);
        else printf("SPA Error Code: %d\n", result);
    }
    printf("Successfully generated "); puts(plot_data_name);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include "spa.h"  //include the SPA header file
#include "useful_functions.c"

#define MAXCHAR 1000

void print_vakyas(FILE *vakya_file){
    double longs[48];
    longs[0] = spa.lambda_na;
    double vakyas[48];
    vakyas[0]=0;
    int i = 0;
    // printf("Starting on JD = %f\n", spa.jd);
    // printf("On JD %f, True long = %fdeg\t ayanamsha = %fdeg\t", spa.jd, spa.lambda_na, spa.ayanamsha);
    spa_calculate(&spa, 't');
    fprintf(vakya_file, "%f,%f,%f,%f\n", spa.jd, spa.lambda_na, spa.lambda, spa.ayanamsha);
    // printf("vakyas[%d]=%fd or %dm%fs\n", i, vakyas[i], (int)floor(fabs(vakyas[i])*60), 60*(fabs(vakyas[i])*60-(int)floor(fabs(vakyas[i])*60)));
    for(i=1; i<=4; i++){
        spa.jd = spa.jd + 8;
        spa_calculate(&spa, 't');
        // printf("On JD %f, True long = %fdeg\t ayanamsha = %fdeg\t", spa.jd, spa.lambda_na, spa.ayanamsha);
        longs[i] = spa.lambda_na;
        vakyas[i] = limit_degrees(longs[i] - longs[i-1])-8;
        fprintf(vakya_file, "%f,%f,%f,%f\n", spa.jd, spa.lambda_na, spa.lambda, spa.ayanamsha);
        // printf("%f=[%d, %fs]\n", vakyas[i], (int)floor(fabs(vakyas[i])*60), 60*(fabs(vakyas[i])*60-(int)floor(fabs(vakyas[i])*60)));
    }
}

int main (int argc, char *argv[])
{
    int result;
    float min, sec;

    //location parameters
    spa.timezone      = 0;
    spa.delta_ut1     = 0;
    spa.delta_t       = 65;
    spa.longitude     = 75.7885;
    spa.latitude      = 0;
    spa.elevation     = 0;
    spa.pressure      = 1013.25;
    spa.temperature   = 25;
    spa.slope         = 0;
    spa.azm_rotation  = 0;
    spa.atmos_refract = 0.5667;
    spa.function      = SPA_ALL;

    spa.year          = 1532;
    spa.month         = 1;
    spa.day           = 8;
    spa.hour          = 0;
    spa.minute        = 0;
    spa.second        = 0;

    // spa_calculate(&spa, 'f');

    spa.jd = 2342488.5000000;
    set_to_target_na_longitude(0);
    // spa.jd = 2280344.75;
    
    FILE *vakya_csv;
    char file_path[MAXCHAR] = "./tables/spa_yogyadi_vakyas_1701AD.csv";

    vakya_csv = fopen(file_path, "w+");
    fprintf(vakya_csv,"jul_day,true_long (na),true_long (sa),ayanamsha\n");

    for(int i=0; i<=11; i++){
        set_to_target_na_longitude(i*30);
        print_vakyas(vakya_csv);
    }

    printf("\nSuccessfully computed sidereal longitudes\n");
    return 0;
}
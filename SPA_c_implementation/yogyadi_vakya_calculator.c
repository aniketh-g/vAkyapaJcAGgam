#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include "spa.h"  //include the SPA header file
#include "useful_functions.c"

#define MAXCHAR 1000
#define V fabs(vakyas[i])
#define MIN(v) (int)floor(V*60)
#define SEC(v) (int)floor((V*60-(int)floor(V*60))*60)
#define TRD(v) ((V*60-(int)floor(V*60))*60-(int)floor((V*60-(int)floor(V*60))*60))*60

void print_vakyas(FILE *vakya_file){
    double longs[48];
    longs[0] = spa.lambda_na;
    double vakyas[48];
    vakyas[0]=0;
    int i = 0;
    spa_calculate(&spa, 't');
    for(i=1; i<=4; i++){
        spa.jd = spa.jd + 8;
        spa_calculate(&spa, 't');
        longs[i] = spa.lambda_na;
        vakyas[i] = limit_degrees(longs[i] - longs[i-1])-8;
        if(vakyas[i] >= 0)
            fprintf(vakya_file, "%f,%f,%f,+,%d,%d,%f\n", spa.jd, spa.lambda_na, spa.ayanamsha, MIN(V), SEC(V), TRD(V));
        else
            fprintf(vakya_file, "%f,%f,%f,-,%d,%d,%f\n", spa.jd, spa.lambda_na, spa.ayanamsha, MIN(V), SEC(V), TRD(V));
        // printf("%f=[%dm, %ds, %ft]\n",vakyas[i], MIN(V), SEC(V), TRD(V));
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

    for(spa.jd = 2460048.5000000; spa.jd <= 2460048.5000000 + 365.26*61; spa.jd+=365/2){
        set_to_target_na_longitude(0);
        FILE *vakya_csv;
        char file_path[MAXCHAR];
        sprintf(file_path, "./yogyadi_tables/spa_yogyadi_vakyas_%dAD.csv", (int)(spa.jd/365.2422-4712));
        vakya_csv = fopen(file_path, "w+");
        fprintf(vakya_csv, "jul_day,true_long (na),true_long (sa),ayanamsha,vakya_sign,min,sec,trd\n");

        for(int i=0; i<=11; i++){
            set_to_target_na_longitude(i*30);
            print_vakyas(vakya_csv);
        }

        printf("\nSuccessfully generated file %s\n", file_path);
    }
    return 0;
}
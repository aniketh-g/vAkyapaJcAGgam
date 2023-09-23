#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
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
    spa.delta_t       = 65;
    spa.longitude     = 0;
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

    spa.jd = 2280627.500000;
    double epsilon = 0.000000001;
    double target = 0;
    spa_calculate(&spa, 't');
    double delta = epsilon+1;

    double dates[12];

    // for(int target = 0; target < 360; target += 30){
    //     delta = spa.alpha_na - target;
    //     while(delta >= epsilon || delta <= -epsilon){
    //     delta = spa.alpha_na - target;
    //     spa_calculate(&spa, 't');
    //     // printf("JD = %f, Longitude = %f, delta = %f\t", spa.jd, spa.alpha_na, delta);
    //     if(delta >= epsilon){
    //         spa.jd -= spa.alpha_na - target;
    //         // printf("Decreasing JD by %f\n", spa.alpha_na);
    //         }
    //     if(delta <= -epsilon){
    //         spa.jd += spa.alpha_na - target;
    //         // printf("Increasing JD by %f\n", spa.alpha_na);
    //         }
    //     }
    //     printf("JD = %f, Longitude = %f, delta = %f\n", spa.jd, spa.alpha_na, delta);
    //     dates[target/30] = spa.jd;
    // }

    while(delta >= epsilon || delta <= -epsilon){
        delta = spa.alpha_na - target;
        spa_calculate(&spa, 't');
        // printf("JD = %f, Longitude = %f, delta = %f\t", spa.jd, spa.alpha_na, delta);
        if(delta >= epsilon){
            spa.jd -= spa.alpha_na - target;
            // printf("Decreasing JD by %f\n", spa.alpha_na);
        }
        if(delta <= -epsilon){
            spa.jd += spa.alpha_na - target;
            // printf("Increasing JD by %f\n", spa.alpha_na);
        }
    }
    printf("JD = %f, Longitude = %f, delta = %f\n", spa.jd, spa.alpha_na, delta);

    // spa.jd = 2280344.238585;
    double longs[48];
    longs[0] = 0;
    double vakyas[48];

    for(int i=1; i<=5; i++){
        spa_calculate(&spa, 't');
        printf("True longitude after %d days = %f deg\t", (i-1)*8, spa.alpha_na);
        longs[i] = spa.alpha_na;
        vakyas[i] = longs[i] - longs[i-1] - 8;

        printf("vakya %d = %fdeg = -%dm%fs\n", i-1, vakyas[i]*60, (int)floor(fabs(vakyas[i])*60), 60*(fabs(vakyas[i])*60-(int)floor(fabs(vakyas[i])*60)));
        spa.jd = spa.jd + 8;
    }

    printf("\nSuccessfully computed sidereal longitudes\n");
    return 0;
}
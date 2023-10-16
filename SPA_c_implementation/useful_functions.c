#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include "spa.h"  //include the SPA header file

spa_data spa; //declare the SPA structure

void set_to_target_na_longitude(double target){
    double epsilon = 0.000000001;
    spa_calculate(&spa, 't');
    double delta = epsilon+1;
    while(delta >= epsilon || delta <= -epsilon){
        delta = spa.lambda_na - target;
        spa_calculate(&spa, 't');
        // printf("JD = %f, Longitude = %f, delta = %f\t", spa.jd, spa.lambda_na, delta);
        if(delta >= epsilon || delta <= -epsilon){
            spa.jd -= spa.lambda_na - target;
            // printf("Decreasing JD by %f\n", spa.lambda_na);
        }
    }
    // printf("\nJD set to %f: True Nirayana Longitude = %f+/-%f\n", spa.jd, spa.lambda_na, delta);
}
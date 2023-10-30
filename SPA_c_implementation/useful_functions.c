#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include "spa.h"  //include the SPA header file

spa_data spa; //declare the SPA structure

void set_to_target_na_longitude(double target){
    double epsilon = 0.000001;
    spa_calculate(&spa, 't');
    double delta = epsilon+1;
    while(delta >= epsilon || delta <= -epsilon){
        delta = spa.lambda_na - target;
        spa_calculate(&spa, 't');
        // printf("JD = %f, Longitude = %f, delta = %f\t", spa.jd, spa.lambda_na, delta);
        if(delta >= epsilon || delta <= -epsilon){
            if(spa.lambda_na>=355) spa.lambda_na -= 360;
            spa.jd -= spa.lambda_na - target;
            // printf("Decreasing JD by %f\n", spa.lambda_na);
        }
    }
    // printf("\nJD set to %f: True Nirayana Longitude = %f+/-%f\n", spa.jd, spa.lambda_na, delta);
}

void set_to_target_sa_longitude(double target){
    double epsilon = 0.000001;
    spa_calculate(&spa, 't');
    double delta = epsilon+1;
    while(delta >= epsilon || delta <= -epsilon){
        delta = spa.lambda - target;
        spa_calculate(&spa, 't');
        // printf("JD = %f, Longitude = %f, delta = %f\t", spa.jd, spa.lambda_na, delta);
        if(delta >= epsilon || delta <= -epsilon){
            if(spa.lambda >=355) spa.lambda -= 360;
            spa.jd -= spa.lambda - target;
            // printf("Decreasing JD by %f\n", spa.lambda_na);
        }
    }
    // printf("\nJD set to %f: True Nirayana Longitude = %f+/-%f\n", spa.jd, spa.lambda_na, delta);
}

void print_dms(double input){
    int d = input;
    input = (input - d)*60;
    int m = input;
    double s = (input - m)*60;
    printf("%d*%d\'%.2f\"\n", d, m, s);
}
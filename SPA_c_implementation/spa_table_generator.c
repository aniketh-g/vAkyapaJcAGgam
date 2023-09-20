#include <stdio.h>
#include "spa.h"  //include the SPA header file

int main (int argc, char *argv[])
{
    spa_data spa;  //declare the SPA structure
    int result;
    float min, sec;

    //enter required input values into SPA structure

    spa.year          = 2023;
    spa.month         = 1;
    spa.day           = 1;
    spa.hour          = 0;
    spa.minute        = 0;
    spa.second        = 0;
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

    //call the SPA calculate function and pass the SPA structure

    result = spa_calculate(&spa);

    if (result == 0)  //check for SPA errors
    {
        //display the results inside the SPA structure
        printf("Longitude: %f degrees\n", spa.lamda);
        printf("Right Ascension: %dd%dm%fs\n", (int) spa.alpha, (int) (60*(spa.alpha-(int) spa.alpha)), 60*(60*(spa.alpha-(int) spa.alpha)) - 60*((int) (60*(spa.alpha-(int) spa.alpha))) );
        printf("Radius: %f\n", spa.r);

    } else printf("SPA Error Code: %d\n", result);

    spa.day = 2;
    result = spa_calculate(&spa);

    if (result == 0)  //check for SPA errors
    {
        //display the results inside the SPA structure
        printf("Longitude: %f degrees\n", spa.lamda);
        printf("Right Ascension: %dd%dm%fs\n", (int) spa.alpha, (int) (60*(spa.alpha-(int) spa.alpha)), 60*(60*(spa.alpha-(int) spa.alpha)) - 60*((int) (60*(spa.alpha-(int) spa.alpha))) );

    } else printf("SPA Error Code: %d\n", result);

    return 0;
}
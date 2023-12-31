
/////////////////////////////////////////////
//          SPA TESTER for SPA.C           //
//                                         //
//      Solar Position Algorithm (SPA)     //
//                   for                   //
//        Solar Radiation Application      //
//                                         //
//             August 12, 2004             //
//                                         //
//   Filename: SPA_TESTER.C                //
//                                         //
//   Afshin Michael Andreas                //
//   afshin_andreas@nrel.gov (303)384-6383 //
//                                         //
//   Measurement & Instrumentation Team    //
//   Solar Radiation Research Laboratory   //
//   National Renewable Energy Laboratory  //
//   1617 Cole Blvd, Golden, CO 80401      //
/////////////////////////////////////////////

/////////////////////////////////////////////
// This sample program shows how to use    //
//    the SPA.C code.                      //
/////////////////////////////////////////////

#include <stdio.h>
#include "spa.h"  //include the SPA header file
#include "useful_functions.c"

double sidereal_year = 365.256363004;
double tropical_year = 365.2421897;

int main (int argc, char *argv[])
{
    // spa_data spa;  //declare the SPA structure
    int result;
    float min, sec;

    //enter required input values into SPA structure

    // spa.year          = 2003;
    // spa.month         = 10;
    // spa.day           = 17;
    // spa.hour          = 12;
    // spa.minute        = 30;
    // spa.second        = 30;
    // spa.timezone      = -7.0;
    // spa.delta_ut1     = 0;
    // spa.delta_t       = 67;
    // spa.longitude     = -105.1786;
    // spa.latitude      = 39.742476;
    // spa.elevation     = 1830.14;
    // spa.pressure      = 820;
    // spa.temperature   = 11;
    // spa.slope         = 30;
    // spa.azm_rotation  = -10;
    // spa.atmos_refract = 0.5667;
    // spa.function      = SPA_ALL;

    //call the SPA calculate function and pass the SPA structure

    spa.jd = 2460779.417889+365*1;
    set_to_target_sa_longitude(0);
    result = spa_calculate(&spa, 't');

    if (result == 0)  //check for SPA errors
    {
        //display the results inside the SPA structure

        // printf("Julian Day:    %.6f\n",spa.jd);
        // printf("Direct Sayana Longitude:      %.6f degrees\n", spa.theta);
        // printf("Nutation:                      %.6f degrees\n", spa.del_psi);
        // printf("Aberration:                   %.6f degrees\n", spa.del_tau);
        // printf("Apparent Nirayana Longitude:   %.6f degrees\n", spa.lambda_na);
        // printf("Apparent Sayana Longitude:    %.6f degrees\n", spa.lambda);
        // printf("ayanamsha:                    %.6f degrees\n", spa.ayanamsha);
        printf("Julian Day:    %.6f\n",spa.jd);
        printf("Direct Sayana Longitude:     "); print_dms(spa.theta);
        printf("Direct Nirayana Longitude:   "); print_dms(spa.theta-spa.ayanamsha);
        printf("Nutation:                     "); print_dms(spa.del_psi);
        printf("Aberration:                   "); print_dms(spa.del_tau);
        printf("Apparent Nirayana Longitude:  "); print_dms(spa.lambda_na);
        printf("Apparent Sayana Longitude:   "); print_dms(spa.lambda);
        printf("ayanamsha:                   "); print_dms(spa.ayanamsha);
        // printf("Delta Epsilon:                %.6f degrees\n",spa.del_epsilon);
        // printf("Earth Heliocentric Latitude : %.6f degrees\n",spa.b);
        // printf("Radius:        %.6f AU\n",spa.r);
        // printf("Hour Angle:    %.6f degrees\n",spa.h);
        // printf("Epsilon:       %.6f degrees\n",spa.epsilon);
        // printf("Zenith:        %.6f degrees\n",spa.zenith);
        // printf("Azimuth:       %.6f degrees\n",spa.azimuth);
        // printf("Incidence:     %.6f degrees\n",spa.incidence);

        // min = 60.0*(spa.sunrise - (int)(spa.sunrise));
        // sec = 60.0*(min - (int)min);
        // printf("Sunrise:       %02d:%02d:%02d Local Time\n", (int)(spa.sunrise), (int)min, (int)sec);

        // min = 60.0*(spa.sunset - (int)(spa.sunset));
        // sec = 60.0*(min - (int)min);
        // printf("Sunset:        %02d:%02d:%02d Local Time\n", (int)(spa.sunset), (int)min, (int)sec);

    } else printf("SPA Error Code: %d\n", result);

    return 0;
}

/////////////////////////////////////////////
// The output of this program should be:
//
//Julian Day:    2452930.312847
//L:             2.401826e+01 degrees
//B:             -1.011219e-04 degrees
//R:             0.996542 AU
//H:             11.105902 degrees
//Delta Psi:     -3.998404e-03 degrees
//Delta Epsilon: 1.666568e-03 degrees
//Epsilon:       23.440465 degrees
//Zenith:        50.111622 degrees
//Azimuth:       194.340241 degrees
//Incidence:     25.187000 degrees
//Sunrise:       06:12:43 Local Time
//Sunset:        17:20:19 Local Time
//
/////////////////////////////////////////////

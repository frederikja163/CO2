#include <stdio.h>
#include <time.h>
#include <string.h>
#include "calculateOptimalTime.h"
#include "DMIParser.h"
#include "fileIO.h"

    /* Algorithm to find the most optimal time to run based 
       on array of windspeed data and the device's hours active */
char * find_optimal_time(int activeHours, char *optimalTime) {
    int i, j;
    double currentWindspeed = 0;
    double highestWindspeed = 0; 
    char *inputString;
    inputString = read_file("src/shared/ninjo2dmidk.json");
    char *updateTimeStamp;
    windValue* values = ParseStringToWind(inputString, updateTimeStamp);
    
    for(i = 0; i < DATA_SIZE-(activeHours+1); i++) { 
        currentWindspeed = 0;
        for(j = 0; j < activeHours; j++) {
            /* Cut-in and cut out speed of vestas windturbines */
            if(values[i+j].windspeed >= 3 && values[i+j].windspeed <= 25) {
                currentWindspeed += values[i+j].windspeed;
            }
        }
        if (currentWindspeed > highestWindspeed) {
            highestWindspeed = currentWindspeed;
            strcpy(optimalTime, values[i].timestamp);
        }
    } 
    for (i = 0; i < 97; ++i) {
        free(values[i].timestamp);
    }
    free(values);
    free(inputString);
    return optimalTime;
}
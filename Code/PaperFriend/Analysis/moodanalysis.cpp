#include "moodanalysis.h"
//#include "entryclasses.h"

#include <string>
#include <math.h>
#include <vector>
#include <algorithm>



// MoodAnalysis implementation:



bool MoodAnalysis::alert_depression(int n, int m){
    /**
    * @param int n: number n and m of days with the assumption (needed only for it to make sense)
    *               that n < m                 
    * @returns the mood has been lower on average over the last n days than it has been over the last m
    */
    return get_lastn_average(n, MOOD) < get_lastn_average(m, MOOD);
}


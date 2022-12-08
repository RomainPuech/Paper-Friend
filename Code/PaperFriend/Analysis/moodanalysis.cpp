#include "moodanalysis.h"
//#include "entryclasses.h"

#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <map>



bool MoodAnalysis::alert_depression(){
    /**
    * @param no params
    * @returns whether the mood has been declining over the last few days or not
    */
    int num_days_to_consider = 10;  // These values are just dummy values for now.
    double slope_threshold = -1;

    LinearRegressionCoeffs trend = general_trend(num_days_to_consider, 0);
    return trend.slope < slope_threshold;
}


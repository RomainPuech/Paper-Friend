#include "moodanalysis.h"

#include <string>
#include <math.h>
#include <vector>


vector<string> MoodAnalysis::anomalies_dtection(vector<DayLog> log){
    /**
     * @param vector of log data.
     * @return vector of dates at which anomalie in mood was detected.
     */
    return {"Artem: I'll do it"};
}

bool MoodAnalysis::alert_depression(int n, int m){
    return get_lastn_average(n) < get_lastn_average(m);
}

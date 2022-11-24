#include "moodanalysis.h"

#include <string>
#include <math.h>
#include <vector>

// DayLog implementation:
string DayLog::get_day(){
    return day;
}

double DayLog::get_mood(){
    return mood;
}

vector<DayLog> MoodAnalysis::anomalies_dtection(vector<DayLog> log){
    /**
     * @param vector of DayLogs [string day, double mood].
     * @return vector of dates at which anomalie in mood was detected.
     */
    /*double mean = calculate_mean(log.get_mood());
    //for(vector<DayLog>::iterator i = log.begin(); i < log.end(); i++){
        if (i->get_mood() - )
    }*/
    return {{"Artem: I'll do it", 112}};
}

/* This will be uncommented once get_lastn_average is implemented
// MoodAnalisys implementation:
bool MoodAnalysis::alert_depression(int n, int m){
    return get_lastn_average(n) < get_lastn_average(m);
}
*/

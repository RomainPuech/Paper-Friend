#include "moodanalysis.h"

#include <string>
#include <math.h>
#include <vector>
#include <algorithm>

// DayLog implementation:
std::string DayLog::get_day() const{
    return day;
}

double DayLog::get_mood() const{
    return mood;
}


// MoodAnalysis implementation:
double MoodAnalysis::get_lastn_average(int n){
    /**
     * @param int n: number of n last days we take into account
     * @return double average mood for last n days
     */
    std::vector<double> mood_list{};

    for(int i = std::max<int>(0, log.size() - n); i < log.size(); i++){
        mood_list.push_back((log.begin() + i)->get_mood());
    }
    return avg<double>(mood_list);
}

std::vector<DayLog> MoodAnalysis::anomalies_detection(std::vector<DayLog> log){
    /**
     * @param vector of DayLogs [string day, double mood].
     * @return vector of dates at which anomalie in mood was detected (value is 2 SDs far from its mean).
     */
    std::vector<double> mood_list{};
    std::vector<DayLog> res{};  // stores output info about anomaly points

    for(std::vector<DayLog>::iterator i = log.begin(); i < log.end(); i++){
            mood_list.push_back(i->get_mood());
    }
    double mean = avg<double>(mood_list);
    for(int i = 0; i < log.size(); i++){
        if (*(mood_list.begin() + i) - mean >= 2 * stddev(mood_list)){
            DayLog temp = {(log.begin() + i)->get_day(), (log.begin() + i)->get_mood()};
            res.push_back(temp);
        }
    }
    return res;
}

bool MoodAnalysis::alert_depression(int n, int m){
    return get_lastn_average(n) < get_lastn_average(m);
}


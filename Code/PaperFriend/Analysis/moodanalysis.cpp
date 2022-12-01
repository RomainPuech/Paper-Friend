#include "moodanalysis.h"
#include "entryclasses.h"

#include <string>
#include <math.h>
#include <vector>
#include <algorithm>



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

std::vector<EntryPerso> MoodAnalysis::anomalies_detection(std::vector<EntryPerso> log){
    /**
     * @param vector of EntryPersos.
     * @return vector of dates at which anomalie in mood was detected (value is 2 SDs far from its mean).
     */
    std::vector<double> mood_list{};
    std::vector<EntryPerso> res{};  // stores output info about anomaly points

    for(std::vector<EntryPerso>::iterator i = log.begin(); i < log.end(); i++){
            mood_list.push_back(i->get_mood());
    }
    double mean = avg<double>(mood_list);
    for(int i = 0; i < log.size(); i++){
        if (*(mood_list.begin() + i) - mean >= 2 * stddev(mood_list)){
            EntryPerso temp;
            temp.set_mood((log.begin() + i)->get_mood());
            temp.set_date((log.begin() + i)->get_date());
            res.push_back(temp);
        }
    }
    return res;
}

bool MoodAnalysis::alert_depression(int n, int m){
    /**
    * @param int n: number n and m of days with the assumption (needed only for it to make sense)
    *               that n < m                 
    * @returns the mood has been lower on average over the last n days than it has been over the last m
    */
    return get_lastn_average(n) < get_lastn_average(m);
}


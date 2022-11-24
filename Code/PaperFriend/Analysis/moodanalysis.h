#ifndef MOODANALYSIS_H
#define MOODANALYSIS_H

#include "DataAnalysis.h";

#include <vector>
#include <string>
#include <math.h>
#include <vector>


using namespace std;

class DayLog{
public:
    DayLog(string day_n, double mood_n): day(day_n), mood(mood_n){}
    string get_day();
    double get_mood();
private:
    string day;
    double mood;
};


class MoodAnalysis : public DataAnalysis{
public:
    bool alert_depression(int n, int m);
    vector<DayLog> anomalies_dtection(vector<DayLog> log);
private:
    double get_lastn_average(int n); // This will compute the average mood over the last n days.
                                     // Not implemented yet.
};

template <typename T> double average_vector(std::vector<T> vector){
    T sum = 0;
    for (auto i=vector.begin(); i<vector.end(); i++){
        sum = sum + *i;
    }
    double sumD = sum;
    double vecsizeD = vector.size();
    double average = sumD/vecsizeD;
    return average;
}


#endif // MOODANALYSIS_H

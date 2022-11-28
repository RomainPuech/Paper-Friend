#ifndef MOODANALYSIS_H
#define MOODANALYSIS_H

#include "DataAnalysis.h"

#include <vector>
#include <string>
#include <math.h>
#include <vector>



class DayLog{
public:
    DayLog(std::string day_n, double mood_n): day(day_n), mood(mood_n){}
    std::string get_day() const;
    double get_mood() const;
private:
    std::string day;
    double mood;
};


class MoodAnalysis : public DataAnalysis{
public:
    bool alert_depression(int n, int m);
    std::vector<DayLog> anomalies_detection(std::vector<DayLog> log);
private:
    double get_lastn_average(int n); // This will compute the average mood over the last n days.
                                     // Not implemented yet.
};



#endif // MOODANALYSIS_H

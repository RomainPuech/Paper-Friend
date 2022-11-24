#ifndef MOODANALYSIS_H
#define MOODANALYSIS_H
# include "DataAnalysis.h";
class MoodAnalysis : public DataAnalysis{
private:
    double get_lastn_average(int n); // This will compute the average mood over the last n days.
                                     // Not implemented yet.
public:
    bool alert_depression(int n, int m);
};



#endif // MOODANALYSIS_H

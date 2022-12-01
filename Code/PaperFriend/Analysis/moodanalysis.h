#ifndef MOODANALYSIS_H
#define MOODANALYSIS_H

#include "DataAnalysis.h"
#include "entryclasses.h"

#include <vector>
#include <string>
#include <math.h>
#include <vector>



class MoodAnalysis : public DataAnalysis{
public:
    bool alert_depression(int n, int m);
    std::vector<EntryPerso> anomalies_detection(std::vector<EntryPerso> log);
    std::string suggestion();
private:
    double get_lastn_average(int n); // This will compute the average mood over the last n days.
                                     // Not implemented yet.
};



#endif // MOODANALYSIS_H

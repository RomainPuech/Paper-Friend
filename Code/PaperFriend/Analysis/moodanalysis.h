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
    std::string suggestion(std::vector<EntryPerso> log);  // text that will be suggested to user daily
private:
    double get_lastn_average(int n, std::string item); // This will compute the average mood over the last n days for a particular item (e.g. "mood" or "screen_time")
    std::vector<std::string> item_priority(std::vector<EntryPerso> log);
};



#endif // MOODANALYSIS_H

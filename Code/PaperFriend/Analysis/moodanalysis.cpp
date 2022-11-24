#include "moodanalysis.h"


bool MoodAnalysis::alert_depression(int n, int m){
    return get_lastn_average(n) < get_lastn_average(m);
}

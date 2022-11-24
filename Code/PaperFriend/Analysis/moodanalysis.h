#ifndef MOODANALYSIS_H
#define MOODANALYSIS_H

#include <vector>

#include "DataAnalysis.h";
class MoodAnalysis : public DataAnalysis{
private:
    double get_lastn_average(int n); // This will compute the average mood over the last n days.
                                     // Not implemented yet.
public:
    bool alert_depression(int n, int m);
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

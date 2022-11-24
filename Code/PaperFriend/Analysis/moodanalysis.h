#ifndef MOODANALYSIS_H
#define MOODANALYSIS_H

#include <vector>


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

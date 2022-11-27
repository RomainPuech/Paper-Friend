#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <vector>

using namespace std;

class DataAnalysis{

public:
    double calculateSD(vector<double> data);  // calculates standart deviation

    template <typename T> double calculate_mean(vector<T> data){ // calculates mean
        double sum = 0;
        for (typename vector<T>::iterator i=data.begin(); i<data.end(); i++){sum += *i;}
        return sum/data.size();
    }

private:

};

#endif // DATAANALYSIS_H

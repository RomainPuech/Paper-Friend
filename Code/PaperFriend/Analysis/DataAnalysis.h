#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <vector>

using namespace std;

class DataAnalysis{

public:
    double calculateSD(vector<double> data);  // calculates standart deviation
    double calculate_mean(vector<double> data);
private:

};

#endif // DATAANALYSIS_H

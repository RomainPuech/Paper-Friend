#include "DataAnalysis.h"
#include "math.h"
#include <vector>

using namespace std;


double DataAnalysis:: calculate_mean(vector<double> data){
    /**
     * @param vector data.
     * @return mean.
     */
    double sum = 0.0, res = 0.0;

    for(vector<double>::iterator i = data.begin(); i < data.end(); i++){
        sum += *i;
    }
    res = sum / data.size();
    return res;
}

double DataAnalysis::calculateSD(vector<double> data){
    /**
     * @param vector data.
     * @return standart deviation.
     */
    double sum = 0.0, standardDeviation = 0.0;
    double mean =  calculate_mean(data);

    for(vector<double>::iterator i = data.begin(); i < data.end(); i++) {
        standardDeviation += pow(*i - mean, 2);
    }

    standardDeviation /= data.size();

    return standardDeviation;
}

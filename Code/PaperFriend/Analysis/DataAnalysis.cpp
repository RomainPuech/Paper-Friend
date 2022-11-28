#include "DataAnalysis.h"
#include "math.h"
#include <vector>

using namespace std;


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

    standardDeviation = sqrt(standardDeviation / data.size());

    return standardDeviation;
}

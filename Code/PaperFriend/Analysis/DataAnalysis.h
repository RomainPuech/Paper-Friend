#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <numeric>
#include <vector>

using namespace std;

class DataAnalysis {

public:
  double stddev(vector<double> data); // calculates standart deviation

  template <typename T> double avg(vector<T> data) {

    // prefer STL when available
    double sum = std::accumulate(data.begin(), data.end(), 0.0);

    return sum / data.size();
  }

private:
};

/**
 * @param vector data.
 * @return mean.
 */

#endif // DATAANALYSIS_H

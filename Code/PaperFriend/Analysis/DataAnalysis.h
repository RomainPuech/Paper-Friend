#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <numeric>
#include <vector>


class DataAnalysis {

public:
  double stddev(std::vector<double> data); // calculates standart deviation

  template <typename T> double avg(std::vector<T> data) {

    // prefer STL when available
    double sum = std::accumulate(data.begin(), data.end(), 0.0);

    return sum / data.size();
  }


private:
};


#endif // DATAANALYSIS_H

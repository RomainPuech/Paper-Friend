#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include "entryclasses.h"
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

  std::vector<EntryPerso> get_lastn_days_data(int n) const;  

  std::vector<EntryPerso> log;
};


#endif // DATAANALYSIS_H

#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <vector>


class DataAnalysis {

public:
  double stddev(std::vector<double> data); // calculates standart deviation

  template <typename T> double mean(std::vector<T> data);

private:
};

#endif // DATAANALYSIS_H

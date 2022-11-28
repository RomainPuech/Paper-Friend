#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <vector>

using namespace std;

class DataAnalysis {

public:
  double stddev(vector<double> data); // calculates standart deviation

  template <typename T> double mean(vector<T> data);

private:
};

#endif // DATAANALYSIS_H

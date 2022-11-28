#include "DataAnalysis.h"
#include <cmath> //prefer the c- version rather than the .h
#include <vector>
#include <numeric>

/**
 * @param vector data.
 * @return standart deviation.
 */

// using namespace std; don't be lazy and just use the specifier, it
// avoids naming conflicts. If you really have to use it, put it in the most
// restricted scope possible (

template <typename T> double avg(std::vector<T> data) { // calculates mean

  return static_cast<double>(std::accumulate(data.begin(), data.end())) /
         data.size();
}

double DataAnalysis::stddev(std::vector<double> data) {

  double sum = 0.0, standardDeviation = 0.0;
  double mean = avg<double>(data);

  // Never manually iterate trough an STL container with iterators. Either use
  // the normal syntax or use range based for loops like the one below
  for (auto el : data)
    standardDeviation += pow(el - mean, 2);

  standardDeviation = sqrt(standardDeviation / data.size());

  return standardDeviation;
}

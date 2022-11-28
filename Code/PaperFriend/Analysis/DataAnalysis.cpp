#include "DataAnalysis.h"
#include <algorithm>
#include <cmath> //prefer the c- version rather than the .h
#include <numeric>
#include <vector>

// using namespace std; don't be lazy and just use the specifier, it
// avoids naming conflicts. If you really have to use it, put it in the most
// restricted scope possible (

/**
 * @param vector data.
 * @return standart deviation.
 */

double DataAnalysis::stddev(vector<double> data) {

  double residue_sum = 0.0;
  double mean = avg<double>(data);

  // Never manually iterate trough an STL container with iterators. Either use
  // the normal syntax or use range based for loops like the one below
  for (auto el : data)
    residue_sum = std::pow(mean - el, 2);

  return sqrt(residue_sum / data.size());
}

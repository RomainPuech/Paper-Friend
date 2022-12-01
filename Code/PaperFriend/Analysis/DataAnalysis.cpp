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


double DataAnalysis::stddev(std::vector<double> data) {

  double residue_sum = 0.0;

  double mean = avg<double>(data);

  // Never manually iterate trough an STL container with iterators. Either use
  // the normal syntax or use range based for loops like the one below
  for (auto el : data)
    residue_sum += std::pow(mean - el, 2);

  return sqrt(residue_sum / data.size());
}

std::vector<EntryPerso> DataAnalysis::get_lastn_days_data(int n) const {
    /**
     * @param int n: number n of days.
     * @return a list of all data within n days of the very last log.
     */
    
    int current = log.back().get_absolute_day(); // represents the date of the last log in the data.
    auto comp {[current](auto entry, int n){return entry.get_absolute_day() <= current - n;}};
    auto cutoff = std::lower_bound(log.begin(), log.end(), n, comp);

    std::vector<EntryPerso> res(cutoff, log.end());
    return res;
}

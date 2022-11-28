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
    
    std::vector<EntryPerso> res{};
    
    int N = log.size();
    int current = log[N - 1].get_absolute_day(); // represents the date of the last log in the data.
    bool located_cutoff = false;     // No need to check conditions once we locate the first entry
                                     // within n days.
    
    for (int i = std::max<int>(0, N - n); i < N; ++i) {
        
        if (located_cutoff) {
            res.push_back(log[i]);
            continue;
        }

        if (current - log[i].get_absolute_day() <= n) {
            located_cutoff = true;
            res.push_back(log[i]);
        }

    }
    return res;
}

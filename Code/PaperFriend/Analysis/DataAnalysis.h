#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include "entryclasses.h"
#include <numeric>
#include <vector>

enum Variables {    // These are the variables to analyze. This definition allows to parametrize
                    // which variable is being analyzed in a given method. (we avoid writing the
                    // same funcitons for each variable.)
    MOOD, SLEEP, EATING_HEALTHY, PRODUCTIVITY, COMMUNICATIONS, SCREEN_TIME
};

class DataAnalysis {

public:

  std::vector<EntryPerso> log; // Data to be analysed

  double cov(std::vector<double> X, std::vector<double> Y);  // calculates covariance
  double cor(std::vector<double> X, std::vector<double> Y);  // calculates correlation




  template <typename T> double avg(std::vector<T> data) const{

    // prefer STL when available
    double sum = std::accumulate(data.begin(), data.end(), 0.0);

    return sum / data.size();
  }

  double avg(const std::vector<EntryPerso>& entries, Variables var_name) const; // returns the average value of
                                                                         // the variable across the vector


  std::map<std::string, double> item_priority(std::vector<EntryPerso> log);

  double stddev(std::vector<double> data) const; // calculates standard deviation

  double stddev(const std::vector<EntryPerso>& entries, Variables var_name) const; // returns the standard
                                                                        // deviation of the variable across
                                                                        // the vector



  double get_var(const EntryPerso& entry, Variables var_name) const; // gets the value of the
                                                                     // specified variable
  std::vector<double> get_vect(const std::vector<EntryPerso>& entries, Variables var_name) const; // returns
                                                                     // the vector of values of the variable across the
                                                                     // entries
  void set_var(EntryPerso& entry, Variables var_name, double value) const;  // sets the value of the 
                                                                     // specified variable
                                // This method will probably not be used that much but here just in case.



  std::vector<EntryPerso> get_lastn_days_data(int n) const; // gets the entries within n days of the last entry.

  double get_lastn_average(int n, Variables var_name) const;  // This will compute the average
                                            // of the specified variable over the last n days

  std::vector<EntryPerso> anomalies_detection(const std::vector<EntryPerso>& entries, Variables var_name) const;

  std::string var_to_str(Variables var){
      switch (var)
      {
          case MOOD:
              return "mood";
          case SLEEP:
              return "sleep";
          case EATING_HEALTHY:
              return "healthy eating";
          case PRODUCTIVITY:
              return "productivity";
          case SCREEN_TIME:
              return "screen time";
          case COMMUNICATIONS:
              return "communications";
          default:
              return "0";
      }
  }

};


#endif // DATAANALYSIS_H

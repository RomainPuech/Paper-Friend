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

struct LinearRegressionCoeffs{
                    // A simple struct that contains linear regression coefficients.

    LinearRegressionCoeffs(double slope, double intercept, double quality_coeff) : \

               slope{slope}, intercept{intercept}, quality_coeff{quality_coeff}{}

    LinearRegressionCoeffs() : slope{0}, intercept{0}, quality_coeff{0}{}

    double slope;
    double intercept;
    double quality_coeff;
};

class DataAnalysis {

public:

  std::vector<EntryPerso> log; // Data to be analysed

  double get_var(const EntryPerso& entry, Variables var_name) const; // gets the value of the
                                                                     // specified variable
  std::vector<double> get_vect(const std::vector<EntryPerso>& entries, Variables var_name) const; // returns
                                                                     // the vector of values of the variable across the
                                                                     // entries
  void set_var(EntryPerso& entry, Variables var_name, double value) const;  // sets the value of the
                                                                     // specified variable
                                // This method will probably not be used that much but here just in case.



  std::vector<EntryPerso> get_lastn_days_data(int n) const; // gets the entries within n days of the last entry.

  template <typename T> double avg(const std::vector<T>& data) const{

    // prefer STL when available
    double sum = std::accumulate(data.begin(), data.end(), 0.0);

    return sum / data.size();
  }

  double avg(const std::vector<EntryPerso>& entries, Variables var_name) const; // returns the average value of
                                                                         // the variable across the vector



  double stddev(const std::vector<double>& data) const; // calculates standard deviation

  double stddev(const std::vector<EntryPerso>& entries, Variables var_name) const; // returns the standard
                                                                        // deviation of the variable across
                                                                        // the vector

  double cov(const std::vector<double>& X, const std::vector<double>& Y) const;  // calculates covariance
  double cor(const std::vector<double>& X, const std::vector<double>& Y) const;  // calculates correlation


  LinearRegressionCoeffs compute_linear_regression_coeffs(const std::vector<double>& X, const std::vector<double>& Y);  // Fits Y against X
  LinearRegressionCoeffs compute_linear_regression_coeffs(const std::vector<EntryPerso>& entries, Variables var1, Variables var2);  // Fits var1 against var2 across entries
  LinearRegressionCoeffs general_trend(int n, Variables var);      // Fits the values of var over the last n days against the number of days since the first day being considered.

  double get_lastn_average(int n, Variables var_name) const;  // This will compute the average
                                            // of the specified variable over the last n days

  std::vector<EntryPerso> anomalies_detection(const std::vector<EntryPerso>& entries, Variables var_name) const;

// To be implemented
  std::string var_to_str(Variables a){};                                                      
  
};


#endif // DATAANALYSIS_H

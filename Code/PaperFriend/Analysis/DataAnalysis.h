#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#pragma once

#include "Frontend/entryclasses.h"
#include "Frontend/entryrecap.h"
#include <QDebug>
#include <map>
#include <numeric>
#include <vector>
/*
enum Variables {    // These are the variables to analyze. This definition
allows to parametrize
                    // which variable is being analyzed in a given method. (we
avoid writing the
                    // same funcitons for each variable.)
    MOOD, SLEEP, EATING_HEALTHY, PRODUCTIVITY, SOCIALIZING, PHYSICAL_ACTIVITY
};
*/
struct LinearRegressionCoeffs {
  // A simple struct that contains linear regression coefficients.

  LinearRegressionCoeffs(double slope, double intercept, double quality_coeff)
      :

        slope{slope}, intercept{intercept}, quality_coeff{quality_coeff} {}

  LinearRegressionCoeffs() : slope{0}, intercept{0}, quality_coeff{0} {}

  double slope;
  double intercept;
  double quality_coeff;
};

class DataAnalysis {

protected:
  std::vector<EntryPerso> log; // Data to be analysed

  bool stl = false; // If there is enough entries for us to use STL
  std::vector<std::vector<double>> STL_X;
  std::vector<std::vector<double>> STL_Trends;
  std::vector<std::vector<double>> STL_Seasonalities;
  std::vector<std::vector<double>> STL_Remainders;

  DataAnalysis();

  // double get_var(const EntryPerso& entry, int var_index) const; // gets the
  // value of the
  //  specified variable
  std::vector<double>
  get_vect(const std::vector<EntryPerso> &entries,
           int var_index) const; // returns
                                 // the vector of values of the variable across
                                 // the entries
  // void set_var(EntryPerso& entry, int var_index, double value) const;  //
  // sets the value of the
  //  specified variable
  // This method will probably not be used that much but here just in case it is
  // needed to generate randomized entries for testing.

  std::vector<EntryPerso> get_lastn_days_data(int n, int reference = -1)
      const; // gets the entries within n days of the last entry.

  template <typename T> double avg(const std::vector<T> &data) const {

    // prefer STL when available
    double sum = std::accumulate(data.begin(), data.end(), 0.0);

    return sum / data.size();
  }

  double avg(const std::vector<EntryPerso> &entries,
             int var_index) const; // returns the average value of
                                   // the variable across the vector

  double stddev(
      const std::vector<double> &data) const; // calculates standard deviation

  double stddev(const std::vector<EntryPerso> &entries,
                int var_index) const; // returns the standard
                                      // deviation of the variable across
                                      // the vector

  double cov(const std::vector<double> &X,
             const std::vector<double> &Y) const; // calculates covariance
  double cor(const std::vector<double> &X,
             const std::vector<double> &Y) const; // calculates correlation

  LinearRegressionCoeffs compute_linear_regression_coeffs(
      const std::vector<double> &X,
      const std::vector<double> &Y) const; // Fits Y against X
  LinearRegressionCoeffs compute_linear_regression_coeffs(
      const std::vector<EntryPerso> &entries, int var1_index,
      int var2_index) const; // Fits var1 against var2 across entries
  LinearRegressionCoeffs general_trend(int n, int var_index)
      const; // Fits the values of var over the last n days against the number
             // of days since the first day being considered.
  LinearRegressionCoeffs general_trend(const std::vector<EntryPerso> &entries,
                                       int var_index) const;

  double get_lastn_average(int n, int var_index)
      const; // This will compute the average
             // of the specified variable over the last n entries.

  std::vector<EntryPerso>
  anomalies_detection(const std::vector<EntryPerso> &entries,
                      int var_index) const;
  std::vector<int> anomalies_by_groups(const std::vector<EntryPerso> &entries,
                                       int num_days, int var_index);

  std::vector<double> cyclic_week(int metric_index);

  std::string react_depression();

  std::string var_to_str(int var_index) const {
    if (log.size() == 0) {
      return "";
    }
    return log[0].get_var_name(var_index);
  }

  int get_num_activities() {
    if (log.size() == 0) {
      return 0;
    }
    return log[0].get_num_activities();
  }

  std::vector<int>
  item_priority(const std::vector<EntryPerso> &entries,
                int var_index); // Arranges all other variables w.r.t their
                                // influence on the specified variable

  std::string generate_recap_text(const std::vector<EntryPerso> &entries,
                                  int type);

  void weekly_anomalies_text(const std::vector<EntryPerso> &entries,
                             std::vector<std::string> &string_vect);
  void monthly_anomalies_text(const std::vector<EntryPerso> &entries,
                              std::vector<std::string> &string_vect);
  void yearly_anomalies_text(const std::vector<EntryPerso> &entries,
                             std::vector<std::string> &string_vect);

  std::string
  generate_weekly_recap_text(const std::vector<EntryPerso> &entries);
  EntryRecap* recap(int type);

  // STL returns a vector containing the Trend and the Seasonality component
  // {Trend, Seasonality}. seasonal_length is the length of the seasonality
  // component; can be 7 to analyze a week, 30 for a month, ... dataX is in
  // days, sorted, and the lower indexed day (dataX[0]) is the closest day to
  // today
  std::vector<std::vector<double>> stl_regression(std::vector<double> dataY,
                                                  std::vector<double> dataX,
                                                  int seasonal_length);

public:
  DataAnalysis(std::vector<EntryPerso *> vector_entries);
  EntryRecap* weekly_recap();
  EntryRecap* monthly_recap();
  EntryRecap* yearly_recap();
  std::string
  suggestion(); // text that will be suggested to user daily
};

#endif // DATAANALYSIS_H

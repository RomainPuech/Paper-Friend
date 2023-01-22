#include "DataAnalysis.h"
#include <Frontend/entryclasses.h>

#include <algorithm>
#include <cmath> //prefer the c- version rather than the .h
#include <map>
#include <numeric>
#include <vector>

// using namespace std; don't be lazy and just use the specifier, it
// avoids naming conflicts. If you really have to use it, put it in the most
// restricted scope possible (

// Never manually iterate trough an STL container with iterators. Either use
// the normal syntax or use range based for loops like the one below

double DataAnalysis::avg(const std::vector<EntryPerso> &entries,
                         int var_index) const {
  /**
   * @param vector<EntryPerso>
   *        var_index : variable to average
   * @return average value of the variable across the entries
   */

  return avg<double>(get_vect(entries, var_index));
}

double DataAnalysis::cov(const std::vector<double> &X,
                         const std::vector<double> &Y) const {
  /**
   * @param vectors double X, Y.
   * @return Cov(X, Y).
   */
  // Just in case the two have different sizes but shouldn't be the case
  std::vector<double> XY{};
  for (unsigned int i = 0; i < std::min(X.size(), Y.size()); ++i)
    XY.push_back(X[i] * Y[i]);

  return avg(XY) - avg(X) * avg(Y);
}

LinearRegressionCoeffs DataAnalysis::compute_linear_regression_coeffs(
    const std::vector<double> &X, const std::vector<double> &Y) const {
  /**
   * @param vectors double X, Y.
   * @return LinearRegressionCoeffs object corresponding to fitting Y against X.
   */

  double slope;
  double variance_x = pow(stddev(X), 2);
  if (variance_x == 0)
    slope = 0;
  else
    slope = cov(X, Y) / pow(stddev(X), 2);

  double intercept = avg(Y) - slope * avg(X);
  double quality_coeff = pow(cor(X, Y), 2);

  return LinearRegressionCoeffs(slope, intercept, quality_coeff);
}

LinearRegressionCoeffs DataAnalysis::compute_linear_regression_coeffs(
    const std::vector<EntryPerso> &entries, int var1_index,
    int var2_index) const {
  /**
   * @param vectors of entries, and two variables
   * @return LinearRegressionCoeffs object corresponding to fitting the second
   * variable against the first. across the values of each in entries.
   */
  std::vector<double> X = get_vect(entries, var1_index);
  std::vector<double> Y = get_vect(entries, var2_index);
  return compute_linear_regression_coeffs(X, Y);
}

/*LinearRegressionCoeffs DataAnalysis::general_trend(int n, int var_index) const
{
  /**
   * @param int n : represents number of days to consider.
   *        int var_index: variable to consider.
   * @return LinearRegressionCoeffs object corresponding to fitting the variable
   * against the number of days since the first entry within n days of the last
   * entry in the log. The function uses doubles to store ints because the
   * functions used to calculate the desired coefficients are defined on vectors
   * of doubles.
   *

  std::vector<EntryPerso> entries = get_lastn_days_data(n);
  if (entries.size() == 0){
      return empty;
  }
  std::vector<double> values = get_vect(entries, var_index);
  std::vector<double> no_of_days;

  double first_day = entries.front().get_absolute_day();
  for (auto &entry : entries)
    no_of_days.push_back(entry.get_absolute_day() - first_day);
  return compute_linear_regression_coeffs(no_of_days, values);
}*/

LinearRegressionCoeffs empty(99, 0, 0);

LinearRegressionCoeffs
DataAnalysis::general_trend(const std::vector<EntryPerso> &entries,
                            int var_index) const {
  // Just the above function without the need to get the entries.
  if (entries.size() == 0)
    return empty;

  if (var_index >= 6 || stl == false) {
    std::vector<double> values = get_vect(entries, var_index);
    std::vector<double> no_of_days;

    double first_day = entries.front().get_absolute_day();
    for (auto &entry : entries)
      no_of_days.push_back(entry.get_absolute_day() - first_day);
    return compute_linear_regression_coeffs(no_of_days, values);
  } else {
    std::vector<double> Yvalues;
    std::vector<double> Xvalues;
    bool haveX = false;
    for (int i = 0; i < entries.size(); ++i) {
      for (int j = 0; j < STL_X[var_index].size(); ++j) {
        if (STL_X[var_index][j] == entries[i].get_absolute_day()) {
          Yvalues.push_back(STL_Trends[var_index][j]);
          haveX = true;
        }
      }
      if (haveX == true) {
        Xvalues.push_back(entries[i].get_absolute_day());
        haveX = false;
      }
    }
    return compute_linear_regression_coeffs(Xvalues, Yvalues);
  }
}

double DataAnalysis::stddev(const std::vector<double> &data) const {
  /**
   * @param vector data.
   * @return standart deviation.

   */
  if (data.size() == 0)
    return 0;
  double residue_sum = 0.0;

  double mean = avg<double>(data);

  // Never manually iterate trough an STL container with iterators. Either use
  // the normal syntax or use range based for loops like the one below
  for (auto el : data)
    residue_sum += std::pow(mean - el, 2);

  return sqrt(residue_sum / data.size());
}

double DataAnalysis::stddev(const std::vector<EntryPerso> &entries,
                            int var_index) const {
  /**
   * @param vector<EntryPerso>
   *        var_index : variable to consider
   * @return standard deviation of values of the variable across the entries
   */
  return stddev(get_vect(entries, var_index));
}
double DataAnalysis::cor(const std::vector<double> &X,
                         const std::vector<double> &Y) const {
  /**
   * @param vectors double X, Y.
   * @return Cor(X, Y).
   */
  double stdx = stddev(X);
  double stdy = stddev(Y);
  if (stdx == 0 || stdy == 0)
    return 0;

  return cov(X, Y) / stdx / stdy;
}

std::vector<EntryPerso> DataAnalysis::get_lastn_days_data(int n,
                                                          int reference) const {
  /**
   * @param int n: number n of days.
   * @return a list of all data within n days of the reference (if the reference
   * is negative we count back from the date of last log).
   */
  if (log.size() == 0)
    return std::vector<EntryPerso>();

  int current; // represents the date from which we count backwards
  if (reference < 0)
    current = log[log.size() - 1].get_absolute_day();
  else
    current = reference;

  auto comp_l{[current](auto &entry, int n) {
    return entry.get_absolute_day() < current - n ||
           entry.get_absolute_day() > current;
  }};
  auto cutoff_l = std::lower_bound(log.begin(), log.end(), n, comp_l);

  auto comp_r{[current](auto &entry, int n) {
    return entry.get_absolute_day() <= current;
  }};

  auto cutoff_r = std::lower_bound(cutoff_l, log.end(), n, comp_r);
  std::vector<EntryPerso> res(cutoff_l, cutoff_r);
  return res;
}

// double DataAnalysis::get_var(const EntryPerso& entry, int var_index) const {
/**
 *        Variables var_name : represents the variable to get.
 * @return the value of the variable in the entry.
 */
/*
switch (var_name) {

    case MOOD:
 * @param EntryPerso entry : entry of interest.
        return entry.get_mood();
        break;

    case SLEEP:
        return entry.get_sleep();
        break;

    case EATING_HEALTHY:
        return entry.get_eating_healthy();
        break;

    case PRODUCTIVITY:
        return entry.get_productivity();
        break;

    case SOCIALIZING:
        return entry.get_socializing();
        break;

    case PHYSICAL_ACTIVITY:
        return entry.get_physical_activity();
}


} */

// void DataAnalysis::set_var(EntryPerso& entry, Variables var_name, double
// value) const {
//  This method will probably not be used that much but here just in case.
/**
 * @param EntryPerso entry : entry of interest.
 *        Variables var_name : represents the variable to set.
 *        double value : new value of the variable.
 * @return the value of the variable in the entry.
 */
/*
    switch (var_name) {

        case MOOD:
            entry.set_mood(value);
            break;

        case SLEEP:
            entry.set_sleep(value);
            break;

        case EATING_HEALTHY:
            entry.set_eating_healthy(value);
            break;

        case PRODUCTIVITY:
            entry.set_productivity(value);
            break;

        case SOCIALIZING:
            entry.set_socializing(value);
            break;

        case PHYSICAL_ACTIVITY:
            entry.set_physical_activity(value);
        }
}
*/
std::vector<double>
DataAnalysis::get_vect(const std::vector<EntryPerso> &entries,
                       int var_index) const {
  /**
   * @param vector of entries
   *        var_index : represents the variable we consider
   * @return the vector of values of the variable across entries.
   */
  std::vector<double> res;
  for (auto &entry : entries)
    res.push_back(entry.get_var_value(var_index));

  return res;
}

double DataAnalysis::get_lastn_average(int n, int var_index) const {
  /**
   * @param int n: number of n last entries we take into account
   *        int var_index: variable index starting from 0: MOOD
   * @return double average of the values of the variable represented by
   *        var_index for last n entries
   */
  std::vector<double> val_list{};

  for (unsigned int i = std::max<int>(0, log.size() - n); i < log.size(); ++i)
    val_list.push_back(log[i].get_var_value(var_index));
  return avg<double>(val_list);
}

std::vector<EntryPerso>
DataAnalysis::anomalies_detection(const std::vector<EntryPerso> &entries,
                                  int var_index) const {
  /**
   * @param vector of EntryPersos, var_index.
   * @return vector of entries at which anomalie in the variable was detected
   * (value is 2 SDs far from its mean).
   */
  std::vector<EntryPerso> res;

  if (var_index >= 6 || stl == false) {
    int furthest_day = 0;
    for (int i = 0; i < entries.size(); ++i) {
      if (entries[i].get_absolute_day() - QDate::currentDate().toJulianDay() >
          furthest_day)
        furthest_day =
            entries[i].get_absolute_day() - QDate::currentDate().toJulianDay();
    }
    std::vector<EntryPerso> daysAnalyze = get_lastn_days_data(furthest_day * 2);
    double mean = avg(daysAnalyze, var_index);
    double st_dev = stddev(daysAnalyze, var_index);

    for (auto &entry : entries) {
      if (entry.get_var_value(var_index) - mean >= 2 * st_dev)
        res.push_back(entry);
    }
    return res;
  } else {
    std::vector<double> remain = STL_Remainders[var_index];
    double mean = avg<double>(remain);
    double st_dev = stddev(remain);
    // TODO : Optimize this by considering entries sorted
    // chronologically
    for (int i = 0; i < entries.size(); ++i) {
      for (int j = 0; j < STL_X[var_index].size(); ++j) {
        if (STL_X[var_index][j] == entries[i].get_absolute_day())
          if (STL_Remainders[var_index][j] - mean > 2 * st_dev)
            res.push_back(entries[i]);
      }
    }
    return res;
  }
}

// std::vector<int> DataAnalysis::anomalies_by_groups(const
// std::vector<EntryPerso> &entries, int num_days, int var_index){
/**
 * @param entries, the number of days per group, variable to be considered
 * @return list of indices of groups whose average w.r.t the variable is an
 * anomaly in the sense of the funciton above.
 */
/*   double mean = avg(entries, var_index);
   double standev = stddev(entries, var_index);
   std::vector<int> res;




   return res;
}*/

std::vector<double> DataAnalysis::cyclic_week(int metric_index) {
  /*
   * Input is an int between 0 and 6
   * Output is a 7-len vector containing the average seasonality over [mondays,
   * ..., sundays]
   *
   * */
  std::vector<double> seasonality;
  if (stl == true) {
    std::vector<std::vector<double>> subSeries = {{}, {}, {}, {}, {}, {}, {}};
    for (int i = 0; i < STL_X[metric_index].size(); ++i) {
      subSeries[QDate::fromJulianDay(STL_X[metric_index][i]).dayOfWeek() - 1]
          .push_back(STL_Seasonalities[metric_index][i]);
    }
    for (int sub = 0; sub < 7; ++sub) {
      seasonality.push_back(avg(subSeries[sub]));
    }
  } else {
    seasonality = {0, 0, 0, 0, 0, 0, 0};
  }
  return seasonality;
}

std::multimap<double, int> invert(std::map<int, double> &mymap) {
  /**
   * @param map
   * @returns inversed map (swaps keys with values)
   */
  std::multimap<double, int> multiMap;

  std::map<int, double>::iterator it;
  for (it = mymap.begin(); it != mymap.end(); it++) {
    multiMap.insert(std::make_pair(it->second, it->first));
  }

  return multiMap;
}

std::vector<int>
DataAnalysis::item_priority(const std::vector<EntryPerso> &entries,
                            int var_index) {
  /**
   * @param entries list, index of the variable concerned
   *
   * @returns list of indices (of other variables) with those coming first
   * having the most effect on the given variable.
   */

  std::vector<double> var_vect = get_vect(entries, var_index);
  std::vector<double> current;

  double cor_with_var;
  std::map<int, double> influence;

  for (int i = 0; i < get_num_activities(); ++i) {
    if (var_index == i) {
      continue;
    }
    current = get_vect(entries, var_index);
    cor_with_var = cor(current, var_vect);
    // dev = abs(get_lastn_average(std::min(7, N), i) -
    //           get_lastn_average(std::min(N, 30), i));
    influence[i] = cor_with_var;
  }

  // Sort map (done with MULTIMAP)
  std::map<double, int>::iterator iter;

  // invert mymap using the invert function created above

  std::multimap<double, int> newmap = invert(influence);
  // pushing sorted item names in the vector
  std::vector<int> vec{};
  for (iter = newmap.begin(); iter != newmap.end(); iter++) {
    vec.push_back(iter->second);
  }
  return vec;
}

void reverseStr(std::string &str) {
  int n = str.length();

  // Swap character starting from two
  // corners
  for (int i = 0; i < n / 2; i++)
    std::swap(str[i], str[n - i - 1]);
}

std::string int_to_str(int a) {
  std::string str = "";
  while (a != 0) {
    char temp_str = static_cast<char>(48 + a % 10);
    str += temp_str;
    a /= 10;
  }
  reverseStr(str);

  return str;
}

std::string DataAnalysis::suggestion() { // some more exciting gameplay can be implementen later
  /**
   *
   * @returns string with suggestion to the user
   *
     - Compares todays mood to last 7 days avg. If the mood got wors,
       it recommends to work on top 2 items which contributed to this the most,
       or if the progress in mood is positive, tells which are the top two items that improved the progress the most.

     - Tells the user if he didn't see his friends for last n days [NOT YET]

   */
  std::string str{};

  // Comparing to previous results of MOOD:

  if (log.back().get_var_value(0) >= get_lastn_average(7, 0)) { // compares to last 7 days
    str += "Your " + log[0].get_var_name(0) +
           " today is better than average! \n";
    str +=
        "Your progress in " +
        var_to_str(*(item_priority(log, 0).begin())) + " and " +
        var_to_str(*(item_priority(log, 0).begin() + 1)) +
        " improves your " + log[0].get_var_name(0) +
        " the most, keep it up! \n"; // suggest top two items which affected the
                                     // variable (mood by default) the most
  } else {
    str += "Your " + log[0].get_var_name(0) +
           " today is less than average:( \n";
    str += "Try to work on your " +
           var_to_str(*(item_priority(log, 0).begin())) + " and " +
           var_to_str(*(item_priority(log, 0).begin() + 1)) + "! \n\n";
  }

  return str;
}

std::string DataAnalysis::react_depression(){
    std::string str = "";
    if (log.end()->get_var_value(0) <= 0.5 * get_lastn_average(7, 0)){
        str += "Seems like you have a depression:(";
        str += "The two main things to fix is your " +
        var_to_str(*(item_priority(log, 0).begin())) + " and " +
        var_to_str(*(item_priority(log, 0).begin() + 1)) + "! \n";
        str += "Keep going! Everything will be alright! \n\n";
    }
    return str;
}

std::vector<int> lengths{7, 30, 365};
std::vector<std::string> periods{"week", "month", "year"};

void DataAnalysis::weekly_anomalies_text(
    const std::vector<EntryPerso> &entries,
    std::vector<std::string> &string_vect) {
  /**
   * @param entries, vector of strings
   *
   *fills up the vector with text of the anomalies detection done over the
   *entries (which will represent a week's worth of data)
   *
   */
  for (int i = 0; i < get_num_activities(); ++i) {
    std::vector<EntryPerso> anomalies = anomalies_detection(entries, i);
    if (anomalies.size() == 0) {
      string_vect[i] += "No anomalies were detected over the week.";
    } else if (anomalies.size() == 1) {
      string_vect[i] += "An anomaly was detected on ";
      string_vect[i] += anomalies[0].get_weekday() + ".";
    } else {
      string_vect[i] += "Anomalies were detected on ";
      for (unsigned int j = 0; j < anomalies.size() - 1; ++j) {
        string_vect[i] += anomalies[j].get_weekday();
        string_vect[i] += ", ";
      }
      string_vect[i] += "and ";
      string_vect[i] += anomalies[anomalies.size() - 1].get_weekday() + ".";
    }
    string_vect[i] += "\n\n";
  }
}

void DataAnalysis::monthly_anomalies_text(
    const std::vector<EntryPerso> &entries,
    std::vector<std::string> &string_vect) {
  /**
   * @param entries, vector of strings
   *
   *fills up the vector with text of the anomalies detection done over the
   *entries (which will represent a month's worth of data.
   *
   */
  std::vector<std::vector<EntryPerso>> groups;
  int references[]{-1, 7, 14, 21};
  std::string weeks[]{"first", "second", "third", "fourth"};
  for (int j = 0; j < 4; ++j) {
    groups.push_back(get_lastn_days_data(7, references[j]));
  }
  std::vector<int> anomalies;
  double mean;
  double standev;

  for (int i = 0; i < get_num_activities(); ++i) {
    mean = avg(entries, i);
    standev = stddev(entries, i);
    for (int k = 0; k < 4; ++k) {
      if (groups[k].size() == 0) {
        continue;
      }
      if (abs(mean - avg(groups[k], i)) >= 2 * standev) {
        anomalies.push_back(k);
      }
    }

    if (anomalies.size() == 0 || standev == 0) {
      string_vect[i] +=
          "This has been relatively stable over the weeks of the past month.";

    } else if (anomalies.size() == 1) {
      string_vect[i] += "The " + weeks[anomalies[0]] +
                        " week of the past month was an outlier.";
    } else {
      string_vect[i] += "The ";
      for (unsigned int m = 0; m < anomalies.size() - 1; ++m) {
        string_vect[i] += weeks[anomalies[m]] + ", ";
      }
      string_vect[i] += "and " + weeks[anomalies[anomalies.size() - 1]] +
                        " weeks of the past month were outliers.";
    }
    string_vect[i] += "\n\n";
    anomalies.clear();
  }
}

void DataAnalysis::yearly_anomalies_text(
    const std::vector<EntryPerso> &entries,
    std::vector<std::string> &string_vect) {
  /**
   * @param entries, vector of strings
   *
   *fills up the vector with text of the anomalies detection done over the
   *entries (which will represent a year's worth of data.
   *
   */
  std::vector<std::vector<EntryPerso>> groups;
  int references[]{-1, 30, 60, 90, 120, 150, 180, 210, 240, 270, 300, 330};
  std::string weeks[]{"first", "second", "third", "fourth"};
  for (int j = 0; j < 12; ++j) {
    groups.push_back(get_lastn_days_data(30, references[j]));
  }
  std::vector<int> anomalies;
  double mean;
  double standev;
  for (int i = 0; i < get_num_activities(); ++i) {
    std::vector<int> anomalies;
    mean = avg(entries, i);
    standev = stddev(entries, i);
    for (int k = 0; k < 12; ++k) {
      if (groups[k].size() == 0) {
        continue;
      }
      if (abs(mean - avg(groups[k], i)) >= 2 * standev) {
        anomalies.push_back(k);
      }
    }

    if (anomalies.size() == 0 || standev == 0) {
      string_vect[i] +=
          "This has been relatively stable over the months of the past year.";

    } else if (anomalies.size() == 1) {
      string_vect[i] += groups[anomalies[0]][groups[anomalies[0]].size() / 2]
                            .get_month_name() +
                        " was an outlier in the past year.";
    } else {
      string_vect[i] += "The months of ";
      for (unsigned int m = 0; m < anomalies.size() - 1; ++m) {
        string_vect[i] += groups[anomalies[m]][groups[anomalies[m]].size() / 2]
                              .get_month_name() +
                          ", ";
      }
      string_vect[i] +=
          "and " +
          groups[anomalies[anomalies.size() - 1]]
                [groups[anomalies[anomalies.size() - 1]].size() / 2]
                    .get_month_name() +
          " were outliers in the past year.";
    }
    string_vect[i] += "\n\n";
    anomalies.clear();
  }
}

std::string
DataAnalysis::generate_recap_text(const std::vector<EntryPerso> &entries,
                                  int type) {
  /**
   * @param entries, type of period (0 : weekly, 1 : monthly,
   *2 : yearly).
   *
   *@returns string of the detailed analysis done over the entries over the
   *period described by the type
   */
  std::string res = "";
  std::vector<std::string> anomaly_texts;
  for (int i = 0; i < get_num_activities(); ++i) {
    anomaly_texts.push_back("");
  }
  switch(type){
      case 0:
          weekly_anomalies_text(entries, anomaly_texts);
          break;
      case 1:
          monthly_anomalies_text(entries, anomaly_texts);
          break;
      case 2:
          yearly_anomalies_text(entries, anomaly_texts);

  }

  double slight_threshold = 0.5; // Some constants to guide judgement
  double significant_threshold = 1.5;
  double quality_threshold = 0.7;

  for (int i = 0; i < get_num_activities(); ++i) {

    res += var_to_str(i) + "\n\n";

    LinearRegressionCoeffs coeffs = general_trend(entries, i);

    if (coeffs.quality_coeff < quality_threshold){
        res +=
            "This has not shown any clear trend over the past " + periods[type] + ".";
    }

    else if (abs(coeffs.slope) < slight_threshold) {

       res += "This has been steady over the past " + periods[type] + ".";
    }

    else if (abs(coeffs.slope) < significant_threshold) {
      if (coeffs.slope < 0) {
        res += "This has been slightly dipping over the past " + periods[type] + ".";
      } else {
        res +=
            "This has been slightly improving over the past " + periods[type] + ".";
      }
    }

    else {
      if (coeffs.slope < 0) {

        res += "This has shown a significant downward trend over the past " +
               periods[type] + ".";

      } else {
        res += "This has shown a significant upward trend over the past " +
               periods[type] + ".";
      }
    }
    res += "\n\n";
    std::vector<int> influences = item_priority(entries, i);
    res += "It seems like ";
    res += var_to_str(influences[0]);
    res += " and ";
    res += var_to_str(influences[1]);
    res += " have the most effect.\n\n";
    res += anomaly_texts[i];
  }
  return res;
}

EntryRecap* DataAnalysis::recap(int type) {
  /**
   * @param  an integer representing the period to be considered. 0 = week, 1 =
   * month, 2 = year.
   *
   * @returns an EntryRecap object containing info about the period specified by
   * type.
   */

  std::vector<EntryPerso> period = get_lastn_days_data(lengths[type]);
  auto comp{[](EntryPerso &entry1, EntryPerso &entry2) -> bool {
    return entry1.get_var_value(0) < entry2.get_var_value(0);
  }};

  EntryPerso best_day = *(std::max_element(period.begin(), period.end(), comp));
  EntryPerso worst_day =
      *(std::min_element(period.begin(), period.end(), comp));

  double avg_mood = avg(period, 0);

  double good_threshold = 60;
  double great_threshold = 80;

  std::string detailed_analysis = generate_recap_text(period, type);

  std::string text = "You have made " + std::to_string(period.size()) +
                     " entries over the past " + periods[type] + ".\n\n";

  if (avg_mood < good_threshold) {
    text += "Looks like you've had a tough " + periods[type];
  } else if (avg_mood < great_threshold) {
    text += "Looks like you've had a good " + periods[type];
  } else {
    text += "Looks like you've had a great " + periods[type];
  }
  text += "\n\n";
  text += "Your best and worst days, as indicated by your mood, were on " +
          best_day.get_date() + " and " + worst_day.get_date() +
          " respectively.\n\n";
  text += "Here is a summary of your " + periods[type] + " across all areas: \n\n";
  text += detailed_analysis;


  QDate best_day_date = best_day.get_qdate();
  QDate worst_day_date = worst_day.get_qdate();
  double best_day_mood = best_day.get_mood();
  double worst_day_mood = worst_day.get_mood();
  return new EntryRecap(best_day_date, worst_day_date,best_day_mood,worst_day_mood, text, avg_mood, type);

}

EntryRecap* DataAnalysis::weekly_recap() {
  /**
   * @param
   *
   * @returns an EntryRecap object containing info about the week.
   */
  return recap(0);
}
EntryRecap* DataAnalysis::monthly_recap() {
  /**
   * @param
   *
   * @returns an EntryRecap object containing info about the month.
   */
  return recap(1);
}
EntryRecap* DataAnalysis::yearly_recap() {
  /**
   * @param
   *
   * @returns an EntryRecap object containing info about the year.
   */
  return recap(2);
}

// STL decomposition implementation start

// Robert B. Cleveland, William S. Cleveland, Jean E. McRae, and Irma Terpenning
// : STL : A Seasonal-Trend Decomposition Procedure Based on Loess.

bool smallerEqual(double a, double b) { return a <= b; }

int find_index_sorted(
    double x, std::vector<double> &data) { // Basic dichotomy implementation
  // Returns the biggest index corresponding in data to a number <= x   (for ex,
  // find_index(2.5, {0, 1, 2, 3}) returns 2)
  if (data.size() == 0) {
    qDebug() << "Data of length 0 on find_index_sorted";
  }
  if (x < data[0]) {
    return 0;
  }
  if (data[data.size() - 1] < x) {
    return data.size() - 1;
  }
  return std::distance(data.begin(), std::lower_bound(data.begin(), data.end(),
                                                      x, smallerEqual)) -
         1;
}
std::vector<int> closest_q_index_in_sorted(
    double x, int q, std::vector<double> &data) { // Data needs to be sorted
  // Returns a vector containing the index of the closest q elements to x in
  // data
  if (q > data.size()) {
    q = data.size();
  }
  int biggest_smaller_than_x_index = find_index_sorted(x, data);
  int iterLow = biggest_smaller_than_x_index; // Iterates on values smaller than
                                              // (or equal to) x
  int iterHigh =
      biggest_smaller_than_x_index + 1; // Iterates on values bigger than x
  std::vector<int> answer;
  while (answer.size() < q) {
    // If we reach the end of the vector, we need to take values from the other
    // side
    if (iterLow == -1) {
      answer.push_back(iterHigh);
      iterHigh++;
    } else if (iterHigh == data.size()) {
      answer.push_back(iterLow);
      iterLow--;
    } else {
      // Otherwise, add value closest to x
      if (x - data[iterLow] < data[iterHigh] - x) {
        answer.push_back(iterLow);
        iterLow--;
      } else {
        answer.push_back(iterHigh);
        iterHigh++;
      }
    }
  }
  std::sort(answer.begin(), answer.end());
  return answer;
}
double furthest_distance(
    double x,
    std::vector<double>
        data) { // Used to compute Gamma_q on the data subset gained by
                // closest_q, to compute Gamma_n on the whole dataset
  // Returns the maximum "distance" between x and points in the data
  double max = 0;
  for (int i = 0; i < data.size(); i++) {
    if (max < std::abs(x - data[i])) {
      max = std::abs(x - data[i]);
    }
  }
  return max;
}

double tricube_weight(double u) {
  if (u >= 1) {
    return 0;
  } else {
    return std::pow((1 - (std::pow(u, 3))), 3);
  }
} // W(u)
double neighborhood_weight(double xi, double x,
                           double distance_furthest) { // v_i(x)
  return tricube_weight(std::abs(xi - x) / distance_furthest);
}

double eval_poly(std::vector<double> coeffs,
                 double x) { // coeffs for [x^n, x^n-1, ...]
  // Evaluates a polynomial at x using Horner scheme
  double value = coeffs[0];
  for (int i = 1; i < coeffs.size(); i++) {
    value *= x;
    value += coeffs[i];
  }
  return value;
}

double determinant_m3(std::vector<std::vector<double>> matrix) {
  if (matrix.size() != 3 || matrix[0].size() != 3 || matrix[1].size() != 3 ||
      matrix[2].size() != 3) {
    qDebug() << "Matrix size not 3x3 but " << QString::number(matrix.size())
             << " rows and " << QString::number(matrix[0].size())
             << " columns (on first line)";
    throw std::invalid_argument("Matrix not of correct size");
  }

  return (matrix[0][0] *
          (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])) -
         (matrix[0][1] *
          (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])) +
         (matrix[0][2] *
          (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]));
}

std::vector<double> weighted_least_squares(std::vector<double> dataX,
                                           std::vector<double> dataY,
                                           std::vector<double> weights = {-1}) {
  if (weights.size() == 1 && weights[0] == -1) {
    weights = std::vector<double>(dataX.size(), 1);
  }

  if (dataX.size() == 0) {
    qDebug() << "Weighted least_squares unsuccessful call : data size is 0\n";
    throw std::invalid_argument("Length of data is 0");
  } else if (dataX.size() != dataY.size() || dataY.size() != weights.size()) {
    qDebug() << "Weighted least_squares unsuccessful call : data not of same "
                "sizes (dataX :"
             << QString::number(dataX.size())
             << ", dataY :" << QString::number(dataY.size())
             << ", weights :" << QString::number(weights.size()) << ")\n";
    throw std::invalid_argument("Data not all of same length");
  }

  // We solve this as a linear system using cramer's rule.
  double sum_x = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0, sum_x2y = 0, sum_xy = 0,
         sum_y = 0, sum_1 = 0, xwi, xi, yi;
  for (int i = 0; i < dataX.size(); i++) {
    // I tried to reduce the amount of multiplications but it increased the
    // amount of memory accesses
    sum_1 += weights[i];
    xi = dataX[i];
    yi = dataY[i];
    xwi = xi * weights[i];
    sum_x += xwi;
    sum_y += yi * weights[i];
    sum_xy += xwi * yi;
    sum_x2y += xwi * xi * yi;
    sum_x2 += xwi * xi;
    sum_x3 += xi * xi * xwi;
    sum_x4 += std::pow(xi, 3) * xwi;
  }
  double detMat =
      determinant_m3(std::vector<std::vector<double>>{{sum_x4, sum_x3, sum_x2},
                                                      {sum_x3, sum_x2, sum_x},
                                                      {sum_x2, sum_x, sum_1}});
  double detA =
      determinant_m3(std::vector<std::vector<double>>{{sum_x2y, sum_x3, sum_x2},
                                                      {sum_xy, sum_x2, sum_x},
                                                      {sum_y, sum_x, sum_1}});
  double detB =
      determinant_m3(std::vector<std::vector<double>>{{sum_x4, sum_x2y, sum_x2},
                                                      {sum_x3, sum_xy, sum_x},
                                                      {sum_x2, sum_y, sum_1}});
  double detC =
      determinant_m3(std::vector<std::vector<double>>{{sum_x4, sum_x3, sum_x2y},
                                                      {sum_x3, sum_x2, sum_xy},
                                                      {sum_x2, sum_x, sum_y}});
  // qDebug() << detA << " " << detB << " " << detC << " " << detMat;
  std::vector<double> coefficients = {detA / detMat, detB / detMat,
                                      detC / detMat};
  return coefficients;
}

double loess_x(std::vector<double> dataX, std::vector<double> dataY, double q,
               double x, std::vector<double> robust_w = {-1}) {
  // Computes g_hat (extrapolation of the trend-cycle ?) assuming dataX is
  // sorted

  std::vector<int> closest_xi_index = closest_q_index_in_sorted(x, q, dataX);

  double furthest_distance =
      std::max(
          static_cast<double>(std::abs(x - dataX[closest_xi_index[0]])),
          std::abs(x - dataX[closest_xi_index[closest_xi_index.size() - 1]])) *
      std::max(static_cast<double>(1), q / static_cast<double>(dataX.size()));

  std::vector<double> weights, closest_xi, closest_yi;

  for (int i = 0; i < closest_xi_index.size(); i++) {

    if (robust_w[0] == -1) {
      weights.push_back(neighborhood_weight(dataX[closest_xi_index[i]], x,
                                            furthest_distance));
    } else {
      weights.push_back(neighborhood_weight(dataX[closest_xi_index[i]], x,
                                            furthest_distance) *
                        robust_w[closest_xi_index[i]]);
    }

    closest_xi.push_back(dataX[closest_xi_index[i]]);
    closest_yi.push_back(dataY[closest_xi_index[i]]);
  }
  // Residual = sum wi * (yi - (x^2 b_2 + x b_1 + b_0)^2) = (Y - XB)
  double value =
      eval_poly(weighted_least_squares(closest_xi, closest_yi, weights), x);
  return value;
}

std::vector<double> moving_average(std::vector<double> data, double length) {
  std::vector<double> result;
  double sum = 0;
  for (int i = 0; i < length; i++) {
    sum += data[i];
  }
  result.push_back(sum / length);
  for (int i = 0; i < data.size() - length; i++) {
    sum += data[i + length] - data[i];
    result.push_back(sum / length);
  }
  return result;
}

double bisquare_weight_function(double u) {
  if (u > 1) {
    return 0;
  }
  return std::pow(1 - std::pow(u, 2), 2);
}

std::vector<std::vector<double>> DataAnalysis::stl_regression(
    std::vector<double> dataX, std::vector<double> dataY,
    int seasonal_length =
        7) { // Definitely need to change this and the hpp file
  /**
   *@param seasonal_length : how much observations in a seasonal component cycle
   *(most likely 7/1 otherwise 30/1)
   *
   *
   *
   *
   */
  // TODO : optimize time spent for cycle subseries
  // 0 is today, 1 is yesterday

  if (dataX.size() == 0) {
    qDebug() << "stl_regression unsuccessful call : invalid length of data, "
                "not multiple of seasonal_length\n";
    throw std::invalid_argument("Length of data is invalid");
  } else if (dataX.size() != dataY.size()) {
    qDebug() << "stl_regression unsuccessful call : dataX size "
             << QString::number(dataX.size()) << " != dataY size "
             << QString::number(dataY.size()) << ".\n";
    throw std::invalid_argument("Data not all of same length");
  }

  // dataX starts at 0 to be clearer
  for (int i = 1; i < dataX.size(); i++) {
    dataX[i] = dataX[i] - dataX[0];
  }
  dataX[0] = 0;

  int N = dataX[dataX.size() - 1] + 1; //+1 bc start at 0

  int ni = 1;
  int no = 10;
  int np = seasonal_length;
  int ns = 35; // how much cycle subseries will be smoothed
  int nl = np + (1 - (np % 2));
  int nt;
  if (dataX.size() > 200) {
    nt = 13;
  } else {
    nt = 17;
  } // how much trend is smooth
  int nb_seasons = N / np;
  if (np * nb_seasons != N) {
    nb_seasons++;
  }

  std::vector<double> Trend(N, 0);
  std::vector<double> Seasonality(N, 0);
  std::vector<double> Detrended(dataX.size(), 0);
  std::vector<std::vector<double>> all_cycle_subseries_detrended(
      np); // list of subseries in detrended
  std::vector<std::vector<double>> X_all_cycle_subseries_detrended(np);
  std::vector<std::vector<double>> all_cycle_subseries_smoothed(
      np); // list of subseries smoothed
  std::vector<double> Cycle_subseries_smoothed(N + 2 * seasonal_length,
                                               0); // regroup all subseries
  std::vector<double> Moving_averages_cycle_subseries;
  std::vector<double> Loess_cycle_subseries(N, 0);
  std::vector<double> Deseasonalized(dataX.size(), 0);

  std::vector<double> Remainder(dataX.size(), 0);
  std::vector<double> Abs_Remainder(dataX.size(), 0);
  double h;
  std::vector<double> robustness_weight(dataX.size(), -1);

  for (int outer_loop = 0; outer_loop < no; outer_loop++) {

    /*qDebug() << "\nTrend";
    qDebug()<< Trend ;
    qDebug() << "\nSeasonality";
    qDebug()<< Seasonality ;
    qDebug() << "\nrobustness_weight";
    qDebug()<< robustness_weight ;
    qDebug() << "\ndataX";
    qDebug()<< dataX;
    qDebug() << "\ndataY";
    qDebug()<< dataY;*/

    for (int inner_loop = 0; inner_loop < ni; inner_loop++) {

      // Step 1 : Detrending
      for (int v = 0; v < dataX.size(); v++) {
        Detrended[v] = dataY[v] - Trend[dataX[v]];
      }

      /*qDebug() << "\nDetrended";
      qDebug()<< Detrended ;*/

      // Step 2 : Cycle-subseries smoothing (cycle-subseries = seasonal_length
      // observations)
      for (int i = 0; i < np; i++) {
        all_cycle_subseries_detrended[i] = {};
        X_all_cycle_subseries_detrended[i] = {};
        all_cycle_subseries_smoothed[i] = {};
      }
      for (int i = 0; i < dataX.size(); i++) {
        all_cycle_subseries_detrended[static_cast<int>(dataX[i]) % np]
            .push_back(Detrended[i]);
        X_all_cycle_subseries_detrended[static_cast<int>(dataX[i]) % np]
            .push_back(static_cast<int>(dataX[i]) / np);
      }

      /*qDebug() << "\nsubseries detrended";
      qDebug()<< all_cycle_subseries_detrended;
      qDebug() << "\nX_subseries detrended";
      qDebug()<< X_all_cycle_subseries_detrended;*/

      for (int subseries = 0; subseries < np; subseries++) {
        for (int i = -1; i < nb_seasons + 1;
             i++) { // start at -1, end at nb_seasons + 1
          all_cycle_subseries_smoothed[subseries].push_back(
              loess_x(X_all_cycle_subseries_detrended[subseries],
                      all_cycle_subseries_detrended[subseries], ns, i,
                      robustness_weight));
        }
      }

      /*qDebug() << "\nsubseries smoothed";
      qDebug()<< all_cycle_subseries_smoothed;
      qDebug()<< "\n";*/

      Cycle_subseries_smoothed = {};
      for (int i = 0; i < N + 2 * np; i++) {
        Cycle_subseries_smoothed.push_back(
            all_cycle_subseries_smoothed[i % np][i / np]);
      }

      /*qDebug()  << "\ncycle subseries";
      qDebug() << Cycle_subseries_smoothed;*/

      // Step 3 : Low-Pass Filtering of Smoothed Cycle-Subseries

      Moving_averages_cycle_subseries =
          moving_average(Cycle_subseries_smoothed, np);
      Moving_averages_cycle_subseries =
          moving_average(Moving_averages_cycle_subseries, np);
      Moving_averages_cycle_subseries =
          moving_average(Moving_averages_cycle_subseries, 3);

      /*qDebug() << "\nmoving_average3";
      qDebug() << Moving_averages_cycle_subseries;*/

      for (int i = 0; i < N; i++) {
        Loess_cycle_subseries[i] =
            loess_x(dataX, Moving_averages_cycle_subseries, nl, i);
      }

      /*qDebug()<< "\nloess cycle";
      qDebug()<< Loess_cycle_subseries;*/

      // Step 4 : Detrending of Smoothed Cycle-Subseries
      for (int i = 0; i < N; i++) {
        Seasonality[i] = Cycle_subseries_smoothed[i] - Loess_cycle_subseries[i];
      }

      // Step 5 : Deseasonalizing
      for (int i = 0; i < dataX.size(); i++) {
        Deseasonalized[i] = dataY[i] - Seasonality[dataX[i]];
      }

      /*
       * qDebug() << "\nDeseasonalized";
      qDebug() <<Deseasonalized;
      qDebug() << "\n\n";

      qDebug() << "\nother values";
      qDebug() << robustness_weight.size();
      qDebug() << dataX.size();
      qDebug() << Deseasonalized.size();
      qDebug() << dataX;
      qDebug() << Deseasonalized;
      qDebug() << robustness_weight;*/

      // Step 6 : Trend Smoothing
      for (int i = 0; i < N; i++) {
        Trend[i] = loess_x(dataX, Deseasonalized, nt, i, robustness_weight);
      }
    }

    for (int i = 0; i < dataX.size(); i++) {
      Remainder[i] = dataY[i] - Trend[dataX[i]] - Seasonality[dataX[i]];
      Abs_Remainder[i] =
          std::abs(dataY[i] - Trend[dataX[i]] - Seasonality[dataX[i]]);
    }

    if (dataX.size() % 2 == 0) {
      std::nth_element(Abs_Remainder.begin(),
                       Abs_Remainder.begin() + (dataX.size() / 2),
                       Abs_Remainder.end());
      std::nth_element(Abs_Remainder.begin(),
                       Abs_Remainder.begin() + ((dataX.size() / 2) - 1),
                       Abs_Remainder.end());
      h = 3 * (Abs_Remainder[dataX.size() / 2] +
               Abs_Remainder[(dataX.size() / 2) - 1]);
    } else {
      std::nth_element(Abs_Remainder.begin(),
                       Abs_Remainder.begin() + ((dataX.size() - 1) / 2),
                       Abs_Remainder.end());
      h = 6 * Abs_Remainder[(dataX.size() - 1) / 2];
    }

    for (int i = 0; i < dataX.size(); i++) {
      robustness_weight[i] = bisquare_weight_function(Abs_Remainder[i] / h);
    }
  }

  /*qDebug() << Trend;
  qDebug() << Seasonality;
  qDebug() << N;*/

  std::vector<std::vector<double>> answer = {{}, {}, {}};
  for (int i = 0; i < N; i++) {
    answer[0].push_back(Trend[i]);
    answer[1].push_back(Seasonality[i]);
  }
  for (int i = 0; i < Remainder.size(); i++) {
    answer[2].push_back(Remainder[i]);
  }
  return answer;
}

// STL decomposition implementation end

DataAnalysis::DataAnalysis(std::vector<EntryPerso *> vector_entries) {

  for (EntryPerso *entry : vector_entries) {
    log.push_back(*entry);
  }


  std::vector<EntryPerso> last_3y_temp = get_lastn_days_data(1095);
  std::vector<EntryPerso> last_3y;

  for (int i = 0; i < last_3y_temp.size() - (last_3y_temp.size() % 7); ++i) {
    last_3y.push_back(last_3y_temp[i]);
  }

  if (last_3y.size() > 60) {
    stl = true;
    std::vector<std::vector<double>> stl_reg;
    for (int metric = 0; metric < 6; ++metric) {
      std::vector<double> Xdata;
      std::vector<double> Ydata;
      for (int i = 0; i < last_3y.size(); ++i) {
        Xdata.push_back(last_3y[i].get_absolute_day());
        Ydata.push_back(last_3y[i].get_var_value(metric));
      }
      STL_X.push_back(Xdata);
      stl_reg = stl_regression(Xdata, Ydata);
      STL_Trends.push_back(stl_reg[0]);
      STL_Seasonalities.push_back(stl_reg[1]);
      STL_Remainders.push_back(stl_reg[2]);
    }
    /*qDebug() << STL_Trends;
    qDebug() << STL_Seasonalities;
    qDebug() << STL_Remainders;*/
  } else {
    stl = false;
  }
}

#include "DataAnalysis.h"
#include <algorithm>
#include <cmath> //prefer the c- version rather than the .h
#include <numeric>
#include <vector>


// using namespace std; don't be lazy and just use the specifier, it
// avoids naming conflicts. If you really have to use it, put it in the most
// restricted scope possible (

// Never manually iterate trough an STL container with iterators. Either use
// the normal syntax or use range based for loops like the one below

double DataAnalysis::avg(const std::vector<EntryPerso>& entries, Variables var_name) const{
    /**
     * @param vector<EntryPerso>
     *        var_name : variable to average
     * @return average value of the variable across the entries
     */


    return avg<double>(get_vect(entries, var_name));
}


double DataAnalysis::cov(std::vector<double> X, std::vector<double> Y) {
    /**
     * @param vectors double X, Y.
     * @return Cov(X, Y).
     */
    std::vector<double> XY{};
    for (auto elx : X)
        for(auto ely : Y)
            XY.push_back(elx*ely);

    return avg(X)*avg(Y) - avg(XY);
}

double DataAnalysis::stddev(std::vector<double> data) const{
    /**
     * @param vector data.
     * @return standart deviation.

     */
  double residue_sum = 0.0;

  double mean = avg<double>(data);

  // Never manually iterate trough an STL container with iterators. Either use
  // the normal syntax or use range based for loops like the one below
  for (auto el : data)
    residue_sum += std::pow(mean - el, 2);

  return sqrt(residue_sum / data.size());
}


double DataAnalysis::stddev(const std::vector<EntryPerso>& entries, Variables var_name) const{
    /**
     * @param vector<EntryPerso>
     *        var_name : variable to consider
     * @return standard deviation of values of the variable across the entries
     */
   return stddev(get_vect(entries, var_name));
}
double DataAnalysis::cor(std::vector<double> X, std::vector<double> Y) {
    /**
     * @param vectors double X, Y.
     * @return Cor(X, Y).
     */

    return cov(X,Y)/stddev(X)/stddev(Y);

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


double DataAnalysis::get_var(const EntryPerso& entry, Variables var_name) const {
    /**
     * @param EntryPerso entry : entry of interest.
     *        Variables var_name : represents the variable to get.
     * @return the value of the variable in the entry.
     */

    switch (var_name) {
        
        case MOOD:
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
        
        case COMMUNICATIONS:
            return entry.get_communications();
            break;
        
        case SCREEN_TIME:
            return entry.get_screen_time();
    }

}

void DataAnalysis::set_var(EntryPerso& entry, Variables var_name, double value) const {
    // This method will probably not be used that much but here just in case.
    /**
     * @param EntryPerso entry : entry of interest.
     *        Variables var_name : represents the variable to set.
     *        double value : new value of the variable.
     * @return the value of the variable in the entry.
     */
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

        case COMMUNICATIONS:
            entry.set_communications(value);
            break;

        case SCREEN_TIME:
            entry.set_screen_time(value);
        }
}

std::vector<double> DataAnalysis::get_vect(const std::vector<EntryPerso>& entries, Variables var_name) const{
    /**
     * @param vector of entries
     *        var_name : represents the variable we consider
     * @return the vector of values of the variable across entries.
     */
    std::vector<double> res;
    for (auto& entry : entries){
        res.push_back(get_var(entry, var_name));
    }
    return res;
}

double DataAnalysis::get_lastn_average(int n, Variables var_name) const{
    /**
     * @param int n: number of n last entries we take into account
     * @return double average of the values of the variable represented by var_name for last n entries
     */
    std::vector<double> val_list{};

    for (int i = std::max<int>(0, log.size() - n); i < log.size(); ++i) {
        val_list.push_back(get_var(log[i], var_name));
    }
    return avg<double>(val_list);
}


std::vector<EntryPerso> DataAnalysis::anomalies_detection(const std::vector<EntryPerso>& entries, Variables var_name) const{
    /**
     * @param vector of EntryPersos.
     * @return vector of entries at which anomalie in the variable was detected (value is 2 SDs far from its mean).
     */
    /*std::vector<double> mood_list{};
    std::vector<EntryPerso> res{};  // stores output info about anomaly points

    for(std::vector<EntryPerso>::iterator i = log.begin(); i < log.end(); i++){
            mood_list.push_back(i->get_mood());
    }
    double mean = avg<double>(mood_list);
    for(int i = 0; i < log.size(); i++){
        if (*(mood_list.begin() + i) - mean >= 2 * stddev(mood_list)){
            EntryPerso temp;
            temp.set_mood((log.begin() + i)->get_mood());
            temp.set_date((log.begin() + i)->get_date());
            res.push_back(temp);
        }
    }
    return res;*/
    std::vector<EntryPerso> res;

    double mean = avg(entries, var_name);
    double st_dev = stddev(entries, var_name);

    for (auto& entry : entries){
        if (get_var(entry, var_name) - mean >= 2 * st_dev){
            res.push_back(entry);
        }
    }
    return res;
}

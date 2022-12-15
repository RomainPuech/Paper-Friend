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

double DataAnalysis::avg(const std::vector<EntryPerso>& entries, int var_index) const{
    /**
     * @param vector<EntryPerso>
     *        var_index : variable to average
     * @return average value of the variable across the entries
     */


    return avg<double>(get_vect(entries, var_index));
}


double DataAnalysis::cov(const std::vector<double>& X, const std::vector<double>& Y) const{
    /**
     * @param vectors double X, Y.
     * @return Cov(X, Y).
     */
    std::vector<double> XY{};
    for (unsigned int i = 0; i < std::min(X.size(), Y.size()); ++i){ // Just in case the two have different sizes but shouldn't be the case.
        XY.push_back(X[i] * Y[i]);
    }

    return avg(XY) - avg(X)*avg(Y);
}

LinearRegressionCoeffs DataAnalysis::compute_linear_regression_coeffs(const std::vector<double>& X, const std::vector<double>& Y) const{
    /**
     * @param vectors double X, Y.
     * @return LinearRegressionCoeffs object corresponding to fitting Y against X.
     */

    double slope = cov(X, Y) / pow(stddev(X), 2);
    double intercept = avg(Y) - slope * avg(X);
    double quality_coeff = pow(cor(X, Y), 2);

    return LinearRegressionCoeffs(slope, intercept, quality_coeff);
}

LinearRegressionCoeffs DataAnalysis::compute_linear_regression_coeffs(const std::vector<EntryPerso>& entries, int var1_index, int var2_index) const{
    /**
     * @param vectors of entries, and two variables
     * @return LinearRegressionCoeffs object corresponding to fitting the second variable against the first.
     *         across the values of each in entries.
     */
    return compute_linear_regression_coeffs(get_vect(entries, var1_index), get_vect(entries, var2_index));
}

LinearRegressionCoeffs DataAnalysis::general_trend(int n, int var_index) const{
    /**
     * @param int n : represents number of days to consider.
     *        int var_index: variable to consider.
     * @return LinearRegressionCoeffs object corresponding to fitting the variable against the number of days since the first entry within n days of the last entry in the log.
     *  The function uses doubles to store ints because the functions used to calculate the desired coefficients are defined on vectors of doubles.
     */
    std::vector<EntryPerso> entries = get_lastn_days_data(n);
    std::vector<double> values = get_vect(entries, var_index);
    std::vector<double> no_of_days;

    double first_day = entries.front().get_absolute_day();
    for(auto& entry : entries)
         no_of_days.push_back(entry.get_absolute_day() - first_day);
    return compute_linear_regression_coeffs(no_of_days, values);
}

double DataAnalysis::stddev(const std::vector<double>& data) const{
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


double DataAnalysis::stddev(const std::vector<EntryPerso>& entries, int var_index) const{
    /**
     * @param vector<EntryPerso>
     *        var_index : variable to consider
     * @return standard deviation of values of the variable across the entries
     */
   return stddev(get_vect(entries, var_index));
}
double DataAnalysis::cor(const std::vector<double>& X, const std::vector<double>& Y) const{
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


//double DataAnalysis::get_var(const EntryPerso& entry, int var_index) const {
    /**
     * @param EntryPerso entry : entry of interest.
     *        Variables var_name : represents the variable to get.
     * @return the value of the variable in the entry.
     */
    /*
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


} */

//void DataAnalysis::set_var(EntryPerso& entry, Variables var_name, double value) const {
    // This method will probably not be used that much but here just in case.
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

        case COMMUNICATIONS:
            entry.set_communications(value);
            break;

        case SCREEN_TIME:
            entry.set_screen_time(value);
        }
}
*/
std::vector<double> DataAnalysis::get_vect(const std::vector<EntryPerso>& entries, int var_index) const{
    /**
     * @param vector of entries
     *        var_index : represents the variable we consider
     * @return the vector of values of the variable across entries.
     */
    std::vector<double> res;
    for (auto& entry : entries){
        res.push_back(entry.get_var_value(var_index));
    }
    return res;
}

double DataAnalysis::get_lastn_average(int n, int var_index) const{
    /**
     * @param int n: number of n last entries we take into account
     * @return double average of the values of the variable represented by var_index for last n entries
     */
    std::vector<double> val_list{};

    for (unsigned int i = std::max<int>(0, log.size() - n); i < log.size(); ++i) {
        val_list.push_back(log[i].get_var_value(var_index));
    }
    return avg<double>(val_list);
}


std::vector<EntryPerso> DataAnalysis::anomalies_detection(const std::vector<EntryPerso>& entries, int var_index) const{
    /**
     * @param vector of EntryPersos, var_index.
     * @return vector of entries at which anomalie in the variable was detected (value is 2 SDs far from its mean).
     */

    std::vector<EntryPerso> res;

    double mean = avg(entries, var_index);
    double st_dev = stddev(entries, var_index);

    for (auto& entry : entries){
        if (entry.get_var_value(var_index) - mean >= 2 * st_dev){
            res.push_back(entry);
        }
    }
    return res;
}

std::multimap<double, int> invert(std::map<int, double> & mymap){
    /**
    * @param map
    * @returns inversed map (swaps keys with values)
    */
    std::multimap<double, int> multiMap;

    std::map<int, double> :: iterator it;
    for (it=mymap.begin(); it!=mymap.end(); it++)
    {
        multiMap.insert(std::make_pair(it->second, it->first));
    }

    return multiMap;
}

std::vector<int> DataAnalysis::item_priority(int var_index){
    /**
    * @param index of the variable concerned
    *
    * @returns list of indices (of other variables) with those coming first having the most effect on the given variable.
    */

    int N = log.size();
    std::vector<double> var_vect = get_vect(log, var_index);
    std::vector<double> current;

    double dev;
    double cor_with_var;
    std::map<int, double> influence;

    for(int i = 0; i < get_num_activities(); ++i){
        if (var_index == i){
            continue;
        }
        current = get_vect(log, var_index);
        cor_with_var = cor(current, var_vect);
        dev = abs(get_lastn_average(std::min(7, N), i) - get_lastn_average(std::min(N, 30), i));
        influence[i] = cor_with_var * dev;
    }


    //Sort map (done with MULTIMAP)
    std::map<double, int> :: iterator iter;

    // invert mymap using the invert function created above

    std::multimap<double, int> newmap = invert(influence);
    //pushing sorted item names in the vector
    std::vector<int> vec{};
    for (iter=newmap.begin(); iter!=newmap.end(); iter++)
        {
            vec.push_back(iter->second);
        }
    return vec;
}

std::string DataAnalysis::suggestion(int var_index){  // some more exciting gameplay can be implementen later
    /**
    * @param index of the variable concerned
    *
    * @returns string "general review + suggestion" concerning the variable.
    */
    std::string str{};
    if (log.end()->get_mood() >= get_lastn_average(7, var_index)){
        str += "Your " + log[0].get_var_name(var_index) + " today is better than averadge! \n";
        str += "Your progress in" + var_to_str(*(item_priority(var_index).begin())) + " and " + var_to_str(*(item_priority(var_index).begin() + 1)) + "improves your " + log[0].get_var_name(var_index) + " the most, keep it up!";  // suggest top two items which affected the mood the most
    }
    else{
        str += "Your " + log[0].get_var_name(var_index) + " today is less than averadge:( \n";
        str += "Try to wrok on your " + var_to_str(*(item_priority(var_index).begin())) + " and " + var_to_str(*(item_priority(var_index).begin() + 1)) + "!";
    }

    return str;
}

std::string DataAnalysis::generate_recap_text(const std::vector<EntryPerso>& entries){
    return "";
}

EntryRecap DataAnalysis::weekly_recap(){
    /**
    * @param
    *
    * @returns an EntryRecap object containing info about the week. For now focuses on mood
    */
    std::vector<EntryPerso> period = get_lastn_days_data(7);
    auto comp{[](EntryPerso& entry1, EntryPerso& entry2) -> bool {return entry1.get_var_value(0) < entry2.get_var_value(0);}};

    EntryPerso best_day = *(std::max_element(period.begin(), period.end(), comp));
    EntryPerso worst_day = *(std::min_element(period.begin(), period.end(), comp));

    double avg_mood = avg(period, 0);

    std::string text = generate_recap_text(period);
    return EntryRecap(best_day, worst_day, text, avg_mood, 0);
}



// STL decomposition implementation start


int find_index_sorted(double x, std::vector<double>& data, int start = 0, int end = -1){ // Basic dichotomy implementation
    // Returns the biggest index corresponding in data to a number <= x   (for ex, find_index(2.5, {0, 1, 2, 3}) returns 2)
    if (end == -1){end = data.size();}
    if (end-start == 1){return start;}
    if (end-start == 2){
        if (data[start + 1] <= x){return start+1;}
        else {return start;}
    }
    int middle = (end-start)/2;
    if (data[middle]<=x){return find_index_sorted(x, data, middle, end);}
    else{return find_index_sorted(x, data, start, middle);}
}
std::vector<int> closest_q_index_in_sorted(double x, int q, std::vector<double>& data){ // Data needs to be sorted
    // Returns a vector containing the index of the closest q elements to x in data
    if (q>data.size()){
        qDebug() << "closest_q_index_in_sorted unsuccessful call : asking to retrieve more values than the length of the vector (q: " << QString::number(q) << " > data size: " << QString::number(data.size()) << ")\n";
        throw std::invalid_argument("Asking to retrieve more values than the length of the vector (q > data.size())");
    }
    int biggest_smaller_than_x_index = find_index_sorted(x, data);
    int iterLow = biggest_smaller_than_x_index; // Iterates on values smaller than (or equal to) x
    int iterHigh = biggest_smaller_than_x_index + 1; // Iterates on values bigger than x
    std::vector<int> answer;
    while (answer.size() < q){
        // If we reach the end of the vector, we need to take values from the other side
        if (iterLow == -1){
            answer.push_back(iterHigh);
            iterHigh++;
        }
        else if (iterHigh == data.size()){
            answer.push_back(iterLow);
            iterLow--;
        }
        else {
            // Otherwise, add value closest to x
            if (x - data[iterLow] < data[iterHigh] - x){
                answer.push_back(iterLow);
                iterLow--;
            }
            else{
                answer.push_back(iterHigh);
                iterHigh++;
            }
        }
    }
    std::sort(answer.begin(), answer.end());
    return answer;
}
double furthest_distance(double x, std::vector<double> data){ // Used to compute Gamma_q on the data subset gained by closest_q, to compute Gamma_n on the whole dataset
    // Returns the maximum "distance" between x and points in the data
    double max = 0;
    for (int i=0; i<data.size(); i++){
        if (max < std::abs(x-data[i])){max = std::abs(x-data[i]);}
    }
    return max;
}

double tricube_weight(double u){if (u>=1){return 0;} else{return std::pow( (1-(std::pow(u, 3))) , 3);}} // W(u)
double neighborhood_weight(double xi, double x, double distance_furthest){ // v_i(x)
    return tricube_weight(std::abs(xi - x) / distance_furthest);
}

double eval_poly(std::vector<double> coeffs, double x){ // coeffs for [x^n, x^n-1, ...]
    // Evaluates a polynomial at x using Horner scheme
    double value = coeffs[0];
    for (int i=1; i<coeffs.size(); i++){
        value *= x;
        value += coeffs[i];
    }
    return value;
}


double determinant_m3(std::vector<std::vector<double>> matrix){
    if (matrix.size() != 3 || matrix[0].size() != 3 || matrix[1].size() != 3 || matrix[2].size() != 3){
        qDebug() << "Matrix size not 3x3 but " << QString::number(matrix.size()) << " rows and " << QString::number(matrix[0].size()) << " columns (on first line)";
        throw std::invalid_argument("Matrix not of correct size");}

    return (matrix[0][0] * (matrix[1][1]*matrix[2][2] - matrix[1][2]*matrix[2][1])) - (matrix[0][1] * (matrix[1][0]*matrix[2][2] - matrix[1][2]*matrix[2][0])) + (matrix[0][2] * (matrix[1][0]*matrix[2][1] - matrix[1][1]*matrix[2][0]));
}

std::vector<double> weighted_least_squares(std::vector<double> dataX, std::vector<double> dataY, std::vector<double> weights = {-1}){
    if (weights.size() == 1 && weights[0] == -1){weights = std::vector<double>(dataX.size(), 1);}

    if (dataX.size() == 0){
        qDebug() << "Weighted least_squares unsuccessful call : data size is 0\n";
        throw std::invalid_argument("Length of data is 0");}
    else if (dataX.size() != dataY.size() || dataY.size() != weights.size()){
        qDebug() << "Weighted least_squares unsuccessful call : data not of same sizes (dataX :" << QString::number(dataX.size()) << ", dataY :" << QString::number(dataY.size()) << ", weights :" << QString::number(weights.size()) << ")\n";
        throw std::invalid_argument("Data not all of same length");}

    // We solve this as a linear system using cramer's rule.
    double sum_x=0, sum_x2=0, sum_x3=0, sum_x4=0, sum_x2y=0, sum_xy=0, sum_y=0, xwi, xi, yi;
    double sum_1 = dataX.size();
    for (int i=0; i<dataX.size(); i++){
        // I tried to reduce the amount of multiplications but it increased the amount of memory accesses
        xi = dataX[i];
        yi = dataY[i];
        xwi = xi*weights[i];
        sum_x += xwi;
        sum_y += yi * weights[i];
        sum_xy += xwi * yi;
        sum_x2y += xwi*xi * yi;
        sum_x2 += xwi*xi;
        sum_x3 += xi*xi * xwi;
        sum_x4 += std::pow(xi, 3) * xwi;
    }
    double detMat = determinant_m3(std::vector<std::vector<double>> {{sum_x4, sum_x3, sum_x2}, {sum_x3, sum_x2, sum_x}, {sum_x2, sum_x, sum_1}});
    double detA = determinant_m3(std::vector<std::vector<double>> {{sum_x2y, sum_x3, sum_x2}, {sum_xy, sum_x2, sum_x}, {sum_y, sum_x, sum_1}});
    double detB = determinant_m3(std::vector<std::vector<double>> {{sum_x4, sum_x2y, sum_x2}, {sum_x3, sum_xy, sum_x}, {sum_x2, sum_y, sum_1}});
    double detC = determinant_m3(std::vector<std::vector<double>> {{sum_x4, sum_x3, sum_x2y}, {sum_x3, sum_x2, sum_xy}, {sum_x2, sum_x, sum_y}});
    std::vector<double> coefficients = std::vector<double> {detA/detMat, detB/detMat, detC/detMat};
    return coefficients;
}

double g_hat_x (std::vector<double> dataX, std::vector<double> dataY, double x){
    // Computes g_hat (extrapolation of the trend-cycle ?) assuming dataX is sorted
    double f = 0.1;
    int q = std::max(std::min(3.0, static_cast<double>(dataX.size())), f*(static_cast<double>(dataX.size()))); // Number of neighbors CONSTANT choose Q thanks to M diagram (=q/n) in loess details)
    std::vector<int> closest_xi_index = closest_q_index_in_sorted(x, q, dataX);
    double furthest_distance = std::max(std::abs(x-dataX[closest_xi_index[0]]), std::abs(x-dataX[closest_xi_index[closest_xi_index.size()-1]]));
    std::vector<double> weights, closest_xi, closest_yi;
    for (int i=0; i<closest_xi_index.size(); i++){
        weights.push_back(neighborhood_weight(dataX[closest_xi_index[i]], x, furthest_distance));
        closest_xi.push_back(dataX[closest_xi_index[i]]);
        closest_yi.push_back(dataY[closest_xi_index[i]]);
    }
    // Residual = sum wi * (yi - (x^2 b_2 + x b_1 + b_0)^2) = (Y - XB)
    return eval_poly(weighted_least_squares(closest_xi, closest_yi, weights), x);
}

auto DataAnalysis::stl_regression(std::vector<double> dataX, std::vector<double> dataY){ // Definitely need to change this and the hpp file
    // TODO : Do the testing
    // TODO : replace find_index by a composition of stl's lower_bound and distance to make the code better
    // TODO : make the choice of constants for mood/other stuff if needed
    //          q increase -> smoother
    if (dataX.size() == 0){
        qDebug() << "stl_regression unsuccessful call : data size is 0\n";
        throw std::invalid_argument("Length of data is 0");
    }
    else if (dataX.size() != dataY.size()){
        qDebug() << "stl_regression unsuccessful call : dataX size " << QString::number(dataX.size()) << " != dataY size " << QString::number(dataY.size()) << ".\n";
        throw std::invalid_argument("Data not all of same length");
    }

    // TODO continue implementation now that q_hat_x() works.

    return 0;
}

// STL decomposition implementation end

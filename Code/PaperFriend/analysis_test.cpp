#include <ctime>
#include <utility>
#include <vector>

using time_point = std::pair<time_t, int>;

class Time_series {
private:
  std::vector<time_point> series;
};
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>

double standard_deviation(const std::vector<double>& data) {
    if (data.empty()) {
        return 0.0;
    }

    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double mean = sum / data.size();

    std::vector<double> diff(data.size());
    std::transform(data.begin(), data.end(), diff.begin(), [mean](double x){ return x - mean; });

    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    return std::sqrt(sq_sum / data.size());
}

int main() {
    std::vector<double> data = {2.0, 4.0, 4.0, 4.0, 5.0, 5.0, 7.0, 9.0};
    double std_dev = standard_deviation(data);
    std::cout << "The standard deviation is: " << std_dev << std::endl;
    return 0;
}
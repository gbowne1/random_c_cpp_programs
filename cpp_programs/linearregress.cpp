// File:   linearregress
// Author: Gregory K. Bowne
// Date:   14 MAR 2003
// Time: Unknown
// Brief:  This program does long linear regression calculations.

#include <iostream>
#include <numeric>
#include <vector>

double mean(const std::vector<double> &v)
{
	return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

void linearRegression(const std::vector<double> &x, const std::vector<double> &y, double &a, double &b)
{
	double mx = mean(x);
	double my = mean(y);
	double n = x.size();

	double ssxx = 0, ssyy = 0, ssxy = 0;
	for (size_t i = 0; i < n; ++i)
	{
		ssxx += (x[i] - mx) * (x[i] - mx);
		ssyy += (y[i] - my) * (y[i] - my);
		ssxy += (x[i] - mx) * (y[i] - my);
	}

	b = ssxy / ssxx;
	a = my - b * mx;
}

int main()
{
	std::vector<double> x = {/* x values */};
	std::vector<double> y = {/* y values */};
	double a, b;

	linearRegression(x, y, a, b);

	std::cout << "a: " << a << ", b: " << b << std::endl;

	return 0;
}
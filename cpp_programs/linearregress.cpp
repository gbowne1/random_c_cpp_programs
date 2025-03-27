/*
 *	File:   linearregress.cpp
 *	Author: Gregory K. Bowne
 *	Date:   17 Oct 2018
 *	Time:   23:39:08
 *	Brief: This program calculates linear regressions
*/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

double mean(const std::vector<double> &v)
{
	return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

void linearRegression(const std::vector<double> &x, const std::vector<double> &y, double &a, double &b)
{

	if (std::adjacent_find(x.begin(), x.end(), std::not_equal_to<double>()) == x.end())
	{
		std::cerr << "Warning: All x values are the same. This results in a vertical line." << std::endl;
		a = std::numeric_limits<double>::quiet_NaN();
		b = mean(y);
		return;
	}

	if (x.empty() || y.empty())
	{
		std::cerr << "Error: Input vectors must not be empty." << std::endl;
		return;
	}

	if (x.size() < 2 || y.size() < 2)
	{
		std::cerr << "Error: At least two data points are required for linear regression." << std::endl;
		return;
	}

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

	if (ssxx == 0)
	{
		std::cerr << "Error: Division by zero encountered. Unable to calculate linear regression." << std::endl;
		return;
	}

	b = ssxy / ssxx;
	a = my - b * mx;
}

void saveModel(const std::string &filename, double a, double b)
{
	std::ofstream file(filename);
	if (file.is_open())
	{
		file << "a: " << a << "\n";
		file << "b: " << b << "\n";
		file.close();
	}
	else
	{
		std::cerr << "Unable to open file: " << filename << std::endl;
	}
}

void deleteModel(const std::string &filename)
{
	if (std::remove(filename.c_str()) != 0)
	{
		std::cerr << "Error: Unable to delete file: " << filename << std::endl;
	}
}

std::pair<double, double> loadModel(const std::string &filename)
{
	std::ifstream file(filename);
	double a, b;
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		std::istringstream(line.substr(3)) >> a;
		std::getline(file, line);
		std::istringstream(line.substr(3)) >> b;
		file.close();
	}
	else
	{
		std::cerr << "Unable to open file: " << filename << std::endl;
	}
	return {a, b};
}

void validateModelParameters(double a, double b)
{
	if (a < -10 || a > 10)
	{
		std::cerr << "Warning: The slope (a) is outside the expected range." << std::endl;
	}

	if (b < 0)
	{
		std::cerr << "Warning: The intercept (b) is negative, which may not be physically sensible." << std::endl;
	}
}

bool isValidFilename(const std::string &filename)
{
	if (filename.empty() || filename.find_first_of("*?") != std::string::npos)
	{
		return false;
	}
	return true;
}

std::vector<double> readDataFromFile(const std::string &filename)
{
	std::vector<double> data;
	std::ifstream file(filename);
	if (file.is_open())
	{
		double value;
		while (file >> value)
		{
			data.push_back(value);
		}
		file.close();
	}
	else
	{
		std::cerr << "Unable to open file: " << filename << std::endl;
	}
	return data;
}

void displayMenu()
{
	std::cout << "Choose an option:\n";
	std::cout << "1. Run a new regression\n";
	std::cout << "2. Load a saved model\n";
	std::cout << "3. Save current model\n";
	std::cout << "4. Delete a saved model\n";
	std::cout << "5. Exit\n";
}

int main(int argc, char *argv[])
{
	std::vector<double> x, y;
	double a, b;
	std::string choice;
	std::string filename;

	if (argc > 1)
	{
		std::string filename = argv[1];
		std::tie(a, b) = loadModel(filename);
		validateModelParameters(a, b);
		std::cout << "Loaded model: a = " << a << ", b = " << b << std::endl;
	}
	else
	{
		do
		{
			displayMenu();
			std::cin >> choice;

			if (choice == "1")
			{
				std::cout << "Enter the filename for x values: ";
				std::cin >> filename;
				x = readDataFromFile(filename);
				std::cout << "Enter the filename for y values: ";
				std::cin >> filename;
				y = readDataFromFile(filename);
				linearRegression(x, y, a, b);
				std::cout << "a: " << a << ", b: " << b << std::endl;
			}
			else if (choice == "2")
			{
				std::cout << "Enter the filename of the saved model: ";
				std::cin >> filename;
				std::tie(a, b) = loadModel(filename);
				validateModelParameters(a, b);
				std::cout << "Loaded model: a = " << a << ", b = " << b << std::endl;
			}
			else if (choice == "3")
			{
				std::cout << "Enter the filename to save the current model: ";
				std::cin >> filename;
				saveModel(filename, a, b);
				std::cout << "Model saved to " << filename << std::endl;
			}
			else if (choice == "4")
			{
				std::cout << "Enter the filename of the model to delete: ";
				std::cin >> filename;
				deleteModel(filename);
			}
			else if (choice != "5")
			{
				std::cout << "Invalid option. Please try again.\n";
			}
		} while (choice != "5");
	}

	return 0;
}

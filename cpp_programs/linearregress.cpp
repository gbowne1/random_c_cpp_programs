// File:   linearregress.cpp
// Author: Gregory K. Bowne
// Date:   17 Oct 2018
// Time:   23:39:08
// Brief:  This program calculates linear regressions

#include <iostream>
#include <numeric>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

/**
 * \brief Calculates the mean of a vector of doubles.
 *
 * This function calculates the mean (average) of all elements in a vector.
 *
 * \param v The vector of doubles for which the mean is calculated.
 * \return The mean of the vector elements.
 */
double mean(const std::vector<double> &v)
{
	return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

/**
 * \brief Performs linear regression on two vectors of doubles.
 *
 * This function calculates the slope (a) and intercept (b) of the linear
 * regression line that best fits the given data points.
 *
 * \param x The vector of independent variable values.
 * \param y The vector of dependent variable values.
 * \param a A reference to the variable where the slope will be stored.
 * \param b A reference to the variable where the intercept will be stored.
 */
void linearRegression(const std::vector<double> &x, const std::vector<double> &y, double &a, double &b)
{

	if (x.size() < 2 || y.size() < 2) {
        std::cerr << "Error: At least two data points are required for linear regression." << std::endl;
        return; // Exit function to prevent further calculations
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

	// Error Handling
	if (ssxx == 0)
	{
		std::cerr << "Error: Division by zero encountered. Unable to calculate linear regression." << std::endl;
		return; // Exit function to prevent further calculations
	}

	b = ssxy / ssxx;
	a = my - b * mx;
}

/**
 * \brief Saves the model parameters to a file.
 *
 * This function saves the slope (a) and intercept (b) of a linear regression model
 * to a specified file.
 *
 * \param filename The name of the file to save the model parameters to.
 * \param a The slope of the linear regression model.
 * \param b The intercept of the linear regression model.
 */
void saveModel(const std::string& filename, double a, double b) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "a: " << a << "\n";
        file << "b: " << b << "\n";
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

/**
 * \brief Loads model parameters from a file.
 *
 * This function reads the slope (a) and intercept (b) of a linear regression model
 * from a specified file.
 *
 * \param filename The name of the file to load the model parameters from.
 * \return A pair containing the slope and intercept of the loaded model.
 */
std::pair<double, double> loadModel(const std::string& filename) {
    std::ifstream file(filename);
    double a, b;
    if (file.is_open()) {
        std::string line;
        std::getline(file, line); // Read the first line
        std::istringstream(line.substr(3)) >> a; // Extract 'a' value
        std::getline(file, line); // Read the second line
        std::istringstream(line.substr(3)) >> b; // Extract 'b' value
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    return {a, b};
}

/**
 * \brief Validates the model parameters.
 *
 * This function checks if the slope (a) and intercept (b) of a linear regression model
 * are within expected ranges or make sense in the context of the application.
 *
 * \param a The slope of the linear regression model.
 * \param b The intercept of the linear regression model.
 */
void validateModelParameters(double a, double b) {
   // Example validation: Check if the slope (a) is within a reasonable range
    if (a < -10 || a > 10) {
        std::cerr << "Warning: The slope (a) is outside the expected range." << std::endl;
    }

    // Example validation: Check if the intercept (b) is physically sensible
    // This is a placeholder condition; adjust based on your application's context
    if (b < 0) {
        std::cerr << "Warning: The intercept (b) is negative, which may not be physically sensible." << std::endl;
    }

    // Add more validation checks as needed
    // For example, you might want to check if the model parameters make sense in the context of your application
}

/**
 * \brief The main function of the linear regression program.
 *
 * This function provides the user with options to run a new regression, load a saved model,
 * or exit the program.
 *
 * \return 0 on successful execution.
 */
int main() {
    std::vector<double> x, y;
    double a, b;
    std::string choice;

    do {
        std::cout << "Choose an option:\n";
        std::cout << "1. Run a new regression\n";
        std::cout << "2. Load a saved model\n";
        std::cout << "3. Exit\n";
        std::cin >> choice;

        if (choice == "1") {
            // Example input for new regression
            x = {170, 180, 160, 175, 185};
            y = {60, 70, 55, 75, 80};
            linearRegression(x, y, a, b);
            std::cout << "a: " << a << ", b: " << b << std::endl;
            // Optionally, save the model after running it
            std::string filename = "saved_model.txt";
            saveModel(filename, a, b);
            std::cout << "Model saved to " << filename << std::endl;
        } else if (choice == "2") {
            std::string filename;
            std::cout << "Enter the filename of the saved model: ";
            std::cin >> filename;
            std::tie(a, b) = loadModel(filename);
            validateModelParameters(a, b); // Validate the loaded model parameters
            std::cout << "Loaded model: a = " << a << ", b = " << b << std::endl;
        } else if (choice != "3") {
            std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != "3");

    return 0;
}
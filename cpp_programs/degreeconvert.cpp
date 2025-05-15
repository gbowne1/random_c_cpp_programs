// File:   degreeconvert.cpp
// Author: Gregory K. Bowne
// Date:   08 JAN 1999
// Time:   13:42:45
// Brief:  This program converts degrees to multiple formats.

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <iostream>
#include <sstream>
#include <string>

// Constants for conversion
const double DEG_TO_RAD = M_PI / 180.0;
const double RAD_TO_DEG = 180.0 / M_PI;
const double MIN_TO_DEG = 1.0 / 60.0;
const double SEC_TO_DEG = 1.0 / 3600.0;

double degToRad(double degrees)
{
	return degrees * DEG_TO_RAD;
}

double radToDeg(double radians)
{
	return radians * RAD_TO_DEG;
}

// Function to convert degrees to DMS format
std::string degToDMS(double degrees)
{
	int deg = static_cast<int>(degrees);
	double minFloat = (degrees - deg) * 60;
	int min = static_cast<int>(minFloat);
	double sec = (minFloat - min) * 60;
	return std::to_string(deg) + "° " + std::to_string(min) + "'" + std::to_string(sec) + "\"";
}

double dmsToDeg(double dms)
{
	// Error handling can be added here for input validation
	int deg = static_cast<int>(dms);
	int min = static_cast<int>((dms - deg) * 100);
	double sec = ((dms - deg) * 100 - min) * 100;
	return deg + min * MIN_TO_DEG + sec * SEC_TO_DEG;
}

double parseInput(const std::string &input)
{
	std::istringstream iss(input);
	double value;
	iss >> value;
	return value;
}

int main()
{
	std::string userInput;
	std::cout << "Enter a value in degrees, radians, or DMS: ";
	std::getline(std::cin, userInput);

	double inputValue = parseInput(userInput);

	if (userInput.find('.') != std::string::npos)
	{
		double radians = degToRad(inputValue);
		std::string dms = degToDMS(inputValue);

		std::cout << "Radians: " << radians << std::endl;
		std::cout << "DMS: " << dms << std::endl;
	}
	else if (userInput.find(':') != std::string::npos)
	{
		double degrees = dmsToDeg(inputValue);
		double radians = degToRad(degrees);

		std::cout << "Degrees: " << degrees << std::endl;
		std::cout << "Radians: " << radians << std::endl;
	}
	else
	{
		double degrees = radToDeg(inputValue);
		std::string dms = degToDMS(degrees);

		std::cout << "Degrees: " << degrees << std::endl;
		std::cout << "DMS: " << dms << std::endl;
	}

	return 0;
}
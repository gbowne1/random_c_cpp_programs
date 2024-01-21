// File:   righttriangle.cpp
// Author: Gregory K. Bowne
// Date:   20 Oct 2023
// Time:   23:39:08
// Brief:  This program calculates the right triangle triganometry and to help determine angles.
//         This also 

#include <iostream>
#include <string>
#include <cmath>
#include <limits>
using namespace std;

#define PI 3.141592653589793

int main()
{
    double xLength;
    double yLength;
    double zLength;
    double aAngle;
    double bAngle;
    double cAngle = 90;
    string units;

    // Draw a pretty picture (helps the user to better understand what they are entering)
    cout << "  |* ";
    cout << "\n  |   * ";
    cout << "\n  | B    *       Z";
    cout << "\n  |         * ";
    cout << "\nX |            * ";
    cout << "\n  |               * ";
    cout << "\n  | 90           A   * ";
    cout << "\n  |_____________________* ";
    cout << "\n             Y \n\n";

    // Get the unit of measure.
	cout << "Enter the unit of measure you are using: ";
	cin >> units;
	cout << "You entered " << units << '.' << endl;

	// Get the Length of "x".
	cout << "Enter the length of the first side (x) adjacent to the right angle: ";
	cin >> xLength;
	cout << "You entered " << xLength << ' ' << units << '.' << endl;

	// Clear the input buffer
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// Get the Length of "y".
	cout << "Enter the length of the second side (y) adjacent to the right angle: ";
	cin >> yLength;
	cout << "You entered " << yLength << ' ' << units << '.' << endl;;

    // Calculate the Hypotenuse
    zLength = sqrt(xLength * xLength + yLength * yLength);
    cout << "Hypotenuse = " << zLength << ' ' << units << '.' << endl;

    // Calculate angles
    // Calculate Angle 'a'
    aAngle = atan(yLength / xLength) * 180 / PI;
    cout << "The angle of angle 'a' is: " << aAngle << " degrees" << endl;

    // Calculate angle 'b'
    bAngle = 90 - aAngle;
    cout << "The angle of angle 'b' is: " << bAngle << " degrees" << endl;

    return 0;
}
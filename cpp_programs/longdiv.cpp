// File:   longdiv.c
// Author: Gregory K. Bowne
// Date:   09 MAR 2003
// Time: Unknown
// Brief:  This program does long division calculations.
// Long division is a standard division algorithm used to divide multi-digit numbers
// It involves the dividend (the number being divided), the divisor (the number by which
// the dividend is divided), the quotient (the result of the division), and the remainder
// (the amount left over after the division)

#include <iostream>
#include <string>
using namespace std;

string longDivision(string number, int divisor) {
    if (divisor == 0) {
        return "Error: Division by zero";
    }
    string ans = "";
    int idx = 0;
    int temp = number[idx] - '0';
    while (temp < divisor && idx < number.size()) {
        temp = temp * 10 + (number[++idx] - '0');
    }
    while (number.size() > idx) {
        if (divisor == 0) {
            return "Error: Division by zero";
        }
        ans += (temp / divisor) + '0';
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    }
    if (ans.length() == 0) return "0";
    return ans;
}

int main() {
    string number;
    int divisor;

    cout << "Enter the large number: ";
    cin >> number;
    cout << "Enter the divisor: ";
    cin >> divisor;

    cout << longDivision(number, divisor);
    return 0;
}

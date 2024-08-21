#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <string>

// Constants
const int PRECISION = 2;

// Function to validate and get input
double getInput(const std::string& prompt) {
    double value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Invalid input. Please enter a valid number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return value;
}

// Function to calculate monthly payment
double calculateMonthlyPayment(double loanAmount, double monthlyRate, int numPayments) {
    return (loanAmount * monthlyRate) / (1 - pow(1 + monthlyRate, -numPayments));
}

// Function to print amortization schedule
void printAmortizationSchedule(double loanAmount, double monthlyRate, double monthlyPayment, int numPayments) {
    double balance = loanAmount;
    std::cout << "\nAmortization Schedule:\n";
    std::cout << "---------------------------------------------------------\n";
    std::cout << "Payment\tPrincipal\tInterest\tRemaining Balance\n";
    std::cout << "---------------------------------------------------------\n";

    for (int i = 1; i <= numPayments; ++i) {
        double interest = balance * monthlyRate;
        double principal = monthlyPayment - interest;
        balance -= principal;

        std::cout << i << "\t$" << std::setw(10) << principal
                  << "\t$" << std::setw(8) << interest
                  << "\t$" << std::setw(16) << balance << std::endl;
    }
}

int main() {
    std::cout << std::fixed << std::setprecision(PRECISION);

    double loanAmount = getInput("Enter the loan amount: ");
    double interestRate = getInput("Enter the annual interest rate as a decimal (e.g., 0.05 for 5%): ");
    int numPayments;

    // Validate number of payments
    do {
        numPayments = static_cast<int>(getInput("Enter the number of monthly payments: "));
        if (numPayments <= 0) {
            std::cout << "Number of payments must be a positive integer. Please try again.\n";
        }
    } while (numPayments <= 0);

    double monthlyRate = interestRate / 12;
    double monthlyPayment = calculateMonthlyPayment(loanAmount, monthlyRate, numPayments);

    std::cout << "\nMonthly Payment: $" << monthlyPayment << std::endl;

    printAmortizationSchedule(loanAmount, monthlyRate, monthlyPayment, numPayments);

    return 0;
}

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

int main() {
    double loanAmount, interestRate;
    int numPayments;

    // Input validation for loan amount
    std::cout << "Enter the loan amount: ";
    while (!(std::cin >> loanAmount) || loanAmount <= 0) {
        std::cout << "Invalid input. Please enter a valid positive loan amount: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Input validation for annual interest rate
    std::cout << "Enter the annual interest rate as a decimal (e.g., 0.05 for 5%): ";
    while (!(std::cin >> interestRate) || interestRate <= 0) {
        std::cout << "Invalid input. Please enter a valid positive annual interest rate: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Input validation for number of monthly payments
    std::cout << "Enter the number of monthly payments: ";
    while (!(std::cin >> numPayments) || numPayments <= 0) {
        std::cout << "Invalid input. Please enter a valid positive number of monthly payments: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    double monthlyRate = interestRate / 12;
    double monthlyPayment = (loanAmount * monthlyRate) / (1 - pow(1 + monthlyRate, -numPayments));

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Monthly Payment: $" << monthlyPayment << std::endl;

    double balance = loanAmount;

    for (int i = 1; i <= numPayments; ++i) {
        double interest = balance * monthlyRate;
        double principal = monthlyPayment - interest;
        balance -= principal;

        std::cout << "Payment " << i << " - ";
        std::cout << "Principal: $" << principal << ", ";
        std::cout << "Interest: $" << interest << ", ";
        std::cout << "Remaining Balance: $" << balance << std::endl;
    }

    return 0;
}
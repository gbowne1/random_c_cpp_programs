#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    double loanAmount, interestRate;
    int numPayments;

    std::cout << "Enter the loan amount: ";
    std::cin >> loanAmount;
    std::cout << "Enter the annual interest rate as a decimal (e.g., 0.05 for 5%): ";
    std::cin >> interestRate;
    std::cout << "Enter the number of monthly payments: ";
    std::cin >> numPayments;

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
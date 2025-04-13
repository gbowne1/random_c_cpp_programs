#include <stdio.h>
#include <math.h>

// Function to calculate the mean of an array
double calculateMean(double arr[], int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}

// Function to calculate the standard deviation
double calculateStandardDeviation(double arr[], int size) {
    double mean = calculateMean(arr, size);
    double sumOfSquaredDifferences = 0.0;

    for (int i = 0; i < size; i++) {
        sumOfSquaredDifferences += pow(arr[i] - mean, 2);
    }

    return sqrt(sumOfSquaredDifferences / size);
}

int main() {
    // Example data
    double data[] = {2.0, 4.0, 6.0, 8.0, 10.0};
    int size = sizeof(data) / sizeof(data[0]);

    // Calculate and print the standard deviation
    double stdDev = calculateStandardDeviation(data, size);
    printf("Standard Deviation: %f\n", stdDev);

    return 0;
}
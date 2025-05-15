#include "convertcsv.h"

int main() {
    std::string inputFilename, outputFilename;
    std::cout << "Enter the input CSV file name: ";
    std::cin >> inputFilename;
    std::cout << "Enter the output JSON file name: ";
    std::cin >> outputFilename;

    std::vector<std::vector<std::string>> data;
    if (!readCSV(inputFilename, data)) {
        return 1; // Exit on error
    }

    convertToJSON(data, outputFilename);
    return 0;
}

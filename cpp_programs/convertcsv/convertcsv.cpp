#include "convertcsv.h"

bool readCSV(const std::string& filename, std::vector<std::vector<std::string>>& data) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::istringstream stream(line);
        std::string value;

        while (std::getline(stream, value, ',')) {
            row.push_back(value);
        }
        data.push_back(row);
    }

    file.close();
    return true;
}

void convertToJSON(const std::vector<std::vector<std::string>>& data, const std::string& outputFile) {
    std::ofstream file(outputFile);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot create file " << outputFile << std::endl;
        return;
    }

    file << "{\n";
    for (size_t i = 0; i < data.size(); ++i) {
        file << "  \"row" << i + 1 << "\": [";
        for (size_t j = 0; j < data[i].size(); ++j) {
            file << "\"" << data[i][j] << "\"";
            if (j < data[i].size() - 1) file << ", ";
        }
        file << "]";
        if (i < data.size() - 1) file << ",";
        file << "\n";
    }
    file << "}\n";

    file.close();
    std::cout << "JSON file \"" << outputFile << "\" created successfully." << std::endl;
}

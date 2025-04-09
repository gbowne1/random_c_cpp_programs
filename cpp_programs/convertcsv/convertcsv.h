#ifndef CONVERTCSV_H
#define CONVERTCSV_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Function declarations
bool readCSV(const std::string& filename, std::vector<std::vector<std::string>>& data);
void convertToJSON(const std::vector<std::vector<std::string>>& data, const std::string& outputFile);

#endif // CONVERTCSV_H

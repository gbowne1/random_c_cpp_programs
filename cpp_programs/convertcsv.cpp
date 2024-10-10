// File:   convertcsv.c
// Author: Gregory K. Bowne
// Date:   15 DEC 2020
// Time:   11:15:22
// Brief:  This program converts csv to json and json to csv
//

#include <iostream>
#include <vector>
#include <fstream>
#include "rapidcsv.h"
#include <nlohmann/json.hpp>

// User input
int numColumns = 0;
int numRows = 0;
std::cout << "Enter the number of columns: ";
std::cin >> numColumns;
std::cout << "Enter the number of rows: ";
std::cin >> numRows;

// Generate/Create CSVs
std::vector<std::vector<std::string>> data(numRows, std::vector<std::string>(numColumns));
// TODO: Populate 'data' with user input...

rapidcsv::Document doc(headers, data);
doc.Save("output.csv");

// Read CSVs
rapidcsv::Document doc("output.csv");
std::vector<std::string> col = doc.GetColumn<std::string>("ColumnName");

// Convert CSVs to JSON
nlohmann::json j;
j["key"] = col;

// Export CSVs to JSON
std::ofstream o("file.json");
o << j;

// TODO: Convert CSVs to Table/Header-Based CSVs
// TODO: Implement custom function...
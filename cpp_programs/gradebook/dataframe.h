// File:   dataframe.h
// Author: Andre Wlodkovski
// Date:   23 Jan 2024
// Time:   18:15:00
// Brief:  A DataFrame is a data structure that helps handling CSV-like data. Columns are
//         accessed with keys (strings) and rows are accesses with indexes (unsigned int)

#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <map>
#include <string>
#include <vector>

/**
 * Class DataFrame
 * 
 * This class contains data structures to handle data from CSV files and access/modify them easily.
*/
class DataFrame {
private:
    // Column names. First line of CSV files
    std::vector<std::string> header;
    // CSV data
    std::map<std::string, std::vector<std::string>> data;
public:
    DataFrame();
    DataFrame(const std::string &fileName);

    /**
     * Access a CSV data row, given the index
     * 
     * @param index Index, starting from 0
     * @returns Map of <column name, value>
    */
    std::map<std::string, std::string*> operator[](size_t index);

    /**
     * Access a CSV data column, given the column name (key)
     * 
     * @param key Column name specified in the CSV file header
     * @returns Vector of values as strings
    */
    std::vector<std::string> &operator[](const std::string &key);

    /**
     * Gets the row size of the DataFrame. Equivalent to the number of columns
     * 
     * @returns Number of values in rows
    */
    size_t sizeRows();

    /**
     * Gets the column size of the DataFrame. Equivalent to the number of lines in the CSV file, excluding the header.
     * 
     * @returns Number of values in rows
    */
    size_t sizeCols();

    /**
     * Erases all data in the DataFrame
    */
    void clear();

    /**
     * Adds a line of values to the end of the DataFrame
     * 
     * @param row Map of <column name, value>
    */
    void append(const std::map<std::string, std::string> &row);

    /**
     * Removes a row of the DataFrame given its index
     * 
     * @param index Index of the row to be removed
    */
    void remove(size_t index);

    /**
     * Loads data from a CSV file
     * 
     * @param fileName Name of the CSV file
     * @returns Status code, where 0 is success
    */
    int load(const std::string &fileName);

    /**
     * Saves data to a CSV file
     * 
     * @param fileName Name of the CSV file
     * @returns Status code, where 0 is success
    */
    int save(const std::string &fileName);
};

#endif
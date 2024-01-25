#include "dataframe.h"

#include <fstream>
#include <sstream>
#include <iomanip>

DataFrame::DataFrame() {}

DataFrame::DataFrame(const std::string &fileName) {
    this->load(fileName);
}

std::map<std::string, std::string*> DataFrame::operator[](size_t index) {
    std::map<std::string, std::string*> series;

    for (auto it = this->data.begin(); it != this->data.end(); it++) {
        series[it->first] = &it->second[index];
    }

    return series;
}

std::vector<std::string> &DataFrame::operator[](const std::string &key) {
    return this->data[key];
}

size_t DataFrame::sizeRows() {
    return this->data.size();
}

size_t DataFrame::sizeCols() {
    auto it = this->data.begin();
    if (it == this->data.end())
        return 0;

    return it->second.size();
}

void DataFrame::clear() {
    this->data.clear();
    this->header.clear();
}

void DataFrame::initialize(const std::vector<std::string> &header) {
    if (this->header.size() > 0)
        this->header.clear();

    if (this->data.size() > 0)
        this->data.clear();

    for (const std::string &label : header) {
        this->header.push_back(label);
        this->data[label] = std::vector<std::string>();
    }
}

void DataFrame::append(const std::map<std::string, std::string> &row) {
    if (!this->header.size()) {
        std::vector<std::string> header;
        for (const auto &it : row) {
            header.push_back(it.first);
        }
        this->initialize(header);
    }

    for (auto it = this->data.begin(); it != this->data.end(); it++) {
        std::string key = it->first;
        std::vector<std::string> &col = it->second;
        if (!row.count(key)) {
            col.push_back("");
            continue;
        }

        col.push_back(row.at(key));
    }
}

void DataFrame::remove(size_t index) {
    for (auto it = this->data.begin(); it != this->data.end(); it++) {
        it->second.erase(it->second.begin() + index);
    }
}

std::vector<size_t> DataFrame::getMaxColumnSizes() {
    std::vector<size_t> columnSizes;

    for (const std::string& key : this->header) {
        size_t max = key.size();
        for (const std::string& value : this->data[key]) {
            size_t strSize = value.size();
            if (strSize > max)
                max = strSize;
        }
        columnSizes.push_back(max);
    }

    return columnSizes;
}

void DataFrame::print(std::ostream& out) {
    if (!this->header.size())
        return;

    // Get column sizes
    std::vector<size_t> columnSizes = this->getMaxColumnSizes();

    // Print line
    size_t lineWidth = 1 + 3 * columnSizes.size();
    for (size_t columnSize : columnSizes) 
        lineWidth += columnSize;

    for (int i = 0; i < lineWidth; i++)
        out << "-";
    out << std::endl;

    // Print header
    out << "| ";
    for (int i = 0; i < this->header.size(); i++) {
        out << std::setw(columnSizes[i]) << this->header[i] << " | ";
    }

    // Print line
    out << std::endl;
    for (int i = 0; i < lineWidth; i++)
        out << "-";
    out << std::endl;

    // Print data
    for (int i = 0; i < this->data[this->header[0]].size(); i++) {
        out << "| ";
        for (int j = 0; j < this->header.size(); j++) {
            const std::string& key = this->header[j];
            out << std::setw(columnSizes[j]) << this->data[key][i] << " | ";
        }

        out << std::endl;
    }

    // Print line
    for (int i = 0; i < lineWidth; i++)
        out << "-";
    out << std::endl;
}

int DataFrame::load(const std::string &fileName) {
    std::ifstream ifs(fileName);

    if (!ifs.is_open())
        return 1;

    std::string line, cell;
    size_t index = 0;

    while (getline(ifs, line)) {
        size_t rowIndex = 0;
        std::stringstream str(line);
        while (getline(str, cell, ',')) {
            if (index == 0) {
                this->header.push_back(cell);
                continue;
            }

            this->data[this->header[rowIndex]].push_back(cell);
            rowIndex++;
        }

        index++;
    }

    return 0;
}

int DataFrame::save(const std::string &fileName) {
    if (!this->header.size())
        return 1;

    std::ofstream ofs(fileName);
    for (const std::string& key : this->header) {
        // Check if key is the last one in header
        if (key == this->header[this->header.size()-1]) {
            ofs << key << std::endl;
            continue;
        }

        ofs << key << ",";
    }

    for (size_t i = 0; i < this->sizeCols(); i++) {
        for (const std::string& key : this->header) {
            // Check if key is the last one in header
            if (key == this->header[this->header.size()-1]) {
                ofs << this->data[key][i] << std::endl;
                continue;
            }

            ofs << this->data[key][i] << ",";
        }
    }

    return 0;
}

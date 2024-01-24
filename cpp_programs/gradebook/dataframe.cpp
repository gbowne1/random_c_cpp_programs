#include "dataframe.h"

#include <fstream>
#include <sstream>

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

void DataFrame::append(const std::map<std::string, std::string> &row) {
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

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <sstream>
#include <utility>
#include <memory>

struct JSONNode;

// Define a simple JSONNode structure to hold JSON data
struct JSONNode {
    std::string key;
    std::variant<int, float, bool, std::string, std::vector<JSONNode*>, std::unordered_map<std::string, JSONNode*>> value;
};

// Define the JSON value types outside the struct
using JSONArray = std::vector<JSONNode*>;
using JSONObject = std::unordered_map<std::string, JSONNode*>;

// Function declarations
JSONArray parseArray(std::istringstream &_stream); // Prefix parameter with underscore
std::variant<int, float, bool, std::string> parseValue(std::istringstream &_stream); // Prefix parameter with underscore
JSONObject parseObject(std::istringstream &_stream); // Prefix parameter with underscore

// Function to parse JSON data from a file
std::vector<JSONNode> parseJSON(const std::string &filename) {
    std::vector<JSONNode> jsonData;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return jsonData;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    std::istringstream stream(content);

    // Implement the rest of the parseJSON function...
    // For simplicity, assume the file contains a JSON object
    JSONObject rootObject = parseObject(stream);
    for (const auto &pair : rootObject) {
    JSONNode node;
    node.key = pair.first; // Correctly accessing the key
    node.value = pair.second->value; // Correctly accessing the value using ->
    jsonData.push_back(node);
    }

    return jsonData;
}

// Implementations of the other parsing functions
JSONArray parseArray(std::istringstream &_stream) { // Prefix parameter with underscore
    JSONArray array;
    // Implement array parsing logic here
    return array;
}

std::variant<int, float, bool, std::string> parseValue(std::istringstream &_stream) {
    // Implement value parsing logic here
    // For demonstration, let's pretend we parsed a string value
    std::string parsedValue = "example";

    // Correctly return the parsed string wrapped in a std::variant
    return parsedValue; // This is now correct because parsedValue is of type std::string
}

JSONObject parseObject(std::istringstream &_stream) { // Prefix parameter with underscore
    JSONObject object;
    // Implement object parsing logic here
    return object;
}

int main() {
    std::vector<std::shared_ptr<JSONNode>> parsedData = parseJSON("data.json");
    for (const auto &node : parsedData) {
        std::cout << "Key: " << node->key << ", Value: ";
        if (std::holds_alternative<std::string>(node->value)) {
            std::cout << std::get<std::string>(node->value);
        } else if (std::holds_alternative<JSONObject>(node->value)) {
            std::cout << "{...}";
        } else if (std::holds_alternative<JSONArray>(node->value)) {
            std::cout << "[...]";
        }
        std::cout << std::endl;
    }
    return 0;
}
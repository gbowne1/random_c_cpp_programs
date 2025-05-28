#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <memory>
#include <stdexcept>

class JsonValue;

using JsonObject = std::unordered_map<std::string, std::shared_ptr<JsonValue>>;
using JsonArray = std::vector<std::shared_ptr<JsonValue>>;

class JsonValue
{
public:
    enum class Type
    {
        Null,
        Boolean,
        Number,
        String,
        Array,
        Object
    };

    JsonValue() : type_(Type::Null) {}
    explicit JsonValue(bool value) : type_(Type::Boolean), bool_(value) {}
    explicit JsonValue(double value) : type_(Type::Number), number_(value) {}
    explicit JsonValue(const std::string &value) : type_(Type::String), string_(value) {}
    explicit JsonValue(JsonArray value) : type_(Type::Array), array_(std::move(value)) {}
    explicit JsonValue(JsonObject value) : type_(Type::Object), object_(std::move(value)) {}

    Type getType() const { return type_; }
    bool getBool() const { return bool_; }
    double getNumber() const { return number_; }
    const std::string &getString() const { return string_; }
    const JsonArray &getArray() const { return array_; }
    const JsonObject &getObject() const { return object_; }

private:
    Type type_;
    bool bool_;
    double number_;
    std::string string_;
    JsonArray array_;
    JsonObject object_;
};

class JsonParser
{
public:
    static std::shared_ptr<JsonValue> parse(const std::string &json)
    {
        std::istringstream is(json);
        return parseValue(is);
    }

private:

    static void skipWhitespace(std::istream &is)
    {
        while (std::isspace(is.peek()))
        {
            is.get();
        }
    }

    static std::shared_ptr<JsonValue> parseValue(std::istream &is)
    {
        skipWhitespace(is);
        char c = is.get();

        if (c == '{')
            return std::make_shared<JsonValue>(parseObject(is));
        if (c == '[')
            return std::make_shared<JsonValue>(parseArray(is));
        if (c == '"')
            return std::make_shared<JsonValue>(parseString(is));
        if (c == 't' || c == 'f')
            return std::make_shared<JsonValue>(parseBoolean(is, c));
        if (c == 'n')
            return parseNull(is);
        if (std::isdigit(c) || c == '-')
        {
            is.unget();
            return std::make_shared<JsonValue>(parseNumber(is));
        }

        throw std::runtime_error("Unexpected character");
    }

    static JsonObject parseObject(std::istream &is)
    {
        JsonObject obj;
        skipWhitespace(is);
        char c = is.get();
        if (c == '}')
            return obj;
        is.unget();

        while (true)
        {
            auto key = parseString(is);
            skipWhitespace(is);
            char c = is.get();
            if (c != ':')
                throw std::runtime_error("Expected ':' after key in object, got '" + std::string(1, c) + "'");

            obj[key] = parseValue(is);

            skipWhitespace(is);
            c = is.get();
            if (c == '}')
                break;
            if (c != ',')
                throw std::runtime_error("Expected ',' or '}' in object, got '" + std::string(1, c) + "'");
        }
        return obj;
    }

    static JsonArray parseArray(std::istream &is)
    {
        JsonArray arr;
        skipWhitespace(is);
        char c = is.get();
        if (c == ']')
            return arr;
        is.unget();

        while (true)
        {
            arr.push_back(parseValue(is));
            skipWhitespace(is);
            char c = is.get();
            if (c == ']')
                break;
            if (c != ',')
                throw std::runtime_error("Expected ',' or ']' in array, got '" + std::string(1, c) + "'");
        }
        return arr;
    }

    static std::string parseString(std::istream &is)
    {
        std::string str;
        char c;
        while (is.get(c) && c != '"')
        {
            if (c == '\\')
            {
                is.get(c);
                switch (c)
                {
                case '"':
                case '\\':
                case '/':
                    str += c;
                    break;
                case 'b':
                    str += '\b';
                    break;
                case 'f':
                    str += '\f';
                    break;
                case 'n':
                    str += '\n';
                    break;
                case 'r':
                    str += '\r';
                    break;
                case 't':
                    str += '\t';
                    break;
                case 'u':
                    throw std::runtime_error("Unicode escape sequences (\\uXXXX) are not supported.");
                default:
                    throw std::runtime_error("Invalid escape sequence");
                }
            }
            else
            {
                str += c;
            }
        }
        return str;
    }

    static bool parseBoolean(std::istream &is, char first)
    {
        std::string rest(3, ' ');
        is.read(&rest[0], 3);
        if (first == 't' && rest == "rue")
            return true;
        if (first == 'f' && rest == "als")
        {
            is.get(); // consume 'e'
            return false;
        }
        throw std::runtime_error("Invalid boolean value");
    }

    static std::shared_ptr<JsonValue> parseNull(std::istream &is)
    {
        std::string rest(3, ' ');
        is.read(&rest[0], 3);
        if (rest == "ull")
            return std::make_shared<JsonValue>();
        throw std::runtime_error("Invalid null value");
    }

    static double parseNumber(std::istream &is)
    {
        std::string numStr;
        char c;
        while (is.peek() != EOF && (std::isdigit(is.peek()) || is.peek() == '.' || is.peek() == 'e' ||
                            is.peek() == 'E' || is.peek() == '+' || is.peek() == '-'))
        {
            is.get(c);
            numStr += c;
        }
        return std::stod(numStr);
    }
};

// Example usage
int main()
{
    std::string jsonStr = R"(
        {
            "name": "John Doe",
            "age": 30,
            "city": "New York",
            "isStudent": false,
            "grades": [85, 90, 78],
            "address": {
                "street": "123 Main St",
                "zip": "10001"
            }
        }
    )";

    try
    {
        auto jsonValue = JsonParser::parse(jsonStr);
        if (jsonValue->getType() == JsonValue::Type::Object)
        {
            const auto &obj = jsonValue->getObject();
            std::cout << "Name: " << obj.at("name")->getString() << std::endl;
            std::cout << "Age: " << obj.at("age")->getNumber() << std::endl;
            std::cout << "Is Student: " << (obj.at("isStudent")->getBool() ? "Yes" : "No") << std::endl;

            std::cout << "Grades: ";
            for (const auto &grade : obj.at("grades")->getArray())
            {
                std::cout << grade->getNumber() << " ";
            }
            std::cout << std::endl;

            const auto &address = obj.at("address")->getObject();
            std::cout << "Street: " << address.at("street")->getString() << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

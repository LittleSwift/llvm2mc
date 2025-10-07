#pragma once
#include <string>

inline std::string zerosString(int n) {
    if (n <= 0) {
        return "";
    }
    std::string result = "0b";
    for (int i = 1; i < n; ++i) {
        result += ",0b";
    }
    return result;
}

inline std::string standardizeName(std::string name) {
    std::ranges::transform(name, name.begin(),
                           [](const unsigned char c){ return std::tolower(c); });
    return name;
}

std::string inline escapeQuotes(const std::string &input) {
    std::string result;
    result.reserve(input.size());
    for (char c : input) {
        if (c == '"') {
            result += "\\\"";
        } else {
            result += c;
        }
    }
    return result;
}

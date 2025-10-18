#include "stringUtils.h"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <openssl/sha.h>

std::string zerosString(const int n) {
    if (n <= 0) {
        return "";
    }
    std::string result = "0b";
    for (int i = 1; i < n; ++i) {
        result += ",0b";
    }
    return result;
}

std::string sha256Hash(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

std::string safeName(const std::string& name) {
    if (name.rfind("_Z", 0) != 0) {
        return name;
    }
    return sha256Hash(name);
}

std::string standardizeName(std::string name) {
    std::string result;
    std::ranges::transform(name, result.begin(),
                           [](const unsigned char c){ return std::tolower(c); });
    return name;
}

std::string escapeQuotes(const std::string &input) {
    std::string result;
    result.reserve(input.size());
    for (const char c : input) {
        if (c == '"') {
            result += "\\\"";
        } else {
            result += c;
        }
    }
    return result;
}

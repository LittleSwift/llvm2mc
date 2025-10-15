#pragma once
#include <sstream>
#include <string>
#include <openssl/sha.h>

std::string zerosString(int n);
std::string sha256Hash(const std::string& input);
std::string safeName(const std::string& name);
std::string standardizeName(std::string name);
std::string escapeQuotes(const std::string &input);

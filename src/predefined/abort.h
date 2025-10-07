#pragma once

#include <sstream>

#include "../utils/stringUtils.h"

inline std::string mAbort(const std::string &message) {
    std::ostringstream commands;
    commands << R"(tellraw @a {"type":"text", "color":"red", "text":")" << escapeQuotes(message) << "\"}\n";
    return commands.str();
}

#include "abort.h"

#include <sstream>

#include "../utils/stringUtils.h"

std::string mAbort(const std::string &message) {
    std::ostringstream commands;
    commands << R"(tellraw @a {"type":"text", "color":"red", "text":")" << escapeQuotes(message) << "\"}\n";
    return commands.str();
}

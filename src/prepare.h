#pragma once
#include <fstream>

#include "const.h"
#include "predefined/abort.h"
#include "predefined/data.h"
#include "utils/stringUtils.h"

inline void prepare() {
    std::ofstream entryFile("output/_entry.mcfunction");
    entryFile << "data modify storage " << projectNamespace << " args set value {}\n";
    entryFile << "data modify storage " << projectNamespace << " global set value {}\n";
    entryFile << "data modify storage " << projectNamespace << " stack set value []\n";
    entryFile << "data modify storage " << projectNamespace << " memory set value [" << zerosString(kMemorySize) << "]\n";
    entryFile << "scoreboard objectives add register dummy\n";
    entryFile << "scoreboard players set stackTop register 0\n";
    entryFile << "scoreboard players set stackSize register " << kStackSize << "\n";

    entryFile << "scoreboard objectives add const dummy\n";
    for (int number: kDefinedConsts) {
        entryFile << (number >> ScoreField(std::to_string(number), "const"));
    }

    entryFile << "data modify storage " << projectNamespace << " stack insert -1 value {}\n";
    entryFile << "function llvm2mc:main\n";
    if (debug) {
        entryFile << "execute if data storage " << projectNamespace << " stack[-1].ret run tellraw @a {\"text\":\"Process exited with non-zero return code \",\"color\":\"red\",\"extra\":[{\"storage\":\""
                  << projectNamespace<<"\",\"nbt\":\"stack[-1].ret\"}]}\n";
    }
    entryFile << "data remove storage " << projectNamespace << " stack[-1]\n";
    entryFile.close();

    std::ofstream storeFile("output/_store.mcfunction");
    if (debug) {
        entryFile << "tellraw @a {\"text\":\"Store $(ptr): \",\"extra\":[{\"storage\":\""
                  << projectNamespace <<"\",\"nbt\":\"store\"}]}\n";
    }
    storeFile << "$execute store result storage " << projectNamespace << " memory[$(ptr)] byte 1 run data get storage " << projectNamespace << " store\n";
    storeFile.close();

    std::ofstream loadFile("output/_load.mcfunction");
    loadFile << "$execute store result storage " << projectNamespace << " load int 1 run data get storage " << projectNamespace << " memory[$(ptr)]\n";
    if (debug) {
        entryFile << "tellraw @a {\"text\":\"Load $(ptr): \",\"extra\":[{\"storage\":\""
                  << projectNamespace <<"\",\"nbt\":\"load\"}]}\n";
    }
    storeFile.close();
}

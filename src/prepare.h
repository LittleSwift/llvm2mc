#pragma once
#include <fstream>

#include "const.h"
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
    entryFile << "data remove storage " << projectNamespace << " stack[-1]\n";
    entryFile.close();

    std::ofstream storeFile("output/_store.mcfunction");
    storeFile << "$data modify storage " << projectNamespace << " memory[$(ptr)] set from " << projectNamespace << " store\n";
    storeFile.close();

    std::ofstream loadFile("output/_load.mcfunction");
    loadFile << "$data modify storage" << projectNamespace << " load set from " << projectNamespace << " memory[$(ptr)]\n";
    storeFile.close();
}

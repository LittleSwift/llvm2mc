#pragma once
#include <fstream>

#include "const.h"
#include "predefined/data.h"
#include "utils/stringUtils.h"

inline void prepare() {
    std::ofstream entryFile("output/_entry.mcfunction");
    entryFile << "data modify storage llvm2mc:llvm2mc args set value {}\n";
    entryFile << "data modify storage llvm2mc:llvm2mc global set value {}\n";
    entryFile << "data modify storage llvm2mc:llvm2mc stack set value []\n";
    entryFile << "data modify storage llvm2mc:llvm2mc memory set value [" << zerosString(kMemorySize) << "]\n";
    entryFile << "scoreboard objectives add register dummy\n";
    entryFile << "scoreboard players set stackTop register 0\n";
    entryFile << "scoreboard players set stackSize register " << kStackSize << "\n";

    entryFile << "scoreboard objectives add const dummy\n";
    for (int number: kDefinedConsts) {
        entryFile << (number >> ScoreField(std::to_string(number), "const"));
    }

    entryFile << "data modify storage llvm2mc:llvm2mc stack insert -1 value {}\n";
    entryFile << "function llvm2mc:main\n";
    entryFile << "data remove storage llvm2mc:llvm2mc stack[-1]\n";
    entryFile.close();

    std::ofstream storeFile("output/_store.mcfunction");
    storeFile<<"$data modify storage llvm2mc:llvm2mc memory[$(ptr)] set from llvm2mc:llvm2mc store\n";
    storeFile.close();
}

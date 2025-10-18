#include "prepare.h"

#include <fstream>
#include <numeric>

#include "const.h"
#include "predefined/data.h"
#include "utils/stringUtils.h"

// CLion does not support #embed yet
constexpr static char entryFunc[] = {
#ifndef __JETBRAINS_IDE__
#embed "mcfunctions/_entry.mcfunction"
#else
    0
#endif
    , 0
};
constexpr static char loadFunc[] = {
#ifndef __JETBRAINS_IDE__
#embed "mcfunctions/_load.mcfunction"
#else
    0
#endif
    , 0
};
constexpr static char storeFunc[] = {
#ifndef __JETBRAINS_IDE__
#embed "mcfunctions/_store.mcfunction"
#else
    0
#endif
    , 0
};

void prepare() {
    std::ofstream entryFile("output/_entry.mcfunction");
    entryFile << std::format(entryFunc, projectNamespace, zerosString(kMemorySize), std::accumulate(
        kDefinedConsts.begin(), kDefinedConsts.end(), std::string(),
        [](const std::string& acc, const int n) {
            return acc + (n >> ScoreField(std::to_string(n), "const"));
        }
    ));
    entryFile.close();

    std::ofstream storeFile("output/_store.mcfunction");
    storeFile << std::format(storeFunc, projectNamespace);
    storeFile.close();

    std::ofstream loadFile("output/_load.mcfunction");
    loadFile << std::format(loadFunc, projectNamespace);
    loadFile.close();
}

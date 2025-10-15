#pragma once

#include <llvm/IR/Type.h>
#include "../const.h"

constexpr bool defined(const int value) {
    return std::ranges::any_of(
        kDefinedConsts,
        [value](const int x) { return x == value; }
    );
}

bool is64BitType(const llvm::Type* type);
bool is32BitType(const llvm::Type* type);
bool is16BitType(const llvm::Type* type);
bool is8BitType(const llvm::Type* type);
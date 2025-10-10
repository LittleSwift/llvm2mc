#pragma once
#include "../const.h"

constexpr bool defined(const int value) {
    return std::ranges::any_of(
        kDefinedConsts,
        [value](const int x) { return x == value; }
    );
}

inline bool is64BitType(const llvm::Type* type) {
    return (type->isIntegerTy() && type->getIntegerBitWidth() == 64) ||
           type->isDoubleTy();
}

inline bool is32BitType(const llvm::Type* type) {
    return type->isPointerTy() ||
           (type->isIntegerTy() && type->getIntegerBitWidth() == 32) ||
           type->isFloatTy();
}

inline bool is16BitType(const llvm::Type* type) {
    return type->isIntegerTy() && type->getIntegerBitWidth() == 16;
}

inline bool is8BitType(const llvm::Type* type) {
    return type->isIntegerTy() &&
           (type->getIntegerBitWidth() == 8 || type->getIntegerBitWidth() == 1);
}
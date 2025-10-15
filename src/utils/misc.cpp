#include "misc.h"

#include <llvm/IR/Instruction.h>
#include <llvm/IR/Type.h>

bool is64BitType(const llvm::Type* type) {
    return (type->isIntegerTy() && type->getIntegerBitWidth() == 64) ||
           type->isDoubleTy();
}

bool is32BitType(const llvm::Type* type) {
    return type->isPointerTy() ||
           (type->isIntegerTy() && type->getIntegerBitWidth() == 32) ||
           type->isFloatTy();
}

bool is16BitType(const llvm::Type* type) {
    return type->isIntegerTy() && type->getIntegerBitWidth() == 16;
}

bool is8BitType(const llvm::Type* type) {
    return type->isIntegerTy() &&
           (type->getIntegerBitWidth() == 8 || type->getIntegerBitWidth() == 1);
}

std::string instructionToString(const llvm::Instruction* inst) {
    std::string str;
    llvm::raw_string_ostream rso(str);
    inst->print(rso);
    return rso.str();
}
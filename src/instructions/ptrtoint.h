#pragma once

#include <llvm/IR/Instructions.h>

std::string handlePtrToInt(const llvm::Function &func, const llvm::PtrToIntInst &inst);
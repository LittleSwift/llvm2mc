#pragma once

#include <llvm/IR/Instructions.h>

std::string handleTrunc(const llvm::Function &func, const llvm::TruncInst &inst);

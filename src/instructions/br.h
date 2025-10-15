#pragma once

#include <llvm/IR/Instructions.h>

std::string handleBr(const llvm::Function &func, const llvm::BranchInst &inst);

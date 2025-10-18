#pragma once

#include <llvm/IR/Instructions.h>

std::string handleIntToPtr(const llvm::Function &func, const llvm::IntToPtrInst &inst);
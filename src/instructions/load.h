#pragma once

#include <llvm/IR/Instructions.h>

std::string handleLoad(const llvm::Function &func, const llvm::LoadInst &inst);

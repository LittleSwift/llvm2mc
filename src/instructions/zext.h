#pragma once

#include <llvm/IR/Instructions.h>

std::string handleZExt(const llvm::Function &func, const llvm::ZExtInst &inst);
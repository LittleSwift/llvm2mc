#pragma once

#include <llvm/IR/Instructions.h>

std::string handleAlloca(const llvm::Function &func, const llvm::AllocaInst &inst);
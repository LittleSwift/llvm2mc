#pragma once

#include <llvm/IR/Instructions.h>

std::string handleRet(const llvm::Function &func, const llvm::ReturnInst &inst);
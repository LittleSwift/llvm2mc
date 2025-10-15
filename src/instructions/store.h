#pragma once

#include <llvm/IR/Instructions.h>

std::string handleStore(const llvm::Function &func, const llvm::StoreInst &inst);
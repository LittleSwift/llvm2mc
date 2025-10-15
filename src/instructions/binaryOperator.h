#pragma once

#include <llvm/IR/Instructions.h>

std::string handleBinaryOperator(const llvm::Function &func, const llvm::BinaryOperator &inst);
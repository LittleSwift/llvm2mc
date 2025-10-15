#pragma once

#include <string>
#include <llvm/IR/Constant.h>

std::string constantToString(const llvm::Constant *C);
std::string constantToString(const llvm::Constant& C);
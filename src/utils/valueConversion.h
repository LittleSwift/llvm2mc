#pragma once
#include <string>
#include <llvm/IR/Value.h>

std::string valueToString(const llvm::Value& value);
std::string valueToString(const llvm::Value* value);

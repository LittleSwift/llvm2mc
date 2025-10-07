#pragma once
#include <string>
#include <llvm/IR/Value.h>

inline std::string valueToString(const llvm::Value& value) {
    const std::string &name = value.getNameOrAsOperand();
    if (name[0] == '%') {
        return "stack[-1]." + name.substr(1);
    }
    if (name[0] == '@') {
        return "global." + name.substr(1);
    }
    throw std::runtime_error(name + " is not a value");
}

inline std::string valueToString(const llvm::Value* value) {
    return valueToString(*value);
}

#include "valueConversion.h"
#include <string>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>

std::string valueToString(const llvm::Value& value) {
    const std::string &name = value.getNameOrAsOperand();
    if (name[0] == '%') {
        return "stack[-1]." + name.substr(1);
    }
    return "global." + name;
}

std::string valueToString(const llvm::Value* value) {
    return valueToString(*value);
}

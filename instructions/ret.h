#pragma once

#include <sstream>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include "../constConversion.h"

inline std::string handleRet(const llvm::Function &func, const llvm::ReturnInst &inst) {
    std::ostringstream commands;
    if (inst.getReturnValue()) {
        if (const llvm::Value *ret = inst.getReturnValue(); llvm::isa<llvm::Constant>(ret)) {
            commands << "data modify storage llvm2mc:llvm2mc stack[-1].ret set value "
                     << constantToString(llvm::cast<llvm::Constant>(ret)) << "\n";
        } else {
            commands << "data modify storage llvm2mc:llvm2mc stack[-1].ret set from llvm2mc:llvm2mc stack[-1]."
                     << ret->getNameOrAsOperand() << "\n";
        }
    }
    return commands.str();
}

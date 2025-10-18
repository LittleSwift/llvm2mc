#include "alloca.h"

#include <sstream>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include "../const.h"
#include "../predefined/abort.h"
#include "../predefined/data.h"

std::string handleAlloca(const llvm::Function &func, const llvm::AllocaInst &inst) {
    std::ostringstream commands;
    const ScoreField stackTop("stackTop", "register");
    commands << (stackTop >> DataField(inst));
    commands << (stackTop + inst.getAllocationSize(inst.getDataLayout()).value());
    return commands.str();
}

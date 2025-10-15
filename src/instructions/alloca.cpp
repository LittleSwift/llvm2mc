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
    if (debug) {
        commands << "execute if score stackTop register > stackSize register run " << mAbort("Reached max stack size.");
    }
    return commands.str();
}

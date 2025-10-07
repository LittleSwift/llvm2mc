#pragma once

#include <sstream>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include "../predefined/abort.h"
#include "../utils/valueConversion.h"

inline std::string handleAlloca(const llvm::Function &func, const llvm::AllocaInst &inst) {
    std::ostringstream commands;
    commands << "execute store result storage llvm2mc:llvm2mc "
             << valueToString(inst) << " run scoreboard players get stackTop register\n";
    commands << "run scoreboard players add stackTop register "
          << inst.getAllocationSize(inst.getDataLayout()).value() << "\n";
    if (debug) {
        commands << "execute if score stackTop register > stackSize register run " << mAbort("Reached max stack size.");
    }
    return commands.str();
}

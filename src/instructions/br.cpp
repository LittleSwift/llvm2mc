#include "br.h"

#include <sstream>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

std::string handleBr(const llvm::Function &func, const llvm::BranchInst &inst) {
    std::ostringstream commands;
    if (inst.isConditional()) {
        llvm::Value *cond = inst.getCondition();
        const llvm::BasicBlock *trueBB = inst.getSuccessor(0);
        const llvm::BasicBlock *falseBB = inst.getSuccessor(1);
        if (llvm::isa<llvm::ConstantInt>(cond)) {
            if (llvm::cast<llvm::ConstantInt>(cond)->getValue().getBoolValue()) {
                commands << "function " << func.getName().str() << "/" << trueBB->getNumber() << "\n";
            } else {
                commands << "function " << func.getName().str() << "/" << falseBB->getNumber() << "\n";
            }
        } else {
            commands << "data modify storage llvm2mc:llvm2mc success set value true\n";
            commands << "execute if data storage llvm2mc:llvm2mc stack[-1]."
                      << cond->getNameOrAsOperand()
                      << " store success storage llvm2mc:llvm2mc success byte 1 run function "
                      << func.getName().str() << "/" << trueBB->getNumber() << "\n";
            commands << "execute unless data storage llvm2mc:llvm2mc success run function "
                      << func.getName().str() << "/" << falseBB->getNumber() << "\n";
        }
    } else {
        const llvm::BasicBlock *dest = inst.getSuccessor(0);
        commands << "function " << func.getName().str() << "/" << dest->getNumber() << "\n";
    }
    return commands.str();
}

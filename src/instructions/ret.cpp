#include "ret.h"

#include <sstream>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include "../utils/constConversion.h"
#include "../predefined/data.h"

std::string handleRet(const llvm::Function &func, const llvm::ReturnInst &inst) {
    std::ostringstream commands;
    if (inst.getReturnValue()) {
        const DataField target("stack[-1].ret");
        if (const llvm::Value *ret = inst.getReturnValue(); llvm::isa<llvm::Constant>(ret)) {
            commands << "data modify storage llvm2mc:llvm2mc stack[-1].ret set value "
                     << constantToString(llvm::cast<llvm::Constant>(ret)) << "\n";
        } else {
            commands << (DataField(ret) >> target);
        }
    }
    return commands.str();
}

#include "inttoptr.h"

#include <sstream>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include "../predefined/data.h"
#include "../utils/misc.h"

std::string handleIntToPtr(const llvm::Function &func, const llvm::IntToPtrInst &inst) {
    std::ostringstream commands;
    const llvm::Value *value = inst.getOperand(0);
    const DataField source = DataField(value);
    const DataField dest = DataField(inst);
    if (is64BitType(value->getType())) {
        commands << (source[0] >> dest);
    } else {
        commands << (source >> dest);
    }
    return commands.str();
}

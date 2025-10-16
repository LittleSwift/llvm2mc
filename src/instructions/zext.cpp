#include "zext.h"

#include <sstream>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include "../predefined/data.h"
#include "../utils/misc.h"

std::string handleZExt(const llvm::Function &func, const llvm::ZExtInst &inst) {
    std::ostringstream commands;
    const llvm::Value *value = inst.getOperand(0);
    const DataField source = DataField(value);
    const DataField dest = DataField(inst);
    if (is64BitType(inst.getType())) {
        commands << ("[0,0]" >> dest);
        commands << (source >> dest[0]);
    } else {
        commands << (source >> dest);
    }
    return commands.str();
}

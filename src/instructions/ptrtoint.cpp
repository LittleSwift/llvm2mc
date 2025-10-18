#include "ptrtoint.h"

#include <sstream>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include "../predefined/data.h"
#include "../utils/misc.h"

std::string handlePtrToInt(const llvm::Function &func, const llvm::PtrToIntInst &inst) {
    std::ostringstream commands;
    const llvm::Value *value = inst.getOperand(0);
    const DataField source = DataField(value);
    const DataField dest = DataField(inst);
    if (is64BitType(inst.getType())) {
        commands << ("[0,0]" >> dest);
        commands << "execute store result storage " << projectNamespace << " temp int 1 run data get storage "
                 << projectNamespace << " " << source << "\n";
        commands << "execute store result storage " << projectNamespace << " " << dest[0] << " int 1 run data get storage "
                 << projectNamespace << " temp\n";
    }
    if (is32BitType(inst.getType())) {
        commands << "execute store result storage " << projectNamespace << " temp int 1 run data get storage "
                 << projectNamespace << " " << source << "\n";
        commands << "execute store result storage " << projectNamespace << " " << dest << " int 1 run data get storage "
                 << projectNamespace << " temp\n";
    }
    if (is16BitType(inst.getType())) {
        commands << "execute store result storage " << projectNamespace << " temp short 1 run data get storage "
                 << projectNamespace << " " << source << "\n";
        commands << "execute store result storage " << projectNamespace << " " << dest << " int 1 run data get storage "
                 << projectNamespace << " temp\n";
    }
    if (is8BitType(inst.getType())) {
        commands << "execute store result storage " << projectNamespace << " temp byte 1 run data get storage "
                 << projectNamespace << " " << source << "\n";
        commands << "execute store result storage " << projectNamespace << " " << dest << " int 1 run data get storage "
                 << projectNamespace << " temp\n";
    }
    return commands.str();
}

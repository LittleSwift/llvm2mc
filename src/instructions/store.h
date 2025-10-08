#pragma once

#include <sstream>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include "../utils/valueConversion.h"

inline std::string handleStore(const llvm::Function &func, const llvm::StoreInst &inst) {
    std::ostringstream commands;
    const llvm::Value *value = inst.getValueOperand();
    const llvm::Type *type = value -> getType();
    const llvm::Value *ptr = inst.getPointerOperand();
    if (llvm::isa<llvm::Constant>(value)) {
        commands << "data modify storage llvm2mc:llvm2mc store set value "
                 << constantToString(llvm::cast<llvm::Constant>(value)) << "\n";
    } else {
        commands << "data modify storage llvm2mc:llvm2mc store set from "
                 << valueToString(value) << "\n";
    }
    if (type->isIntegerTy() && type->getIntegerBitWidth() == 64 || type->isDoubleTy()) {
        commands << "execute store result score store register run data get llvm2mc:llvm2mc store[0]\n";
        commands << "execute store result score ptr register run data get llvm2mc:llvm2mc "
                 << valueToString(ptr) << "\n";
        for (int i = 0; i < 4; i++) {
            commands << "execute store result storage llvm2mc:llvm2mc args.ptr int 1 run scoreboard players get ptr register\n";
            commands << "execute store result storage llvm2mc:llvm2mc store int 1 run scoreboard players get store register\n";
            commands << "function llvm2mc:_store with storage llvm2mc:llvm2mc args\n";
            commands << "scoreboard players add ptr register 1\n";
            commands << "scoreboard players operation store register /= 256 const\n";
        }
        commands << "execute store result score store register run data get llvm2mc:llvm2mc store[1]\n";
        for (int i = 0; i < 4; i++) {
            commands << "execute store result storage llvm2mc:llvm2mc args.ptr int 1 run scoreboard players get ptr register\n";
            commands << "execute store result storage llvm2mc:llvm2mc store int 1 run scoreboard players get store register\n";
            commands << "function llvm2mc:_store with storage llvm2mc:llvm2mc args\n";
            commands << "scoreboard players add ptr register 1\n";
            commands << "scoreboard players operation store register /= 256 const\n";
        }
    } else if (type->isPointerTy() || type->isIntegerTy() && type->getIntegerBitWidth() == 32 || type->isFloatTy()) {
        commands << "execute store result score store register run data get llvm2mc:llvm2mc store\n";
        commands << "execute store result score ptr register run data get llvm2mc:llvm2mc "
                 << valueToString(ptr) << "\n";
        for (int i = 0; i < 4; i++) {
            commands << "execute store result storage llvm2mc:llvm2mc args.ptr int 1 run scoreboard players get ptr register\n";
            commands << "execute store result storage llvm2mc:llvm2mc store int 1 run scoreboard players get store register\n";
            commands << "function llvm2mc:_store with storage llvm2mc:llvm2mc args\n";
            commands << "scoreboard players add ptr register 1\n";
            commands << "scoreboard players operation store register /= 256 const\n";
        }
    } else if (type->isIntegerTy() && type->getIntegerBitWidth() == 16) {
        commands << "execute store result score store register run data get llvm2mc:llvm2mc store\n";
        commands << "execute store result score ptr register run data get llvm2mc:llvm2mc "
                 << valueToString(ptr) << "\n";
        for (int i = 0; i < 2; i++) {
            commands << "execute store result storage llvm2mc:llvm2mc args.ptr int 1 run scoreboard players get ptr register\n";
            commands << "execute store result storage llvm2mc:llvm2mc store int 1 run scoreboard players get store register\n";
            commands << "function llvm2mc:_store with storage llvm2mc:llvm2mc args\n";
            commands << "scoreboard players add ptr register 1\n";
            commands << "scoreboard players operation store register /= 256 const\n";
        }
    } else if (type->isIntegerTy() && (type->getIntegerBitWidth() == 8 || type->getIntegerBitWidth() == 1)) {
        commands << "data modify storage llvm2mc:llvm2mc args.ptr set from " << valueToString(ptr) << "\n";
        commands << "function llvm2mc:_store with storage llvm2mc:llvm2mc args\n";
    } else {
        throw std::invalid_argument("Invalid type");
    }
    return commands.str();
}

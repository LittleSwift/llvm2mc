#pragma once

#include <sstream>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include "../predefined/data.h"
#include "../utils/valueConversion.h"

inline std::string handleStore(const llvm::Function &func, const llvm::StoreInst &inst) {
    std::ostringstream commands;
    const llvm::Value *value = inst.getValueOperand();
    const llvm::Type *type = value -> getType();
    const llvm::Value *ptr = inst.getPointerOperand();
    const DataField storeField("store");
    const ScoreField storeBoard("store", "register");
    const DataField ptrField(ptr);
    const ScoreField ptrBoard("ptr", "register");
    const DataField argsPtrField("args.ptr");
    if (llvm::isa<llvm::Constant>(value)) {
        commands << "data modify storage llvm2mc:llvm2mc store set value "
                 << constantToString(llvm::cast<llvm::Constant>(value)) << "\n";
    } else {
        commands << (DataField(value) >> storeField);
    }
    if (type->isIntegerTy() && type->getIntegerBitWidth() == 64 || type->isDoubleTy()) {
        commands << (storeField[0] >> storeBoard);
        commands << (ptrField >> ptrBoard);
        for (int i = 0; i < 4; i++) {
            commands << (ptrBoard >> argsPtrField);
            commands << (storeBoard >> storeField);
            commands << "function llvm2mc:_store with storage llvm2mc:llvm2mc args\n";
            commands << (ptrBoard + 1);
            commands << (storeBoard / 256);
        }
        commands << (storeField[1] >> storeBoard);
        for (int i = 0; i < 4; i++) {
            commands << (ptrBoard >> argsPtrField);
            commands << (storeBoard >> storeField);
            commands << "function llvm2mc:_store with storage llvm2mc:llvm2mc args\n";
            commands << (ptrBoard + 1);
            commands << (storeBoard / 256);
        }
    } else if (type->isPointerTy() || type->isIntegerTy() && type->getIntegerBitWidth() == 32 || type->isFloatTy()) {
        commands << (storeField >> storeBoard);
        commands << (ptrField >> ptrBoard);
        for (int i = 0; i < 4; i++) {
            commands << (ptrBoard >> argsPtrField);
            commands << (storeBoard >> storeField);
            commands << "function llvm2mc:_store with storage llvm2mc:llvm2mc args\n";
            commands << (ptrBoard + 1);
            commands << (storeBoard / 256);
        }
    } else if (type->isIntegerTy() && type->getIntegerBitWidth() == 16) {
        commands << (storeField >> storeBoard);
        commands << (ptrField >> ptrBoard);
        for (int i = 0; i < 2; i++) {
            commands << (ptrBoard >> argsPtrField);
            commands << (storeBoard >> storeField);
            commands << "function llvm2mc:_store with storage llvm2mc:llvm2mc args\n";
            commands << (ptrBoard + 1);
            commands << (storeBoard / 256);
        }
    } else if (type->isIntegerTy() && (type->getIntegerBitWidth() == 8 || type->getIntegerBitWidth() == 1)) {
        commands << (ptrField >> argsPtrField);
        commands << "function llvm2mc:_store with storage llvm2mc:llvm2mc args\n";
    } else {
        throw std::invalid_argument("Invalid type");
    }
    return commands.str();
}

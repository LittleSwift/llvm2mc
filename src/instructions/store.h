#pragma once

#include <sstream>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include "../predefined/data.h"

inline void emitStoreLoop(std::ostringstream& commands,
                          const ScoreField& ptrBoard,
                          const ScoreField& storeBoard,
                          const DataField& argsPtrField,
                          const DataField& storeField,
                          const int iterations) {
    for (int i = 0; i < iterations; i++) {
        commands << (ptrBoard >> argsPtrField);
        commands << (storeBoard >> storeField);
        commands << "function llvm2mc:_store with storage llvm2mc:llvm2mc args\n";
        commands << (ptrBoard + 1);
        commands << (storeBoard / 256);
    }
}

inline bool is64BitType(const llvm::Type* type) {
    return (type->isIntegerTy() && type->getIntegerBitWidth() == 64) ||
           type->isDoubleTy();
}

inline bool is32BitType(const llvm::Type* type) {
    return type->isPointerTy() ||
           (type->isIntegerTy() && type->getIntegerBitWidth() == 32) ||
           type->isFloatTy();
}

inline bool is16BitType(const llvm::Type* type) {
    return type->isIntegerTy() && type->getIntegerBitWidth() == 16;
}

inline bool is8BitType(const llvm::Type* type) {
    return type->isIntegerTy() &&
           (type->getIntegerBitWidth() == 8 || type->getIntegerBitWidth() == 1);
}

inline std::string handleStore(const llvm::Function &func, const llvm::StoreInst &inst) {
    std::ostringstream commands;
    const llvm::Value *value = inst.getValueOperand();
    const llvm::Type *type = value->getType();
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

    if (is64BitType(type)) {
        commands << (storeField[0] >> storeBoard);
        commands << (ptrField >> ptrBoard);
        emitStoreLoop(commands, ptrBoard, storeBoard, argsPtrField, storeField, 4);
        commands << (storeField[1] >> storeBoard);
        emitStoreLoop(commands, ptrBoard, storeBoard, argsPtrField, storeField, 4);
    } else if (is32BitType(type)) {
        commands << (storeField >> storeBoard);
        commands << (ptrField >> ptrBoard);
        emitStoreLoop(commands, ptrBoard, storeBoard, argsPtrField, storeField, 4);
    } else if (is16BitType(type)) {
        commands << (storeField >> storeBoard);
        commands << (ptrField >> ptrBoard);
        emitStoreLoop(commands, ptrBoard, storeBoard, argsPtrField, storeField, 2);
    } else if (is8BitType(type)) {
        commands << (ptrField >> argsPtrField);
        commands << "function llvm2mc:_store with storage llvm2mc:llvm2mc args\n";
    } else {
        throw std::invalid_argument("Invalid type for store instruction");
    }
    return commands.str();
}

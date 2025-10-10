#pragma once

#include <sstream>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include "../predefined/data.h"

inline void emitLoadLoop(std::ostringstream& commands,
                          const ScoreField& ptrBoard,
                          const ScoreField& loadBoard,
                          const DataField& argsPtrField,
                          const DataField& loadField,
                          const ScoreField& tmpBoard,
                          const int iterations) {
    for (int i = 0; i < iterations; i++) {
        commands << (loadBoard * 256);
        commands << (ptrBoard >> argsPtrField);
        commands << "function llvm2mc:_load with storage llvm2mc:llvm2mc args\n";
        commands << (loadField >> tmpBoard);
        commands << (loadBoard + tmpBoard);
        commands << (ptrBoard + 1);
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

inline std::string handleLoad(const llvm::Function &func, const llvm::LoadInst &inst) {
    std::ostringstream commands;
    const llvm::Value *value = &inst;
    const llvm::Type *type = value->getType();
    const llvm::Value *ptr = inst.getPointerOperand();

    const DataField resultField(value);
    const DataField loadField("load");
    const ScoreField loadBoard("load", "register");
    const DataField ptrField(ptr);
    const ScoreField ptrBoard("ptr", "register");
    const DataField argsPtrField("args.ptr");
    const ScoreField tmpBoard("tmp", "register");

    commands << (ptrField >> ptrBoard);

    if (is64BitType(type)) {
        commands << ("[]" >> resultField);
        commands << (ptrField >> ptrBoard);
        commands << (0 >> loadBoard);
        emitLoadLoop(commands, ptrBoard, loadBoard, argsPtrField, loadField, tmpBoard, 4);
        commands << (loadBoard >> resultField[0]);
        commands << (0 >> loadBoard);
        emitLoadLoop(commands, ptrBoard, loadBoard, argsPtrField, loadField, tmpBoard, 4);
        commands << (loadBoard >> resultField[1]);
    } else if (is32BitType(type)) {
        commands << (ptrField >> ptrBoard);
        commands << (0 >> loadBoard);
        emitLoadLoop(commands, ptrBoard, loadBoard, argsPtrField, loadField, tmpBoard, 4);
        commands << (loadBoard >> resultField);
    } else if (is16BitType(type)) {
        commands << (ptrField >> ptrBoard);
        commands << (0 >> loadBoard);
        emitLoadLoop(commands, ptrBoard, loadBoard, argsPtrField, loadField, tmpBoard, 2);
        commands << (loadBoard >> resultField);
    } else if (is8BitType(type)) {
        commands << (ptrField >> argsPtrField);
        commands << "function llvm2mc:_load with storage llvm2mc:llvm2mc args\n";
    } else {
        throw std::invalid_argument("Invalid type for load instruction");
    }
    return commands.str();
}

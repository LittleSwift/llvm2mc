#pragma once

#include <iostream>
#include <sstream>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

inline bool is64(const llvm::Instruction &inst) {
    return inst.getType()->getIntegerBitWidth() == 64;
}

inline std::string handleBinaryOperator(const llvm::Function &func, const llvm::BinaryOperator &inst) {
    std::ostringstream commands;
    switch (inst.getOpcode()) {
        case llvm::Instruction::Add:
            if (is64(inst)) {
                if (llvm::isa<llvm::Constant>(inst.getOperand(0))) {
                    commands << "scoreboard players set arg1lo register "
                             << llvm::cast<llvm::ConstantInt>(inst.getOperand(0))->getValue().getLoBits(32).getLimitedValue()
                             << "\n";
                    commands << "scoreboard players set arg1hi register "
                             << llvm::cast<llvm::ConstantInt>(inst.getOperand(0))->getValue().getHiBits(32).getLimitedValue()
                             << "\n";
                } else {
                    commands << "execute store result score arg1lo register run data get llvm2mc::llvm2mc llvm2mc::llvm2mc "
                             << valueToString(inst.getOperand(0)) << "[0]\n";
                    commands << "execute store result score arg1hi register run data get llvm2mc::llvm2mc llvm2mc::llvm2mc "
                             << valueToString(inst.getOperand(0)) << "[1]\n";
                }
                if (llvm::isa<llvm::Constant>(inst.getOperand(1))) {
                    commands << "scoreboard players set arg2lo register "
                             << llvm::cast<llvm::ConstantInt>(inst.getOperand(1))->getValue().getLoBits(32).getLimitedValue()
                             << "\n";
                    commands << "scoreboard players set arg2hi register "
                             << llvm::cast<llvm::ConstantInt>(inst.getOperand(1))->getValue().getHiBits(32).getLimitedValue()
                             << "\n";
                } else {
                    commands << "execute store result score arg2lo register run data get llvm2mc::llvm2mc "
                             << valueToString(inst.getOperand(1)) << "[0]\n";
                    commands << "execute store result score arg2hi register run data get llvm2mc::llvm2mc "
                             << valueToString(inst.getOperand(1)) << "[1]\n";
                }
                commands << "scoreboard players set carry register 0\n";
                commands << "scoreboard players operation arg1lo register += arg2lo register\n";
                commands << "execute if arg1lo register < arg2lo register run scoreboard players set carry 1\n";
                commands << "scoreboard players operation arg1hi register += arg2hi register\n";
                commands << "scoreboard players operation arg1hi register += carry register\n";
                commands << "data modify llvm2mc::llvm2mc " << valueToString(inst) << " set {}\n";
                commands << "execute store result storage llvm2mc::llvm2mc " << valueToString(inst)
                         << "[0] int 1 run scoreboard players get arg1lo register\n";
                commands << "execute store result storage llvm2mc::llvm2mc " << valueToString(inst)
                         << "[1] int 1 run scoreboard players get arg1hi register\n";
            } else {
                if (llvm::isa<llvm::Constant>(inst.getOperand(0))) {
                    commands << "scoreboard players set arg1 register "
                             << llvm::cast<llvm::ConstantInt>(inst.getOperand(0))->getValue().getLimitedValue()
                             << "\n";
                } else {
                    commands << "execute store result score arg1 register run data get llvm2mc::llvm2mc "
                             << valueToString(inst.getOperand(0)) << "\n";
                }
                if (llvm::isa<llvm::Constant>(inst.getOperand(1))) {
                    commands << "scoreboard players set arg2 register "
                             << llvm::cast<llvm::ConstantInt>(inst.getOperand(1))->getValue().getLimitedValue()
                             << "\n";
                } else {
                    commands << "execute store result score arg2 register run data get llvm2mc::llvm2mc "
                             << valueToString(inst.getOperand(1)) << "\n";
                }
                commands << "scoreboard players operation arg1 register += arg2 register\n";
                std::string type;
                switch (inst.getType()->getIntegerBitWidth()) {
                    case 1:
                    case 8: type = "byte"; break;
                    case 16: type = "short"; break;
                    case 32: type = "int"; break;
                    default: throw std::runtime_error("Unknown operand type");
                }
                commands << "execute store result storage llvm2mc::llvm2mc " << valueToString(inst)
                         << " " << type << " 1 run scoreboard players get arg1 register\n";
            }
            break;
        case llvm::Instruction::Sub:
            if (is64(inst)) {
                if (llvm::isa<llvm::Constant>(inst.getOperand(0))) {
                    commands << "scoreboard players set arg1lo register "
                             << llvm::cast<llvm::ConstantInt>(inst.getOperand(0))->getValue().getLoBits(32).getLimitedValue()
                             << "\n";
                    commands << "scoreboard players set arg1hi register "
                             << llvm::cast<llvm::ConstantInt>(inst.getOperand(0))->getValue().getHiBits(32).getLimitedValue()
                             << "\n";
                } else {
                    commands << "execute store result score arg1lo register run data get llvm2mc::llvm2mc llvm2mc::llvm2mc "
                             << valueToString(inst.getOperand(0)) << "[0]\n";
                    commands << "execute store result score arg1hi register run data get llvm2mc::llvm2mc llvm2mc::llvm2mc "
                             << valueToString(inst.getOperand(0)) << "[1]\n";
                }
                if (llvm::isa<llvm::Constant>(inst.getOperand(1))) {
                    commands << "scoreboard players set arg2lot register "
                             << llvm::cast<llvm::ConstantInt>(inst.getOperand(1))->getValue().getLoBits(32).getLimitedValue()
                             << "\n";
                    commands << "scoreboard players set arg2hit register "
                             << llvm::cast<llvm::ConstantInt>(inst.getOperand(1))->getValue().getHiBits(32).getLimitedValue()
                             << "\n";
                } else {
                    commands << "execute store result score arg2lot register run data get llvm2mc::llvm2mc "
                             << valueToString(inst.getOperand(1)) << "[0]\n";
                    commands << "execute store result score arg2hit register run data get llvm2mc::llvm2mc "
                             << valueToString(inst.getOperand(1)) << "[1]\n";
                }
                commands << "scoreboard players set arg2lo register 0\n";
                commands << "scoreboard players set arg2hi register 0\n";
                commands << "scoreboard players set carry register 0\n";
                commands << "scoreboard players operation arg2lo register -= arg2lot register\n";
                commands << "scoreboard players operation arg2hi register -= arg2hit register\n";
                commands << "execute if score arg2lo register != 0 const run scoreboard players add arg2hi -1\n";
                commands << "scoreboard players operation arg1lo register += arg2lo register\n";
                commands << "execute if arg1lo register < arg2lo register run scoreboard players set carry 1\n";
                commands << "scoreboard players operation arg1hi register += arg2hi register\n";
                commands << "scoreboard players operation arg1hi register += carry register\n";
                commands << "data modify llvm2mc::llvm2mc " << valueToString(inst) << " set {}\n";
                commands << "execute store result storage llvm2mc::llvm2mc " << valueToString(inst)
                         << "[0] int 1 run scoreboard players get arg1lo register\n";
                commands << "execute store result storage llvm2mc::llvm2mc " << valueToString(inst)
                         << "[1] int 1 run scoreboard players get arg1hi register\n";
            } else {
                if (llvm::isa<llvm::Constant>(inst.getOperand(0))) {
                    commands << "scoreboard players set arg1 register "
                             << llvm::cast<llvm::ConstantInt>(inst.getOperand(0))->getValue().getLimitedValue()
                             << "\n";
                } else {
                    commands << "execute store result score arg1 register run data get llvm2mc::llvm2mc "
                             << valueToString(inst.getOperand(0)) << "\n";
                }
                if (llvm::isa<llvm::Constant>(inst.getOperand(1))) {
                    commands << "scoreboard players set arg2 register "
                             << llvm::cast<llvm::ConstantInt>(inst.getOperand(1))->getValue().getLimitedValue()
                             << "\n";
                } else {
                    commands << "execute store result score arg2 register run data get llvm2mc::llvm2mc "
                             << valueToString(inst.getOperand(1)) << "\n";
                }
                commands << "scoreboard players operation arg1 register -= arg2 register\n";
                std::string type;
                switch (inst.getType()->getIntegerBitWidth()) {
                    case 1:
                    case 8: type = "byte"; break;
                    case 16: type = "short"; break;
                    case 32: type = "int"; break;
                    default: throw std::runtime_error("Unknown operand type");
                }
                commands << "execute store result storage llvm2mc::llvm2mc " << valueToString(inst)
                         << " " << type << " 1 run scoreboard players get arg1 register\n";
            }
            break;
        default:
            throw std::runtime_error("Unknown opcode " + std::string(inst.getOpcodeName()));
    }
    return commands.str();
}

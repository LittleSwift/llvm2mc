#include "binaryOperator.h"

#include <iostream>
#include <sstream>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include "../predefined/data.h"
#include "../utils/valueConversion.h"

inline bool is64(const llvm::Instruction &inst) {
    return inst.getType()->getIntegerBitWidth() == 64;
}

std::string handleBinaryOperator(const llvm::Function &func, const llvm::BinaryOperator &inst) {
    std::ostringstream commands;
    switch (inst.getOpcode()) {
        case llvm::Instruction::Add: {
            DataField operand1(inst.getOperand(0));
            DataField operand2(inst.getOperand(1));
            DataField result(inst);
            if (is64(inst)) {
                ScoreField arg1lo("arg1lo", "register");
                ScoreField arg1hi("arg1hi", "register");
                ScoreField arg2lo("arg2lo", "register");
                ScoreField arg2hi("arg2hi", "register");
                ScoreField carry("carry", "register");
                if (llvm::isa<llvm::Constant>(inst.getOperand(0))) {
                    commands << (llvm::cast<llvm::ConstantInt>(inst.getOperand(0))->getValue().getLoBits(32).getLimitedValue() >> arg1lo);
                    commands << (llvm::cast<llvm::ConstantInt>(inst.getOperand(0))->getValue().getHiBits(32).getLimitedValue() >> arg1hi);
                } else {
                    commands << (operand1[0] >> arg1lo);
                    commands << (operand1[1] >> arg1hi);
                }
                if (llvm::isa<llvm::Constant>(inst.getOperand(1))) {
                    commands << (llvm::cast<llvm::ConstantInt>(inst.getOperand(1))->getValue().getLoBits(32).getLimitedValue() >> arg2lo);
                    commands << (llvm::cast<llvm::ConstantInt>(inst.getOperand(1))->getValue().getHiBits(32).getLimitedValue() >> arg2hi);
                } else {
                    commands << (operand2[0] >> arg2lo);
                    commands << (operand2[1] >> arg2hi);
                }
                commands << (0 >> carry);
                commands << (arg1lo + arg2lo);
                commands << "execute if score arg1lo register < arg2lo register run " << (1 >> carry);
                commands << (arg1hi + arg2hi);
                commands << (arg1hi + carry);
                commands << "data modify storage llvm2mc:llvm2mc " << valueToString(inst) << " set value [0,0]\n";
                commands << (arg1lo >> result[0]);
                commands << (arg1hi >> result[1]);
            } else {
                ScoreField arg1("arg1", "register");
                ScoreField arg2("arg2", "register");
                if (llvm::isa<llvm::Constant>(inst.getOperand(0))) {
                    commands << (llvm::cast<llvm::ConstantInt>(inst.getOperand(0))->getValue().getLimitedValue() >> arg1);
                } else {
                    commands << (operand1 >> arg1);
                }
                if (llvm::isa<llvm::Constant>(inst.getOperand(1))) {
                    commands << (llvm::cast<llvm::ConstantInt>(inst.getOperand(1))->getValue().getLimitedValue() >> arg2);
                } else {
                    commands << (operand2 >> arg2);
                }
                commands << (arg1 + arg2);
                std::string type;
                switch (inst.getType()->getIntegerBitWidth()) {
                    case 1:
                    case 8: type = "byte"; break;
                    case 16: type = "short"; break;
                    case 32: type = "int"; break;
                    default: throw std::runtime_error("Unknown operand type");
                }
                commands << "execute store result storage llvm2mc:llvm2mc " << valueToString(inst)
                         << " " << type << " 1 run scoreboard players get arg1 register\n";
            }
            break;
        }
        case llvm::Instruction::Sub: {
            DataField operand1(inst.getOperand(0));
            DataField operand2(inst.getOperand(1));
            DataField result(inst);
            if (is64(inst)) {
                ScoreField arg1lo("arg1lo", "register");
                ScoreField arg1hi("arg1hi", "register");
                ScoreField arg2lo("arg2lo", "register");
                ScoreField arg2hi("arg2hi", "register");
                ScoreField arg2lot("arg2lot", "register");
                ScoreField arg2hit("arg2hit", "register");
                ScoreField carry("carry", "register");
                if (llvm::isa<llvm::Constant>(inst.getOperand(0))) {
                    commands << (llvm::cast<llvm::ConstantInt>(inst.getOperand(0))->getValue().getLoBits(32).getLimitedValue() >> arg1lo);
                    commands << (llvm::cast<llvm::ConstantInt>(inst.getOperand(0))->getValue().getHiBits(32).getLimitedValue() >> arg1hi);
                } else {
                    commands << (operand1[0] >> arg1lo);
                    commands << (operand1[1] >> arg1hi);
                }
                if (llvm::isa<llvm::Constant>(inst.getOperand(1))) {
                    commands << (llvm::cast<llvm::ConstantInt>(inst.getOperand(1))->getValue().getLoBits(32).getLimitedValue() >> arg2lot);
                    commands << (llvm::cast<llvm::ConstantInt>(inst.getOperand(1))->getValue().getHiBits(32).getLimitedValue() >> arg2hit);
                } else {
                    commands << (operand2[0] >> arg2lot);
                    commands << (operand2[1] >> arg2hit);
                }
                commands << (0 >> arg2lo);
                commands << (0 >> arg2hi);
                commands << (0 >> carry);
                commands << (arg2lo - arg2lot);
                commands << (arg2hi - arg2hit);
                commands << "execute if score arg2lo register != 0 const run " << (arg2hi - 1);
                commands << (arg1lo + arg2lo);
                commands << "execute if score arg1lo register < arg2lo register run " << (1 >> carry);
                commands << (arg1hi + arg2hi);
                commands << (arg1hi + carry);
                commands << "data modify storage llvm2mc:llvm2mc " << valueToString(inst) << " set value [0,0]\n";
                commands << (arg1lo >> result[0]);
                commands << (arg1hi >> result[1]);
            } else {
                ScoreField arg1("arg1", "register");
                ScoreField arg2("arg2", "register");
                if (llvm::isa<llvm::Constant>(inst.getOperand(0))) {
                    commands << (llvm::cast<llvm::ConstantInt>(inst.getOperand(0))->getValue().getLimitedValue() >> arg1);
                } else {
                    commands << (operand1 >> arg1);
                }
                if (llvm::isa<llvm::Constant>(inst.getOperand(1))) {
                    commands << (llvm::cast<llvm::ConstantInt>(inst.getOperand(1))->getValue().getLimitedValue() >> arg2);
                } else {
                    commands << (operand2 >> arg2);
                }
                commands << (arg1 - arg2);
                std::string type;
                switch (inst.getType()->getIntegerBitWidth()) {
                    case 1:
                    case 8: type = "byte"; break;
                    case 16: type = "short"; break;
                    case 32: type = "int"; break;
                    default: throw std::runtime_error("Unknown operand type");
                }
                commands << "execute store result storage llvm2mc:llvm2mc " << valueToString(inst)
                         << " " << type << " 1 run scoreboard players get arg1 register\n";
            }
            break;
        }
        default:
            throw std::runtime_error("Unknown opcode " + std::string(inst.getOpcodeName()));
    }
    return commands.str();
}

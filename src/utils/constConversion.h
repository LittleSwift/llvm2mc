#pragma once

#include <string>
#include <sstream>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <cstring>

inline std::string constantToString(const llvm::Constant *C);

static std::string aggregateToString(const llvm::Constant *C) {
    std::ostringstream oss;
    oss << "[";
    const unsigned numOps = C->getNumOperands();
    for (unsigned i = 0; i < numOps; ++i) {
        if (i > 0) oss << ",";
        oss << constantToString(llvm::cast<const llvm::Constant>(C->getOperand(i)));
    }
    oss << "]";
    return oss.str();
}

inline std::string i32ToString(uint32_t val) {
    return std::to_string(static_cast<int32_t>(val)) + "i";
}

inline std::string constantToString(const llvm::Constant *C) {
    if (!C) {
        return "0i";
    }

    if (llvm::isa<llvm::ConstantPointerNull>(C) || llvm::isa<llvm::UndefValue>(C)) {
        return "0i";
    }

    if (auto *CI = llvm::dyn_cast<llvm::ConstantInt>(C)) {
        uint64_t val = CI->getZExtValue();
        unsigned bw = CI->getType()->getIntegerBitWidth();

        if (bw == 64) {
            auto low  = static_cast<uint32_t>(val & 0xFFFFFFFF);
            auto high = static_cast<uint32_t>((val >> 32) & 0xFFFFFFFF);
            std::ostringstream oss;
            oss << "[" << i32ToString(low) << "," << i32ToString(high) << "]";
            return oss.str();
        }
        std::ostringstream oss;
        oss << static_cast<int64_t>(val);
        switch (bw) {
            case 1:
            case 8:  oss << "b"; break;
            case 16: oss << "s"; break;
            case 32: oss << "i"; break;
            default: throw std::runtime_error("Unsupported integer width");
        }
        return oss.str();
    }

    if (auto *CFP = llvm::dyn_cast<llvm::ConstantFP>(C)) {
        if (CFP->getType()->isFloatTy()) {
            float val = CFP->getValueAPF().convertToFloat();
            uint32_t intVal;
            std::memcpy(&intVal, &val, sizeof(float));
            return i32ToString(intVal);
        }
        if (CFP->getType()->isDoubleTy()) {
            double val = CFP->getValueAPF().convertToDouble();
            uint64_t bits;
            std::memcpy(&bits, &val, sizeof(double));
            auto low  = static_cast<uint32_t>(bits & 0xFFFFFFFF);
            auto high = static_cast<uint32_t>((bits >> 32) & 0xFFFFFFFF);
            std::ostringstream oss;
            oss << "[" << i32ToString(low) << "," << i32ToString(high) << "]";
            return oss.str();
        }
        throw std::runtime_error("Unsupported FP type");
    }

    if (llvm::isa<llvm::ConstantStruct>(C) ||
        llvm::isa<llvm::ConstantArray>(C) ||
        llvm::isa<llvm::ConstantVector>(C) ||
        llvm::isa<llvm::ConstantDataSequential>(C)) {
        return aggregateToString(C);
    }

    throw std::runtime_error("Unexpected type of constant");
}

inline std::string constantToString(const llvm::Constant& C) {
    return aggregateToString(&C);
}
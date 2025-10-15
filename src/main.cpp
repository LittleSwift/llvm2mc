#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Constants.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/BasicBlock.h>

#include <iostream>
#include <fstream>

#include "const.h"
#include "prepare.h"
#include "utils/stringUtils.h"
#include "instructions/alloca.h"
#include "instructions/binaryOperator.h"
#include "instructions/br.h"
#include "instructions/load.h"
#include "instructions/ret.h"
#include "instructions/store.h"
#include "instructions/trunc.h"
#include "predefined/data.h"
#include "utils/misc.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.bc|input.ll>\n";
        return 1;
    }

    std::string filePath = argv[1];
    llvm::LLVMContext context;
    std::unique_ptr<llvm::Module> module;

    if (filePath.size() >= 3 && filePath.substr(filePath.size() - 3) == ".ll") {
        llvm::SMDiagnostic err;
        module = llvm::parseIRFile(filePath, err, context);
        if (!module) {
            std::cerr << "Error: Failed to parse LLVM IR file " << filePath << "\n";
            err.print(argv[0], llvm::errs());
            return 1;
        }
    } else if (filePath.size() >= 3 && filePath.substr(filePath.size() - 3) == ".bc") {
        auto bufferOrErr = llvm::MemoryBuffer::getFile(filePath);
        if (!bufferOrErr) {
            std::cerr << "Error: Failed to open Bitcode file " << filePath << "\n";
            return 1;
        }
        auto buffer = std::move(bufferOrErr.get());

        auto moduleOrErr = llvm::parseBitcodeFile(buffer->getMemBufferRef(), context);
        if (!moduleOrErr) {
            std::cerr << "Error: Failed to parse Bitcode file " << filePath << "\n";
            return 1;
        }
        module = std::move(moduleOrErr.get());
    } else {
        std::cerr << "Error: Unsupported file type. Use .bc or .ll\n";
        return 1;
    }
    try {
        if (std::filesystem::exists("output") && std::filesystem::is_directory("output")) {
            for (const auto& entry : std::filesystem::directory_iterator("output")) {
                std::filesystem::remove_all(entry);
            }
        }
    } catch ([[maybe_unused]] const std::filesystem::filesystem_error& e) {}
    std::filesystem::create_directories("output");
    prepare();
    for (auto &func : *module) {
        std::filesystem::create_directories("output/" + standardizeName(func.getName().str()));
        std::ofstream funcFile("output/"
            + standardizeName(func.getName().str()) + ".mcfunction");
        funcFile << "execute store result storage llvm2mc:llvm2mc stack[-1].stackTop int 1 "
                    "run scoreboard players get stackTop register\n";
        funcFile << "function llvm2mc:" << standardizeName(func.getName().str()) << "/0" << "\n";
        funcFile << "execute store result score stackTop register run "
                    "data get storage llvm2mc:llvm2mc stack[-1].stackTop\n";
        for (auto &bb : func) {
            std::ofstream blockFile("output/"
                + standardizeName(func.getName().str()) + "/"
                + std::to_string(bb.getNumber()) + ".mcfunction");
            for (auto &inst : bb) {
                if (debug) {
                    blockFile << R"(tellraw @a {"type":"text", "color":"yellow", "text":")" << escapeQuotes(instructionToString(&inst)) << "\"}\n";
                }
                if (auto* cInst = llvm::dyn_cast<llvm::AllocaInst>(&inst)) {
                    blockFile << handleAlloca(func, *cInst);
                }
                if (auto* cInst = llvm::dyn_cast<llvm::BranchInst>(&inst)) {
                    blockFile << handleBr(func, *cInst);
                }
                if (auto* cInst = llvm::dyn_cast<llvm::BinaryOperator>(&inst)) {
                    blockFile << handleBinaryOperator(func, *cInst);
                }
                if (auto* cInst = llvm::dyn_cast<llvm::LoadInst>(&inst)) {
                    blockFile << handleLoad(func, *cInst);
                }
                if (auto* cInst = llvm::dyn_cast<llvm::ReturnInst>(&inst)) {
                    blockFile << handleRet(func, *cInst);
                }
                if (auto* cInst = llvm::dyn_cast<llvm::StoreInst>(&inst)) {
                    blockFile << handleStore(func, *cInst);
                }
                if (auto* cInst = llvm::dyn_cast<llvm::TruncInst>(&inst)) {
                    blockFile << handleTrunc(func, *cInst);
                }
                if (debug && inst.getNameOrAsOperand() != "<badref>") {
                    blockFile << R"(tellraw @a {"type":"text", "color":"yellow", "text":")"
                              << inst.getNameOrAsOperand() << R"(=", "extra":[{"storage":")" << projectNamespace
                              << R"(", "nbt":")" << DataField(inst) << "\"}]}\n";
                }
            }
            blockFile.close();
        }
    }

    return 0;
}

#pragma once
#include <array>

constexpr int kMemorySize = 256 * 1024;
constexpr int kStackSize = 128 * 1024;
const std::string projectNamespace = "llvm2mc:llvm2mc";
constexpr bool debug = true;

constexpr std::array kDefinedConsts = {0, 256};
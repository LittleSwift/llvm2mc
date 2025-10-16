# llvm2mc
![Instruction Coverage](https://img.shields.io/badge/Instruction%20Coverage-25.8%25-yellow)
![Command Coverage](https://img.shields.io/badge/Command%20Coverage-0%25-red)

**llvm2mc** is a project that compiles LLVM IR into a Minecraft datapack. It translates LLVM instructions into Minecraft functions, enabling you to run LLVM-based programs inside Minecraft.

## Development Status
We are currently working on supporting Clang IR subset of LLVM IR, which is much easier to implement in Minecraft.
## Supported Instructions

<details>
<summary>Terminator Instructions</summary>

- [x] `ret` Instruction
- [x] `br` Instruction
- [ ] `switch` Instruction
- [ ] `indirectbr` Instruction
- [ ] `invoke` Instruction
- [ ] `callbr` Instruction
- [ ] `resume` Instruction
- [x] `catchswitch` Instruction (won't implement)
- [x] `catchret` Instruction (won't implement)
- [x] `cleanupret` Instruction (won't implement)
- [x] `unreachable` Instruction (won't implement)

</details>

<details>
<summary>Unary Operations</summary>

- [ ] `fneg` Instruction

</details>

<details>
<summary>Binary Operations</summary>

- [x] `add` Instruction
- [ ] `fadd` Instruction
- [x] `sub` Instruction
- [ ] `fsub` Instruction
- [ ] `mul` Instruction
- [ ] `fmul` Instruction
- [ ] `udiv` Instruction
- [ ] `sdiv` Instruction
- [ ] `fdiv` Instruction
- [ ] `urem` Instruction
- [ ] `srem` Instruction
- [ ] `frem` Instruction

</details>

<details>
<summary>Bitwise Binary Operations</summary>

- [ ] `shl` Instruction
- [ ] `lshr` Instruction
- [ ] `ashr` Instruction
- [ ] `and` Instruction
- [ ] `or` Instruction
- [ ] `xor` Instruction

</details>

<details>
<summary>Vector Operations</summary>

- [ ] `extractelement` Instruction
- [ ] `insertelement` Instruction
- [ ] `shufflevector` Instruction

</details>

<details>
<summary>Aggregate Operations</summary>

- [ ] `extractvalue` Instruction
- [ ] `insertvalue` Instruction

</details>

<details>
<summary>Memory Access and Addressing Operations</summary>

- [x] `alloca` Instruction
- [x] `load` Instruction (Clang IR subset)
- [x] `store` Instruction (Clang IR subset)
- [x] `fence` Instruction (won't implement)
- [ ] `cmpxchg` Instruction
- [ ] `atomicrmw` Instruction
- [ ] `getelementptr` Instruction

</details>

<details>
<summary>Conversion Operations</summary>

- [x] `trunc .. to` Instruction
- [x] `zext .. to` Instruction
- [ ] `sext .. to` Instruction
- [ ] `fptrunc .. to` Instruction
- [ ] `fpext .. to` Instruction
- [ ] `fptoui .. to` Instruction
- [ ] `fptosi .. to` Instruction
- [ ] `uitofp .. to` Instruction
- [ ] `sitofp .. to` Instruction
- [ ] `ptrtoint .. to` Instruction
- [ ] `ptrtoaddr .. to` Instruction
- [ ] `inttoptr .. to` Instruction
- [ ] `bitcast .. to` Instruction
- [ ] `addrspacecast .. to` Instruction

</details>

<details>
<summary>Other Operations</summary>

- [ ] `icmp` Instruction
- [ ] `fcmp` Instruction
- [ ] `phi` Instruction
- [ ] `select` Instruction
- [ ] `freeze` Instruction
- [ ] `call` Instruction
- [ ] `va_arg` Instruction
- [x] `landingpad` Instruction (won't implement)
- [x] `catchpad` Instruction (won't implement)
- [x] `cleanuppad` Instruction (won't implement)

</details>

## Tips
- Please note that llvm2mc only supports LLVM libc++ at 32 bit. This means you should not compile any code using MSVC STL or gcc libstdc++.
- All Minecraft native functions can be imported from `llvm2mc/mcfunc.h`.
- We suggest using `clang -c -emit-llvm -Xclang -disable-llvm-passes -O0 -target i386-pc-linux-gnu -std=c++20 -fno-exceptions -fno-rtti foo.cpp -o foo.bc` to compile your code when you are using c++.
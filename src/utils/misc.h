#pragma once
#include "../const.h"

constexpr bool defined(const int value) {
    return std::ranges::any_of(
        kDefinedConsts,
        [value](const int x) { return x == value; }
    );
}

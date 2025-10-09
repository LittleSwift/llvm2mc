#pragma once
#include "../const.h"

constexpr bool defined(const int value) {
    for (int x : kDefinedConsts) {
        if (x == value) {
            return true;
        }
    }
    return false;
}

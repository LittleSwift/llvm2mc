#pragma once
#include <string>
#include "selector.h"

namespace minecraft {
    enum class AdvancementMode { Everything, Only, OnlyCriterion, From, Until, Through };

    template<AdvancementMode Mode>
    bool advancement(selector::Selector& p,
                     bool grant);
    template<>
    bool advancement<AdvancementMode::Everything>(selector::Selector& p,
                     bool grant); // TODO
    void say(std::string s) = delete;
}
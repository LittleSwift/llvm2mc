#pragma once
#include <map>
#include <optional>
#include <string>

namespace minecraft::selector {
    enum SelectorType: uint8_t { p, r, a, e, s, n };
    enum Sort: uint8_t { Nearest , Furthest, Random, Arbitrary };
    template<typename T>
    class Exclude {
    public:
        T value;
        bool isExcluded;
        Exclude(T value) : value(value), isExcluded(false) {} // NOLINT(google-explicit-constructor)
        Exclude(T value, const bool isExcluded) : value(value), isExcluded(isExcluded) {}
        static Exclude exclude(T value) {
            return Exclude(value, false);
        }
    };
    class IntRange {
    public:
        int minValue;
        int maxValue;
        bool minSet;
        bool maxSet;

        IntRange(const int n) // NOLINT(google-explicit-constructor)
            : minValue(n), maxValue(n), minSet(true), maxSet(true) {}

        IntRange(const int n, const bool toInfinity)
            : minValue(n), maxValue(0), minSet(true), maxSet(false) {
            (void) toInfinity;
        }

        IntRange(const bool fromNegInfinity, const int m)
            : minValue(0), maxValue(m), minSet(false), maxSet(true) {
            (void) fromNegInfinity;
        }

        IntRange(const int n, const int m)
            : minValue(n), maxValue(m), minSet(true), maxSet(true) {}
    };

    class FloatRange {
        public:
        float minValue;
        float maxValue;
        bool minSet;
        bool maxSet;

        FloatRange(const float n) // NOLINT(google-explicit-constructor)
            : minValue(n), maxValue(n), minSet(true), maxSet(true) {}

        FloatRange(const float n, const bool toInfinity)
            : minValue(n), maxValue(0), minSet(true), maxSet(false) {
            (void) toInfinity;
        }

        FloatRange(const bool fromNegInfinity, const float m)
            : minValue(0), maxValue(m), minSet(false), maxSet(true) {
            (void) fromNegInfinity;
        }

        FloatRange(const float n, const float m)
            : minValue(n), maxValue(m), minSet(true), maxSet(true) {}
    };

    class DoubleRange {
    public:
        double minValue;
        double maxValue;
        bool minSet;
        bool maxSet;

        DoubleRange(const double n) // NOLINT(google-explicit-constructor)
            : minValue(n), maxValue(n), minSet(true), maxSet(true) {}

        DoubleRange(const double n, const bool toInfinity)
            : minValue(n), maxValue(0), minSet(true), maxSet(false) {
            (void) toInfinity;
        }

        DoubleRange(const bool fromNegInfinity, const double m)
            : minValue(0), maxValue(m), minSet(false), maxSet(true) {
            (void) fromNegInfinity;
        }

        DoubleRange(const double n, const double m)
            : minValue(n), maxValue(m), minSet(true), maxSet(true) {}
    };

    class Selector {
    public:
        SelectorType type;
        std::optional<Exclude<std::string>> name;
        std::optional<DoubleRange> distance;
        std::optional<IntRange> level;
        std::optional<double> x;
        std::optional<double> y;
        std::optional<double> z;
        std::optional<double> dx;
        std::optional<double> dy;
        std::optional<double> dz;
        std::optional<FloatRange> x_rotation;
        std::optional<FloatRange> y_rotation;
        std::optional<int> limit;
        std::optional<Sort> sort;
        std::optional<Exclude<std::string>> gamemode;
        std::optional<Exclude<std::string>> team;
        std::optional<Exclude<std::string>> tag;
        std::optional<Exclude<std::string>> nbt; //TODO nbt
        std::optional<std::map<std::string, IntRange>> scores;
        std::optional<std::map<std::string, std::variant<bool, std::map<std::string, bool>>>> advancements;
        std::optional<Exclude<std::string>> predicate;

        explicit Selector(const SelectorType type) : type(type) {}
    };
}
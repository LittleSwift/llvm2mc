#pragma once
#include <string>
#include <llvm/IR/Value.h>

class ScoreField ;

class DataField {
    std::string path;
public:
    explicit DataField(std::string path);
    explicit DataField(const llvm::Value& value);
    explicit DataField(const llvm::Value* value);

    std::string operator>>(const DataField& field) const;
    std::string operator>>(const ScoreField &scoreField) const;
    friend std::string operator>>(const std::string& value, const DataField& field);
    friend std::string operator>>(const llvm::Constant& value, const DataField& field);
    DataField operator[](const int &arg) const;

    friend class ScoreField;
};

class ScoreField {
    std::string name;
    std::string board;
public:
    explicit ScoreField(std::string name, std::string board);

    std::string operator>>(const DataField& field) const;
    friend std::string operator>>(int value, const ScoreField& field);
    std::string operator+(int arg) const;
    std::string operator-(int arg) const;
    std::string operator*(int arg) const;
    std::string operator/(int arg) const;
    std::string operator%(int arg) const;

    std::string operator+(const ScoreField& field) const;
    std::string operator-(const ScoreField& field) const;
    std::string operator*(const ScoreField& field) const;
    std::string operator/(const ScoreField& field) const;
    std::string operator%(const ScoreField& field) const;
    friend class DataField;
};

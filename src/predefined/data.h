#pragma once
#include <string>
#include <llvm/IR/Value.h>

#include "data.h"
#include "../const.h"
#include "../utils/valueConversion.h"

class ScoreField ;

class DataField {
private:
    std::string path;
public:
    explicit DataField(const std::string& path) : path(path) {}
    explicit DataField(const llvm::Value& value) {
        path = valueToString(value);
    }
    explicit DataField(const llvm::Value* value) {
        path = valueToString(value);
    }
    std::string operator>>(const DataField& field) const {
        return "data modify storage " + projectNamespace + " " + field.path
                + " set from " + projectNamespace + " " + path + "\n";
    }

    std::string operator>>(const ScoreField &scoreField) const;

    DataField operator[](const int &arg) const {
        DataField result(*this);
        result.path += "[" + std::to_string(arg) + "]";
        return result;
    }

    friend class ScoreField;
};

class ScoreField {
private:
    std::string name;
    std::string board;
public:
    explicit ScoreField(const std::string& name, const std::string& board) : name(name), board(board) {}

    std::string operator>>(const DataField& field) const {
        return "execute store result storage " + projectNamespace + " " + field.path
                + " int 1 run scoreboard players get " + name + " " + board + "\n";
    }

    friend std::string operator>>(const int value, const ScoreField& field) {
        return "scoreboard players set " + field.name + " " + field.board + " " + std::to_string(value) + "\n";
    }

    std::string operator+(const int arg) const {
        return "scoreboard players add " + name + " " + board + " " + std::to_string(arg) + "\n";
    }
    std::string operator-(const int arg) const {
        return "scoreboard players remove " + name + " " + board + " " + std::to_string(arg) + "\n";
    }
    std::string operator*(const int arg) const {
        return "scoreboard players operation " + name + " " + board + " *= " + std::to_string(arg) + " const\n";
    }
    std::string operator/(const int arg) const {
        return "scoreboard players operation " + name + " " + board + " /= " + std::to_string(arg) + " const\n";
    }
    std::string operator%(const int arg) const {
        return "scoreboard players operation " + name + " " + board + " %= " + std::to_string(arg) + " const\n";
    }

    std::string operator+(const ScoreField& field) const {
        return "scoreboard players operation " + name + " " + board + " += " + field.name + " " + field.board + "\n";
    }
    std::string operator-(const ScoreField& field) const {
        return "scoreboard players operation " + name + " " + board + " -= " + field.name + " " + field.board + "\n";
    }
    std::string operator*(const ScoreField& field) const {
        return "scoreboard players operation " + name + " " + board + " *= " + field.name + " " + field.board + "\n";
    }
    std::string operator/(const ScoreField& field) const {
        return "scoreboard players operation " + name + " " + board + " /= " + field.name + " " + field.board + "\n";
    }
    std::string operator%(const ScoreField& field) const {
        return "scoreboard players operation " + name + " " + board + " %= " + field.name + " " + field.board + "\n";
    }
    friend class DataField;
};


inline std::string DataField::operator>>(const ScoreField& scoreField) const {
    return "execute store result score " + scoreField.name + " " + scoreField.board
            + " run data get " + projectNamespace + " " + path + "\n";
}

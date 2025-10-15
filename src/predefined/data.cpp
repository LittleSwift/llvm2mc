#include "data.h"
#include <string>
#include <utility>

#include "../const.h"
#include "../utils/constConversion.h"
#include "../utils/misc.h"
#include "../utils/valueConversion.h"

DataField::DataField(std::string path) : path(std::move(path)) {}
DataField::DataField(const llvm::Value& value) : path(valueToString(value)) {}
DataField::DataField(const llvm::Value* value) : path(valueToString(value)) {}

std::string DataField::operator>>(const DataField& field) const {
    return "data modify storage " + projectNamespace + " " + field.path
           + " set from storage " + projectNamespace + " " + path + "\n";
}

std::string DataField::operator>>(const ScoreField& scoreField) const {
    return "execute store result score " + scoreField.name + " " + scoreField.board
           + " run data get storage " + projectNamespace + " " + path + "\n";
}

DataField DataField::operator[](const int &arg) const {
    DataField result(*this);
    result.path += "[" + std::to_string(arg) + "]";
    return result;
}

std::string operator>>(const std::string& value, const DataField& field) {
    return "data modify storage " + projectNamespace + " " + field.path
           + " set value " + value + "\n";
}

std::string operator>>(const llvm::Constant& value, const DataField& field) {
    return "data modify storage " + projectNamespace + " " + field.path
           + " set value " + constantToString(value) + "\n";
}

ScoreField::ScoreField(std::string name, std::string board) : name(std::move(name)), board(std::move(board)) {}

std::string ScoreField::operator>>(const DataField& field) const {
    return "execute store result storage " + projectNamespace + " " + field.path
           + " int 1 run scoreboard players get " + name + " " + board + "\n";
}

std::string operator>>(const int value, const ScoreField& field) {
    return "scoreboard players set " + field.name + " " + field.board + " " + std::to_string(value) + "\n";
}

std::string ScoreField::operator+(const int arg) const {
    return "scoreboard players add " + name + " " + board + " " + std::to_string(arg) + "\n";
}

std::string ScoreField::operator-(const int arg) const {
    return "scoreboard players remove " + name + " " + board + " " + std::to_string(arg) + "\n";
}

std::string ScoreField::operator*(const int arg) const {
    assert(defined(arg));
    return "scoreboard players operation " + name + " " + board + " *= " + std::to_string(arg) + " const\n";
}

std::string ScoreField::operator/(const int arg) const {
    assert(defined(arg));
    return "scoreboard players operation " + name + " " + board + " /= " + std::to_string(arg) + " const\n";
}

std::string ScoreField::operator%(const int arg) const {
    assert(defined(arg));
    return "scoreboard players operation " + name + " " + board + " %= " + std::to_string(arg) + " const\n";
}

std::string ScoreField::operator+(const ScoreField& field) const {
    return "scoreboard players operation " + name + " " + board + " += " + field.name + " " + field.board + "\n";
}

std::string ScoreField::operator-(const ScoreField& field) const {
    return "scoreboard players operation " + name + " " + board + " -= " + field.name + " " + field.board + "\n";
}

std::string ScoreField::operator*(const ScoreField& field) const {
    return "scoreboard players operation " + name + " " + board + " *= " + field.name + " " + field.board + "\n";
}

std::string ScoreField::operator/(const ScoreField& field) const {
    return "scoreboard players operation " + name + " " + board + " /= " + field.name + " " + field.board + "\n";
}

std::string ScoreField::operator%(const ScoreField& field) const {
    return "scoreboard players operation " + name + " " + board + " %= " + field.name + " " + field.board + "\n";
}
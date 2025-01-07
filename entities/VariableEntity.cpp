#include "VariableEntity.h"

std::string VariableEntity::toString() {
    string x = (multiplier == 1 ? "" : StringUtils::toString(multiplier)) + symbol;
    if(power != 1) {
        x += "^" + StringUtils::toString(power);
    }
    return x;
}

VariableEntity::VariableEntity(double multiplier) : multiplier(multiplier){}

VariableEntity::VariableEntity(double multiplier, double power) : multiplier(multiplier), power(power) {}

#define _USE_MATH_DEFINES
#include <cmath>
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

VariableEntity::VariableEntity(string symbol, double multiplier, double power) : symbol(symbol), multiplier(multiplier), power(power) {}

BaseEntity* VariableEntity::evaluateValue(double x) {
    BaseEntity * result;
    if(symbol == "x") {
        result = evaluate(x);
    } else if(symbol == "e") {
        result = evaluate(M_E);
    } else if(symbol == "pi") {
        result = evaluate(M_PI);
    } else {
        result = this;
    }
    return result;
}

ScalarEntity* VariableEntity::evaluate(double x) {
    return new ScalarEntity(multiplier * pow(x, power));
}

BaseEntity *VariableEntity::evaluateFunction() {
    if(multiplier == 0)
        return new ScalarEntity(0);
    if(power == 0)
        return new ScalarEntity(1);
    return this;
}


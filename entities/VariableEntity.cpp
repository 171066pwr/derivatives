#define _USE_MATH_DEFINES
#include <cmath>
#include "VariableEntity.h"

string VariableEntity::SUBSTITUTE_SYMBOL = "x";
map<string, double> VariableEntity::constants {std::make_pair("e", M_E), std::make_pair("pi", M_PI)};

void VariableEntity::changeSubstituteSymbol(string symbol) {
    SUBSTITUTE_SYMBOL = symbol;
}

VariableEntity::VariableEntity(double multiplier) : BaseEntity(multiplier) {
    updateAndGetIsFunction();
}

VariableEntity::VariableEntity(string symbol = SUBSTITUTE_SYMBOL, double multiplier): BaseEntity(multiplier), symbol(symbol) {
    updateAndGetIsFunction();
}

BaseEntity *VariableEntity::copy() {
    return new VariableEntity(symbol, multiplier);
}

bool VariableEntity::equals(const BaseEntity *entity) {
    const VariableEntity* e = dynamic_cast<const VariableEntity*>(entity);
    if(e == nullptr)
        return false;
    else
        return this->symbol == e->symbol && NumberUtils::doubleEquals(this->multiplier, e->multiplier);
}

std::string VariableEntity::toString() {
    return (NumberUtils::doubleEquals(multiplier, 1.0) ?
            "" :  NumberUtils::doubleEquals(multiplier, -1.0) ?
                  "-" : NumberUtils::toString(multiplier)) + symbol;
}

BaseEntity* VariableEntity::evaluateValue(double x) {
    BaseEntity * result;
    if(symbol == SUBSTITUTE_SYMBOL) {
        result = evaluate(x);
    } else if(constants.find(symbol) != constants.end()) {
        result = evaluate(constants[symbol]);
    } else {
        result = evaluateFunction();
    }
    return result;
}

ScalarEntity* VariableEntity::evaluate(double x) {
    return new ScalarEntity(multiplier * x);
}

BaseEntity* VariableEntity::evaluateFunction() {
    if(NumberUtils::doubleEquals(multiplier, 0))
        return new ScalarEntity(0);
    return this;
}

bool VariableEntity::updateAndGetIsFunction() {
    return isFunction = (symbol == SUBSTITUTE_SYMBOL);
}


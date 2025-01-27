#define _USE_MATH_DEFINES
#include <cmath>
#include "Variable.h"

string Variable::SUBSTITUTE_SYMBOL = "x";
map<string, double> Variable::constants {std::make_pair("e", M_E), std::make_pair("pi", M_PI)};

void Variable::changeSubstituteSymbol(string symbol) {
    SUBSTITUTE_SYMBOL = symbol;
}

Variable::Variable(double multiplier) : BaseEntity(multiplier) {
    updateAndGetIsFunction();
}

Variable::Variable(string symbol = SUBSTITUTE_SYMBOL, double multiplier): BaseEntity(multiplier), symbol(symbol) {
    updateAndGetIsFunction();
}

BaseEntity *Variable::copy() {
    return new Variable(symbol, multiplier);
}

bool Variable::equals(const BaseEntity *entity) {
    return contentsEquals(entity) && NumberUtils::doubleEquals(this->multiplier, entity->getMultiplier());
}

bool Variable::contentsEquals(const BaseEntity *entity) {
    const Variable *e = dynamic_cast<const Variable *>(entity);
    if(e == nullptr)
        return false;
    else
        return this->symbol == e->symbol;
}

std::string Variable::toString() {
    return (NumberUtils::doubleEquals(multiplier, 1.0) ?
            "" :  NumberUtils::doubleEquals(multiplier, -1.0) ?
                  "-" : NumberUtils::toString(multiplier)) + symbol;
}

BaseEntity *Variable::evaluateValue(double x) {
    if (isZero())
        return Scalar::zero();
    BaseEntity * result;
    if(symbol == SUBSTITUTE_SYMBOL) {
        result = evaluate(x);
    } else if(constants.find(symbol) != constants.end()) {
        result = evaluate(constants[symbol]);
    } else {
        result = this->copy();
    }
    return result;
}

Scalar *Variable::evaluate(double x) {
    return new Scalar(multiplier * x);
}

bool Variable::updateAndGetIsFunction() {
    return isFunction = (symbol == SUBSTITUTE_SYMBOL);
}

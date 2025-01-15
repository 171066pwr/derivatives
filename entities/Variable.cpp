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
    const Variable *e = dynamic_cast<const Variable *>(entity);
    if(e == nullptr)
        return false;
    else
        return this->symbol == e->symbol && NumberUtils::doubleEquals(this->multiplier, e->multiplier);
}

std::string Variable::toString() {
    return (NumberUtils::doubleEquals(multiplier, 1.0) ?
            "" :  NumberUtils::doubleEquals(multiplier, -1.0) ?
                  "-" : NumberUtils::toString(multiplier)) + symbol;
}

BaseEntity *Variable::evaluateValue(double x) {
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

Scalar *Variable::evaluate(double x) {
    return new Scalar(multiplier * x);
}

BaseEntity *Variable::evaluateFunction() {
    if(NumberUtils::doubleEquals(multiplier, 0))
        return new Scalar(0);
    return this;
}

bool Variable::updateAndGetIsFunction() {
    return isFunction = (symbol == SUBSTITUTE_SYMBOL);
}


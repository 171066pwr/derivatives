#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>
#include "Variable.h"

map<string, double> Variable::constants {std::make_pair("e", M_E), std::make_pair("pi", M_PI)};

vector<string> Variable::getConstants() {
    vector<string> result;
    for(auto & constant : constants)
        result.push_back(constant.first);
    return result;
}

Variable::Variable(double multiplier) : BaseEntity(multiplier) {}

Variable::Variable(string symbol, double multiplier): BaseEntity(multiplier), symbol(std::move(symbol)) {}

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

BaseEntity *Variable::evaluateValue(double x, string variable) {
    if (isZero())
        return Scalar::zero();
    BaseEntity * result;
    if(symbol == variable) {
        result = evaluate(x);
    } else if(constants.find(symbol) != constants.end()) {
        result = evaluate(constants[symbol]);
    } else {
        result = this->copy();
    }
    return result;
}

BaseEntity * Variable::evaluateDerivative(string variable) {
    if (isFunction(variable))
        return new Scalar(multiplier);
    return Scalar::zero();
}

Scalar *Variable::evaluate(double x) {
    return new Scalar(multiplier * x);
}

bool Variable::isFunction(string symbol) {
    return this->symbol == symbol;
}

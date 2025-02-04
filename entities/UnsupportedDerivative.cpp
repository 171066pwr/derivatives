#include "UnsupportedDerivative.h"
#include "../utils/Logger.h"

BaseEntity * UnsupportedDerivative::copy() {
    return new UnsupportedDerivative(getBase()->copy(), multiplier);
}

bool UnsupportedDerivative::equals(const BaseEntity *entity) {
    return typeEquals<UnsupportedDerivative>(entity) && BaseEntity::equals(entity);
}

bool UnsupportedDerivative::equalsExceptMultiplier(const BaseEntity *entity) {
return contentsEquals(entity);
}

bool UnsupportedDerivative::contentsEquals(const BaseEntity *entity) {
    return typeEquals<UnsupportedDerivative>(entity) && BaseEntity::contentsEquals(entity);
}

std::string UnsupportedDerivative::toString() {
    if (elements.empty()) {
        return "0";
    }
    string result = NumberUtils::doubleEquals(multiplier, 1.0) ?
                     "" : NumberUtils::doubleEquals(multiplier, -1.0) ?
                           "-": NumberUtils::toString(multiplier) + "*";
    result += "(" + elements[0]->toString() + ")" + "' ";
    return result;
}

bool UnsupportedDerivative::addElement(BaseEntity *element) {
    if(elements.size() > 1) {
        Logger::log("This UnsupportedDerivative already has base");
        return false;
    }
    return BaseEntity::addElement(element);
}

BaseEntity * UnsupportedDerivative::evaluateFunction() {
    return copy();
}

BaseEntity * UnsupportedDerivative::evaluateValue(double x, string variable) {
    return copy();
}

BaseEntity * UnsupportedDerivative::getBase() {
    if(!elements.empty())
        return elements[0];
    return nullptr;
}

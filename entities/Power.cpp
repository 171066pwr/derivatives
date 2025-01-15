#include "Power.h"
#include "../utils/NumberUtils.h"

BaseEntity *Power::copy() {
    BaseEntity* copy = new Power(power->copy(), multiplier);
    for(auto element: elements){
        copy->addElement(element->copy());
    }
    return copy;
}

bool Power::equals(const BaseEntity *entity) {
    const Power *e = dynamic_cast<const Power *>(entity);
    if(e == nullptr)
        return false;
    else
        return (*this->power == *e->power) && BaseEntity::equals(e);
}

bool Power::contentsEquals(const BaseEntity *entity) {
    return typeEquals<Power>(entity) && BaseEntity::contentsEquals(entity);
}

std::string Power::toString() {
    if (elements.size() == 0) {
        return "0";
    }
    string result = NumberUtils::doubleEquals(multiplier, 1.0) ?
                     "" : NumberUtils::doubleEquals(multiplier, -1.0) ?
                           "-": NumberUtils::toString(multiplier) + "*";
    result += elements[0]->toString() + "^";
    result += power->toString();
    return result;
}

bool Power::addElement(BaseEntity *element) {
    return BaseEntity::addElement(element);
}

BaseEntity *Power::evaluateFunction() {
    return BaseEntity::evaluateFunction();
}

BaseEntity *Power::evaluateValue(double x) {
    return BaseEntity::evaluateValue(x);
}

bool Power::updateAndGetIsFunction() {
    return BaseEntity::updateAndGetIsFunction();
}

bool Power::addPower(Power power) {
    return false;
}

bool Power::multiplyPower(Power power) {
    return false;
}

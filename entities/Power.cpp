#include "Power.h"

Power::Power(double multiplier, double power): BaseEntity(multiplier), power(power) {}

BaseEntity *Power::copy() {
    return BaseEntity::copy();
}

bool Power::equals(const BaseEntity *entity) {
    return BaseEntity::equals(entity);
}

bool Power::contentsEquals(const BaseEntity *entity) {
    return BaseEntity::contentsEquals(entity);
}

std::string Power::toString() {
    return BaseEntity::toString();
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

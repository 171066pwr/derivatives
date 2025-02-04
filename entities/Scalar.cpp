#include "Scalar.h"

#include "../utils/Logger.h"

Scalar::Scalar(double multiplier) : BaseEntity(multiplier) {}

BaseEntity *Scalar::copy() {
    return new Scalar(multiplier);
}

bool Scalar::equals(const BaseEntity *entity) {
    return typeEquals<Scalar>(entity) && BaseEntity::equals(entity);
}

bool Scalar::contentsEquals(const BaseEntity *entity) {
    return typeEquals<Scalar>(entity);
}

std::string Scalar::toString() {
    return NumberUtils::toString(multiplier);
}

BaseEntity *Scalar::evaluateValue(double x, string variable) {
    return new Scalar(multiplier);
}

BaseEntity * Scalar::evaluateDerivative(string variable) {
    return zero();
}

bool Scalar::addElement(BaseEntity *element) {
    Logger::log("Can't add child entity to scalar value");
    return false;
}

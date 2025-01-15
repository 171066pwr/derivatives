#include "Scalar.h"

#include "../utils/Logger.h"

Scalar::Scalar(double multiplier) : BaseEntity(multiplier) {}

BaseEntity *Scalar::copy() {
    return new Scalar(multiplier);
}

bool Scalar::equals(const BaseEntity *entity) {
    const Scalar *e = dynamic_cast<const Scalar *>(entity);
    if(e == nullptr)
        return false;
    else
        return BaseEntity::equals(e);
}

std::string Scalar::toString() {
    return NumberUtils::toString(multiplier);
}

BaseEntity *Scalar::evaluateValue(double x) {
    return new Scalar(multiplier);
}

bool Scalar::addElement(BaseEntity *element) {
    Logger::log("Can't add child entity to scalar value");
    return false;
}

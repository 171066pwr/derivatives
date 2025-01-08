#include "ScalarEntity.h"

ScalarEntity::ScalarEntity(double value) : value(value) {}

std::string ScalarEntity::toString() {
    return StringUtils::toString(value);
}

BaseEntity *ScalarEntity::evaluateValue(double x) {
    return new ScalarEntity(value);
}

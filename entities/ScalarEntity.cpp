#include "ScalarEntity.h"

std::string ScalarEntity::toString() {
    return StringUtils::toString(value);
}

ScalarEntity::ScalarEntity(double value) : value(value) {}

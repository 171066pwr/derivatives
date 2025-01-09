#include "ScalarEntity.h"

#include "../utils/Logger.h"

ScalarEntity::ScalarEntity(double multiplier) : BaseEntity(multiplier) {}

std::string ScalarEntity::toString() {
    return StringUtils::toString(multiplier);
}

BaseEntity *ScalarEntity::evaluateValue(double x) {
    return new ScalarEntity(multiplier);
}

bool ScalarEntity::addElement(BaseEntity *element) {
    Logger::log("Can't add child entity to scalar value");
    return false;
}

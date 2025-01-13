#include "ScalarEntity.h"

#include "../utils/Logger.h"

ScalarEntity::ScalarEntity(double multiplier) : BaseEntity(multiplier) {}

BaseEntity *ScalarEntity::copy() {
    return new ScalarEntity(multiplier);
}

bool ScalarEntity::equals(const BaseEntity *entity) {
    const ScalarEntity* e = dynamic_cast<const ScalarEntity*>(entity);
    if(e == nullptr)
        return false;
    else
        return BaseEntity::equals(e);
}

std::string ScalarEntity::toString() {
    return NumberUtils::toString(multiplier);
}

BaseEntity *ScalarEntity::evaluateValue(double x) {
    return new ScalarEntity(multiplier);
}

bool ScalarEntity::addElement(BaseEntity *element) {
    Logger::log("Can't add child entity to scalar value");
    return false;
}

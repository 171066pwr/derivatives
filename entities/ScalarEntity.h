#ifndef DERIVATIVES_SCALARENTITY_H
#define DERIVATIVES_SCALARENTITY_H

#include "BaseEntity.h"
#include "../utils/StringUtils.h"
#include <iostream>
#include <sstream>

class ScalarEntity: public BaseEntity {
public:
    ScalarEntity(double multiplier);
    BaseEntity* copy() override;
    bool equals(const BaseEntity* entity) override;

    bool operator==(const BaseEntity& entity) override {
        const ScalarEntity* variable = dynamic_cast<const ScalarEntity*>(&entity);
        if(variable == nullptr)
            return false;
        return BaseEntity::operator==(*variable);
    }

    bool operator==(const BaseEntity* entity) override {
        return equals(entity);
    }

    std::string toString() override;
    BaseEntity* evaluateValue(double x) override;
    bool addElement(BaseEntity *element) override;

    void add(ScalarEntity scalar) {
        this->multiplier += scalar.multiplier;
    }

    void multiply(ScalarEntity scalar) {
        this->multiplier *= scalar.multiplier;
    }
};

#endif //DERIVATIVES_SCALARENTITY_H

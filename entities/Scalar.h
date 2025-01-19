#ifndef DERIVATIVES_SCALARENTITY_H
#define DERIVATIVES_SCALARENTITY_H

#include "BaseEntity.h"
#include "../utils/NumberUtils.h"
#include <iostream>
#include <sstream>

class Scalar: public BaseEntity {
public:
    Scalar(double multiplier = 1.0);
    BaseEntity *copy() override;
    bool equals(const BaseEntity *entity) override;
    bool contentsEquals(const BaseEntity *entity) override;

    bool operator==(const BaseEntity& entity) override {
        return equals(&entity);
    }

    std::string toString() override;
    BaseEntity *evaluateValue(double x) override;
    bool addElement(BaseEntity *element) override;
};

#endif //DERIVATIVES_SCALARENTITY_H

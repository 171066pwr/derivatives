#ifndef DERIVATIVES_SCALARENTITY_H
#define DERIVATIVES_SCALARENTITY_H

#include "BaseEntity.h"
#include "../utils/StringUtils.h"
#include <iostream>
#include <sstream>

class ScalarEntity: public BaseEntity {
private:
    double value;

public:
    ScalarEntity(double value);
    std::string toString() override ;
    BaseEntity* evaluateValue(double x) override;
};

#endif //DERIVATIVES_SCALARENTITY_H

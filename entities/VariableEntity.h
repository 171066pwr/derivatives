#ifndef DERIVATIVES_VARIABLEENTITY_H
#define DERIVATIVES_VARIABLEENTITY_H

#include "BaseEntity.h"
#include "../utils/StringUtils.h"

class VariableEntity: public BaseEntity {
private:
    char symbol = 'x';
    double multiplier;
    double power = 1;

public:
    VariableEntity(double multiplier);

    VariableEntity(double multiplier, double power);

    char getSymbol() {
        return symbol;
    }

    std::string toString() override;
};

#endif //DERIVATIVES_VARIABLEENTITY_H

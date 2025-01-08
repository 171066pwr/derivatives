#ifndef DERIVATIVES_VARIABLEENTITY_H
#define DERIVATIVES_VARIABLEENTITY_H

#include "BaseEntity.h"
#include "../utils/StringUtils.h"
#include "ScalarEntity.h"

class VariableEntity: public BaseEntity {
private:
    string symbol = "x";
    double multiplier;
    double power = 1;

public:
    VariableEntity(double multiplier);
    VariableEntity(double multiplier, double power);
    VariableEntity(string symbol, double multiplier, double power);
    std::string toString() override;
    BaseEntity* evaluateFunction() override ;
    BaseEntity* evaluateValue(double x) override;
    ScalarEntity* evaluate(double x);

    string getSymbol() {
        return symbol;
    }
};

#endif //DERIVATIVES_VARIABLEENTITY_H

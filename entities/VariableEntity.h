#ifndef DERIVATIVES_VARIABLEENTITY_H
#define DERIVATIVES_VARIABLEENTITY_H

#include "BaseEntity.h"
#include "../utils/StringUtils.h"
#include "ScalarEntity.h"

class VariableEntity: public BaseEntity {
private:
    string symbol = "x";
    double power;
    ScalarEntity* getScalarEdgeCases();

public:
    VariableEntity(double multiplier = 1, double power = 1);
    VariableEntity(string symbol, double multiplier = 1, double power = 1);
    std::string toString() override;
    BaseEntity* evaluateFunction() override ;
    BaseEntity* evaluateValue(double x) override;
    ScalarEntity* evaluate(double x);
    void add(VariableEntity entity) {
        if (this->symbol == entity.symbol && this->power == entity.power)
            this->multiplier += entity.multiplier;
    }

    string getSymbol() {
        return symbol;
    }

    double getMultiplier() {
        return multiplier;
    }

    double getPower() {
        return power;
    }
};

#endif //DERIVATIVES_VARIABLEENTITY_H

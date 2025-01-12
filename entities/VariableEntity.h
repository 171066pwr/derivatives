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
    bool equals(const BaseEntity* entity) override;

public:
    VariableEntity(double multiplier = 1, double power = 1);
    VariableEntity(string symbol, double multiplier = 1, double power = 1);
    BaseEntity* copy() override;

    bool operator==(const BaseEntity& entity) override {
        const VariableEntity* variable = dynamic_cast<const VariableEntity*>(&entity);
        if(variable == nullptr)
            return false;
        else {
            bool result = BaseEntity::operator==(*variable);
            result = result && symbol == variable->symbol;
            result = result && power == variable->power;
            return result;
        }
    }

    bool operator==(const BaseEntity* entity) override {
        return equals(entity);
    }

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

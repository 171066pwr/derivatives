#ifndef DERIVATIVES_VARIABLEENTITY_H
#define DERIVATIVES_VARIABLEENTITY_H

#include <map>
#include "BaseEntity.h"
#include "../utils/NumberUtils.h"
#include "ScalarEntity.h"

class VariableEntity: public BaseEntity {
private:
    static string SUBSTITUTE_SYMBOL;
    static map<string, double> constants;
    string symbol = SUBSTITUTE_SYMBOL;

    bool equals(const BaseEntity* entity) override;
    ScalarEntity* evaluate(double x);
public:
    static void changeSubstituteSymbol(string symbol);
    VariableEntity(double multiplier = 1);
    VariableEntity(string symbol, double multiplier = 1);
    BaseEntity* copy() override;

    bool operator==(const BaseEntity& entity) override {
        const VariableEntity* variable = dynamic_cast<const VariableEntity*>(&entity);
        if(variable == nullptr)
            return false;
        else {
            bool result = BaseEntity::operator==(*variable);
            result = result && symbol == variable->symbol;
            return result;
        }
    }

    bool operator==(const BaseEntity* entity) override {
        return equals(entity);
    }

    std::string toString() override;
    BaseEntity* evaluateFunction() override ;
    BaseEntity* evaluateValue(double x) override;
    bool updateAndGetIsFunction() override;

    void add(VariableEntity entity) {
        if (this->symbol == entity.symbol)
            this->multiplier += entity.multiplier;
    }

    string getSymbol() {
        return symbol;
    }
};

#endif //DERIVATIVES_VARIABLEENTITY_H

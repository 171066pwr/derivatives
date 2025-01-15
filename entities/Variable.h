#ifndef DERIVATIVES_VARIABLEENTITY_H
#define DERIVATIVES_VARIABLEENTITY_H

#include <map>
#include "BaseEntity.h"
#include "../utils/NumberUtils.h"
#include "Scalar.h"

class Variable: public BaseEntity {
private:
    static string SUBSTITUTE_SYMBOL;
    static map<string, double> constants;
    string symbol = SUBSTITUTE_SYMBOL;

    bool equals(const BaseEntity *entity) override;
    Scalar *evaluate(double x);
public:
    static void changeSubstituteSymbol(string symbol);
    Variable(double multiplier = 1.0);
    Variable(string symbol, double multiplier = 1.0);
    BaseEntity *copy() override;

    bool operator==(const BaseEntity& entity) override {
        equals(&entity);
    }

    std::string toString() override;
    BaseEntity *evaluateFunction() override ;
    BaseEntity *evaluateValue(double x) override;
    bool updateAndGetIsFunction() override;

    void add(Variable entity) {
        if (this->symbol == entity.symbol)
            this->multiplier += entity.multiplier;
    }

    string getSymbol() {
        return symbol;
    }
};

#endif //DERIVATIVES_VARIABLEENTITY_H

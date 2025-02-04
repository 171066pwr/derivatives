#ifndef DERIVATIVES_VARIABLEENTITY_H
#define DERIVATIVES_VARIABLEENTITY_H

#include <map>
#include "BaseEntity.h"
#include "../utils/NumberUtils.h"
#include "Scalar.h"

class Variable: public BaseEntity {
    static map<string, double> constants;
    string symbol = "x";

    Scalar *evaluate(double x);
public:
    static vector<string> getConstants();
    Variable(double multiplier = 1.0);
    Variable(string symbol, double multiplier = 1.0);
    BaseEntity *copy() override;
    bool equals(const BaseEntity *entity) override;
    bool contentsEquals(const BaseEntity *entity) override;

    bool operator==(const BaseEntity& entity) override {
        return equals(&entity);
    }

    std::string toString() override;
    BaseEntity *evaluateValue(double x, string variable) override;
    BaseEntity *evaluateDerivative(string variable) override;
    bool isFunction(string symbol) override;

    string getSymbol() {
        return symbol;
    }
};

#endif //DERIVATIVES_VARIABLEENTITY_H

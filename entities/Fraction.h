#ifndef FRACTION_H
#define FRACTION_H

#include "BaseEntity.h"

class Fraction: public BaseEntity {
    double mergeMultipliers();
public:
    Fraction(double multiplier = 1.0): BaseEntity(multiplier) {}
    Fraction(double multiplier, initializer_list<BaseEntity *> list): BaseEntity(multiplier, list) {}
    BaseEntity *copy();
    bool equals(const BaseEntity *entity) override;
    bool contentsEquals(const BaseEntity *entity) override;

    bool operator==(const BaseEntity& entity) override {
        return equals(&entity);
    }

    std::string toString() override;
    BaseEntity *evaluateFunction() override ;
    BaseEntity *evaluateValue(double x) override;
    bool updateAndGetIsFunction() override;
};

#endif //FRACTION_H

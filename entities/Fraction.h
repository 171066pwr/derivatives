#ifndef FRACTION_H
#define FRACTION_H

#include "BaseEntity.h"
#include "Scalar.h"
#include "Multiplication.h"

class Fraction: public BaseEntity {
    void replaceNumerator(BaseEntity *numerator);
    void replaceDenominator(BaseEntity *denominator);
    BaseEntity *handleEdgeCases(BaseEntity *numerator, BaseEntity *denominator);
    BaseEntity *handleEdgeCases();
    BaseEntity *splitSum();
    BaseEntity *mergeOther();
    void mergeMultiplications(Multiplication *dividend, Multiplication *divisor);
    BaseEntity *swapPower();
    BaseEntity *numeratorTimesMultiplier();
    double mergeMultipliers();
public:
    Fraction(double denominator, double numerator = 1.0, double multiplier = 1.0):
            BaseEntity(multiplier, {new Scalar(numerator), new Scalar(denominator)}) {}
    Fraction(BaseEntity *denominator, BaseEntity *numerator, double multiplier = 1.0):
            BaseEntity(multiplier, {numerator, denominator}) {}
    BaseEntity *copy() override;
    bool equals(const BaseEntity *entity) override;
    bool contentsEquals(const BaseEntity *entity) override;

    bool operator==(const BaseEntity& entity) override {
        return equals(&entity);
    }

    std::string toString() override;
    bool addElement(BaseEntity * element) override;
    BaseEntity *evaluateFunction() override ;
    BaseEntity *evaluateValue(double x) override;
    bool updateAndGetIsFunction() override;

    BaseEntity *getNumerator();
    BaseEntity *getDenominator();
};

#endif //FRACTION_H

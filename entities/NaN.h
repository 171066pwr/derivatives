#ifndef TESTS_NAN_H
#define TESTS_NAN_H

#include "BaseEntity.h"
#include "cmath"

class NaN: public BaseEntity {
    static const string NOT_A_NUMBER;
public:
    NaN(): BaseEntity(numeric_limits<double>::quiet_NaN()) {};
    BaseEntity *copy() override;
    bool equals(const BaseEntity *entity) override { return false;};
    bool equalsExceptMultiplier(const BaseEntity *entity) { return false;};
    bool contentsEquals(const BaseEntity *entity) { return false;};

    bool operator==(const BaseEntity& entity) override {
        return false;
    }

    std::string toString() override;
    bool addElement(BaseEntity * element) override;
    BaseEntity *evaluateFunction() override ;
    BaseEntity *evaluateValue(double x) override;
    bool updateAndGetIsFunction() override;
};

#endif //TESTS_NAN_H

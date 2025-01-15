#ifndef TESTS_POWER_H
#define TESTS_POWER_H

#include "BaseEntity.h"

class Power: public BaseEntity {
private:
    double power;

public:
    Power(double multiplier = 1.0, double power = 1.0);
    Power(double multiplier, double power, initializer_list<BaseEntity *> list): BaseEntity(multiplier, list), power(power) {};
    BaseEntity *copy();
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
};

#endif //TESTS_POWER_H

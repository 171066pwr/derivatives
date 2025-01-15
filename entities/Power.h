#ifndef TESTS_POWER_H
#define TESTS_POWER_H

#include "BaseEntity.h"
#include "Scalar.h"

class Power: public BaseEntity {
private:
    BaseEntity* power;

public:
    Power(double power, double multiplier = 1.0): BaseEntity(multiplier) {
        this->power = new Scalar(power);
    };
    Power(BaseEntity *power, double multiplier = 1.0): BaseEntity(multiplier) {
        this->power = power;
    };
    Power(double power, BaseEntity * base, double multiplier = 1.0): BaseEntity(multiplier, {base}) {
        this->power = new Scalar(power);
    };
    Power(BaseEntity *power, BaseEntity * base, double multiplier = 1.0): BaseEntity(multiplier, {base}), power(power) {};
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

    bool addPower(Power power);
    bool multiplyPower(Power power);
};

#endif //TESTS_POWER_H

#ifndef TESTS_POWER_H
#define TESTS_POWER_H

#include "BaseEntity.h"
#include "Scalar.h"

class Power: public BaseEntity {
    void replaceBase(BaseEntity *base);
    void replacePower(BaseEntity *power);
    void mergePower();
    BaseEntity *handleEdgeCases();
public:
    Power(double power, double base, double multiplier = 1.0): BaseEntity(multiplier, {new Scalar(base), new Scalar(power)}) {}
    Power(double power, BaseEntity * base, double multiplier = 1.0): BaseEntity(multiplier, {base, new Scalar(power)}) {}
    Power(BaseEntity *power, BaseEntity * base, double multiplier = 1.0): BaseEntity(multiplier, {base, power}) {}
    BaseEntity *copy();
    bool equals(const BaseEntity *entity) override;
    bool equalsExceptMultiplier(const BaseEntity *entity) override;
    bool contentsEquals(const BaseEntity *entity) override;

    bool operator==(const BaseEntity& entity) override {
        return equals(&entity);
    }

    std::string toString() override;
    bool addElement(BaseEntity * element) override;
    BaseEntity *evaluateFunction() override ;
    BaseEntity *evaluateValue(double x) override;
    bool updateAndGetIsFunction() override;

    BaseEntity *splitMultiplications();
    BaseEntity *getBase();
    BaseEntity *getPower();
    bool mergePower(Power *pwr);
    void addToPower(double increase);
};

#endif //TESTS_POWER_H

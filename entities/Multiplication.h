#ifndef DERIVATIVES_MULTIPLICATIONENTITY_H
#define DERIVATIVES_MULTIPLICATIONENTITY_H

#include "BaseEntity.h"
#include "Sum.h"

class Multiplication: public BaseEntity {
    void mergeMultiplications();
    double mergeMultipliers();
    void mergeVariables();
    void mergePowers();
    BaseEntity *mergeSums();
    BaseEntity *sumProduct(Sum *sum);
    Multiplication *copyAllWithoutSelected(BaseEntity *selected);
public:
    Multiplication(double multiplier = 1.0): BaseEntity(multiplier) {}
    Multiplication(double multiplier, initializer_list<BaseEntity *> list): BaseEntity(multiplier, list) {}
    BaseEntity *copy() override;
    bool equals(const BaseEntity *entity) override;
    bool contentsEquals(const BaseEntity *entity) override;

    bool operator==(const BaseEntity& entity) override {
        return equals(&entity);
    }

    std::string toString() override;
    BaseEntity *evaluateFunction() override;
    BaseEntity *evaluateValue(double x) override;
    bool updateAndGetIsFunction() override;
};

#endif //DERIVATIVES_MULTIPLICATIONENTITY_H
